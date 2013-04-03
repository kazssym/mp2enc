/*
 * TestMp2EncoderImpl - unit tests for the Mp2EncoderImpl unit (implementation)
 * Copyright (C) 2013  Kaz Sasa
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
 * You should have received a copy of the GNU General Public License along with
 * this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <System.hpp>
#pragma hdrstop

#include <Mp2Encoder.h>
#include <dmo.h>
#include <System.Win.ComObj.hpp>
#include <TestFramework.hpp>

typedef DelphiInterface<IMediaObject> _di_IMediaObject;

class TTestTMp2EncoderImpl : public TTestCase {
__published:
    void __fastcall TestGetStreamCount();
    void __fastcall TestGetInputStreamInfo();
    void __fastcall TestGetOutputStreamInfo();
    void __fastcall TestGetInputType();
    void __fastcall TestGetOutputType();
    void __fastcall TestSetInputType();
    void __fastcall TestSetOutputType();
    void __fastcall TestGetInputCurrentType();
    void __fastcall TestGetOutputCurrentType();
    void __fastcall TestGetInputSizeInfo();
    void __fastcall TestGetOutputSizeInfo();
    void __fastcall TestGetInputMaxLatency();
    void __fastcall TestSetInputMaxLatency();
    void __fastcall TestFlush();
    void __fastcall TestDiscontinuity();
    void __fastcall TestAllocateStreamingResources();
    void __fastcall TestFreeStreamingResources();
    void __fastcall TestGetInputStatus();
    void __fastcall TestProcessInput();
    void __fastcall TestProcessOutput();
    void __fastcall TestLock();

public:
    __fastcall virtual TTestTMp2EncoderImpl(System::String name)
            : TTestCase(name) {
    }
    virtual void __fastcall SetUp();
    virtual void __fastcall TearDown();

private:
    _di_IMediaObject Mp2Encoder;
};

void __fastcall TTestTMp2EncoderImpl::SetUp() {
    TComObjectFactory *factory = // NO FILL
            ComClassManager()->GetFactoryFromClassID(CLSID_Mp2Encoder);
    if (!factory) {
        StopTests();
    }

    TComObject *object = factory->CreateComObject(0);
    if (!object || !object->GetInterface(Mp2Encoder)) {
        delete object;
        StopTests();
    }
}

void __fastcall TTestTMp2EncoderImpl::TearDown() {
    Mp2Encoder.Release();
}

void __fastcall TTestTMp2EncoderImpl::TestGetStreamCount() {
    DWORD input;
    DWORD output;
    Check(SUCCEEDED(Mp2Encoder->GetStreamCount(&input, &output)));
    CheckEquals(input, 1);
    CheckEquals(output, 1);
}

void __fastcall TTestTMp2EncoderImpl::TestGetInputStreamInfo() {
    DWORD flags;
    CheckEqualsHex(Mp2Encoder->GetInputStreamInfo(0, 0), E_POINTER);
    Check(SUCCEEDED(Mp2Encoder->GetInputStreamInfo(0, &flags)));
    CheckEqualsHex(flags,
            DMO_INPUT_STREAMF_WHOLE_SAMPLES |
            DMO_INPUT_STREAMF_FIXED_SAMPLE_SIZE);
    CheckEqualsHex(Mp2Encoder->GetInputStreamInfo(1, &flags),
            DMO_E_INVALIDSTREAMINDEX);
}

void __fastcall TTestTMp2EncoderImpl::TestGetOutputStreamInfo() {
    DWORD flags;
    CheckEqualsHex(Mp2Encoder->GetOutputStreamInfo(0, 0), E_POINTER);
    Check(SUCCEEDED(Mp2Encoder->GetOutputStreamInfo(0, &flags)));
    CheckEqualsHex(flags, DMO_OUTPUT_STREAMF_DISCARDABLE);
    CheckEqualsHex(Mp2Encoder->GetOutputStreamInfo(1, &flags),
            DMO_E_INVALIDSTREAMINDEX);
}

void __fastcall TTestTMp2EncoderImpl::TestGetInputType() {
    DMO_MEDIA_TYPE mt = {};
    Check(SUCCEEDED(Mp2Encoder->GetInputType(0, 0, 0)));
    Check(SUCCEEDED(Mp2Encoder->GetInputType(0, 0, &mt)));
    MoFreeMediaType(&mt);
    CheckEqualsHex(Mp2Encoder->GetInputType(1, 0, 0),
            DMO_E_INVALIDSTREAMINDEX);
}

void __fastcall TTestTMp2EncoderImpl::TestGetOutputType() {
    DMO_MEDIA_TYPE mt = {};
    Check(SUCCEEDED(Mp2Encoder->GetOutputType(0, 0, 0)));
    Check(SUCCEEDED(Mp2Encoder->GetOutputType(0, 0, &mt)));
    MoFreeMediaType(&mt);
    CheckEqualsHex(Mp2Encoder->GetOutputType(1, 0, 0),
            DMO_E_INVALIDSTREAMINDEX);
}

void __fastcall TTestTMp2EncoderImpl::TestSetInputType() {
    // HRESULT STDMETHODCALLTYPE SetInputType(DWORD dwInputStreamIndex, const DMO_MEDIA_TYPE *pmt, DWORD dwFlags)
}

void __fastcall TTestTMp2EncoderImpl::TestSetOutputType() {
    // HRESULT STDMETHODCALLTYPE SetOutputType(DWORD dwOutputStreamIndex, const DMO_MEDIA_TYPE *pmt, DWORD dwFlags)
}

void __fastcall TTestTMp2EncoderImpl::TestGetInputCurrentType() {
    // HRESULT STDMETHODCALLTYPE GetInputCurrentType(DWORD dwInputStreamIndex, DMO_MEDIA_TYPE *pmt)
}

void __fastcall TTestTMp2EncoderImpl::TestGetOutputCurrentType() {
    // HRESULT STDMETHODCALLTYPE GetOutputCurrentType(DWORD dwOutputStreamIndex, DMO_MEDIA_TYPE *pmt)
}

void __fastcall TTestTMp2EncoderImpl::TestGetInputSizeInfo() {
    // HRESULT STDMETHODCALLTYPE GetInputSizeInfo(DWORD dwInputStreamIndex, DWORD *pcbSize, DWORD *pcbMaxLookahead, DWORD *pcbAlignment)
}

void __fastcall TTestTMp2EncoderImpl::TestGetOutputSizeInfo() {
    // HRESULT STDMETHODCALLTYPE GetOutputSizeInfo(DWORD dwOutputStreamIndex, DWORD *pcbSize, DWORD *pcbAlignment)
}

void __fastcall TTestTMp2EncoderImpl::TestGetInputMaxLatency() {
    // HRESULT STDMETHODCALLTYPE GetInputMaxLatency(DWORD dwInputStreamIndex, REFERENCE_TIME *prtMaxLatency)
}

void __fastcall TTestTMp2EncoderImpl::TestSetInputMaxLatency() {
    // HRESULT STDMETHODCALLTYPE SetInputMaxLatency(DWORD dwInputStreamIndex, REFERENCE_TIME rtMaxLatency)
}

void __fastcall TTestTMp2EncoderImpl::TestFlush() {
    // HRESULT STDMETHODCALLTYPE Flush()
}

void __fastcall TTestTMp2EncoderImpl::TestDiscontinuity() {
    // HRESULT STDMETHODCALLTYPE Discontinuity(DWORD dwInputStreamIndex)
}

void __fastcall TTestTMp2EncoderImpl::TestAllocateStreamingResources() {
    // HRESULT STDMETHODCALLTYPE AllocateStreamingResources()
}

void __fastcall TTestTMp2EncoderImpl::TestFreeStreamingResources() {
    // HRESULT STDMETHODCALLTYPE FreeStreamingResources()
}

void __fastcall TTestTMp2EncoderImpl::TestGetInputStatus() {
    // HRESULT STDMETHODCALLTYPE GetInputStatus(DWORD dwInputStreamIndex, DWORD *dwFlags)
}

void __fastcall TTestTMp2EncoderImpl::TestProcessInput() {
    // HRESULT STDMETHODCALLTYPE ProcessInput(DWORD dwInputStreamIndex, IMediaBuffer *pBuffer, DWORD dwFlags, REFERENCE_TIME rtTimestamp, REFERENCE_TIME rtTimelength)
}

void __fastcall TTestTMp2EncoderImpl::TestProcessOutput() {
    // HRESULT STDMETHODCALLTYPE ProcessOutput(DWORD dwFlags, DWORD cOutputBufferCount, DMO_OUTPUT_DATA_BUFFER *pOutputBuffers, DWORD *pdwStatus)
}

void __fastcall TTestTMp2EncoderImpl::TestLock() {
    // HRESULT STDMETHODCALLTYPE Lock(LONG bLock)
}

static void registerTests() {
    Testframework::RegisterTest(TTestTMp2EncoderImpl::Suite());
}
#pragma startup registerTests 33
