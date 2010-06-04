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
#include <dshow.h>
#include <dmo.h>
#include <dmodshow.h>
#include <ks.h>
#pragma warn -8098
#include <ksmedia.h>
#pragma warn .8098
#include <ComObj.hpp>

#pragma link "quartz.lib"

const GUID KSDATAFORMAT_SUBTYPE_MPEG1Payload = {STATIC_KSDATAFORMAT_SUBTYPE_MPEG1Payload};

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
                   IBaseFilter *pInput, bool bDirect = false)
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

    if (bDirect)
        return pGraphBuilder->ConnectDirect(inputPin, outputPin, 0);
    else
        return pGraphBuilder->Connect(outputPin, inputPin);
}

inline void
__fastcall RaiseError(HRESULT hr)
{
    TCHAR text[128];
    AMGetErrorText(hr, text, 128);
    throw Exception(text);
}

/**
 * Raises an exception if an operation result indicates a failure.
 */
inline void
__fastcall CheckSucceeded(HRESULT hr)
{
    if (FAILED(hr))
        RaiseError(hr);
}

__fastcall TMainForm::TMainForm(TComponent* Owner)
: TForm(Owner)
{
}

UnicodeString
__fastcall TMainForm::GetDefaultOutputFileName() const
{
    return InputFileName + ".mp2"; // @todo
}

void
__fastcall TMainForm::OpenFile(const UnicodeString FileName)
{
    DelphiInterface<IGraphBuilder> graphBuilder1;
    CheckSucceeded(CoCreateInstance(CLSID_FilterGraph, 0, CLSCTX_INPROC_SERVER,
                                    &graphBuilder1));

    DelphiInterface<IBaseFilter> source1;
    CheckSucceeded(graphBuilder1->AddSourceFilter(FileName.t_str(), 0, &source1));

    DelphiInterface<IBaseFilter> encoder1;
    CheckSucceeded(CoCreateInstance(CLSID_DMOWrapperFilter, 0,
                                    CLSCTX_INPROC_SERVER, &encoder1));
    CheckSucceeded(graphBuilder1->AddFilter(encoder1, 0));

    DelphiInterface<IDMOWrapperFilter> dmoWrapper1;
    CheckSucceeded(encoder1->QueryInterface(&dmoWrapper1));
    CheckSucceeded(dmoWrapper1->Init(CLSID_Mp2Encoder, DMOCATEGORY_AUDIO_ENCODER));

    // Now we can connect the two.
    CheckSucceeded(Connect(graphBuilder1, source1, encoder1));

    DelphiInterface<IPin> pin1;
    CheckSucceeded(FindUnconnectedPin(encoder1, PINDIR_OUTPUT, &pin1));

    DelphiInterface<IAMStreamConfig> streamConfig1;
    CheckSucceeded(pin1->QueryInterface(&streamConfig1));

    int n, size;
    CheckSucceeded(streamConfig1->GetNumberOfCapabilities(&n, &size));
    if (n > 0 && size >= (int) sizeof (AUDIO_STREAM_CONFIG_CAPS))
    {
        for (int i = 0; i != n; ++i)
        {
            AM_MEDIA_TYPE *pmt;
            AUDIO_STREAM_CONFIG_CAPS caps;
            HRESULT hr = streamConfig1->GetStreamCaps(i, &pmt, reinterpret_cast<BYTE *>(&caps));
            if (SUCCEEDED(hr) && pmt->majortype == MEDIATYPE_Stream)
            {
                assert(pmt != 0);
                hr = streamConfig1->SetFormat(pmt);
                CoTaskMemFree(pmt->pbFormat);
                CoTaskMemFree(pmt);
                if (SUCCEEDED(hr))
                    break;
            }
        }
    }

    GraphBuilder1 = graphBuilder1;
    // QueryInterface does not Release.
    MediaControl1 = 0;
    MediaEvent1 = 0;
    CheckSucceeded(GraphBuilder1->QueryInterface(&MediaControl1));
    CheckSucceeded(GraphBuilder1->QueryInterface(&MediaEvent1));
    Encoder = encoder1;
    InputFileName = FileName;

    Close1->Enabled = true;
    Encode1->Enabled = true;
    EncodeAs1->Enabled = true;
}

void
__fastcall TMainForm::CloseFile()
{
    GraphBuilder1 = 0;
    MediaControl1 = 0;
    MediaEvent1 = 0;
    Encoder = 0;
    InputFileName = L"";

    Close1->Enabled = false;
    Encode1->Enabled = false;
    EncodeAs1->Enabled = false;
}

void
__fastcall TMainForm::EncodeAs(const UnicodeString FileName)
{
    HRESULT hr;
    DelphiInterface<IBaseFilter> writer1;
    hr = CoCreateInstance(CLSID_FileWriter, 0, CLSCTX_INPROC_SERVER, &writer1);
    if (SUCCEEDED(hr))
    {
        DelphiInterface<IFileSinkFilter2> fileSink1;
        hr = writer1->QueryInterface(&fileSink1);
        if (SUCCEEDED(hr))
            hr = fileSink1->SetFileName(FileName.t_str(), 0);
        if (SUCCEEDED(hr))
            hr = GraphBuilder1->AddFilter(writer1, 0);
    }
    if (FAILED(hr))
        RaiseError(hr);

    hr = Connect(GraphBuilder1, Encoder, writer1, true);
    if (FAILED(hr))
        RaiseError(hr);

    DelphiInterface<IMediaFilter> mediaFilter1;
    CheckSucceeded(GraphBuilder1->QueryInterface(&mediaFilter1));
    CheckSucceeded(mediaFilter1->SetSyncSource(0));

    CheckSucceeded(MediaControl1->Run());
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
    OpenDialog1->FileName = L"";
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
    EncodeAs(GetDefaultOutputFileName());
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::EncodeAs1Click(TObject *Sender)
{
    SaveDialog1->FileName = GetDefaultOutputFileName();
    if (SaveDialog1->Execute(Handle))
        EncodeAs(SaveDialog1->FileName);
}
//---------------------------------------------------------------------------

void
__fastcall TMainForm::About1Click(TObject *Sender)
{
    AboutBox->ShowModal();
}
//---------------------------------------------------------------------------

void
__fastcall TMainForm::Timer1Timer(TObject *Sender)
{
    if (MediaEvent1 != 0)
    {
        long code;
        LONG_PTR param1, param2;
        HRESULT hr = MediaEvent1->GetEvent(&code, &param1, &param2, 0);
        if (hr == S_OK)
        {
            switch (code)
            {
            case EC_COMPLETE:
                MediaControl1->Stop();
                break;
            case EC_ERRORABORT:
                ShowMessage(L"Operation aborted because of error");
                MediaControl1->Stop();
                break;
            }
        }
    }
}
//---------------------------------------------------------------------------

