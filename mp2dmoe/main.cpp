//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "encoder.h"
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

#define EXPORT __export

static TComModule MP2DMOEncoderModule;
TComModule &_Module = MP2DMOEncoderModule;

BEGIN_OBJECT_MAP(ObjectMap)
OBJECT_ENTRY(CLSID_MP2Encoder, CMP2Encoder)
END_OBJECT_MAP()

#pragma argsused
BOOL WINAPI
DllMain(HINSTANCE hinstDLL, DWORD dwReason, LPVOID lpvReserved)
{
  if (dwReason == DLL_PROCESS_ATTACH)
  {
    _Module.Init(ObjectMap, hinstDLL);
    DisableThreadLibraryCalls(hinstDLL);
  }
  return TRUE;
}
//---------------------------------------------------------------------------

static void
ModuleTerm(void)
{
  _Module.Term();
}
#pragma exit ModuleTerm

/*
 * Retrieves the class object from a DLL object handler.
 */
STDAPI EXPORT
DllGetClassObject(REFCLSID rclsid, REFIID riid, LPVOID *ppv)
{
  return _Module.GetClassObject(rclsid, riid, ppv);
}

/*
 * Determines whether this DLL is in use.
 */
STDAPI EXPORT
DllCanUnloadNow(void)
{
  return _Module.GetLockCount() == 0 ? S_OK : S_FALSE;
}

// モジュールでサポートされたすべてのクラスに対するレジストリ エントリ
// を作成するようにサーバーに指示するため呼び出されたサーバーのエントリ ポイント。
//
STDAPI EXPORT
DllRegisterServer(void)
{
  // No type library in this DLL.
  return _Module.RegisterServer(FALSE);
}

// DllRegisterServer を通じて作成されたすべてのレジストリ エントリを
// 削除するようにサーバーに指示するため呼び出されたサーバーのエントリ ポイント。
//
STDAPI EXPORT
DllUnregisterServer(void)
{
  return _Module.UnregisterServer();
}
