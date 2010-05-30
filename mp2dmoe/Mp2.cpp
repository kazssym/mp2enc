/*
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
#include <cstring>
#include <cassert>

//using namespace std;

#pragma package(smart_init)

// Specifies the libraries to link.
#pragma link "libtwolame.lib"
#pragma link "msdmo.lib"

#define CHANNEL_MASK(c)\
    ((c) == 2 ? SPEAKER_FRONT_LEFT | SPEAKER_FRONT_RIGHT : 0)
#define PCM(c, s, b, v) {\
    {WAVE_FORMAT_PCM, (c), (s), (s) * (c) * (b), (c) * (b), 8 * (b), 0}\
}
#define PCM_EXT(c, s, b, v) {\
    {WAVE_FORMAT_EXTENSIBLE, (c), (s), (s) * (c) * (b), (c) * (b), 8 * (b), 22},\
    (v), CHANNEL_MASK(c), {STATIC_KSDATAFORMAT_SUBTYPE_PCM}\
}
#define MPEG1(c, s, r) {\
    {WAVE_FORMAT_EXTENSIBLE, (c), (s), (r) / 8, 1, 0, 22},\
    1152, CHANNEL_MASK(c), {STATIC_KSDATAFORMAT_SUBTYPE_MPEG1Payload}\
}
static const WAVEFORMATEXTENSIBLE InputFormat[] = {
    PCM_EXT(2, 48000, 2, 16),
    PCM_EXT(1, 48000, 2, 16),
    PCM(2, 44100, 2, 16),
    PCM(1, 44100, 2, 16),
    PCM(2, 32000, 2, 16),
    PCM(1, 32000, 2, 16),
};
static const WAVEFORMATEXTENSIBLE OutputFormat[] = {
    MPEG1(2, 48000, 384000),
    MPEG1(1, 48000, 192000),
    MPEG1(2, 44100, 384000),
    MPEG1(1, 44100, 192000),
    MPEG1(2, 32000, 384000),
    MPEG1(1, 32000, 192000),
};

HRESULT WINAPI
TMp2EncoderImpl::UpdateRegistry(BOOL bRegister)
{
  TComServerRegistrarT<TMp2EncoderImpl> reg(GetObjectCLSID(), 0, GetDescription());
  return reg.UpdateRegistry(bRegister);
}

/*
 * Initializes each member to a safe value.
 */
TMp2EncoderImpl::TMp2EncoderImpl(void)
{
  Options = 0;
}

HRESULT WINAPI
TMp2EncoderImpl::FinalConstruct(void)
{
  Options = twolame_init();
  if (Options == 0)
    return E_OUTOFMEMORY;
  return S_OK;
}

void WINAPI
TMp2EncoderImpl::FinalRelease(void)
{
  twolame_close(&Options);
}

HRESULT WINAPI
TMp2EncoderImpl::InternalGetInputStreamInfo(DWORD dwInputStreamIndex,
                                        DWORD *pdwFlags)
{
  if (dwInputStreamIndex >= 1)
    return DMO_E_INVALIDSTREAMINDEX;
  if (pdwFlags == 0)
    return E_POINTER;

  *pdwFlags = (DMO_INPUT_STREAMF_WHOLE_SAMPLES |
               DMO_INPUT_STREAMF_FIXED_SAMPLE_SIZE);
  return S_OK;
}

HRESULT WINAPI
TMp2EncoderImpl::InternalGetOutputStreamInfo(DWORD dwOutputStreamIndex,
                                         DWORD *pdwFlags)
{
  if (dwOutputStreamIndex >= 1)
    return DMO_E_INVALIDSTREAMINDEX;
  if (pdwFlags == 0)
    return E_POINTER;

  *pdwFlags = (DMO_OUTPUT_STREAMF_WHOLE_SAMPLES |
               DMO_OUTPUT_STREAMF_FIXED_SAMPLE_SIZE);
  return S_OK;
}

HRESULT WINAPI
TMp2EncoderImpl::InternalGetInputType(DWORD dwInputStreamIndex, DWORD dwTypeIndex,
                                  DMO_MEDIA_TYPE *pmt)
{
  if (dwInputStreamIndex >= 1)
    return DMO_E_INVALIDSTREAMINDEX;
  if (dwTypeIndex >= sizeof InputFormat / sizeof InputFormat[0])
    return DMO_E_NO_MORE_ITEMS;

  if (pmt != 0)
  {
    HRESULT hres = MoInitMediaType(pmt, sizeof (WAVEFORMATEXTENSIBLE));
    if (FAILED(hres))
      return hres;
    pmt->majortype = MEDIATYPE_Audio;
    pmt->subtype = MEDIASUBTYPE_PCM;
    pmt->bFixedSizeSamples = TRUE;
    pmt->lSampleSize = 2 * 2;
    pmt->formattype = FORMAT_WaveFormatEx;
    WAVEFORMATEXTENSIBLE *pFormat = reinterpret_cast<WAVEFORMATEXTENSIBLE *>(pmt->pbFormat);
    *pFormat = InputFormat[dwTypeIndex];
  }
  return S_OK;
}

HRESULT WINAPI
TMp2EncoderImpl::InternalGetOutputType(DWORD dwOutputStreamIndex, DWORD dwTypeIndex,
                                   DMO_MEDIA_TYPE *pmt)
{
  if (dwOutputStreamIndex >= 1)
    return DMO_E_INVALIDSTREAMINDEX;
  if (dwTypeIndex >= sizeof OutputFormat / sizeof OutputFormat[0])
    return DMO_E_NO_MORE_ITEMS;

  if (pmt != 0)
  {
    HRESULT hres = MoInitMediaType(pmt, sizeof (WAVEFORMATEXTENSIBLE));
    if (FAILED(hres))
      return hres;
    pmt->majortype = MEDIATYPE_Audio;
    pmt->subtype = MEDIASUBTYPE_MPEG1Payload;
    pmt->bFixedSizeSamples = TRUE;
    pmt->formattype = FORMAT_WaveFormatEx;
    WAVEFORMATEXTENSIBLE *pFormat = reinterpret_cast<WAVEFORMATEXTENSIBLE *>(pmt->pbFormat);
    *pFormat = OutputFormat[dwTypeIndex];
  }
  return S_OK;
}

HRESULT STDMETHODCALLTYPE
TMp2EncoderImpl::InternalCheckInputType(DWORD dwInputStreamIndex,
                                        const DMO_MEDIA_TYPE *pmt)
{
    assert(dwInputStreamIndex < 1);
    assert(pmt != 0);

    if (pmt->majortype == MEDIATYPE_Audio &&
        pmt->subtype == MEDIASUBTYPE_PCM)
    {
        if (pmt->formattype == FORMAT_WaveFormatEx &&
            pmt->cbFormat >= sizeof (WAVEFORMATEX) && 
            pmt->pbFormat != 0)
        {
            WAVEFORMATEX *format = 
                reinterpret_cast<WAVEFORMATEX *>(pmt->pbFormat);
            if (format->wFormatTag == WAVE_FORMAT_PCM ||
                (format->wFormatTag == WAVE_FORMAT_EXTENSIBLE && format->cbSize >= 22U)) 
            {
                if ((ULONG) format->nChannels != pmt->lSampleSize / 2U ||
                    (ULONG) format->nBlockAlign != pmt->lSampleSize ||
                    format->wBitsPerSample != 16U)
                    return DMO_E_INVALIDTYPE;
                if (format->wFormatTag == WAVE_FORMAT_EXTENSIBLE) 
                {
                    WAVEFORMATEXTENSIBLE *formatExt =
                        reinterpret_cast<WAVEFORMATEXTENSIBLE *>(format);
                    if (formatExt->Samples.wValidBitsPerSample != 16U) {
                        return DMO_E_INVALIDTYPE;
                    }
                }
                switch (format->nSamplesPerSec) 
                {
                case 48000:
                case 44100:
                case 32000:
                    return S_OK;    
                }
            }
        }
    }
    return DMO_E_INVALIDTYPE;
}

HRESULT WINAPI
TMp2EncoderImpl::InternalCheckOutputType(DWORD dwOutputStreamIndex, const DMO_MEDIA_TYPE *pmt)
{
  if (dwOutputStreamIndex >= 1)
    return DMO_E_INVALIDSTREAMINDEX;

  return E_NOTIMPL;
}

HRESULT WINAPI
TMp2EncoderImpl::InternalGetInputSizeInfo(DWORD, DWORD *, DWORD *, DWORD *)
{
  return E_NOTIMPL;
}

HRESULT WINAPI
TMp2EncoderImpl::InternalGetOutputSizeInfo(DWORD, DWORD *, DWORD *)
{
  return E_NOTIMPL;
}

HRESULT WINAPI
TMp2EncoderImpl::InternalGetInputMaxLatency(DWORD, REFERENCE_TIME *)
{
  return E_NOTIMPL;
}

HRESULT WINAPI
TMp2EncoderImpl::InternalSetInputMaxLatency(DWORD, REFERENCE_TIME)
{
  return E_NOTIMPL;
}

HRESULT WINAPI
TMp2EncoderImpl::InternalFlush(void)
{
  return E_NOTIMPL;
}

HRESULT WINAPI
TMp2EncoderImpl::InternalDiscontinuity(DWORD)
{
  return E_NOTIMPL;
}

HRESULT WINAPI
TMp2EncoderImpl::InternalAllocateStreamingResources(void)
{
  return E_NOTIMPL;
}

HRESULT WINAPI
TMp2EncoderImpl::InternalFreeStreamingResources(void)
{
  return E_NOTIMPL;
}

HRESULT WINAPI
TMp2EncoderImpl::InternalAcceptingInput(DWORD dwInputStreamIndex)
{
  return E_NOTIMPL;
}

HRESULT WINAPI
TMp2EncoderImpl::InternalProcessInput(DWORD, IMediaBuffer *, DWORD, REFERENCE_TIME, REFERENCE_TIME)
{
  return E_NOTIMPL;
}

HRESULT WINAPI
TMp2EncoderImpl::InternalProcessOutput(DWORD, DWORD, DMO_OUTPUT_DATA_BUFFER *, DWORD *)
{
  return E_NOTIMPL;
}