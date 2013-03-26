/*
 * Mp2EncoderImpl - C++ class for Mp2Encoder (implementation)
 * Copyright (C) 2010-2013  Kaz Sasa
 *
 * This program is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the Free
 * Software Foundation, either version 3 of the License, or (at your option)
 * any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <vcl.h>
#pragma hdrstop

#include <initguid.h>
#include "Mp2EncoderImpl.h"

#include "Mp2Encoder.h"
#include <System.Win.ComServ.hpp>

static void CreateFactory() {
    new TComObjectFactory(ComServer, __classid(TMp2EncoderImpl),
            CLSID_Mp2Encoder, L"TMp2EncoderImpl", L"MP2 Encoder DMO",
            ciMultiInstance, Comobj::tmBoth);
}
#pragma startup CreateFactory 64

// TMp2EncoderImpl implementation

__fastcall TMp2EncoderImpl::TMp2EncoderImpl() {
}

__fastcall TMp2EncoderImpl::TMp2EncoderImpl
        (const _di_IInterface Controller)
        : inherited(Controller) {
}

__fastcall TMp2EncoderImpl::TMp2EncoderImpl(TComObjectFactory *Factory,
        const _di_IInterface Controller)
        : inherited(Factory, Controller) {
}

STDMETHODIMP TMp2EncoderImpl::GetStreamCount(DWORD *pcInputStreams,
        DWORD *pcOutputStreams) {
    return E_NOTIMPL;
}

STDMETHODIMP TMp2EncoderImpl::GetInputStreamInfo(DWORD dwInputStreamIndex,
        DWORD *pdwFlags) {
    return E_NOTIMPL;
}

STDMETHODIMP TMp2EncoderImpl::GetOutputStreamInfo
        (DWORD dwOutputStreamIndex, DWORD *pdwFlags) {
    return E_NOTIMPL;
}

STDMETHODIMP TMp2EncoderImpl::GetInputType(DWORD dwInputStreamIndex,
        DWORD dwTypeIndex, DMO_MEDIA_TYPE *pmt) {
    return E_NOTIMPL;
}

STDMETHODIMP TMp2EncoderImpl::GetOutputType(DWORD dwOutputStreamIndex,
        DWORD dwTypeIndex, DMO_MEDIA_TYPE *pmt){
    return E_NOTIMPL;
}

STDMETHODIMP TMp2EncoderImpl::SetInputType(DWORD dwInputStreamIndex,
        const DMO_MEDIA_TYPE *pmt, DWORD dwFlags){
    return E_NOTIMPL;
}

STDMETHODIMP TMp2EncoderImpl::SetOutputType(DWORD dwOutputStreamIndex,
        const DMO_MEDIA_TYPE *pmt, DWORD dwFlags){
    return E_NOTIMPL;
}

STDMETHODIMP TMp2EncoderImpl::GetInputCurrentType(DWORD dwInputStreamIndex,
        DMO_MEDIA_TYPE *pmt){
    return E_NOTIMPL;
}

STDMETHODIMP TMp2EncoderImpl::GetOutputCurrentType(DWORD dwOutputStreamIndex,
        DMO_MEDIA_TYPE *pmt){
    return E_NOTIMPL;
}

STDMETHODIMP TMp2EncoderImpl::GetInputSizeInfo(DWORD dwInputStreamIndex,
        DWORD *pcbSize, DWORD *pcbMaxLookahead, DWORD *pcbAlignment) {
    return E_NOTIMPL;
}

STDMETHODIMP TMp2EncoderImpl::GetOutputSizeInfo(DWORD dwOutputStreamIndex,
        DWORD *pcbSize, DWORD *pcbAlignment) {
    return E_NOTIMPL;
}

STDMETHODIMP TMp2EncoderImpl::GetInputMaxLatency(DWORD dwInputStreamIndex,
        REFERENCE_TIME *prtMaxLatency){
    return E_NOTIMPL;
}

STDMETHODIMP TMp2EncoderImpl::SetInputMaxLatency(DWORD dwInputStreamIndex,
        REFERENCE_TIME rtMaxLatency){
    return E_NOTIMPL;
}

STDMETHODIMP TMp2EncoderImpl::Flush(){
    return E_NOTIMPL;
}

STDMETHODIMP TMp2EncoderImpl::Discontinuity(DWORD dwInputStreamIndex) {
    return E_NOTIMPL;
}

STDMETHODIMP TMp2EncoderImpl::AllocateStreamingResources(){
    return E_NOTIMPL;
}

STDMETHODIMP TMp2EncoderImpl::FreeStreamingResources(){
    return E_NOTIMPL;
}

STDMETHODIMP TMp2EncoderImpl::GetInputStatus(DWORD dwInputStreamIndex,
        DWORD *dwFlags){
    return E_NOTIMPL;
}

STDMETHODIMP TMp2EncoderImpl::ProcessInput(DWORD dwInputStreamIndex,
        IMediaBuffer *pBuffer, DWORD dwFlags, REFERENCE_TIME rtTimestamp,
        REFERENCE_TIME rtTimelength){
    return E_NOTIMPL;
}

STDMETHODIMP TMp2EncoderImpl::ProcessOutput(DWORD dwFlags,
        DWORD cOutputBufferCount, DMO_OUTPUT_DATA_BUFFER *pOutputBuffers,
        DWORD *pdwStatus){
    return E_NOTIMPL;
}

STDMETHODIMP TMp2EncoderImpl::Lock(LONG bLock){
    return E_NOTIMPL;
}
