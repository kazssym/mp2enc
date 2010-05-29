/*
 * MP2 Encoder front-end.
 * Copyright (C) 2010 Kaz Sasa.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <vcl.h>
#pragma hdrstop

#include <initguid.h>

#include "Main.h"
#include "About.h"
#include "resource.h"
#include <mp2guid.h>
#include <dmo.h>
#include <dmodshow.h>
#include <ComObj.hpp>

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TMainForm *MainForm;
//---------------------------------------------------------------------------

/**
 * Creates a COM object instance.  This version takes a typed pointer.
 */
template<class Interface>
inline HRESULT
STDAPICALLTYPE CoCreateInstance(REFCLSID rclsid, IUnknown *pUnkOuter,
                                DWORD dwClsContext, Interface **pp)
{
    return CoCreateInstance(rclsid, pUnkOuter, dwClsContext, __uuidof (Interface),
                            reinterpret_cast<void **>(pp));
}

inline HRESULT
__fastcall FindUnconnectedPin(IBaseFilter *filter, PIN_DIRECTION dir,
                              IPin **ppPin)
{
    HRESULT hr;
    DelphiInterface<IEnumPins> pins1;
    hr = filter->EnumPins(&pins1);
    if (FAILED(hr))
        return hr;

    do
    {
        DelphiInterface<IPin> pin1;
        hr = pins1->Next(1, &pin1, NULL);
        if (SUCCEEDED(hr))
        {
            PIN_DIRECTION dir1;
            hr = pin1->QueryDirection(&dir1);
            if (SUCCEEDED(hr) && dir1 == dir)
            {
                DelphiInterface<IPin> pin2;
                hr = pin1->ConnectedTo(&pin2);
                if (hr == VFW_E_NOT_CONNECTED)
                {
                    pin1->AddRef();
                    *ppPin = pin1;
                    return S_OK;
                }
            }
        }
    }
    while (SUCCEEDED(hr));
    return hr;
}

inline HRESULT
__fastcall Connect(IGraphBuilder *pGraphBuilder, IBaseFilter *pOutput,
                   IBaseFilter *pInput)
{
    HRESULT hr;
    DelphiInterface<IPin> outputPin;
    hr = FindUnconnectedPin(pOutput, PINDIR_OUTPUT, &outputPin);
    if (FAILED(hr))
        return hr;

    DelphiInterface<IPin> inputPin;
    hr = FindUnconnectedPin(pInput, PINDIR_INPUT, &inputPin);
    if (FAILED(hr))
        return hr;

    return pGraphBuilder->Connect(outputPin, inputPin);
}

inline UnicodeString
__fastcall ErrorText(HRESULT hr)
{
    TCHAR text[128];
    AMGetErrorText(hr, text, 128);
    return UnicodeString(text);
}

__fastcall TMainForm::TMainForm(TComponent* Owner)
: TForm(Owner)
{
}

void
__fastcall TMainForm::OpenFile(const UnicodeString Name)
{
    HRESULT hr;
    DelphiInterface<IGraphBuilder> graphBuilder1;
    hr = CoCreateInstance(CLSID_FilterGraph, 0, CLSCTX_INPROC_SERVER, &graphBuilder1);
    if (FAILED(hr))
    {
        ShowMessage(ErrorText(hr));
        return;
    }

    DelphiInterface<IBaseFilter> source;
    hr = graphBuilder1->AddSourceFilter(Name.t_str(), 0, &source);
    if (FAILED(hr))
    {
        ShowMessage(ErrorText(hr));
        return;
    }

    DelphiInterface<IBaseFilter> encoder;
    hr = CoCreateInstance(CLSID_DMOWrapperFilter, 0, CLSCTX_INPROC_SERVER, &encoder);
    if (SUCCEEDED(hr))
    {
        DelphiInterface<IDMOWrapperFilter> dmoWrapper;
        hr = encoder->QueryInterface(&dmoWrapper);
        if (SUCCEEDED(hr))
            hr = dmoWrapper->Init(CLSID_Mp2Encoder, DMOCATEGORY_AUDIO_ENCODER);
    }
    if (SUCCEEDED(hr))
        hr = graphBuilder1->AddFilter(encoder, 0);
    if (FAILED(hr))
    {
        ShowMessage(ErrorText(hr));
        return;
    }

    hr = Connect(graphBuilder1, source, encoder);
    if (FAILED(hr))
    {
        ShowMessage(ErrorText(hr));
        return;
    }

    GraphBuilder1 = graphBuilder1;

    Close1->Enabled = true;
    Encode1->Enabled = true;
    EncodeAs1->Enabled = true;
}

void
__fastcall TMainForm::CloseFile(void)
{
    GraphBuilder1 = 0;

    Close1->Enabled = false;
    Encode1->Enabled = false;
    EncodeAs1->Enabled = false;
}
//---------------------------------------------------------------------------

void
__fastcall TMainForm::FormClose(TObject *Sender, TCloseAction &Action)
{
    CloseFile();
}
//---------------------------------------------------------------------------

void
__fastcall TMainForm::Exit1Click(TObject *Sender)
{
    Close();
}
//---------------------------------------------------------------------------
void
__fastcall TMainForm::Open1Click(TObject *Sender)
{
    OpenDialog1->Filter = UnicodeString::LoadStr(IDS_OPEN_DIALOG_FILTER);
    if (OpenDialog1->Execute(Handle))
        OpenFile(OpenDialog1->FileName);
}
//---------------------------------------------------------------------------

void
__fastcall TMainForm::Close1Click(TObject *Sender)
{
    CloseFile();
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::Encode1Click(TObject *Sender)
{
    // @todo
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::EncodeAs1Click(TObject *Sender)
{
    SaveDialog1->Execute(Handle);
}
//---------------------------------------------------------------------------

void
__fastcall TMainForm::About1Click(TObject *Sender)
{
    AboutBox->ShowModal();
}
//---------------------------------------------------------------------------
