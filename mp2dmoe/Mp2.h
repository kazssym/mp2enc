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

#include "mp2guid.h"

#include <twolame.h>
#define FIX_LOCK_NAME 1
#include <dmo.h>
#include <dmoimpl.h>
#undef FIX_LOCK_NAME

class ATL_NO_VTABLE TMp2EncoderImpl :
    public CComObjectRootEx<CComMultiThreadModel>,
    public CComCoClass<TMp2EncoderImpl, &CLSID_Mp2Encoder>,
    public IMediaObjectImpl<TMp2EncoderImpl, 1, 1>
{
    BEGIN_COM_MAP(TMp2EncoderImpl)
    COM_INTERFACE_ENTRY(IMediaObject)
    END_COM_MAP()
public:
    // For <atl/atlmod.h>
    DECLARE_DESCRIPTION(TEXT("MP2 Encoder DMO"));
    DECLARE_THREADING_MODEL(otBoth);
    static HRESULT WINAPI UpdateRegistry(BOOL bRegister);
public:
    /*
     * Initializes each member to a safe value.
     */
    TMp2EncoderImpl()
    {
        Options = 0;
    }

    HRESULT FinalConstruct();
    void FinalRelease();

  // IMediaObjectImpl internal methods
    HRESULT InternalGetInputStreamInfo(DWORD dwInputStreamIndex,
                                       DWORD *pdwFlags);
    HRESULT InternalGetOutputStreamInfo(DWORD dwOutputStreamIndex,
                                        DWORD *pdwFlags);
    HRESULT InternalGetInputType(DWORD dwInputStreamIndex,
                                 DWORD dwTypeIndex, DMO_MEDIA_TYPE *pmt);
    HRESULT InternalGetOutputType(DWORD dwOutputStreamIndex,
                                  DWORD dwTypeIndex, DMO_MEDIA_TYPE *pmt);
    HRESULT InternalCheckInputType(DWORD dwInputStreamIndex,
                                   const DMO_MEDIA_TYPE *pmt);
    HRESULT InternalCheckOutputType(DWORD dwOutputStreamIndex,
                                    const DMO_MEDIA_TYPE *pmt);
    HRESULT InternalGetInputSizeInfo(DWORD, DWORD *, DWORD *, DWORD *);
    HRESULT InternalGetOutputSizeInfo(DWORD, DWORD *, DWORD *);
    HRESULT InternalGetInputMaxLatency(DWORD, REFERENCE_TIME *);
    HRESULT InternalSetInputMaxLatency(DWORD, REFERENCE_TIME);
    HRESULT InternalFlush();
    HRESULT InternalDiscontinuity(DWORD);
    HRESULT InternalAllocateStreamingResources();
    HRESULT InternalFreeStreamingResources();
    HRESULT InternalAcceptingInput(DWORD dwInputStreamIndex);
    HRESULT InternalProcessInput(DWORD, IMediaBuffer *, DWORD, REFERENCE_TIME, REFERENCE_TIME);
    HRESULT InternalProcessOutput(DWORD, DWORD, DMO_OUTPUT_DATA_BUFFER *, DWORD *);
private:
    twolame_options *Options;
};

#endif

