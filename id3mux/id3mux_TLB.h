// ************************************************************************ //
// �x��
// -------
// ���̃t�@�C���Ő錾����Ă���^�̓^�C�v���C�u��������ǂݎ��ꂽ�f�[�^����
// ��������Ă��܂��B���̃^�C�v���C�u�����������I���邢�́i���̃^�C�v���C�u��
// �����Q�Ƃ��Ă���ق��̃^�C�v���C�u�����o�R�Łj�ԐړI�ɍăC���|�[�g���ꂽ
// ��C�^�C�v���C�u���C�u�����̕ҏW���Ƀ^�C�v���C�u�����G�f�B�^�́m�X�V�n�R�}
// ���h�����s�����ꍇ�C���̃t�@�C���̓��e�͂��ׂčĐ�������C�蓮�ŉ������ύX
// �͂��ׂĎ����܂��B
// ************************************************************************ //


// $Rev: 17252 $
// ���ɐ������ꂽ�^�C�v ���C�u�������� 2010/06/05 15:21:25 �ɐ������ꂽ�t�@�C���B

// ************************************************************************  //
// �^�C�v ���C�u����: E:\UserData\Kaz\Documents\RAD Studio\Projects\mp2enc\id3mux\id3mux (1)
// LIBID: {F503A583-0F48-4671-A45B-32D889F22DCF}
// LCID: 0
// �w���v�t�@�C��:
// �w���v������:
// �ˑ��֌W���X�g:
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
// C++ Builder �̃C���|�[�g|ActiveX �ƃC���|�[�g|�^�C�v���C�u�����@�\�܂��� TLIBIMP ���[�e�B���e�B
// ��萶�������R�[�h�� INCLUDE\VCL �f�B���N�g���ɂ���
// UTILCLS.H �w�b�_�[ �t�@�C���̓���o�[�W�����Ɉˑ����܂��B�t�@�C����
// �ȑO�̃o�[�W���������o���ꂽ�ꍇ�́A�X�V��p�b�`���K�v�ɂȂ邱�Ƃ�����܂��B
//
#error "���̃t�@�C���ł͐V�����o�[�W�����̃w�b�_�[ UTILCLS.H ���K�v�ł��B" \r
"C++ Builder ���X�V�܂��̓p�b�`��K�p����K�v������܂�"
#endif
#include <olectl.h>
#include <ocidl.h>
#if defined(USING_ATLVCL) || defined(USING_ATL)
#if !defined(__TLB_NO_EVENT_WRAPPERS)
#include <atl/atlmod.h>
#endif
#endif


// *********************************************************************//
// �ꕔ�� VCL �^�̑O���Q�� (STDVCL.HPP �̃C���N���[�h��������邽��)
// *********************************************************************//
namespace Stdvcl {class IStrings; class IStringsDisp;}
using namespace Stdvcl;
typedef TComInterface<IStrings> IStringsPtr;
typedef TComInterface<IStringsDisp> IStringsDispPtr;

namespace Id3mux_tlb
{

// *********************************************************************//
// �w���v������:
// �o�[�W����: 1.0
// *********************************************************************//


// *********************************************************************//
// �^�C�v���C�u�����Ő錾���ꂽ GUID���̃v���t�B�b�N�X���g�p����܂�:
// �^�C�v ���C�u����      : LIBID_xxxx
//   CoClasses          : CLSID_xxxx
// �f�B�X�p�b�` �C���^�[�t�F�C�X: DIID_xxxx
// ��f�B�X�p�b�` �C���^�[�t�F�C�X: IID_xxxx
// *********************************************************************//
extern __declspec (package) const GUID LIBID_id3mux;
extern __declspec (package) const GUID IID_IConfigId3Mux;
// *********************************************************************//

// �^�C�v���C�u�����Ő錾�����O���Q��

// *********************************************************************//

interface DECLSPEC_UUID("{F82FF012-2B6A-4CB8-8989-6DCB5A6EB49A}") IConfigId3Mux;
typedef TComInterface<IConfigId3Mux, &IID_IConfigId3Mux> IConfigId3MuxPtr;

// *********************************************************************//
// �C���^�[�t�F�C�X: IConfigId3Mux
// �t���O: (320) Dual OleAutomation
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
// �t���O:     (320) Dual OleAutomation
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
// �t���O:     (320) Dual OleAutomation
// GUID:      {F82FF012-2B6A-4CB8-8989-6DCB5A6EB49A}
// *********************************************************************//
#endif  //   __TLB_NO_INTERFACE_WRAPPERS


};     // namespace Id3mux_tlb

#if !defined(NO_IMPLICIT_NAMESPACE_USE)
using  namespace Id3mux_tlb;
#endif

#pragma option pop

#endif // id3mux_TLBH

