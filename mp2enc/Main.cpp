//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Main.h"
#include "About.h"
#include <ComObj.hpp>

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TMainForm *MainForm;
//---------------------------------------------------------------------------

__fastcall TMainForm::TMainForm(TComponent* Owner)
: TForm(Owner)
{
}

void
__fastcall TMainForm::OpenFile(const UnicodeString Name)
{
  DelphiInterface<IUnknown> unknown1(CreateComObject(CLSID_FilterGraph));
  if (unknown1 == 0 || FAILED(unknown1->QueryInterface(&GraphBuilder1)))
  {
    ShowMessage(L"Failed to instantiate a filter graph");
    return;
  }

  // @todo Add source filter.

  Close1->Enabled = true;
  Encode1->Enabled = true;
  EncodeAs1->Enabled = true;
}

void
__fastcall TMainForm::CloseFile(void)
{
  GraphBuilder1 = 0;

  Close1->Enabled = false;
  Encode1->Enabled = false;
  EncodeAs1->Enabled = false;
}

//---------------------------------------------------------------------------
void
__fastcall TMainForm::Exit1Click(TObject *Sender)
{
  CloseFile();
  Close();
}
//---------------------------------------------------------------------------
void
__fastcall TMainForm::Open1Click(TObject *Sender)
{
  if (OpenDialog1->Execute(Handle))
  {
    OpenFile(OpenDialog1->FileName);
  }
}
//---------------------------------------------------------------------------

void
__fastcall TMainForm::Close1Click(TObject *Sender)
{
  CloseFile();
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::Encode1Click(TObject *Sender)
{
  //
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::EncodeAs1Click(TObject *Sender)
{
  SaveDialog1->Execute(Handle);
}
//---------------------------------------------------------------------------

void
__fastcall TMainForm::About1Click(TObject *Sender)
{
  AboutBox->ShowModal();
}
//---------------------------------------------------------------------------

