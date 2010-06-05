//$$---- axlib proj source ---- (stAXLibProjectSource)
#include <vcl.h>
#pragma hdrstop
#include <atl\atlvcl.h>

#pragma package(smart_init)
#pragma link "vclnp.lib"
#pragma resource "*.tlb"
TComModule  Project1Module;
TComModule &_Module = Project1Module;

// ATL オブジェクト マップは _ATL_OBJMAP_ENTRY 構造体
// (ユーザーの OLE サーバーのオブジェクトを記述) の配列を保持します。MAP は
// ユーザー プロジェクトの CComModule-derived _Module オブジェクトに Init メソッド経由で渡されます。
//
BEGIN_OBJECT_MAP(ObjectMap)
END_OBJECT_MAP()

// 初期化または終了されたスレッドやプロセスに対して Windows によって
// 呼び出されたサーバーのエントリ ポイント。
//
int WINAPI DllEntryPoint(HINSTANCE hinst, unsigned long reason, void*)
{
    if (reason == DLL_PROCESS_ATTACH)
    {
        _Module.Init(ObjectMap, hinst);
        DisableThreadLibraryCalls(hinst);
    }
    return TRUE;
}

// _Module.Term は通常、ユーザーの DllEntryPoint の DLL_PROCESS_DETACH から
// 呼び出されます。ただし、この結果としてシャットダウン シーケンスが不正になることがあります。
// 代わりに Exit ルーチンを設定して、クリーンアップ ルーチン
// CComModule::Term を呼び出します。
//
void ModuleTerm(void)
{
    _Module.Term();
}
#pragma exit ModuleTerm 63

// DLL が使用されなくなり、アンロードが必要かどうかを
// 問い合わせるために呼び出されたサーバーのエントリ ポイント。
//
STDAPI __export DllCanUnloadNow(void)
{
    return (_Module.GetLockCount()==0) ? S_OK : S_FALSE;
}

// ユーザーのサーバーからクラス オブジェクトを取得することを OLE に許可した
// サーバーのエントリ ポイント。
//
STDAPI __export DllGetClassObject(REFCLSID rclsid, REFIID riid, LPVOID* ppv)
{
    return _Module.GetClassObject(rclsid, riid, ppv);
}

// モジュールでサポートされたすべてのクラスに対するレジストリ エントリ
// を作成するようにサーバーに指示するため呼び出されたサーバーのエントリ ポイント。
//
STDAPI __export DllRegisterServer(void)
{
    return _Module.RegisterServer(TRUE);
}

// DllRegisterServer を通じて作成されたすべてのレジストリ エントリを
// 削除するようにサーバーに指示するため呼び出されたサーバーのエントリ ポイント。
//
STDAPI __export DllUnregisterServer(void)
{
    return _Module.UnregisterServer();
}
//---------------------------------------------------------------------------
