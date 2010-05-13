#include <vcl.h>
#pragma hdrstop

#include <initguid.h>

#include <mp2guid.h>
#include <dmo.h>
#include <DShow.h>
#include <TestFramework.hpp>
#include <ComObj.hpp>

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
  DelphiInterface<IMediaObject> MediaObject1;
};


void
__fastcall TTestMp2Encoder::SetUp()
{
  DelphiInterface<IUnknown> unknown1(CreateComObject(CLSID_Mp2Encoder));
  if (FAILED(unknown1->QueryInterface(&MediaObject1)))
    StopTests(L"Failed to instantiate an MP2 Encoder DMO");
}

void
__fastcall TTestMp2Encoder::TearDown()
{
  MediaObject1 = 0;
}


void __fastcall
TTestMp2Encoder::TestGetStreamCount(void)
{
  DWORD cInput, cOutput;
  HRESULT hres = MediaObject1->GetStreamCount(&cInput, &cOutput);
  Check(SUCCEEDED(hres), L"GetStreamCount failed");
  Check(cInput == 1);
  Check(cOutput == 1);
}

void __fastcall
TTestMp2Encoder::TestGetInputStreamInfo(void)
{
  HRESULT hres;
  DWORD flags;
  hres = MediaObject1->GetInputStreamInfo(0, &flags);
  Check(SUCCEEDED(hres));
  hres = MediaObject1->GetInputStreamInfo(1, &flags);
  Check(hres == DMO_E_INVALIDSTREAMINDEX);
}

void __fastcall
TTestMp2Encoder::TestGetOutputStreamInfo(void)
{
  HRESULT hres;
  DWORD flags;
  hres = MediaObject1->GetOutputStreamInfo(0, &flags);
  Check(SUCCEEDED(hres));
  hres = MediaObject1->GetOutputStreamInfo(1, &flags);
  Check(hres == DMO_E_INVALIDSTREAMINDEX);
}

void __fastcall
TTestMp2Encoder::TestGetInputType(void)
{
  HRESULT hres;
  // Tests stream index 0
  hres = MediaObject1->GetInputType(0, 0, 0);
  Check(SUCCEEDED(hres), L"GetInputType failed");
  // Gets media type actually.
  DMO_MEDIA_TYPE mt;
  hres = MediaObject1->GetInputType(0, 0, &mt);
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
  hres = MediaObject1->GetInputType(1, 0, 0);
  Check(hres == DMO_E_INVALIDSTREAMINDEX);
}

void __fastcall
TTestMp2Encoder::TestGetOutputType(void)
{
  DMO_MEDIA_TYPE mt;
  HRESULT hres = MediaObject1->GetOutputType(0, 0, &mt);
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
