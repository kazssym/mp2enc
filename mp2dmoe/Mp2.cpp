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
#include <DShow.h>
//#include <mmreg.h>
#include <ks.h>
#pragma warn -8098
#include <ksmedia.h>
#pragma warn .8098
#include <cstring>

using namespace std;

#pragma package(smart_init)

#define CHANNEL_MASK(c)\
  ((c) == 2 ? SPEAKER_FRONT_LEFT | SPEAKER_FRONT_RIGHT : 0)
#define PCM(c, s, b, v) {\
  {WAVE_FORMAT_EXTENSIBLE, (c), (s), (s) * (c) * (b), (c) * (b), 8 * (b), 22},\
  (v), CHANNEL_MASK(c), {STATIC_KSDATAFORMAT_SUBTYPE_PCM}\
}
#define MPEG1(c, s, r) {\
  {WAVE_FORMAT_EXTENSIBLE, (c), (s), (r) / 8, 1, 0, 22},\
  1152, CHANNEL_MASK(c), {STATIC_KSDATAFORMAT_SUBTYPE_MPEG1Payload}\
}
static const WAVEFORMATEXTENSIBLE InputFormat[] = {
  PCM(2, 48000, 2, 16),
  PCM(1, 48000, 2, 16),
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

CMp2Encoder::CMp2Encoder(void)
{
}

CMp2Encoder::~CMp2Encoder(void)
{
}

HRESULT WINAPI
CMp2Encoder::UpdateRegistry(BOOL bRegister)
{
  TComServerRegistrarT<CMp2Encoder> regObj(GetObjectCLSID(), 0, GetDescription());
  return regObj.UpdateRegistry(bRegister);
}

HRESULT WINAPI
CMp2Encoder::InternalGetInputStreamInfo(DWORD dwInputStreamIndex, DWORD *pdwFlags)
{
  if (dwInputStreamIndex >= 1)
    return DMO_E_INVALIDSTREAMINDEX;
  if (pdwFlags == 0)
    return E_POINTER;
  *pdwFlags = DMO_INPUT_STREAMF_WHOLE_SAMPLES | DMO_INPUT_STREAMF_FIXED_SAMPLE_SIZE;
  return S_OK;
}

HRESULT WINAPI
CMp2Encoder::InternalGetOutputStreamInfo(DWORD dwOutputStreamIndex, DWORD *pdwFlags)
{
  if (dwOutputStreamIndex >= 1)
    return DMO_E_INVALIDSTREAMINDEX;
  if (pdwFlags == 0)
    return E_POINTER;
  *pdwFlags = DMO_OUTPUT_STREAMF_WHOLE_SAMPLES | DMO_OUTPUT_STREAMF_FIXED_SAMPLE_SIZE;
  return S_OK;
}

HRESULT WINAPI
CMp2Encoder::InternalGetInputType(DWORD dwInputStreamIndex, DWORD dwTypeIndex,
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
CMp2Encoder::InternalGetOutputType(DWORD dwOutputStreamIndex, DWORD dwTypeIndex,
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

HRESULT WINAPI
CMp2Encoder::InternalCheckInputType(DWORD dwInputStreamIndex, const DMO_MEDIA_TYPE *pmt)
{
  if (dwInputStreamIndex >= 1)
    return DMO_E_INVALIDSTREAMINDEX;
  return E_NOTIMPL;
}

HRESULT WINAPI
CMp2Encoder::InternalCheckOutputType(DWORD dwOutputStreamIndex, const DMO_MEDIA_TYPE *pmt)
{
  if (dwOutputStreamIndex >= 1)
    return DMO_E_INVALIDSTREAMINDEX;
  return E_NOTIMPL;
}

HRESULT WINAPI
CMp2Encoder::InternalGetInputSizeInfo(DWORD, DWORD *, DWORD *, DWORD *)
{
  return E_NOTIMPL;
}

HRESULT WINAPI
CMp2Encoder::InternalGetOutputSizeInfo(DWORD, DWORD *, DWORD *)
{
  return E_NOTIMPL;
}

HRESULT WINAPI
CMp2Encoder::InternalGetInputMaxLatency(DWORD, REFERENCE_TIME *)
{
  return E_NOTIMPL;
}

HRESULT WINAPI
CMp2Encoder::InternalSetInputMaxLatency(DWORD, REFERENCE_TIME)
{
  return E_NOTIMPL;
}

HRESULT WINAPI
CMp2Encoder::InternalFlush(void)
{
  return E_NOTIMPL;
}

HRESULT WINAPI
CMp2Encoder::InternalDiscontinuity(DWORD)
{
  return E_NOTIMPL;
}

HRESULT WINAPI
CMp2Encoder::InternalAllocateStreamingResources(void)
{
  return E_NOTIMPL;
}

HRESULT WINAPI
CMp2Encoder::InternalFreeStreamingResources(void)
{
  return E_NOTIMPL;
}

HRESULT WINAPI
CMp2Encoder::InternalAcceptingInput(DWORD dwInputStreamIndex)
{
  return E_NOTIMPL;
}

HRESULT WINAPI
CMp2Encoder::InternalProcessInput(DWORD, IMediaBuffer *, DWORD, REFERENCE_TIME, REFERENCE_TIME)
{
  return E_NOTIMPL;
}

HRESULT WINAPI
CMp2Encoder::InternalProcessOutput(DWORD, DWORD, DMO_OUTPUT_DATA_BUFFER *, DWORD *)
{
  return E_NOTIMPL;
}