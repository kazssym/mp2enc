﻿/*
 * MP2 Encoder DMO.
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

#include "Mp2.h"
#include <dshow.h>
//#include <mmreg.h>
#include <ks.h>
#pragma warn -8098
#include <ksmedia.h>
#pragma warn .8098
#include <new>
#include <cstring>
#include <cassert>

//using namespace std;

#pragma package(smart_init)

// Specifies the libraries to link.
#pragma link "libtwolame.lib"
#pragma link "msdmo.lib"

const GUID KSDATAFORMAT_SUBTYPE_PCM = {STATIC_KSDATAFORMAT_SUBTYPE_PCM};
#if 0
const GUID KSDATAFORMAT_SUBTYPE_MPEG1Payload = {STATIC_KSDATAFORMAT_SUBTYPE_MPEG1Payload};
#endif

#define CHANNEL_MASK(c)\
    ((c) == 2 ? SPEAKER_FRONT_LEFT | SPEAKER_FRONT_RIGHT : 0)
#define PCM(c, s, b, v) {\
    {WAVE_FORMAT_PCM, (c), (s), (s) * (c) * (b), (c) * (b), 8 * (b), 0}\
}
#define PCMX(c, s, b, v) {\
    {WAVE_FORMAT_EXTENSIBLE, (c), (s), (s) * (c) * (b), (c) * (b), 8 * (b), 22},\
    (v), CHANNEL_MASK(c), {STATIC_KSDATAFORMAT_SUBTYPE_PCM}\
}
#define MPEG1(c, s, r) {\
    {WAVE_FORMAT_EXTENSIBLE, (c), (s), (r) / 8, 1, 0, 22},\
    TWOLAME_SAMPLES_PER_FRAME, CHANNEL_MASK(c), {STATIC_KSDATAFORMAT_SUBTYPE_MPEG1Payload}\
}
static const WAVEFORMATEXTENSIBLE InputFormat[] = {
    PCMX(2, 48000, 2, 16),
    PCM(2, 44100, 2, 16),
    PCM(2, 32000, 2, 16),
    PCMX(1, 48000, 2, 16),
    PCM(1, 44100, 2, 16),
    PCM(1, 32000, 2, 16),
};
static const WAVEFORMATEXTENSIBLE OutputFormat[] = {
    MPEG1(2, 48000, 384000),
    MPEG1(2, 44100, 384000),
    MPEG1(2, 32000, 384000),
    MPEG1(1, 48000, 192000),
    MPEG1(1, 44100, 192000),
    MPEG1(1, 32000, 192000),
};

HRESULT
TMp2EncoderImpl::SetInputParameters(twolame_options *options,
                                    const DMO_MEDIA_TYPE *pmt)
{
    assert(options != 0);
    assert(pmt != 0);

    if (pmt->majortype == MEDIATYPE_Audio &&
        pmt->subtype == MEDIASUBTYPE_PCM)
    {
        if (pmt->formattype == FORMAT_WaveFormatEx)
        {
            if (pmt->cbFormat < sizeof (WAVEFORMATEX) || pmt->pbFormat == 0)
                return DMO_E_INVALIDTYPE;

            WAVEFORMATEX *format =
                reinterpret_cast<WAVEFORMATEX *>(pmt->pbFormat);
            if (format->wBitsPerSample != 16) // We support 16-bit audio only.
                return DMO_E_INVALIDTYPE;
            if (pmt->lSampleSize != format->nChannels * 2UL ||
                pmt->cbFormat < sizeof (WAVEFORMATEX) + format->cbSize)
                return DMO_E_INVALIDTYPE;
            // We just ignores any wrong wFormatTag value.
            if (format->wFormatTag == WAVE_FORMAT_EXTENSIBLE)
            {
                if (format->cbSize < 22)
                    return DMO_E_INVALIDTYPE;

                WAVEFORMATEXTENSIBLE *formatExt =
                    reinterpret_cast<WAVEFORMATEXTENSIBLE *>(format);
                if (formatExt->SubFormat != KSDATAFORMAT_SUBTYPE_PCM &&
                    formatExt->Samples.wValidBitsPerSample != 16)
                    return DMO_E_INVALIDTYPE;
            }

            if (twolame_set_num_channels(options, format->nChannels) == 0 &&
                twolame_set_in_samplerate(options, format->nSamplesPerSec) == 0)
                return S_OK;
        }
    }
    return DMO_E_INVALIDTYPE;
}

HRESULT
TMp2EncoderImpl::SetOutputParameters(twolame_options *options,
                                     const DMO_MEDIA_TYPE *pmt)
{
    assert(options != 0);
    assert(pmt != 0);

    if (pmt->majortype == MEDIATYPE_Audio &&
        (pmt->subtype == MEDIASUBTYPE_MPEG1Audio ||
         pmt->subtype == MEDIASUBTYPE_MPEG1Payload) ||
        pmt->majortype == MEDIATYPE_Stream &&
        pmt->subtype == MEDIASUBTYPE_MPEG1Audio)
    {
        if (pmt->formattype == FORMAT_WaveFormatEx)
        {
            if (pmt->cbFormat < sizeof (WAVEFORMATEX) || pmt->pbFormat == 0)
                return DMO_E_INVALIDTYPE;

            WAVEFORMATEX *format =
                reinterpret_cast<WAVEFORMATEX *>(pmt->pbFormat);
            if (pmt->cbFormat < sizeof (WAVEFORMATEX) + format->cbSize)
                return DMO_E_INVALIDTYPE;
#if 0 // I do not know what is the standard value for MPEG audio.
            if (format->wFormatTag == WAVE_FORMAT_EXTENSIBLE)
            {
                if (format->cbSize < 22)
                    return DMO_E_INVALIDTYPE;

                WAVEFORMATEXTENSIBLE *formatExt =
                    reinterpret_cast<WAVEFORMATEXTENSIBLE *>(format);
                if (formatExt->SubFormat != KSDATAFORMAT_SUBTYPE_MPEG1Payload &&
                    formatExt->Samples.wSamplesPerBlock != TWOLAME_SAMPLES_PER_FRAME)
                    return DMO_E_INVALIDTYPE;
            }
#endif // 0

            int bitrate = format->nAvgBytesPerSec * 8;
            if (bitrate % 1000 != 0)
                return DMO_E_INVALIDTYPE;
            if (twolame_set_mode(options, format->nChannels == 1 ? TWOLAME_MONO : TWOLAME_JOINT_STEREO) == 0 &&
                twolame_set_out_samplerate(options, format->nSamplesPerSec) == 0 &&
                twolame_set_bitrate(options, bitrate / 1000) == 0)
                return S_OK;
        }
    }
    return DMO_E_INVALIDTYPE;
}

HRESULT WINAPI
TMp2EncoderImpl::UpdateRegistry(BOOL bRegister)
{
    TComServerRegistrarT<TMp2EncoderImpl> reg(GetObjectCLSID(), 0,
                                              TEXT("MP2 Encoder DMO"));
    return reg.UpdateRegistry(bRegister);
}

HRESULT
TMp2EncoderImpl::FinalConstruct()
{
#if 0
    Options = twolame_init();
    if (Options == 0)
        return E_OUTOFMEMORY;
    twolame_set_copyright(Options, TRUE);
#endif // 0
    return S_OK;
}

void
TMp2EncoderImpl::FinalRelease()
{
    delete[] InternalBuffer;
    twolame_close(&Options);
}

HRESULT
TMp2EncoderImpl::InitializeEncoder(const DMO_MEDIA_TYPE *pmtInput,
                                   const DMO_MEDIA_TYPE *pmtOutput)
{
    twolame_close(&Options);

    Options = twolame_init();
    if (Options == 0)
        return E_OUTOFMEMORY;

    if (pmtInput != 0)
    {
        HRESULT hr = SetInputParameters(Options, pmtInput);
        if (FAILED(hr))
            return hr;
    }
    if (pmtOutput != 0)
    {
        HRESULT hr = SetOutputParameters(Options, pmtOutput);
        if (FAILED(hr))
            return hr;
    }
    twolame_set_copyright(Options, TRUE);

    if (twolame_get_num_channels(Options) == 0)
        twolame_set_num_channels(Options, 2);
    if (twolame_get_in_samplerate(Options) == 0)
        twolame_set_in_samplerate(Options, twolame_get_out_samplerate(Options));
    if (twolame_init_params(Options) != 0)
        return DMO_E_INVALIDTYPE;
    return S_OK;
}

HRESULT
TMp2EncoderImpl::InternalGetInputStreamInfo(DWORD dwInputStreamIndex,
                                            DWORD *pdwFlags)
{
    assert(dwInputStreamIndex < 1);
    assert(pdwFlags != 0);

    *pdwFlags = (DMO_INPUT_STREAMF_WHOLE_SAMPLES |
                 DMO_INPUT_STREAMF_FIXED_SAMPLE_SIZE);
    return S_OK;
}

HRESULT
TMp2EncoderImpl::InternalGetOutputStreamInfo(DWORD dwOutputStreamIndex,
                                             DWORD *pdwFlags)
{
    assert(dwOutputStreamIndex < 1);
    assert(pdwFlags != 0);

    *pdwFlags = (DMO_OUTPUT_STREAMF_WHOLE_SAMPLES |
                 DMO_OUTPUT_STREAMF_FIXED_SAMPLE_SIZE |
                 DMO_OUTPUT_STREAMF_DISCARDABLE);
    return S_OK;
}

HRESULT
TMp2EncoderImpl::InternalGetInputType(DWORD dwInputStreamIndex,
                                      DWORD dwTypeIndex, DMO_MEDIA_TYPE *pmt)
{
    assert(dwInputStreamIndex < 1);

    if (dwTypeIndex >= sizeof InputFormat / sizeof InputFormat[0])
        return DMO_E_NO_MORE_ITEMS;

    if (pmt != 0)
    {
        HRESULT hr = MoInitMediaType(pmt, sizeof (WAVEFORMATEXTENSIBLE));
        if (FAILED(hr))
            return hr;
        pmt->majortype = MEDIATYPE_Audio;
        pmt->subtype = MEDIASUBTYPE_PCM;
        pmt->bFixedSizeSamples = TRUE;
        pmt->lSampleSize = 2 * 2;
        pmt->formattype = FORMAT_WaveFormatEx;
        WAVEFORMATEXTENSIBLE *format =
            reinterpret_cast<WAVEFORMATEXTENSIBLE *>(pmt->pbFormat);
        *format = InputFormat[dwTypeIndex];
    }
    return S_OK;
}

HRESULT
TMp2EncoderImpl::InternalGetOutputType(DWORD dwOutputStreamIndex,
                                       DWORD dwTypeIndex, DMO_MEDIA_TYPE *pmt)
{
    assert(dwOutputStreamIndex < 1);

    if (dwTypeIndex >= sizeof OutputFormat / sizeof OutputFormat[0])
        return DMO_E_NO_MORE_ITEMS;

    if (pmt != 0)
    {
        HRESULT hr = MoInitMediaType(pmt, sizeof (WAVEFORMATEXTENSIBLE));
        if (FAILED(hr))
            return hr;
        pmt->majortype = MEDIATYPE_Audio;
        pmt->subtype = MEDIASUBTYPE_MPEG1Audio;
        pmt->bFixedSizeSamples = TRUE;
        pmt->formattype = FORMAT_WaveFormatEx;
        WAVEFORMATEXTENSIBLE *format =
            reinterpret_cast<WAVEFORMATEXTENSIBLE *>(pmt->pbFormat);
        *format = OutputFormat[dwTypeIndex];
    }
    return S_OK;
}

HRESULT
TMp2EncoderImpl::InternalCheckInputType(DWORD dwInputStreamIndex,
                                        const DMO_MEDIA_TYPE *pmt)
{
    assert(dwInputStreamIndex < 1);
    assert(pmt != 0);

    HRESULT hr = InitializeEncoder(pmt, OutputType(0));
    return hr;
}

HRESULT
TMp2EncoderImpl::InternalCheckOutputType(DWORD dwOutputStreamIndex,
                                         const DMO_MEDIA_TYPE *pmt)
{
    assert(dwOutputStreamIndex < 1);
    assert(pmt != 0);

    HRESULT hr = InitializeEncoder(InputType(0), pmt);
    return hr;
}

HRESULT
TMp2EncoderImpl::InternalGetInputSizeInfo(DWORD dwInputStreamIndex,
                                          DWORD *pcbSize,
                                          DWORD *pcbMaxLookahead,
                                          DWORD *pcbAlignment)
{
    assert(dwInputStreamIndex < 1);
    assert(pcbSize != 0);
    assert(pcbMaxLookahead != 0);
    assert(pcbAlignment != 0);

    const int nChannels = twolame_get_num_channels(Options);
    *pcbSize = nChannels * 2;
    *pcbMaxLookahead = 0;
    *pcbAlignment = nChannels * 2;
    return S_OK;
}

HRESULT
TMp2EncoderImpl::InternalGetOutputSizeInfo(DWORD dwOutputStreamIndex,
                                           DWORD *pcbSize, DWORD *pcbAlignment)
{
    assert(dwOutputStreamIndex < 1);
    assert(pcbSize != 0);
    assert(pcbAlignment != 0);

    *pcbSize = twolame_get_framelength(Options);
    *pcbAlignment = 1;
    return S_OK;
}

HRESULT
TMp2EncoderImpl::InternalGetInputMaxLatency(DWORD, REFERENCE_TIME *)
{
    return E_NOTIMPL;
}

HRESULT
TMp2EncoderImpl::InternalSetInputMaxLatency(DWORD, REFERENCE_TIME)
{
    return E_NOTIMPL;
}

HRESULT
TMp2EncoderImpl::InternalFlush()
{
    InputBuffer = 0;
    GotDiscontinuity = false;
    HRESULT hr = InitializeEncoder(InputType(0), OutputType(0));
    return hr;
}

HRESULT
TMp2EncoderImpl::InternalDiscontinuity(DWORD dwInputStreamIndex)
{
    assert(dwInputStreamIndex < 1);

    GotDiscontinuity = true;
    return S_OK;
}

HRESULT
TMp2EncoderImpl::InternalAllocateStreamingResources()
{
    // We do nothing.
    return S_OK;
}

HRESULT
TMp2EncoderImpl::InternalFreeStreamingResources()
{
    // We do nothing.
    return S_OK;
}

HRESULT
TMp2EncoderImpl::InternalAcceptingInput(DWORD dwInputStreamIndex)
{
    assert(dwInputStreamIndex < 1);

    if (InputBuffer == 0 && !GotDiscontinuity)
        return S_OK;
    else
        return S_FALSE;
}

HRESULT
TMp2EncoderImpl::InternalProcessInput(DWORD dwInputStreamIndex,
                                      IMediaBuffer *pBuffer, DWORD dwFlags,
                                      REFERENCE_TIME rtTimestamp,
                                      REFERENCE_TIME rtTimelength)
{
    assert(dwInputStreamIndex < 1);
    assert(pBuffer != 0);
    assert(InputBuffer == 0);

    InputBuffer = pBuffer;
    EncodedLength = 0;
    return S_OK;
}

HRESULT
TMp2EncoderImpl::InternalProcessOutput(DWORD dwFlags, DWORD cOutputBufferCount,
                                       DMO_OUTPUT_DATA_BUFFER *pOutputBuffers,
                                       DWORD *pdwStatus)
{
    assert(cOutputBufferCount >= 1);
    assert(pOutputBuffers != 0);
    assert(pdwStatus != 0);

    HRESULT hr;
    BYTE *output;
    DWORD outputLength;
    DWORD outputCapacity;
    if (pOutputBuffers[0].pBuffer == 0)
    {
        if (InternalBuffer == 0)
        {
            InternalBuffer = new (std::nothrow) BYTE[8192];
            if (InternalBuffer == 0)
                return E_OUTOFMEMORY;
        }
        output = InternalBuffer;
        outputLength = 0;
        outputCapacity = 8192;
    }
    else
    {
        hr = pOutputBuffers[0].pBuffer->GetBufferAndLength(&output, &outputLength);
        if (FAILED(hr))
            return hr;
        hr = pOutputBuffers[0].pBuffer->GetMaxLength(&outputCapacity);
        if (FAILED(hr))
            return hr;
        assert(outputLength == 0);
    }

    const std::size_t sampleSize =
        twolame_get_num_channels(Options) * sizeof (short);
    const DWORD frameLength = twolame_get_framelength(Options);

    if (InputBuffer != 0)
    {
        BYTE *input;
        DWORD inputLength;
        hr = InputBuffer->GetBufferAndLength(&input, &inputLength);
        if (FAILED(hr))
            return hr;
        assert(inputLength >= EncodedLength);
        input += EncodedLength;
        inputLength -= EncodedLength;

        assert(inputLength % sampleSize == 0);
        while (inputLength != 0 && outputCapacity >= frameLength)
        {
            DWORD m = TWOLAME_SAMPLES_PER_FRAME * sampleSize;
            if (m > inputLength)
                m = inputLength;

            int n = twolame_encode_buffer_interleaved
                (Options, reinterpret_cast<short *>(input), m / sampleSize,
                 output, outputCapacity);
            if (n < 0)
                return E_FAIL;
            EncodedLength += m;
            outputLength += n;

            input += m;
            inputLength -= m;
            output += n;
            outputCapacity -= n;
        }
        if (inputLength == 0)
            InputBuffer = 0;
        else
            pOutputBuffers[0].dwStatus |= DMO_OUTPUT_DATA_BUFFERF_INCOMPLETE;
    }

    if (InputBuffer == 0 && GotDiscontinuity && outputCapacity >= frameLength)
    {
        int n = twolame_encode_flush(Options, output, outputCapacity);
        if (n < 0)
            return E_FAIL;
        outputLength += n;
        GotDiscontinuity = false;
    }

    if (outputLength != 0)
    {
        if (pOutputBuffers[0].pBuffer != 0)
        {
            hr = pOutputBuffers[0].pBuffer->SetLength(outputLength);
            if (FAILED(hr))
                return hr;
        }

        return S_OK;
    }
    else
        return S_FALSE;
}
