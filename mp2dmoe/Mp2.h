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
#include <Dmo.h>
#include <Dmoimpl.h>
#undef FIX_LOCK_NAME

#define DEFGUID(Name, Type) const GUID Name = __uuidof(Type);

class __declspec(uuid("{3FCD30F6-88FE-4A44-A518-1DBB0937DAE4}")) ATL_NO_VTABLE CMp2Encoder;

extern const GUID CLSID_Mp2Encoder;

class CMp2Encoder
: public CComObjectRootEx<CComMultiThreadModel>,
  public CComCoClass<CMp2Encoder, &CLSID_Mp2Encoder>,
  public IMediaObjectImpl<CMp2Encoder, 1, 1>
{
  BEGIN_COM_MAP(CMp2Encoder)
  COM_INTERFACE_ENTRY(IMediaObject)
  END_COM_MAP()
public:
  CMp2Encoder(void);
  ~CMp2Encoder(void);

  // For <atl/atlmod.h>
  DECLARE_DESCRIPTION(_TEXT("MP2 Encoder DMO"));
  DECLARE_THREADING_MODEL(otBoth);
  static HRESULT WINAPI UpdateRegistry(BOOL bRegister);

  // IMediaObjectImpl internal methods
  HRESULT WINAPI InternalGetInputStreamInfo(DWORD dwInputStreamIndex, DWORD *pdwFlags);
  HRESULT WINAPI InternalGetOutputStreamInfo(DWORD dwOutputStreamIndex, DWORD *pdwFlags);
  HRESULT WINAPI InternalGetInputType(DWORD dwInputStreamIndex,
                                      DWORD dwTypeIndex, DMO_MEDIA_TYPE *pmt);
  HRESULT WINAPI InternalGetOutputType(DWORD dwOutputStreamIndex,
                                       DWORD dwTypeIndex, DMO_MEDIA_TYPE *pmt);
  HRESULT WINAPI InternalCheckInputType(DWORD dwInputStreamIndex, const DMO_MEDIA_TYPE *pmt);
  HRESULT WINAPI InternalCheckOutputType(DWORD dwOutputStreamIndex, const DMO_MEDIA_TYPE *pmt);
  HRESULT WINAPI InternalGetInputSizeInfo(DWORD, DWORD *, DWORD *, DWORD *);
  HRESULT WINAPI InternalGetOutputSizeInfo(DWORD, DWORD *, DWORD *);
  HRESULT WINAPI InternalGetInputMaxLatency(DWORD, REFERENCE_TIME *);
  HRESULT WINAPI InternalSetInputMaxLatency(DWORD, REFERENCE_TIME);
  HRESULT WINAPI InternalFlush(void);
  HRESULT WINAPI InternalDiscontinuity(DWORD);
  HRESULT WINAPI InternalAllocateStreamingResources(void);
  HRESULT WINAPI InternalFreeStreamingResources(void);
  HRESULT WINAPI InternalAcceptingInput(DWORD dwInputStreamIndex);
  HRESULT WINAPI InternalProcessInput(DWORD, IMediaBuffer *, DWORD, REFERENCE_TIME, REFERENCE_TIME);
  HRESULT WINAPI InternalProcessOutput(DWORD, DWORD, DMO_OUTPUT_DATA_BUFFER *, DWORD *);
};

#endif
