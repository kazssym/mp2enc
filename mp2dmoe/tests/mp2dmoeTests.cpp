//---------------------------------------------------------------------------
// DUnit Project File.
//   Entry point of C++ project using DUnit framework.
//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include <GUITestRunner.hpp>


WINAPI wWinMain(HINSTANCE, HINSTANCE, LPWSTR, int)
{
  try
  {
     Application->Initialize();
     Guitestrunner::RunRegisteredTests();
  }
  catch (Exception &exception)
  {
     Application->ShowException(&exception);
  }
  catch (...)
  {
     try
     {
       throw Exception("");
     }
     catch (Exception &exception)
     {
       Application->ShowException(&exception);
     }
  }
  return 0;
}

