// ************************************************************************ //
// �x��
// -------
// ���̃t�@�C���Ő錾����Ă���^�̓^�C�v ���C�u��������ǂݎ��ꂽ�f�[�^����
// ��������Ă��܂��B���̃^�C�v ���C�u�����������I���邢�́i���̃^�C�v ���C�u��
// �����Q�Ƃ��Ă���ق��̃^�C�v ���C�u�����o�R�Łj�ԐړI�ɍăC���|�[�g���ꂽ
// ��A�^�C�v ���C�u���C�u�����̕ҏW���Ƀ^�C�v ���C�u���� �G�f�B�^�́m�X�V�n�R�}
// ���h�����s�����ꍇ�A���̃t�@�C���̓��e�͂��ׂčĐ�������A�蓮�ŉ������ύX
// �͂��ׂĎ����܂��B
// ************************************************************************ //

// $Rev: 34747 $
// ���ɐ������ꂽ�^�C�v ���C�u�������� 2012/06/02 16:53:38 �ɐ������ꂽ�t�@�C���B

// ************************************************************************  //
// �^�C�v ���C�u����: E:\UserData\Kaz\Documents\RAD Studio\Projects\mp2enc\mp2dmoe\mp2dmoe (1)
// LIBID: {67FC4F6A-1F74-41AE-8F59-B0A174D394DF}
// LCID: 0
// �w���v�t�@�C��:
// �w���v������:
// �ˑ��֌W���X�g:
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
// C++ Builder �̃C���|�[�g|ActiveX �ƃC���|�[�g|�^�C�v ���C�u�����@�\�܂��� TLIBIMP ���[�e�B���e�B
// ��萶�������R�[�h�� INCLUDE\VCL �f�B���N�g���ɂ���
// UTILCLS.H �w�b�_�[ �t�@�C���̓���o�[�W�����Ɉˑ����܂��B�t�@�C����
// �ȑO�̃o�[�W���������o���ꂽ�ꍇ�́A�X�V��p�b�`���K�v�ɂȂ邱�Ƃ�����܂��B
//
#error "���̃t�@�C���ł͐V�����o�[�W�����̃w�b�_�[ UTILCLS.H ���K�v�ł��B" \
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

namespace Mp2dmoe_tlb
{

// *********************************************************************//
// �w���v������:
// �o�[�W����: 1.0
// *********************************************************************//

// *********************************************************************//
// �^�C�v ���C�u�����Ő錾���ꂽ GUID���̃v���t�B�b�N�X���g�p����܂�:
// �^�C�v ���C�u����      : LIBID_xxxx
//   CoClasses          : CLSID_xxxx
// �f�B�X�p�b�` �C���^�[�t�F�C�X: DIID_xxxx
// ��f�B�X�p�b�` �C���^�[�t�F�C�X: IID_xxxx
// *********************************************************************//
extern __declspec (package) const GUID LIBID_mp2dmoe;
};     // namespace Mp2dmoe_tlb

#if !defined(NO_IMPLICIT_NAMESPACE_USE)
using  namespace Mp2dmoe_tlb;
#endif

#pragma option pop

#endif // mp2dmoe_TLBH

