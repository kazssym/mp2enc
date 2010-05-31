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

inline UnicodeString
__fastcall ErrorText(HRESULT hr)
{
    TCHAR text[128];
    AMGetErrorText(hr, text, 128);
    return UnicodeString(text);
}

inline void
__fastcall RaiseError(HRESULT hr)
{
    TCHAR text[128];
    AMGetErrorText(hr, text, 128);
    throw Exception(text);
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
        RaiseError(hr);

    DelphiInterface<IBaseFilter> source;
    hr = graphBuilder1->AddSourceFilter(Name.t_str(), 0, &source);
    if (FAILED(hr))
        RaiseError(hr);

#if 1
    DelphiInterface<IBaseFilter> writer;
    hr = CoCreateInstance(CLSID_FileWriter, 0, CLSCTX_INPROC_SERVER, &writer);
    if (SUCCEEDED(hr))
        hr = graphBuilder1->AddFilter(writer, 0);
    if (FAILED(hr))
        RaiseError(hr);
#endif

    DelphiInterface<IBaseFilter> encoder;
    hr = CoCreateInstance(CLSID_DMOWrapperFilter, 0, CLSCTX_INPROC_SERVER, &encoder);
    if (SUCCEEDED(hr))
    {
        DelphiInterface<IDMOWrapperFilter> dmoWrapper;
        hr = encoder->QueryInterface(&dmoWrapper);
        if (SUCCEEDED(hr))
            hr = dmoWrapper->Init(CLSID_Mp2Encoder, DMOCATEGORY_AUDIO_ENCODER);
        if (SUCCEEDED(hr))
            hr = graphBuilder1->AddFilter(encoder, 0);
    }
    if (FAILED(hr))
        RaiseError(hr);

    hr = Connect(graphBuilder1, source, encoder);
    if (FAILED(hr))
        RaiseError(hr);

    DelphiInterface<IPin> pin1;
    hr = FindUnconnectedPin(encoder, PINDIR_OUTPUT, &pin1);
    if (SUCCEEDED(hr))
    {
        DelphiInterface<IAMStreamConfig> config;
        hr = pin1->QueryInterface(&config);
        if (SUCCEEDED(hr))
        {
            int n1, n2;
            hr = config->GetNumberOfCapabilities(&n1, &n2);
            AM_MEDIA_TYPE *pmt;
            AUDIO_STREAM_CONFIG_CAPS caps;
            hr = config->GetStreamCaps(0, &pmt, reinterpret_cast<BYTE *>(&caps));
#if 0
            hr = config->GetFormat(&pmt);
#endif
            WAVEFORMATEXTENSIBLE *format = reinterpret_cast<WAVEFORMATEXTENSIBLE *>(pmt->pbFormat);
            CoTaskMemFree(pmt->pbFormat);
            CoTaskMemFree(pmt);
#if 0
            AM_MEDIA_TYPE mt = {};
            mt.majortype = MEDIATYPE_Stream;
            mt.subtype = MEDIASUBTYPE_MPEG1Payload;
            mt.bFixedSizeSamples = TRUE;
            mt.bTemporalCompression = FALSE;
            mt.formattype = FORMAT_WaveFormatEx;
            mt.cbFormat = sizeof (WAVEFORMATEXTENSIBLE);
            mt.pbFormat = static_cast<BYTE *>(CoTaskMemAlloc(sizeof (WAVEFORMATEXTENSIBLE)));
            WAVEFORMATEXTENSIBLE *format = reinterpret_cast<WAVEFORMATEXTENSIBLE *>(mt.pbFormat);
            format->Format.wFormatTag = WAVE_FORMAT_EXTENSIBLE;
            format->Format.nChannels = 2;
            format->Format.nSamplesPerSec = 48000;
            format->Format.nAvgBytesPerSec = 384000 / 8;
            format->Format.nBlockAlign = 0;
            format->Format.wBitsPerSample = 0;
            format->Format.cbSize = 22;
            format->Samples.wSamplesPerBlock = 1152;
            format->dwChannelMask = 0;
            format->SubFormat = KSDATAFORMAT_SUBTYPE_MPEG1Payload;

            hr = config->SetFormat(&mt);
#endif
        }
    }
    if (FAILED(hr))
        RaiseError(hr);

#if 1
    hr = Connect(graphBuilder1, encoder, writer, true);
    if (FAILED(hr))
        RaiseError(hr);
#endif

    GraphBuilder1 = graphBuilder1;
    EncoderFilter = encoder;
    FileName = Name;

    Close1->Enabled = true;
    Encode1->Enabled = true;
    EncodeAs1->Enabled = true;
}

void
__fastcall TMainForm::CloseFile()
{
    GraphBuilder1 = 0;
    EncoderFilter = 0;
    FileName = L"";

    Close1->Enabled = false;
    Encode1->Enabled = false;
    EncodeAs1->Enabled = false;
}

void
__fastcall TMainForm::EncodeAs(const UnicodeString OutputName)
{
    // @todo
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
    // @todo
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::EncodeAs1Click(TObject *Sender)
{
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
