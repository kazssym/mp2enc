#include <vcl.h>
#pragma hdrstop

#include <initguid.h>

#include <mp2guid.h>
#include <dmo.h>
#include <DShow.h>
#include <TestFramework.hpp>
#include <ComObj.hpp>

// Specifies the libraries to link.
#pragma link "msdmo.lib"
#pragma link "quartz.lib"

/**
 * Creates a COM object instance.  This version takes a typed pointer.
 */
template<class Interface>
inline HRESULT
STDAPICALLTYPE CoCreateInstance(REFCLSID rclsid, IUnknown *pUnkOuter,
                                DWORD dwClsContext, Interface **pp)
{
    return CoCreateInstance(rclsid, pUnkOuter, dwClsContext, __uuidof (Interface),
                            reinterpret_cast<void **>(pp));
}

inline UnicodeString
__fastcall ErrorText(HRESULT hr)
{
    TCHAR text[128];
    AMGetErrorText(hr, text, 128);
    return UnicodeString(text);
}

class TTestMp2Encoder : public TTestCase
{
public:
    __fastcall virtual TTestMp2Encoder(System::String name) : TTestCase(name) {}
    virtual void __fastcall SetUp();
    virtual void __fastcall TearDown();
__published:
    void __fastcall TestGetStreamCount();
    void __fastcall TestGetInputStreamInfo();
    void __fastcall TestGetOutputStreamInfo();
    void __fastcall TestGetInputType();
    void __fastcall TestGetOutputType();
    void __fastcall TestSetInputType();
    void __fastcall TestSetOutputType();
private:
    DelphiInterface<IMediaObject> Encoder;
};


void
__fastcall TTestMp2Encoder::SetUp()
{
    HRESULT hr;
    hr = CoCreateInstance(CLSID_Mp2Encoder, 0, CLSCTX_INPROC_SERVER, &Encoder);
    if (FAILED(hr))
      StopTests(ErrorText(hr));
}

void
__fastcall TTestMp2Encoder::TearDown()
{
    Encoder = 0;
}


void __fastcall
TTestMp2Encoder::TestGetStreamCount(void)
{
  DWORD cInput, cOutput;
  HRESULT hres = Encoder->GetStreamCount(&cInput, &cOutput);
  Check(SUCCEEDED(hres), L"GetStreamCount failed");
  Check(cInput == 1);
  Check(cOutput == 1);
}

void __fastcall
TTestMp2Encoder::TestGetInputStreamInfo(void)
{
  HRESULT hres;
  DWORD flags;
  hres = Encoder->GetInputStreamInfo(0, &flags);
  Check(SUCCEEDED(hres));
  hres = Encoder->GetInputStreamInfo(1, &flags);
  Check(hres == DMO_E_INVALIDSTREAMINDEX);
}

void __fastcall
TTestMp2Encoder::TestGetOutputStreamInfo(void)
{
  HRESULT hres;
  DWORD flags;
  hres = Encoder->GetOutputStreamInfo(0, &flags);
  Check(SUCCEEDED(hres));
  hres = Encoder->GetOutputStreamInfo(1, &flags);
  Check(hres == DMO_E_INVALIDSTREAMINDEX);
}

void __fastcall
TTestMp2Encoder::TestGetInputType(void)
{
  HRESULT hres;
  // Tests stream index 0
  hres = Encoder->GetInputType(0, 0, 0);
  Check(SUCCEEDED(hres), L"GetInputType failed");
  // Gets media type actually.
  DMO_MEDIA_TYPE mt;
  hres = Encoder->GetInputType(0, 0, &mt);
  Check(SUCCEEDED(hres), L"GetInputType failed");
  try
  {
    Check(mt.majortype == MEDIATYPE_Audio);
    Check(mt.subtype == MEDIASUBTYPE_PCM);
    Check(mt.formattype == FORMAT_WaveFormatEx);
  }
  __finally
  {
    MoFreeMediaType(&mt);
  }
  // Tests stream index 1
  hres = Encoder->GetInputType(1, 0, 0);
  Check(hres == DMO_E_INVALIDSTREAMINDEX);
}

void __fastcall
TTestMp2Encoder::TestGetOutputType(void)
{
  DMO_MEDIA_TYPE mt;
  HRESULT hres = Encoder->GetOutputType(0, 0, &mt);
  Check(SUCCEEDED(hres), L"GetOutputType failed");
  try
  {
    Check(mt.majortype == MEDIATYPE_Audio);
    Check(mt.subtype == MEDIASUBTYPE_MPEG1Payload || mt.subtype == MEDIASUBTYPE_MPEG2_AUDIO);
    Check(mt.formattype == FORMAT_WaveFormatEx);
  }
  __finally
  {
    MoFreeMediaType(&mt);
  }
}

void
__fastcall TTestMp2Encoder::TestSetInputType()
{
    HRESULT hr;
    DMO_MEDIA_TYPE mt;
    hr = Encoder->GetInputType(0, 0, &mt);
    if (SUCCEEDED(hr))
    {
        try
        {
            hr = Encoder->SetInputType(0, &mt, 0);
            Check(SUCCEEDED(hr), ErrorText(hr));
        }
        __finally
        {
            MoFreeMediaType(&mt);
        }
    }
}

void
__fastcall TTestMp2Encoder::TestSetOutputType()
{
    HRESULT hr;
    DMO_MEDIA_TYPE mt;
    hr = Encoder->GetOutputType(0, 0, &mt);
    if (SUCCEEDED(hr))
    {
        try
        {
            hr = Encoder->SetOutputType(0, &mt, 0);
            Check(SUCCEEDED(hr), ErrorText(hr));
        }
        __finally
        {
            MoFreeMediaType(&mt);
        }
    }
}

static void registerTests()
{
  _di_ITestSuite iSuite;
  TTestSuite* testSuite = new TTestSuite("Testing Mp2Encoder");
  if (testSuite->GetInterface(iSuite)) {
    testSuite->AddTests(__classid(TTestMp2Encoder));
    Testframework::RegisterTest(iSuite);
  } else {
    delete testSuite;
  }
}
#pragma startup registerTests 33


/* [For debug purposes only - To be removed soon!!]
GenerateHeaderComment=true
DefaultExtension=.cpp
FileName=E:\UserData\Kaz\Documents\RAD Studio\Projects\mp2enc\mp2dmoe\tests\TestHelper.cpp
TestFramework=DUnit / C++ Win32
OutputPersonality=CPlusPlusBuilder.Personality
TestProject=E:\UserData\Kaz\Documents\RAD Studio\Projects\mp2enc\mp2dmoe\tests\mp2dmoeTests.cbproj
UnitUnderTest=E:\UserData\Kaz\Documents\RAD Studio\Projects\mp2enc\mp2dmoe\tests\Helper.h
NameOfUnitUnderTest=Helper.h
TestCaseBaseClass=TTestCase
TestCasePrefix=Test
UnitName=TestHelper
Namespace=TestHelper
TestClasses=
  <0>
    Name=TTestHelper
    Methods=
      <0>
        Name=CreateInstance
        Signature=void CreateInstance(void)
      <1>
        Name=ReleaseInstance
        Signature=void ReleaseInstance(void)
TestClass=
Method=
*/
