/*
 * Mp2EncoderImpl - C++ class for Mp2Encoder (interface)
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

#ifndef Mp2EncoderImplH
#define Mp2EncoderImplH

#include <dmo.h>
#include <axbase.h>

#if __cplusplus < 201103L
#define override
#endif

namespace Mp2encoderimpl {
    /*
     * Mp2Encoder implementation.
     */
    class DAX_COM_CLASS TMp2EncoderImpl : public TComObject, public IInterface,
            public IMediaObject {
        typedef TComObject inherited;

    public:
        __fastcall TMp2EncoderImpl();
        __fastcall TMp2EncoderImpl(const System::_di_IInterface Controller);
        __fastcall TMp2EncoderImpl(System::Win::Comobj::TComObjectFactory *Factory,
                const System::_di_IInterface Controller);

        // IMediaObject methods
        virtual HRESULT STDMETHODCALLTYPE GetStreamCount(DWORD *pcInputStreams,
                DWORD *pcOutputStreams) override;
        virtual HRESULT STDMETHODCALLTYPE GetInputStreamInfo
                (DWORD dwInputStreamIndex, DWORD *pdwFlags) override;
        virtual HRESULT STDMETHODCALLTYPE GetOutputStreamInfo
                (DWORD dwOutputStreamIndex, DWORD *pdwFlags) override;
        virtual HRESULT STDMETHODCALLTYPE GetInputType(DWORD dwInputStreamIndex,
                DWORD dwTypeIndex, DMO_MEDIA_TYPE *pmt) override;
        virtual HRESULT STDMETHODCALLTYPE GetOutputType
                (DWORD dwOutputStreamIndex, DWORD dwTypeIndex,
                DMO_MEDIA_TYPE *pmt) override;
        virtual HRESULT STDMETHODCALLTYPE SetInputType(DWORD dwInputStreamIndex,
                const DMO_MEDIA_TYPE *pmt, DWORD dwFlags) override;
        virtual HRESULT STDMETHODCALLTYPE SetOutputType
                (DWORD dwOutputStreamIndex, const DMO_MEDIA_TYPE *pmt,
                DWORD dwFlags) override;
        virtual HRESULT STDMETHODCALLTYPE GetInputCurrentType
                (DWORD dwInputStreamIndex, DMO_MEDIA_TYPE *pmt) override;
        virtual HRESULT STDMETHODCALLTYPE GetOutputCurrentType
                (DWORD dwOutputStreamIndex, DMO_MEDIA_TYPE *pmt) override;
        virtual HRESULT STDMETHODCALLTYPE GetInputSizeInfo
                (DWORD dwInputStreamIndex, DWORD *pcbSize,
                DWORD *pcbMaxLookahead, DWORD *pcbAlignment) override;
        virtual HRESULT STDMETHODCALLTYPE GetOutputSizeInfo
                (DWORD dwOutputStreamIndex, DWORD *pcbSize, DWORD *pcbAlignment)
                override;
        virtual HRESULT STDMETHODCALLTYPE GetInputMaxLatency
                (DWORD dwInputStreamIndex, REFERENCE_TIME *prtMaxLatency)
                override;
        virtual HRESULT STDMETHODCALLTYPE SetInputMaxLatency
                (DWORD dwInputStreamIndex, REFERENCE_TIME rtMaxLatency)
                override;
        virtual HRESULT STDMETHODCALLTYPE Flush() override;
        virtual HRESULT STDMETHODCALLTYPE Discontinuity
                (DWORD dwInputStreamIndex) override;
        virtual HRESULT STDMETHODCALLTYPE AllocateStreamingResources() override;
        virtual HRESULT STDMETHODCALLTYPE FreeStreamingResources() override;
        virtual HRESULT STDMETHODCALLTYPE GetInputStatus
                (DWORD dwInputStreamIndex, DWORD *dwFlags) override;
        virtual HRESULT STDMETHODCALLTYPE ProcessInput(DWORD dwInputStreamIndex,
                IMediaBuffer *pBuffer, DWORD dwFlags,
                REFERENCE_TIME rtTimestamp, REFERENCE_TIME rtTimelength)
                override;
        virtual HRESULT STDMETHODCALLTYPE ProcessOutput(DWORD dwFlags,
                DWORD cOutputBufferCount,
                DMO_OUTPUT_DATA_BUFFER *pOutputBuffers, DWORD *pdwStatus)
                override;
        virtual HRESULT STDMETHODCALLTYPE Lock(LONG bLock) override;

        DAX_IMPL_IUNKNOWN(inherited);
    };
}
using namespace Mp2encoderimpl;

#endif
