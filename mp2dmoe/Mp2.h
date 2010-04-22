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

#ifndef Mp2H
#define Mp2H 1
#pragma once

#define FIX_LOCK_NAME 1
#include <dmo.h>
#include <dmoimpl.h>
#undef FIX_LOCK_NAME

#define DEFGUID(Name, Type) const GUID Name = __uuidof(Type);

class __declspec(uuid("{3FCD30F6-88FE-4A44-A518-1DBB0937DAE4}")) CMp2Encoder;

extern const GUID CLSID_Mp2Encoder;

class ATL_NO_VTABLE CMp2Encoder
: public CComObjectRootEx<CComMultiThreadModel>,
  public CComCoClass<CMp2Encoder, &CLSID_Mp2Encoder>,
  public IMediaObjectImpl<CMp2Encoder, 1, 1>
{
  friend class IMediaObjectImpl<CMp2Encoder, 1, 1>;
public:
  // <atl/atlmod.h>
  DECLARE_DESCRIPTION(_TEXT("MP2 Encoder DMO"));
  DECLARE_THREADING_MODEL(otBoth);
public:
  static HRESULT WINAPI UpdateRegistry(BOOL bRegister);

  // <atlcom.h>
  BEGIN_COM_MAP(CMp2Encoder)
  COM_INTERFACE_ENTRY(IMediaObject)
  END_COM_MAP()

private:
  // IMediaObjectImpl internal methods
  HRESULT InternalGetInputStreamInfo(DWORD dwInputStreamIndex, DWORD *pdwFlags);
  HRESULT InternalGetOutputStreamInfo(DWORD dwOutputStreamIndex, DWORD *pdwFlags);
  HRESULT InternalGetInputType(DWORD, DWORD, DMO_MEDIA_TYPE *);
  HRESULT InternalGetOutputType(DWORD, DWORD, DMO_MEDIA_TYPE *);
  HRESULT InternalCheckInputType(DWORD dwInputStreamIndex, const DMO_MEDIA_TYPE *pmt);
  HRESULT InternalCheckOutputType(DWORD dwOutputStreamIndex, const DMO_MEDIA_TYPE *pmt);
  HRESULT InternalGetInputSizeInfo(DWORD, DWORD *, DWORD *, DWORD *);
  HRESULT InternalGetOutputSizeInfo(DWORD, DWORD *, DWORD *);
  HRESULT InternalGetInputMaxLatency(DWORD, REFERENCE_TIME *);
  HRESULT InternalSetInputMaxLatency(DWORD, REFERENCE_TIME);
  HRESULT InternalFlush(void);
  HRESULT InternalDiscontinuity(DWORD);
  HRESULT InternalAllocateStreamingResources(void);
  HRESULT InternalFreeStreamingResources(void);
  HRESULT InternalAcceptingInput(DWORD dwInputStreamIndex);
  HRESULT InternalProcessInput(DWORD, IMediaBuffer *, DWORD, REFERENCE_TIME, REFERENCE_TIME);
  HRESULT InternalProcessOutput(DWORD, DWORD, DMO_OUTPUT_DATA_BUFFER *, DWORD *);
};

#endif
