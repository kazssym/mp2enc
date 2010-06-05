/*
 * MP2 Encoder front-end.
 * Copyright (C) 2010 Kaz Sasa.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef MainH
#define MainH 1

#include <dshow.h>

#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Dialogs.hpp>
#include <Menus.hpp>
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TMainForm : public TForm
{
__published:	// IDE 管理のコンポーネント
    TMainMenu *MainMenu1;
    TMenuItem *File1;
    TMenuItem *Open1;
    TMenuItem *Close1;
    TMenuItem *N1;
    TMenuItem *Encode1;
    TMenuItem *EncodeAs1;
    TMenuItem *N2;
    TMenuItem *Exit1;
    TMenuItem *Tools1;
    TMenuItem *NewProfile1;
    TMenuItem *DeleteProfile1;
    TMenuItem *SaveProfile1;
    TMenuItem *Help1;
    TMenuItem *About1;
    TButton *EncodeButton;
    TTimer *Timer1;
    TOpenDialog *OpenDialog1;
    TSaveDialog *SaveDialog1;
    void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
    void __fastcall Exit1Click(TObject *Sender);
    void __fastcall Open1Click(TObject *Sender);
    void __fastcall Close1Click(TObject *Sender);
    void __fastcall About1Click(TObject *Sender);
    void __fastcall Encode1Click(TObject *Sender);
    void __fastcall EncodeAs1Click(TObject *Sender);
    void __fastcall Timer1Timer(TObject *Sender);
private:	// ユーザー宣言
public:		// ユーザー宣言
    __fastcall TMainForm(TComponent* Owner);
protected:
    UnicodeString __fastcall GetDefaultOutputFileName() const;
    void __fastcall OpenFile(const UnicodeString FileName);
    void __fastcall CloseFile(void);
    void __fastcall EncodeAs(const UnicodeString FileName);
private:
    DelphiInterface<IGraphBuilder> GraphBuilder1;
    DelphiInterface<IMediaControl> MediaControl1;
    DelphiInterface<IMediaEvent> MediaEvent1;
    DelphiInterface<IBaseFilter> Encoder;
    UnicodeString InputFileName;
};
//---------------------------------------------------------------------------
extern PACKAGE TMainForm *MainForm;
//---------------------------------------------------------------------------
#endif
