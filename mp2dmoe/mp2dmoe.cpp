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
//#include <atl/atlvcl.h>

//---------------------------------------------------------------------------
//   以下は，ユーザー DLL が静的ランタイムライブラリを使う場合の DLL
//   メモリ管理に関する重要な注意です
//
//   引数または返り値として String 型オブジェクト (または String を含む構
//   造体・クラス) を扱う関数を DLL からエクスポートする使う場合，その DLL
//   のプロジェクトや，その DLL を使うプロジェクトに MEMMGR.LIB ライブラリ
//   を追加する必要があります。
//
//   DLL からエクスポートされた，TObject から派生されていないクラスに対して
//   new または delete を使う場合にも MEMMGR.LIB を追加しなければなりません。
//
//   MEMMGR.LIB を追加することにより，DLL と DLL を参照する EXE が共通の
//   メモリマネージャとして BORLNDMM.DLL を使うようになります。
//   この場合，DLL またはアプリケーションとともに BORLANDMM.DLL を配布して
//   ください。
//
//   BORLNDMM.DLL が使われるのを避けるには，String 型のかわりに
//   "char *" または ShortString 型を使ってください。
//
//   作成する DLL が共有 RTL DLL を使う場合，RTL の方で MEMMGR.LIB をライブ
//   ラリとして追加するため DLL プロジェクトに明示的に追加する必要はありま
//   せん。
//---------------------------------------------------------------------------

// Exports functions.
STDAPI __declspec(dllexport) DllGetClassObject(REFCLSID rclsid, REFIID riid, LPVOID *ppv);
STDAPI __declspec(dllexport) DllCanUnloadNow(void);
STDAPI __declspec(dllexport) DllRegisterServer(void);
STDAPI __declspec(dllexport) DllUnregisterServer(void);

static TComModule ThisModule;
TComModule &_Module = ThisModule;

BEGIN_OBJECT_MAP(ObjectMap)
OBJECT_ENTRY(CLSID_Mp2Encoder, TMp2EncoderImpl)
END_OBJECT_MAP()

/*
 * Initializes the module on the first load.
 */
BOOL WINAPI
DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved)
{
  if (fdwReason == DLL_PROCESS_ATTACH)
  {
    _Module.Init(ObjectMap, hinstDLL);
    DisableThreadLibraryCalls(hinstDLL);
  }
  return TRUE;
}

static void
ModuleTerm(void)
{
  _Module.Term();
}
#pragma exit ModuleTerm

/*
 * Retrieves the class object from a DLL object handler.
 */
HRESULT WINAPI
DllGetClassObject(REFCLSID rclsid, REFIID riid, LPVOID *ppv)
{
  return _Module.GetClassObject(rclsid, riid, ppv);
}

/*
 * Determines whether this DLL is in use.
 */
HRESULT WINAPI
DllCanUnloadNow(void)
{
  return _Module.GetLockCount() == 0 ? S_OK : S_FALSE;
}

// モジュールでサポートされたすべてのクラスに対するレジストリ エントリ
// を作成するようにサーバーに指示するため呼び出されたサーバーのエントリ ポイント。
//
HRESULT WINAPI
DllRegisterServer(void)
{
  // No type library in this DLL.
  return _Module.RegisterServer(FALSE);
}

// DllRegisterServer を通じて作成されたすべてのレジストリ エントリを
// 削除するようにサーバーに指示するため呼び出されたサーバーのエントリ ポイント。
//
HRESULT WINAPI
DllUnregisterServer(void)
{
  return _Module.UnregisterServer();
}
