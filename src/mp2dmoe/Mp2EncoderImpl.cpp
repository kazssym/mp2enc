/*
 * Mp2EncoderImpl - C++ class for Mp2Encoder (implementation)
 * Copyright (C) 2010-2013  Kaz Sasa
 *
 * This program is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the Free
 * Software Foundation, either version 3 of the License, or (at your option)
 * any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <vcl.h>
#pragma hdrstop

#include <initguid.h>
#include "Mp2EncoderImpl.h"

#include "Mp2Encoder.h"
#include <twolame.h>
#include <ks.h>
#include <ksmedia.h>
#include <mmreg.h>
#pragma option push -w-mcc
#include <uuids.h>
#pragma option pop
#include <System.Win.ComServ.hpp>

#pragma link "System.Win.ComServ"

// TMp2EncoderImpl implementation

#define PCM(s, c, b, v) {\
    {WAVE_FORMAT_PCM, (c), (s), (s) * (c) * (b), (c) * (b), 8 * (b), 0}\
}

#define MPEG1(s, c, r) {\
    {WAVE_FORMAT_EXTENSIBLE, (c), (s), (r) / 8, 1, 0, 22},\
    TWOLAME_SAMPLES_PER_FRAME, 0, {STATIC_KSDATAFORMAT_SUBTYPE_MPEG1Payload}\
}

static const WAVEFORMATEXTENSIBLE InputFormat[] = {
    PCM(48000, 2, 2, 16),
    PCM(44100, 2, 2, 16),
    PCM(32000, 2, 2, 16),
    PCM(48000, 1, 2, 16),
    PCM(44100, 1, 2, 16),
    PCM(32000, 1, 2, 16),
};

static const WAVEFORMATEXTENSIBLE OutputFormat[] = {
    MPEG1(48000, 2, 384000),
    MPEG1(44100, 2, 384000),
    MPEG1(32000, 2, 384000),
    MPEG1(48000, 1, 192000),
    MPEG1(44100, 1, 192000),
    MPEG1(32000, 1, 192000),
};

__fastcall TMp2EncoderImpl::TMp2EncoderImpl() {
}

__fastcall TMp2EncoderImpl::TMp2EncoderImpl
        (const _di_IInterface Controller)
        : inherited(Controller) {
}

__fastcall TMp2EncoderImpl::TMp2EncoderImpl(TComObjectFactory *Factory,
        const _di_IInterface Controller)
        : inherited(Factory, Controller) {
}

STDMETHODIMP TMp2EncoderImpl::GetStreamCount(DWORD *pcInputStreams,
        DWORD *pcOutputStreams) {
    if (!pcInputStreams || !pcOutputStreams) {
        return E_POINTER;
    }

    *pcInputStreams = NumberOfInputStreams;
    *pcOutputStreams = NumberOfOutputStreams;
    return S_OK;
}

STDMETHODIMP TMp2EncoderImpl::GetInputStreamInfo(DWORD dwInputStreamIndex,
        DWORD *pdwFlags) {
    if (dwInputStreamIndex >= NumberOfInputStreams) {
        return DMO_E_INVALIDSTREAMINDEX;
    }
    if (!pdwFlags) {
        return E_POINTER;
    }

    *pdwFlags =
            DMO_INPUT_STREAMF_WHOLE_SAMPLES |
            DMO_INPUT_STREAMF_FIXED_SAMPLE_SIZE;
    return S_OK;
}

STDMETHODIMP TMp2EncoderImpl::GetOutputStreamInfo
        (DWORD dwOutputStreamIndex, DWORD *pdwFlags) {
    if (dwOutputStreamIndex >= NumberOfOutputStreams) {
        return DMO_E_INVALIDSTREAMINDEX;
    }
    if (!pdwFlags) {
        return E_POINTER;
    }

    *pdwFlags = DMO_OUTPUT_STREAMF_DISCARDABLE;
    return S_OK;
}

STDMETHODIMP TMp2EncoderImpl::GetInputType(DWORD dwInputStreamIndex,
        DWORD dwTypeIndex, DMO_MEDIA_TYPE *pmt) {
    if (dwInputStreamIndex >= NumberOfInputStreams) {
        return DMO_E_INVALIDSTREAMINDEX;
    }
    if (dwTypeIndex >= sizeof InputFormat / sizeof InputFormat[0]) {
        return DMO_E_NO_MORE_ITEMS;
    }

    HRESULT hr = S_OK;
    if (pmt) {
        hr = MoInitMediaType(pmt, sizeof InputFormat[dwTypeIndex]);
        if (SUCCEEDED(hr)) {
            pmt->majortype = MEDIATYPE_Audio;
            pmt->subtype = MEDIASUBTYPE_PCM;
            pmt->bFixedSizeSamples = TRUE;
            pmt->lSampleSize = InputFormat[dwTypeIndex].Format.nChannels * 2;
            pmt->formattype = FORMAT_WaveFormatEx;

            WAVEFORMATEXTENSIBLE *format =
                    reinterpret_cast<WAVEFORMATEXTENSIBLE*>(pmt->pbFormat);
            *format = InputFormat[dwTypeIndex];
        }
    }
    return hr;
}

STDMETHODIMP TMp2EncoderImpl::GetOutputType(DWORD dwOutputStreamIndex,
        DWORD dwTypeIndex, DMO_MEDIA_TYPE *pmt){
    if (dwOutputStreamIndex >= NumberOfOutputStreams) {
        return DMO_E_INVALIDSTREAMINDEX;
    }
    if (dwTypeIndex >= sizeof OutputFormat / sizeof OutputFormat[0]) {
        return DMO_E_NO_MORE_ITEMS;
    }

    HRESULT hr = S_OK;
    if (pmt) {
        hr = MoInitMediaType(pmt, sizeof OutputFormat[dwTypeIndex]);
        if (SUCCEEDED(hr)) {
            pmt->majortype = MEDIATYPE_Audio;
            pmt->subtype = MEDIASUBTYPE_MPEG1Payload;
            pmt->bFixedSizeSamples = TRUE;
            pmt->formattype = FORMAT_WaveFormatEx;

            WAVEFORMATEXTENSIBLE *format =
                    reinterpret_cast<WAVEFORMATEXTENSIBLE*>(pmt->pbFormat);
            *format = OutputFormat[dwTypeIndex];
        }
    }
    return hr;
}

STDMETHODIMP TMp2EncoderImpl::SetInputType(DWORD dwInputStreamIndex,
        const DMO_MEDIA_TYPE *pmt, DWORD dwFlags){
    if (dwInputStreamIndex >= NumberOfInputStreams) {
        return DMO_E_INVALIDSTREAMINDEX;
    }

    return E_NOTIMPL;
}

STDMETHODIMP TMp2EncoderImpl::SetOutputType(DWORD dwOutputStreamIndex,
        const DMO_MEDIA_TYPE *pmt, DWORD dwFlags){
    if (dwOutputStreamIndex >= NumberOfOutputStreams) {
        return DMO_E_INVALIDSTREAMINDEX;
    }

    return E_NOTIMPL;
}

STDMETHODIMP TMp2EncoderImpl::GetInputCurrentType(DWORD dwInputStreamIndex,
        DMO_MEDIA_TYPE *pmt){
    if (dwInputStreamIndex >= NumberOfInputStreams) {
        return DMO_E_INVALIDSTREAMINDEX;
    }

    return E_NOTIMPL;
}

STDMETHODIMP TMp2EncoderImpl::GetOutputCurrentType(DWORD dwOutputStreamIndex,
        DMO_MEDIA_TYPE *pmt){
    if (dwOutputStreamIndex >= NumberOfOutputStreams) {
        return DMO_E_INVALIDSTREAMINDEX;
    }

    return E_NOTIMPL;
}

STDMETHODIMP TMp2EncoderImpl::GetInputSizeInfo(DWORD dwInputStreamIndex,
        DWORD *pcbSize, DWORD *pcbMaxLookahead, DWORD *pcbAlignment) {
    if (dwInputStreamIndex >= NumberOfInputStreams) {
        return DMO_E_INVALIDSTREAMINDEX;
    }

    return E_NOTIMPL;
}

STDMETHODIMP TMp2EncoderImpl::GetOutputSizeInfo(DWORD dwOutputStreamIndex,
        DWORD *pcbSize, DWORD *pcbAlignment) {
    if (dwOutputStreamIndex >= NumberOfOutputStreams) {
        return DMO_E_INVALIDSTREAMINDEX;
    }

    return E_NOTIMPL;
}

STDMETHODIMP TMp2EncoderImpl::GetInputMaxLatency(DWORD dwInputStreamIndex,
        REFERENCE_TIME *prtMaxLatency){
    if (dwInputStreamIndex >= NumberOfInputStreams) {
        return DMO_E_INVALIDSTREAMINDEX;
    }

    return E_NOTIMPL;
}

STDMETHODIMP TMp2EncoderImpl::SetInputMaxLatency(DWORD dwInputStreamIndex,
        REFERENCE_TIME rtMaxLatency){
    if (dwInputStreamIndex >= NumberOfInputStreams) {
        return DMO_E_INVALIDSTREAMINDEX;
    }

    return E_NOTIMPL;
}

STDMETHODIMP TMp2EncoderImpl::Flush(){
    return E_NOTIMPL;
}

STDMETHODIMP TMp2EncoderImpl::Discontinuity(DWORD dwInputStreamIndex) {
    if (dwInputStreamIndex >= NumberOfInputStreams) {
        return DMO_E_INVALIDSTREAMINDEX;
    }

    return E_NOTIMPL;
}

STDMETHODIMP TMp2EncoderImpl::AllocateStreamingResources(){
    return E_NOTIMPL;
}

STDMETHODIMP TMp2EncoderImpl::FreeStreamingResources(){
    return E_NOTIMPL;
}

STDMETHODIMP TMp2EncoderImpl::GetInputStatus(DWORD dwInputStreamIndex,
        DWORD *dwFlags){
    if (dwInputStreamIndex >= NumberOfInputStreams) {
        return DMO_E_INVALIDSTREAMINDEX;
    }

    return E_NOTIMPL;
}

STDMETHODIMP TMp2EncoderImpl::ProcessInput(DWORD dwInputStreamIndex,
        IMediaBuffer *pBuffer, DWORD dwFlags, REFERENCE_TIME rtTimestamp,
        REFERENCE_TIME rtTimelength){
    if (dwInputStreamIndex >= NumberOfInputStreams) {
        return DMO_E_INVALIDSTREAMINDEX;
    }

    return E_NOTIMPL;
}

STDMETHODIMP TMp2EncoderImpl::ProcessOutput(DWORD dwFlags,
        DWORD cOutputBufferCount, DMO_OUTPUT_DATA_BUFFER *pOutputBuffers,
        DWORD *pdwStatus){
    return E_NOTIMPL;
}

STDMETHODIMP TMp2EncoderImpl::Lock(LONG bLock){
    return E_NOTIMPL;
}

// Unit initialization

static void CreateFactory() {
    new TComObjectFactory(ComServer, __classid(TMp2EncoderImpl),
            CLSID_Mp2Encoder, L"TMp2EncoderImpl", L"MP2 Encoder DMO",
            ciMultiInstance, Comobj::tmBoth);
}
#pragma startup CreateFactory 64
