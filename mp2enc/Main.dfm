object MainForm: TMainForm
  Left = 0
  Top = 0
  Caption = 'MP2 Encoder'
  ClientHeight = 282
  ClientWidth = 418
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -12
  Font.Name = 'Segoe UI'
  Font.Style = []
  Menu = MainMenu1
  OldCreateOrder = False
  PixelsPerInch = 96
  TextHeight = 15
  object MainMenu1: TMainMenu
    Top = 256
    object File1: TMenuItem
      Caption = '&File'
      object Open1: TMenuItem
        Caption = '&Open...'
      end
      object Close1: TMenuItem
        Caption = '&Close'
        Enabled = False
      end
      object N1: TMenuItem
        Caption = '-'
      end
      object Encode1: TMenuItem
        Caption = '&Encode'
        Enabled = False
      end
      object EncodeAs1: TMenuItem
        Caption = 'E&ncode As...'
        Enabled = False
      end
      object N2: TMenuItem
        Caption = '-'
      end
      object Exit1: TMenuItem
        Caption = 'E&xit'
      end
    end
    object Help1: TMenuItem
      Caption = '&Help'
      object About1: TMenuItem
        Caption = '&About...'
      end
    end
  end
  object OpenDialog1: TOpenDialog
    Left = 32
    Top = 256
  end
  object SaveDialog1: TSaveDialog
    Left = 64
    Top = 256
  end
end
