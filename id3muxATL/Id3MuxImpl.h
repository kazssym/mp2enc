/*
 * ID3 Mux - DirectShow filter to add ID3 tags to audio streams.
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

#ifndef Id3MuxImplH
#define Id3MuxImplH 1

#include "id3muxguid.h"
#include "id3mux_TLB.h"
#include <dshow.h>
#include <string>

class ATL_NO_VTABLE TId3MuxImpl :
    public CComObjectRootEx<CComMultiThreadModel>,
    public CComCoClass<TId3MuxImpl, &CLSID_Id3Mux>,
    public IPersistImpl<TId3MuxImpl>,
    public IBaseFilter, public IConfigId3Mux
{
    BEGIN_COM_MAP(TId3MuxImpl)
    COM_INTERFACE_ENTRY(IBaseFilter)
    COM_INTERFACE_ENTRY(IConfigId3Mux)
    END_COM_MAP()
public:
    // For <atl/atlmod.h>.
    DECLARE_THREADING_MODEL(otBoth);
    static HRESULT WINAPI UpdateRegistry(BOOL bRegister);
public:
    TId3MuxImpl()
    {
        State = State_Stopped;
        Clock = 0;
        Graph = 0;
    }

    HRESULT FinalConstruct();
    void FinalRelease();
public:
    using IPersistImpl<TId3MuxImpl>::GetClassID;
    // Overrides IMediaFilter.
    HRESULT STDMETHODCALLTYPE Stop();
    HRESULT STDMETHODCALLTYPE Pause();
    HRESULT STDMETHODCALLTYPE Run(REFERENCE_TIME timeStart);
    HRESULT STDMETHODCALLTYPE GetState(DWORD dwMilliSecsTimeout, FILTER_STATE *pState);
    HRESULT STDMETHODCALLTYPE SetSyncSource(IReferenceClock *pClock);
    HRESULT STDMETHODCALLTYPE GetSyncSource(IReferenceClock **ppClock);
    // Overrides IBaseFilter.
    HRESULT STDMETHODCALLTYPE EnumPins(IEnumPins **ppEnum);
    HRESULT STDMETHODCALLTYPE FindPin(LPCWSTR pId, IPin **ppPin);
    HRESULT STDMETHODCALLTYPE QueryFilterInfo(FILTER_INFO *pInfo);
    HRESULT STDMETHODCALLTYPE JoinFilterGraph(IFilterGraph *pGraph, LPCWSTR pName);
    HRESULT STDMETHODCALLTYPE QueryVendorInfo(LPWSTR *pVendorInfo);
private:
    FILTER_STATE State;
    IReferenceClock *Clock;
    IFilterGraph *Graph; // No reference counting.
    std::wstring Name;
};

#endif
