
#include <vcl.h>
#pragma hdrstop
#include <ComServ.hpp>
#include <axbase.h>

#pragma package(smart_init)
#pragma link "ComServ.obj"



// -----------------------------------------------------------------------------
// �������܂��͏I�����ꂽ�X���b�h��v���Z�X�ɑ΂��� Windows �ɂ����
// �Ăяo���ꂽ�T�[�o�[�̃G���g�� �|�C���g�B
//
// -----------------------------------------------------------------------------
int WINAPI DllEntryPoint(HINSTANCE hinst, unsigned long reason, void*)
{
    return TRUE;
}


// -----------------------------------------------------------------------------
// DLL ���g�p����Ȃ��Ȃ�A�ǂݍ��݉������K�v���ǂ�����
// �₢���킹�邽�߂ɌĂяo���ꂽ�T�[�o�[�̃G���g�� �|�C���g�B
// -----------------------------------------------------------------------------
STDAPI __export DllCanUnloadNow(void)
{
    Comserv::TComServer* comserver = Comserv::GetComServer();
    return (!comserver ||
            ((comserver->ObjectCount /* + comserver->FactoryCount */) == 0)) ?
            S_OK : S_FALSE;
}

// -----------------------------------------------------------------------------
// ���[�U�[�̃T�[�o�[����N���X �I�u�W�F�N�g���擾���邱�Ƃ� OLE �ɋ�����
// �T�[�o�[�̃G���g�� �|�C���g�B
// -----------------------------------------------------------------------------
STDAPI __export DllGetClassObject(REFCLSID rclsid, REFIID riid, LPVOID* ppv)
{
    Comobj::TComObjectFactory* Factory = Comobj::ComClassManager()->GetFactoryFromClassID(rclsid);
    if (Factory)
    {
      if (Factory->GetInterface(riid, ppv))
        return S_OK;
      else
        return E_NOINTERFACE;
    }
    else
    {
      *ppv = 0;
      return CLASS_E_CLASSNOTAVAILABLE;
    }
}

// -----------------------------------------------------------------------------
// ���W���[���ŃT�|�[�g���ꂽ���ׂẴN���X�ɑ΂��郌�W�X�g�� �G���g��
// ���쐬����悤�ɃT�[�o�[�Ɏw�����邽�ߌĂяo���ꂽ�T�[�o�[�̃G���g�� �|�C���g�B
// -----------------------------------------------------------------------------
STDAPI __export DllRegisterServer(void)
{
    Comserv::TComServer* comserver = Comserv::GetComServer();
    if (comserver)
    {
        try
        {
            comserver->LoadTypeLib();
            comserver->UpdateRegistry(true);
            return S_OK;
        }
        catch(...)
        {
            return E_FAIL;
        }
    }
    else
    {
        return E_FAIL;
    }
}

// -----------------------------------------------------------------------------
// DllRegisterServer ��ʂ��č쐬���ꂽ���ׂẴ��W�X�g�� �G���g����
// �폜����悤�ɃT�[�o�[�Ɏw�����邽�ߌĂяo���ꂽ�T�[�o�[�̃G���g�� �|�C���g�B
// -----------------------------------------------------------------------------
STDAPI __export DllUnregisterServer(void)
{
    Comserv::TComServer* comserver = Comserv::GetComServer();
    if (comserver)
    {
        try
        {
            comserver->LoadTypeLib();
            comserver->UpdateRegistry(false);
            return S_OK;
        }
        catch(...)
        {
            return E_FAIL;
        }
    }
    else
    {
        return E_FAIL;
    }
}

// ------------------------------------------------------------------------------
// �T�[�o�[ �C���X�g�[��/�Z�b�g�A�b�v�̃G���g�� �|�C���g�B'���[�U�[���Ƃ�' �o�^�Ɏg�p
// "regsvr32 /n /i:user [/u] axlibrary.dll" �̌Ăяo����ʂ��ċN��
// ------------------------------------------------------------------------------
STDAPI __export DllInstall(BOOL bInstall, LPCWSTR pszCmdLine)
{
    Comserv::TComServer* comserver = Comserv::GetComServer();
    if (comserver)
    {
        bool savePerUser = comserver->PerUserRegistration;
        if (pszCmdLine && !Sysutils::StrIComp(pszCmdLine, L"user"))
            comserver->PerUserRegistration = true;
        else
            comserver->PerUserRegistration = false;
        HRESULT result = E_FAIL;
        if (bInstall)
        {
            result = DllRegisterServer();
            if (result == E_FAIL)
                DllUnregisterServer();
        }
        else
            result = DllUnregisterServer();
        comserver->PerUserRegistration = savePerUser;
        return result;
    }
    else
    {
        return E_FAIL;
    }
}




