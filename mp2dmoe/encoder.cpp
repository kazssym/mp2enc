//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "encoder.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)

DEFUUID(CLSID_MP2Encoder, CMP2Encoder)

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