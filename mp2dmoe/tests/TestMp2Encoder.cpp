#include <vcl.h>
#pragma hdrstop

#include <Initguid.h>
#include <Mp2.h>
#include <Dshow.h>
#include <TestFramework.hpp>

DEFGUID(CLSID_Mp2Encoder, CMp2Encoder)

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
private:
  IMediaObject *MediaObject;
};


void __fastcall
TTestMp2Encoder::SetUp()
{
  HRESULT hres = CoCreateInstance(CLSID_Mp2Encoder, 0, CLSCTX_INPROC_SERVER,
                                  IID_IMediaObject,
                                  reinterpret_cast<void **>(&MediaObject));
  if (FAILED(hres))
    StopTests(L"CoCreateInstance failed");
}

void __fastcall TTestMp2Encoder::TearDown()
{
  MediaObject->Release();
}


void __fastcall
TTestMp2Encoder::TestGetStreamCount(void)
{
  DWORD cInput, cOutput;
  HRESULT hres = MediaObject->GetStreamCount(&cInput, &cOutput);
  Check(SUCCEEDED(hres), L"GetStreamCount failed");
  Check(cInput == 1);
  Check(cOutput == 1);
}

void __fastcall
TTestMp2Encoder::TestGetInputStreamInfo(void)
{
  HRESULT hres;
  DWORD flags;
  hres = MediaObject->GetInputStreamInfo(0, &flags);
  Check(SUCCEEDED(hres));
  hres = MediaObject->GetInputStreamInfo(1, &flags);
  Check(hres == DMO_E_INVALIDSTREAMINDEX);
}

void __fastcall
TTestMp2Encoder::TestGetOutputStreamInfo(void)
{
  HRESULT hres;
  DWORD flags;
  hres = MediaObject->GetOutputStreamInfo(0, &flags);
  Check(SUCCEEDED(hres));
  hres = MediaObject->GetOutputStreamInfo(1, &flags);
  Check(hres == DMO_E_INVALIDSTREAMINDEX);
}

void __fastcall
TTestMp2Encoder::TestGetInputType(void)
{
  HRESULT hres;
  // Tests stream index 0
  hres = MediaObject->GetInputType(0, 0, 0);
  Check(SUCCEEDED(hres), L"GetInputType failed");
  // Gets media type actually.
  DMO_MEDIA_TYPE mt;
  hres = MediaObject->GetInputType(0, 0, &mt);
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
  hres = MediaObject->GetInputType(1, 0, 0);
  Check(hres == DMO_E_INVALIDSTREAMINDEX);
}

void __fastcall
TTestMp2Encoder::TestGetOutputType(void)
{
  DMO_MEDIA_TYPE mt;
  HRESULT hres = MediaObject->GetOutputType(0, 0, &mt);
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
