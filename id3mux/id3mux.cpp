//$$---- axlib proj source ---- (stAXLibProjectSource)
#include <vcl.h>
#pragma hdrstop
#include <atl\atlvcl.h>

#pragma package(smart_init)
#pragma link "vclnp.lib"
#pragma resource "*.tlb"
TComModule  Project1Module;
TComModule &_Module = Project1Module;

// ATL �I�u�W�F�N�g �}�b�v�� _ATL_OBJMAP_ENTRY �\����
// (���[�U�[�� OLE �T�[�o�[�̃I�u�W�F�N�g���L�q) �̔z���ێ����܂��BMAP ��
// ���[�U�[ �v���W�F�N�g�� CComModule-derived _Module �I�u�W�F�N�g�� Init ���\�b�h�o�R�œn����܂��B
//
BEGIN_OBJECT_MAP(ObjectMap)
END_OBJECT_MAP()

// �������܂��͏I�����ꂽ�X���b�h��v���Z�X�ɑ΂��� Windows �ɂ����
// �Ăяo���ꂽ�T�[�o�[�̃G���g�� �|�C���g�B
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

// _Module.Term �͒ʏ�A���[�U�[�� DllEntryPoint �� DLL_PROCESS_DETACH ����
// �Ăяo����܂��B�������A���̌��ʂƂ��ăV���b�g�_�E�� �V�[�P���X���s���ɂȂ邱�Ƃ�����܂��B
// ����� Exit ���[�`����ݒ肵�āA�N���[���A�b�v ���[�`��
// CComModule::Term ���Ăяo���܂��B
//
void ModuleTerm(void)
{
    _Module.Term();
}
#pragma exit ModuleTerm 63

// DLL ���g�p����Ȃ��Ȃ�A�A�����[�h���K�v���ǂ�����
// �₢���킹�邽�߂ɌĂяo���ꂽ�T�[�o�[�̃G���g�� �|�C���g�B
//
STDAPI __export DllCanUnloadNow(void)
{
    return (_Module.GetLockCount()==0) ? S_OK : S_FALSE;
}

// ���[�U�[�̃T�[�o�[����N���X �I�u�W�F�N�g���擾���邱�Ƃ� OLE �ɋ�����
// �T�[�o�[�̃G���g�� �|�C���g�B
//
STDAPI __export DllGetClassObject(REFCLSID rclsid, REFIID riid, LPVOID* ppv)
{
    return _Module.GetClassObject(rclsid, riid, ppv);
}

// ���W���[���ŃT�|�[�g���ꂽ���ׂẴN���X�ɑ΂��郌�W�X�g�� �G���g��
// ���쐬����悤�ɃT�[�o�[�Ɏw�����邽�ߌĂяo���ꂽ�T�[�o�[�̃G���g�� �|�C���g�B
//
STDAPI __export DllRegisterServer(void)
{
    return _Module.RegisterServer(TRUE);
}

// DllRegisterServer ��ʂ��č쐬���ꂽ���ׂẴ��W�X�g�� �G���g����
// �폜����悤�ɃT�[�o�[�Ɏw�����邽�ߌĂяo���ꂽ�T�[�o�[�̃G���g�� �|�C���g�B
//
STDAPI __export DllUnregisterServer(void)
{
    return _Module.UnregisterServer();
}
//---------------------------------------------------------------------------
