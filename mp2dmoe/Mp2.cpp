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

#include "Mp2.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)

DEFGUID(CLSID_MP2Encoder, CMP2Encoder)

HRESULT WINAPI
CMP2Encoder::UpdateRegistry(BOOL bRegister)
{
  TComServerRegistrarT<CMP2Encoder> regObj(GetObjectCLSID(), 0, GetDescription());
  return regObj.UpdateRegistry(bRegister);
}

HRESULT
CMP2Encoder::InternalGetInputStreamInfo(DWORD dwInputStreamIndex, DWORD *pdwFlags)
{
  return E_NOTIMPL;
}

HRESULT
CMP2Encoder::InternalGetOutputStreamInfo(DWORD dwOutputStreamIndex, DWORD *pdwFlags)
{
  return E_NOTIMPL;
}

HRESULT
CMP2Encoder::InternalGetInputType(DWORD, DWORD, DMO_MEDIA_TYPE *)
{
  return E_NOTIMPL;
}

HRESULT
CMP2Encoder::InternalGetOutputType(DWORD, DWORD, DMO_MEDIA_TYPE *)
{
  return E_NOTIMPL;
}

HRESULT
CMP2Encoder::InternalCheckInputType(DWORD dwInputStreamIndex, const DMO_MEDIA_TYPE *pmt)
{
  return E_NOTIMPL;
}

HRESULT
CMP2Encoder::InternalCheckOutputType(DWORD dwOutputStreamIndex, const DMO_MEDIA_TYPE *pmt)
{
  return E_NOTIMPL;
}

HRESULT
CMP2Encoder::InternalGetInputSizeInfo(DWORD, DWORD *, DWORD *, DWORD *)
{
  return E_NOTIMPL;
}

HRESULT
CMP2Encoder::InternalGetOutputSizeInfo(DWORD, DWORD *, DWORD *)
{
  return E_NOTIMPL;
}

HRESULT
CMP2Encoder::InternalGetInputMaxLatency(DWORD, REFERENCE_TIME *)
{
  return E_NOTIMPL;
}

HRESULT
CMP2Encoder::InternalSetInputMaxLatency(DWORD, REFERENCE_TIME)
{
  return E_NOTIMPL;
}

HRESULT
CMP2Encoder::InternalFlush(void)
{
  return E_NOTIMPL;
}

HRESULT
CMP2Encoder::InternalDiscontinuity(DWORD)
{
  return E_NOTIMPL;
}

HRESULT
CMP2Encoder::InternalAllocateStreamingResources(void)
{
  return E_NOTIMPL;
}

HRESULT
CMP2Encoder::InternalFreeStreamingResources(void)
{
  return E_NOTIMPL;
}

HRESULT
CMP2Encoder::InternalAcceptingInput(DWORD dwInputStreamIndex)
{
  return E_NOTIMPL;
}

HRESULT
CMP2Encoder::InternalProcessInput(DWORD, IMediaBuffer *, DWORD, REFERENCE_TIME, REFERENCE_TIME)
{
  return E_NOTIMPL;
}

HRESULT
CMP2Encoder::InternalProcessOutput(DWORD, DWORD, DMO_OUTPUT_DATA_BUFFER *, DWORD *)
{
  return E_NOTIMPL;
}