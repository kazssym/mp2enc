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

#include <Initguid.h>

#include "Mp2.h"
#include <Dshow.h>
#include <cstring>

using namespace std;

//---------------------------------------------------------------------------

#pragma package(smart_init)

DEFGUID(CLSID_Mp2Encoder, CMp2Encoder)

#define PCM(c, s) {WAVE_FORMAT_PCM, (c), (s), (s) * (c) * 2, (c) * 2, 16, 0}
static const WAVEFORMATEX inputFormat[] = {
  PCM(2, 48000),
  PCM(2, 44100),
  PCM(2, 32000),
  PCM(1, 48000),
  PCM(1, 44100),
  PCM(1, 32000),
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
  return E_NOTIMPL;
}

HRESULT WINAPI
CMp2Encoder::InternalGetOutputStreamInfo(DWORD dwOutputStreamIndex, DWORD *pdwFlags)
{
  return E_NOTIMPL;
}

HRESULT WINAPI
CMp2Encoder::InternalGetInputType(DWORD dwInputStreamIndex, DWORD dwTypeIndex,
                                  DMO_MEDIA_TYPE *pmt)
{
  if (dwInputStreamIndex >= 1)
    return DMO_E_INVALIDSTREAMINDEX;
  if (dwTypeIndex >= sizeof inputFormat / sizeof inputFormat[0])
    return DMO_E_NO_MORE_ITEMS;
  if (pmt != 0)
  {
    HRESULT hres = MoInitMediaType(pmt, sizeof (WAVEFORMATEX));
    pmt->majortype = MEDIATYPE_Audio;
    pmt->subtype = MEDIASUBTYPE_PCM;
    pmt->bFixedSizeSamples = TRUE;
    pmt->lSampleSize = 2 * 2;
    pmt->formattype = FORMAT_WaveFormatEx;
    WAVEFORMATEX *pFormat = reinterpret_cast<WAVEFORMATEX *>(pmt->pbFormat);
    *pFormat = inputFormat[0];
  }
  return S_OK;
}

HRESULT WINAPI
CMp2Encoder::InternalGetOutputType(DWORD dwOutputStreamIndex, DWORD dwTypeIndex,
                                   DMO_MEDIA_TYPE *pmt)
{
  if (dwOutputStreamIndex >= 1)
    return DMO_E_INVALIDSTREAMINDEX;
  if (dwTypeIndex >= sizeof inputFormat / sizeof inputFormat[0])
    return DMO_E_NO_MORE_ITEMS;
  if (pmt != 0)
  {
    // @todo
  }
  return E_NOTIMPL;
}

HRESULT WINAPI
CMp2Encoder::InternalCheckInputType(DWORD dwInputStreamIndex, const DMO_MEDIA_TYPE *pmt)
{
  return E_NOTIMPL;
}

HRESULT WINAPI
CMp2Encoder::InternalCheckOutputType(DWORD dwOutputStreamIndex, const DMO_MEDIA_TYPE *pmt)
{
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