//---------------------------------------------------------------------------

#ifndef encoderH
#define encoderH
//---------------------------------------------------------------------------

#define FIX_LOCK_NAME 1
#include <dmo.h>
#include <dmoimpl.h>
#undef FIX_LOCK_NAME

#define UUID(UUID) __declspec(uuid(UUID))
#define DEFUUID(Name, Type) const GUID Name = __uuidof(Type);

extern const GUID CLSID_MP2Encoder;

class ATL_NO_VTABLE UUID("{3FCD30F6-88FE-4A44-A518-1DBB0937DAE4}") CMP2Encoder
: public CComObjectRootEx<CComMultiThreadModel>,
  public CComCoClass<CMP2Encoder, &CLSID_MP2Encoder>,
  public IMediaObjectImpl<CMP2Encoder, 1, 1>
{
  friend class IMediaObjectImpl<CMP2Encoder, 1, 1>;
public:
  // <atlmod.h>
  //DECLARE_PROGID("mp2dmoe.MP2Encoder");
  DECLARE_DESCRIPTION("MP2 Encoder DMO");
  DECLARE_THREADING_MODEL(otBoth);
public:
  static HRESULT WINAPI UpdateRegistry(BOOL bRegister)
  {
    TComServerRegistrarT<CMP2Encoder>
      regObj(GetObjectCLSID(), 0, GetDescription());
    return regObj.UpdateRegistry(bRegister);
  }

  BEGIN_COM_MAP(CMP2Encoder)
  COM_INTERFACE_ENTRY(IMediaObject)
  END_COM_MAP()

private:
  // IMediaObjectImpl internal methods
  HRESULT InternalGetInputStreamInfo(DWORD dwInputStreamIndex, DWORD *pdwFlags);
  HRESULT InternalGetOutputStreamInfo(DWORD dwOutputStreamIndex, DWORD *pdwFlags);
  HRESULT InternalGetInputType(DWORD, DWORD, DMO_MEDIA_TYPE *);
  HRESULT InternalGetOutputType(DWORD, DWORD, DMO_MEDIA_TYPE *);
  HRESULT InternalCheckInputType(DWORD dwInputStreamIndex, const DMO_MEDIA_TYPE *pmt);
  HRESULT InternalCheckOutputType(DWORD dwOutputStreamIndex, const DMO_MEDIA_TYPE *pmt);
  HRESULT InternalGetInputSizeInfo(DWORD, DWORD *, DWORD *, DWORD *);
  HRESULT InternalGetOutputSizeInfo(DWORD, DWORD *, DWORD *);
  HRESULT InternalGetInputMaxLatency(DWORD, REFERENCE_TIME *);
  HRESULT InternalSetInputMaxLatency(DWORD, REFERENCE_TIME);
  HRESULT InternalFlush(void);
  HRESULT InternalDiscontinuity(DWORD);
  HRESULT InternalAllocateStreamingResources(void);
  HRESULT InternalFreeStreamingResources(void);
  HRESULT InternalAcceptingInput(DWORD dwInputStreamIndex);
  HRESULT InternalProcessInput(DWORD, IMediaBuffer *, DWORD, REFERENCE_TIME, REFERENCE_TIME);
  HRESULT InternalProcessOutput(DWORD, DWORD, DMO_OUTPUT_DATA_BUFFER *, DWORD *);
};

#endif
