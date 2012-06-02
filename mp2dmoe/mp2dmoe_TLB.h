// ************************************************************************ //
// 警告
// -------
// このファイルで宣言されている型はタイプ ライブラリから読み取られたデータから
// 生成されています。このタイプ ライブラリが明示的あるいは（このタイプ ライブラ
// リを参照しているほかのタイプ ライブラリ経由で）間接的に再インポートされた
// り、タイプ ライブライブラリの編集中にタイプ ライブラリ エディタの［更新］コマ
// ンドを実行した場合、このファイルの内容はすべて再生成され、手動で加えた変更
// はすべて失われます。
// ************************************************************************ //

// $Rev: 34747 $
// 下に説明されたタイプ ライブラリから 2012/06/02 16:53:38 に生成されたファイル。

// ************************************************************************  //
// タイプ ライブラリ: E:\UserData\Kaz\Documents\RAD Studio\Projects\mp2enc\mp2dmoe\mp2dmoe (1)
// LIBID: {67FC4F6A-1F74-41AE-8F59-B0A174D394DF}
// LCID: 0
// ヘルプファイル:
// ヘルプ文字列:
// 依存関係リスト:
//   (1) v2.0 stdole, (C:\Windows\SysWOW64\stdole2.tlb)
// ************************************************************************ //
#ifndef   mp2dmoe_TLBH
#define   mp2dmoe_TLBH

#pragma option push -b -a4 -w-inl -w-8118

#if !defined(__UTILCLS_H)
#include <utilcls.h>
#endif
#if !defined(__UTILCLS_H_VERSION) || (__UTILCLS_H_VERSION < 0x0700)
//
// C++ Builder のインポート|ActiveX とインポート|タイプ ライブラリ機能または TLIBIMP ユーティリティ
// より生成されるコードは INCLUDE\VCL ディレクトリにある
// UTILCLS.H ヘッダー ファイルの特定バージョンに依存します。ファイルの
// 以前のバージョンが検出された場合は、更新やパッチが必要になることがあります。
//
#error "このファイルでは新しいバージョンのヘッダー UTILCLS.H が必要です。" \
"C++ Builder を更新またはパッチを適用する必要があります"
#endif
#include <olectl.h>
#include <ocidl.h>
#if defined(USING_ATLVCL) || defined(USING_ATL)
#if !defined(__TLB_NO_EVENT_WRAPPERS)
#include <atl/atlmod.h>
#endif
#endif


// *********************************************************************//
// 一部の VCL 型の前方参照 (STDVCL.HPP のインクルードを回避するため)
// *********************************************************************//
namespace Stdvcl {class IStrings; class IStringsDisp;}
using namespace Stdvcl;
typedef TComInterface<IStrings> IStringsPtr;
typedef TComInterface<IStringsDisp> IStringsDispPtr;

namespace Mp2dmoe_tlb
{

// *********************************************************************//
// ヘルプ文字列:
// バージョン: 1.0
// *********************************************************************//

// *********************************************************************//
// タイプ ライブラリで宣言された GUID次のプレフィックスが使用されます:
// タイプ ライブラリ      : LIBID_xxxx
//   CoClasses          : CLSID_xxxx
// ディスパッチ インターフェイス: DIID_xxxx
// 非ディスパッチ インターフェイス: IID_xxxx
// *********************************************************************//
extern __declspec (package) const GUID LIBID_mp2dmoe;
};     // namespace Mp2dmoe_tlb

#if !defined(NO_IMPLICIT_NAMESPACE_USE)
using  namespace Mp2dmoe_tlb;
#endif

#pragma option pop

#endif // mp2dmoe_TLBH

