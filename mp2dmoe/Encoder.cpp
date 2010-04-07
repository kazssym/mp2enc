//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Encoder.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)

DEFUUID(CLSID_MP2Encoder, CMP2Encoder)

/*
 * We implements our own as the general implementation lacks error checking.
 */
template<> HRESULT
TComServerRegistrarT<CMP2Encoder>::UpdateRegistry(bool bRegister)
{
  LONG error;
  if (bRegister)
  {
    static TCHAR szAutomation[] = _T(" /Automation");

    // Create registry entries
    //
    error = CreateRegKey(m_ClassKey, _T(""), m_Description);
    if (error != ERROR_SUCCESS)
      return HRESULT_FROM_WIN32(error);

    // ClassKey\ServerType
    //
    TAPtr<TCHAR> key(new TCHAR[_MAX_PATH]);
    lstrcpy(key, m_ClassKey);
    lstrcat(key, m_ServerType);

    // Copy over module name
    //
    TAPtr<TCHAR> mod(new TCHAR[_MAX_PATH + sizeof(szAutomation)]);
    lstrcpy(mod, m_ModuleName);

    // Make sure we have /Automation on EXE Automation Servers
    //
    if (_Module.m_bExe && _Module.m_bAutomationServer)
      lstrcat(mod, szAutomation);

    // Register ClassKey\ServerType
    //
    error = CreateRegKey(key, _T(""), mod);
    if (error != ERROR_SUCCESS)
      return HRESULT_FROM_WIN32(error);

    // Store Threading Model
    // Ambient relies on defines (a la CBuilder3)
    //
    LPCTSTR szThrdMdl = _T("ThreadingModel");
    if (IsEqual(CMP2Encoder::GetThreadModel(), otAmbientThreadModel))
    {
#if   defined(_ATL_SINGLE_THREADED)
      error = CreateRegKey(key, szThrdMdl, _T("Single"));
#elif defined(_ATL_BOTH_THREADED)
      error = CreateRegKey(key, szThrdMdl, _T("Both"));
#elif defined(_ATL_APARTMENT_THREADED)
      error = CreateRegKey(key, szThrdMdl, _T("Apartment"));
#elif defined(_ATL_NEUTRAL_THREADED)
      error = CreateRegKey(key, szThrdMdl, _T("Neutral"));
#elif defined(_ATL_FREE_THREADED)           // NOTE: Check _ATL_FREE_THREADED last
                                            //       because ATLBASE.H defines it for BOTH
      error = CreateRegKey(key, szThrdMdl, _T("Free"));
#else
      error = CreateRegKey(key, _T("NoThreadingModel"), _T(""));
#endif
    }
    else if (IsEqual(CMP2Encoder::GetThreadModel(), otSingle))
    {
      error = CreateRegKey(key, szThrdMdl, _T("Single"));
    }
    else if (IsEqual(CMP2Encoder::GetThreadModel(), otFree))
    {
      error = CreateRegKey(key, szThrdMdl, _T("Free"));
    }
    else if (IsEqual(CMP2Encoder::GetThreadModel(), otBoth))
    {
      error = CreateRegKey(key, szThrdMdl, _T("Both"));
    }
    else if (IsEqual(CMP2Encoder::GetThreadModel(), otNeutral))
    {
      error = CreateRegKey(key, szThrdMdl, _T("Neutral"));
    }
    else /* if (CMP2Encoder::GetThreadModel() == otApartment)  (Default case) */
    {
      error = CreateRegKey(key, szThrdMdl, _T("Apartment"));
    }
    if (error != ERROR_SUCCESS)
      return HRESULT_FROM_WIN32(error);

    // Register CLSID/ProgID
    //
    if (m_ProgID && *m_ProgID)
    {
      error = CreateRegKey(m_ProgID, _T(""), m_Description);
      if (error != ERROR_SUCCESS)
        return HRESULT_FROM_WIN32(error);

      TAPtr<TCHAR> buff(new TCHAR[_MAX_PATH]);
      lstrcpy(buff, m_ProgID);
      lstrcat(buff, _T("\\CLSID"));
      error = CreateRegKey(buff, _T(""), m_ClassIDstr);
      if (error != ERROR_SUCCESS)
        return HRESULT_FROM_WIN32(error);

      lstrcpy(buff, m_ClassKey);
      lstrcat(buff, _T("\\ProgID"));
      error = CreateRegKey(buff, _T(""), m_ProgID);
      if (error != ERROR_SUCCESS)
        return HRESULT_FROM_WIN32(error);
    }
  }
  else
  {
    // Remove registry entries
    //
    error = NukeRegKey(m_ClassKey);
    if (error != ERROR_SUCCESS)
      return HRESULT_FROM_WIN32(error);
    if (m_ProgID && *m_ProgID)
    {
      error = NukeRegKey(m_ProgID);
      if (error != ERROR_SUCCESS)
        return HRESULT_FROM_WIN32(error);
    }
  }
  return S_OK;
}

HRESULT WINAPI
CMP2Encoder::UpdateRegistry(BOOL bRegister)
{
  TComServerRegistrarT<CMP2Encoder> regObj(GetObjectCLSID(), 0, GetDescription());
  return regObj.UpdateRegistry(bRegister);
}

HRESULT
CMP2Encoder::InternalGetInputStreamInfo(DWORD dwInputStreamIndex, DWORD *pdwFlags)
{
  return E_NOTIMPL;
}

HRESULT
CMP2Encoder::InternalGetOutputStreamInfo(DWORD dwOutputStreamIndex, DWORD *pdwFlags)
{
  return E_NOTIMPL;
}

HRESULT
CMP2Encoder::InternalGetInputType(DWORD, DWORD, DMO_MEDIA_TYPE *)
{
  return E_NOTIMPL;
}

HRESULT
CMP2Encoder::InternalGetOutputType(DWORD, DWORD, DMO_MEDIA_TYPE *)
{
  return E_NOTIMPL;
}

HRESULT
CMP2Encoder::InternalCheckInputType(DWORD dwInputStreamIndex, const DMO_MEDIA_TYPE *pmt)
{
  return E_NOTIMPL;
}

HRESULT
CMP2Encoder::InternalCheckOutputType(DWORD dwOutputStreamIndex, const DMO_MEDIA_TYPE *pmt)
{
  return E_NOTIMPL;
}

HRESULT
CMP2Encoder::InternalGetInputSizeInfo(DWORD, DWORD *, DWORD *, DWORD *)
{
  return E_NOTIMPL;
}

HRESULT
CMP2Encoder::InternalGetOutputSizeInfo(DWORD, DWORD *, DWORD *)
{
  return E_NOTIMPL;
}

HRESULT
CMP2Encoder::InternalGetInputMaxLatency(DWORD, REFERENCE_TIME *)
{
  return E_NOTIMPL;
}

HRESULT
CMP2Encoder::InternalSetInputMaxLatency(DWORD, REFERENCE_TIME)
{
  return E_NOTIMPL;
}

HRESULT
CMP2Encoder::InternalFlush(void)
{
  return E_NOTIMPL;
}

HRESULT
CMP2Encoder::InternalDiscontinuity(DWORD)
{
  return E_NOTIMPL;
}

HRESULT
CMP2Encoder::InternalAllocateStreamingResources(void)
{
  return E_NOTIMPL;
}

HRESULT
CMP2Encoder::InternalFreeStreamingResources(void)
{
  return E_NOTIMPL;
}

HRESULT
CMP2Encoder::InternalAcceptingInput(DWORD dwInputStreamIndex)
{
  return E_NOTIMPL;
}

HRESULT
CMP2Encoder::InternalProcessInput(DWORD, IMediaBuffer *, DWORD, REFERENCE_TIME, REFERENCE_TIME)
{
  return E_NOTIMPL;
}

HRESULT
CMP2Encoder::InternalProcessOutput(DWORD, DWORD, DMO_OUTPUT_DATA_BUFFER *, DWORD *)
{
  return E_NOTIMPL;
}