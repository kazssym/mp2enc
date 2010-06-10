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

#include <vcl.h>
#pragma hdrstop

#include "Id3MuxImpl.h"

#include <cstring>

#pragma package(smart_init)

HRESULT WINAPI
TId3MuxImpl::UpdateRegistry(BOOL bRegister)
{
    TTypedComServerRegistrarT<TId3MuxImpl> reg(GetObjectCLSID(), 0,
                                               TEXT("ID3 Mux"));
    return reg.UpdateRegistry(bRegister);
}

HRESULT
TId3MuxImpl::FinalConstruct()
{
    return S_OK;
}

void
TId3MuxImpl::FinalRelease()
{
    if (Clock != 0)
        Clock->Release();
    Clock = 0;
    // We must not have a reference count on the filter graph.
}

STDMETHODIMP
TId3MuxImpl::Stop()
{
    State = State_Stopped;
    return S_OK;
}

STDMETHODIMP
TId3MuxImpl::Pause()
{
    State = State_Paused;
    return S_OK;
}

STDMETHODIMP
TId3MuxImpl::Run(REFERENCE_TIME timeStart)
{
    State = State_Running;
    return S_OK;
}

STDMETHODIMP
TId3MuxImpl::GetState(DWORD dwMilliSecsTimeout, FILTER_STATE *pState)
{
    if (pState != 0)
        return E_POINTER;

    *pState = State;
    return S_OK;
}

STDMETHODIMP
TId3MuxImpl::SetSyncSource(IReferenceClock *pClock)
{
    if (Clock != 0)
        Clock->Release();
    Clock = pClock;
    if (Clock != 0)
        Clock->AddRef();
    return S_OK;
}

STDMETHODIMP
TId3MuxImpl::GetSyncSource(IReferenceClock **ppClock)
{
    if (ppClock == 0)
        return E_POINTER;

    *ppClock = Clock;
    if (*ppClock != 0)
        (*ppClock)->AddRef();
    return S_OK;
}

STDMETHODIMP
TId3MuxImpl::EnumPins(IEnumPins **ppEnum)
{
    return E_NOTIMPL;
}

STDMETHODIMP
TId3MuxImpl::FindPin(LPCWSTR pId, IPin **ppPin)
{
    return E_NOTIMPL;
}

STDMETHODIMP
TId3MuxImpl::QueryFilterInfo(FILTER_INFO *pInfo)
{
    if (pInfo == 0)
        return E_POINTER;

    std::wcsncpy(pInfo->achName, Name.c_str(), MAX_FILTER_NAME);
    pInfo->pGraph = Graph;
    if (pInfo->pGraph != 0)
        pInfo->pGraph->AddRef();
    return S_OK;
}

STDMETHODIMP
TId3MuxImpl::JoinFilterGraph(IFilterGraph *pGraph, LPCWSTR pName)
{
    if (pName == 0)
        return E_POINTER;

    // We must not hold a reference count on the filter graph.
    Graph = pGraph;
    Name = pName;
    return S_OK;
}

STDMETHODIMP
TId3MuxImpl::QueryVendorInfo(LPWSTR *pVendorInfo)
{
    // This is OK.
    return E_NOTIMPL;
}

