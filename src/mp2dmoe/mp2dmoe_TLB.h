// ************************************************************************ //
// WARNING
// -------
// The types declared in this file were generated from data read from a
// Type Library. If this type library is explicitly or indirectly (via
// another type library referring to this type library) re-imported, or the
// 'Refresh' command of the Type Library Editor activated while editing the
// Type Library, the contents of this file will be regenerated and all
// manual modifications will be lost.
// ************************************************************************ //

// $Rev: 34747 $
// File generated on 2012/06/16 11:04:14 from Type Library described below.

// ************************************************************************  //
// Type Lib: E:\UserData\Kaz\Documents\RAD Studio\Projects\mp2enc\src\mp2dmoe\mp2dmoe (1)
// LIBID: {67FC4F6A-1F74-41AE-8F59-B0A174D394DF}
// LCID: 0
// Helpfile:
// HelpString:
// DepndLst:
//   (1) v2.0 stdole, (C:\Windows\system32\stdole2.tlb)
// ************************************************************************ //
#ifndef   mp2dmoe_TLBH
#define   mp2dmoe_TLBH

#pragma option push -b -a4 -w-inl -w-8118

#if !defined(__UTILCLS_H)
#include <utilcls.h>
#endif
#if !defined(__UTILCLS_H_VERSION) || (__UTILCLS_H_VERSION < 0x0700)
//
// The code generated by the TLIBIMP utility or the Import|TypeLibrary
// and Import|ActiveX feature of C++Builder rely on specific versions of
// the header file UTILCLS.H found in the INCLUDE\VCL directory. If an
// older version of the file is detected, you probably need an update/patch.
//
#error "This file requires a newer version of the header UTILCLS.H" \
       "You need to apply an update/patch to your copy of C++Builder"
#endif
#include <olectl.h>
#include <ocidl.h>
#if defined(USING_ATLVCL) || defined(USING_ATL)
#if !defined(__TLB_NO_EVENT_WRAPPERS)
#include <atl/atlmod.h>
#endif
#endif


// *********************************************************************//
// Forward reference of some VCL types (to avoid including STDVCL.HPP)
// *********************************************************************//
namespace Stdvcl {class IStrings; class IStringsDisp;}
using namespace Stdvcl;
typedef TComInterface<IStrings> IStringsPtr;
typedef TComInterface<IStringsDisp> IStringsDispPtr;

namespace Mp2dmoe_tlb
{

// *********************************************************************//
// HelpString:
// Version:    1.0
// *********************************************************************//


// *********************************************************************//
// GUIDS declared in the TypeLibrary. Following prefixes are used:
//   Type Libraries     : LIBID_xxxx
//   CoClasses          : CLSID_xxxx
//   DISPInterfaces     : DIID_xxxx
//   Non-DISP interfaces: IID_xxxx
// *********************************************************************//
extern __declspec (package) const GUID LIBID_mp2dmoe;
extern __declspec (package) const GUID IID_IMp2Encoder;
extern __declspec (package) const GUID CLSID_Mp2Encoder;

// *********************************************************************//
// Forward declaration of types defined in TypeLibrary
// *********************************************************************//
interface DECLSPEC_UUID("{42DE0644-6C1B-4C79-ADE5-FEE766D74011}") IMp2Encoder;
typedef TComInterface<IMp2Encoder, &IID_IMp2Encoder> IMp2EncoderPtr;


// *********************************************************************//
// Declaration of CoClasses defined in Type Library
// (NOTE: Here we map each CoClass to its Default Interface)
//
// The LIBID_OF_ macro(s) map a LIBID_OF_CoClassName to the GUID of this
// TypeLibrary. It simplifies the updating of macros when CoClass name
// change.
// *********************************************************************//
typedef IMp2Encoder Mp2Encoder;
typedef IMp2EncoderPtr Mp2EncoderPtr;

#define LIBID_OF_Mp2Encoder (&LIBID_mp2dmoe)
// *********************************************************************//
// Interface: IMp2Encoder
// Flags:     (16) Hidden
// GUID:      {42DE0644-6C1B-4C79-ADE5-FEE766D74011}
// *********************************************************************//
interface IMp2Encoder  : public IUnknown
{
public:
};

#if !defined(__TLB_NO_INTERFACE_WRAPPERS)
// *********************************************************************//
// SmartIntf: TCOMIMp2Encoder
// Interface: IMp2Encoder
// *********************************************************************//
template <class T /* IMp2Encoder */ >
class TCOMIMp2EncoderT : public TComInterface<IMp2Encoder>, public TComInterfaceBase<IUnknown>
{
public:
  TCOMIMp2EncoderT() {}
  TCOMIMp2EncoderT(IMp2Encoder *intf, bool addRef = false) : TComInterface<IMp2Encoder>(intf, addRef) {}
  TCOMIMp2EncoderT(const TCOMIMp2EncoderT& src) : TComInterface<IMp2Encoder>(src) {}
  TCOMIMp2EncoderT& operator=(const TCOMIMp2EncoderT& src) { Bind(src, true); return *this;}


};
typedef TCOMIMp2EncoderT<IMp2Encoder> TCOMIMp2Encoder;

// *********************************************************************//
// SmartIntf: TCOMIMp2Encoder
// Interface: IMp2Encoder
// *********************************************************************//
// *********************************************************************//
// The following typedefs expose classes (named CoCoClassName) that
// provide static Create() and CreateRemote(LPWSTR machineName) methods
// for creating an instance of an exposed object. These functions can
// be used by client wishing to automate CoClasses exposed by this
// typelibrary.
// *********************************************************************//

// *********************************************************************//
// COCLASS DEFAULT INTERFACE CREATOR
// CoClass  : Mp2Encoder
// Interface: TCOMIMp2Encoder
// *********************************************************************//
typedef TCoClassCreatorT<TCOMIMp2Encoder, IMp2Encoder, &CLSID_Mp2Encoder, &IID_IMp2Encoder> CoMp2Encoder;
#endif  //   __TLB_NO_INTERFACE_WRAPPERS


};     // namespace Mp2dmoe_tlb

#if !defined(NO_IMPLICIT_NAMESPACE_USE)
using  namespace Mp2dmoe_tlb;
#endif

#pragma option pop

#endif // mp2dmoe_TLBH
