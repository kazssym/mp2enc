//---------------------------------------------------------------------------

#ifndef MainH
#define MainH 1

#include <DShow.h>

//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Dialogs.hpp>
#include <Menus.hpp>
//---------------------------------------------------------------------------
class TMainForm : public TForm
{
__published:	// IDE 管理のコンポーネント
  TMainMenu *MainMenu1;
  TMenuItem *File1;
  TMenuItem *Open1;
  TMenuItem *Close1;
  TMenuItem *N1;
  TMenuItem *Exit1;
  TMenuItem *Help1;
  TMenuItem *About1;
  TMenuItem *N2;
  TMenuItem *Encode1;
  TMenuItem *EncodeAs1;
  TOpenDialog *OpenDialog1;
  TSaveDialog *SaveDialog1;
  void __fastcall Exit1Click(TObject *Sender);
  void __fastcall Open1Click(TObject *Sender);
  void __fastcall Close1Click(TObject *Sender);
  void __fastcall About1Click(TObject *Sender);
  void __fastcall Encode1Click(TObject *Sender);
  void __fastcall EncodeAs1Click(TObject *Sender);
private:	// ユーザー宣言
public:		// ユーザー宣言
  __fastcall TMainForm(TComponent* Owner);
protected:
  void __fastcall OpenFile(const UnicodeString Name);
  void __fastcall CloseFile(void);
private:
  DelphiInterface<IGraphBuilder> GraphBuilder1;
};
//---------------------------------------------------------------------------
extern PACKAGE TMainForm *MainForm;
//---------------------------------------------------------------------------
#endif
