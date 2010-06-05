// ************************************************************************ //
// 警告
// -------
// このファイルで宣言されている型はタイプライブラリから読み取られたデータから
// 生成されています。このタイプライブラリが明示的あるいは（このタイプライブラ
// リを参照しているほかのタイプライブラリ経由で）間接的に再インポートされた
// り，タイプライブライブラリの編集中にタイプライブラリエディタの［更新］コマ
// ンドを実行した場合，このファイルの内容はすべて再生成され，手動で加えた変更
// はすべて失われます。
// ************************************************************************ //


// $Rev: 17252 $
// 下に説明されたタイプ ライブラリから 2010/06/05 15:21:25 に生成されたファイル。

// ************************************************************************  //
// タイプ ライブラリ: E:\UserData\Kaz\Documents\RAD Studio\Projects\mp2enc\id3mux\id3mux (1)
// LIBID: {F503A583-0F48-4671-A45B-32D889F22DCF}
// LCID: 0
// ヘルプファイル:
// ヘルプ文字列:
// 依存関係リスト:
//   (1) v2.0 stdole, (C:\Windows\system32\stdole2.tlb)
// ************************************************************************ //
#ifndef   id3mux_TLBH
#define   id3mux_TLBH

#pragma option push -b -a4 -w-inl

#if !defined(__UTILCLS_H)
#include <utilcls.h>
#endif
#if !defined(__UTILCLS_H_VERSION) || (__UTILCLS_H_VERSION < 0x0700)
//
// C++ Builder のインポート|ActiveX とインポート|タイプライブラリ機能または TLIBIMP ユーティリティ
// より生成されるコードは INCLUDE\VCL ディレクトリにある
// UTILCLS.H ヘッダー ファイルの特定バージョンに依存します。ファイルの
// 以前のバージョンが検出された場合は、更新やパッチが必要になることがあります。
//
#error "このファイルでは新しいバージョンのヘッダー UTILCLS.H が必要です。" \r
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

namespace Id3mux_tlb
{

// *********************************************************************//
// ヘルプ文字列:
// バージョン: 1.0
// *********************************************************************//


// *********************************************************************//
// タイプライブラリで宣言された GUID次のプレフィックスが使用されます:
// タイプ ライブラリ      : LIBID_xxxx
//   CoClasses          : CLSID_xxxx
// ディスパッチ インターフェイス: DIID_xxxx
// 非ディスパッチ インターフェイス: IID_xxxx
// *********************************************************************//
extern __declspec (package) const GUID LIBID_id3mux;
extern __declspec (package) const GUID IID_IConfigId3Mux;
// *********************************************************************//

// タイプライブラリで宣言される前方参照

// *********************************************************************//

interface DECLSPEC_UUID("{F82FF012-2B6A-4CB8-8989-6DCB5A6EB49A}") IConfigId3Mux;
typedef TComInterface<IConfigId3Mux, &IID_IConfigId3Mux> IConfigId3MuxPtr;

// *********************************************************************//
// インターフェイス: IConfigId3Mux
// フラグ: (320) Dual OleAutomation
// GUID: {F82FF012-2B6A-4CB8-8989-6DCB5A6EB49A}
// *********************************************************************//
interface IConfigId3Mux  : public IUnknown
{
public:

#if !defined(__TLB_NO_INTERFACE_WRAPPERS)



#endif //   __TLB_NO_INTERFACE_WRAPPERS

};

#if !defined(__TLB_NO_INTERFACE_WRAPPERS)
typedef TComInterface<IConfigId3Mux>  TCOMIConfigId3Mux;

// *********************************************************************//
// DispIntf:  IConfigId3Mux
// フラグ:     (320) Dual OleAutomation
// GUID:      {F82FF012-2B6A-4CB8-8989-6DCB5A6EB49A}
// *********************************************************************//
template<class T>
class IConfigId3MuxDispT : public TAutoDriver<IConfigId3Mux>
{
public:
  IConfigId3MuxDispT(){}

  IConfigId3MuxDispT(IConfigId3Mux *pintf)
  {
    TAutoDriver<IConfigId3Mux>::Bind(pintf, false);
  }

  IConfigId3MuxDispT(IConfigId3MuxPtr pintf)
  {
    TAutoDriver<IConfigId3Mux>::Bind(pintf, true);
  }

  IConfigId3MuxDispT& operator=(IConfigId3Mux *pintf)
  {
    TAutoDriver<IConfigId3Mux>::Bind(pintf, false);
    return *this;
  }

  IConfigId3MuxDispT& operator=(IConfigId3MuxPtr pintf)
  {
    TAutoDriver<IConfigId3Mux>::Bind(pintf, true);
    return *this;
  }


};
typedef IConfigId3MuxDispT<IConfigId3Mux> IConfigId3MuxDisp;

// *********************************************************************//
// DispIntf:  IConfigId3Mux
// フラグ:     (320) Dual OleAutomation
// GUID:      {F82FF012-2B6A-4CB8-8989-6DCB5A6EB49A}
// *********************************************************************//
#endif  //   __TLB_NO_INTERFACE_WRAPPERS


};     // namespace Id3mux_tlb

#if !defined(NO_IMPLICIT_NAMESPACE_USE)
using  namespace Id3mux_tlb;
#endif

#pragma option pop

#endif // id3mux_TLBH

