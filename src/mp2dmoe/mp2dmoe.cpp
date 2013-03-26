/*
 * mp2dmoe - DLL entry points
 * Copyright (C) 2010-2013  Kaz Sasa
 *
 * This program is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the Free
 * Software Foundation, either version 3 of the License, or (at your option)
 * any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <vcl.h>
#pragma hdrstop
#pragma package(smart_init)

#include <System.Win.ComServ.hpp>

#pragma link "System.Win.ComServ"
#pragma comment(lib, "msdmo")

// -----------------------------------------------------------------------------
// Entry point of your Server invoked by Windows for processes or threads are
// initialized or terminated.
//
// -----------------------------------------------------------------------------
int WINAPI DllEntryPoint(HINSTANCE hinst, unsigned long reason, void *) {
    return TRUE;
}

// -----------------------------------------------------------------------------
// Entry point of your Server invoked to inquire whether the DLL is no
// longer in use and should be unloaded.
// -----------------------------------------------------------------------------
STDAPI __export DllCanUnloadNow(void) {
    if (!ComServer ||
            (ComServer->ObjectCount == 0 && ComServer->FactoryCount == 0)) {
        return S_OK;
    }
    return S_FALSE;
}

// -----------------------------------------------------------------------------
// Entry point of your Server allowing OLE to retrieve a class object from
// your Server
// -----------------------------------------------------------------------------
STDAPI __export DllGetClassObject(REFCLSID rclsid, REFIID riid, LPVOID *ppv) {
    TComObjectFactory *Factory =
            ComClassManager()->GetFactoryFromClassID(rclsid);
    if (Factory) {
        if (Factory->GetInterface(riid, ppv))
            return S_OK;
        else
            return E_NOINTERFACE;
    }
    *ppv = 0;
    return CLASS_E_CLASSNOTAVAILABLE;
}

// -----------------------------------------------------------------------------
// Entry point of your Server invoked to instruct the server to create
// registry entries for all classes supported by the module
// -----------------------------------------------------------------------------
STDAPI __export DllRegisterServer(void) {
    try {
        ComServer->UpdateRegistry(true);
    } catch (...) {
        return E_FAIL;
    }
    return S_OK;
}

// -----------------------------------------------------------------------------
// Entry point of your Server invoked to instruct the server to remove
// all registry entries created through DllRegisterServer.
// -----------------------------------------------------------------------------
STDAPI __export DllUnregisterServer(void) {
    try {
        ComServer->UpdateRegistry(false);
    } catch (...) {
        return E_FAIL;
    }
    return S_OK;
}

// ------------------------------------------------------------------------------
// Entry point of your Server installation/setup. Used for 'PerUser' registration
// Invoked via call to "regsvr32 /n /i:user [/u] axlibrary.dll"
// ------------------------------------------------------------------------------
STDAPI __export DllInstall(BOOL bInstall, LPCWSTR pszCmdLine) {
    bool savePerUser = ComServer->PerUserRegistration;
    ComServer->PerUserRegistration =
            pszCmdLine && Sysutils::StrIComp(pszCmdLine, L"user") == 0;

    HRESULT hr;
    if (bInstall) {
        hr = DllRegisterServer();
        if (hr == E_FAIL) {
            DllUnregisterServer();
        }
    } else {
        hr = DllUnregisterServer();
    }

    ComServer->PerUserRegistration = savePerUser;
    return hr;
}
