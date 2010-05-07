//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Main.h"
#include "About.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TMainForm *MainForm;
//---------------------------------------------------------------------------
__fastcall TMainForm::TMainForm(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall
TMainForm::Exit1Click(TObject *Sender)
{
  Close();
}
//---------------------------------------------------------------------------

void __fastcall
TMainForm::About1Click(TObject *Sender)
{
  AboutBox->ShowModal();
}
//---------------------------------------------------------------------------

