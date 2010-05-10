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
  OnClose = FormClose
  PixelsPerInch = 96
  TextHeight = 15
  object MainMenu1: TMainMenu
    Top = 256
    object File1: TMenuItem
      Caption = '&File'
      object Open1: TMenuItem
        Caption = '&Open...'
        ShortCut = 16463
        OnClick = Open1Click
      end
      object Close1: TMenuItem
        Caption = '&Close'
        Enabled = False
        ShortCut = 16471
        OnClick = Close1Click
      end
      object N1: TMenuItem
        Caption = '-'
      end
      object Encode1: TMenuItem
        Caption = '&Encode'
        Enabled = False
        ShortCut = 16453
        OnClick = Encode1Click
      end
      object EncodeAs1: TMenuItem
        Caption = 'E&ncode as...'
        Enabled = False
        OnClick = EncodeAs1Click
      end
      object N2: TMenuItem
        Caption = '-'
      end
      object Exit1: TMenuItem
        Caption = 'E&xit'
        OnClick = Exit1Click
      end
    end
    object Tools1: TMenuItem
      Caption = '&Tools'
      object NewProfile1: TMenuItem
        Caption = '&New profile'
        Enabled = False
      end
      object SaveProfile1: TMenuItem
        Caption = '&Save profile'
        Enabled = False
      end
      object DeleteProfile1: TMenuItem
        Caption = '&Delete profile...'
        Enabled = False
      end
    end
    object Help1: TMenuItem
      Caption = '&Help'
      object About1: TMenuItem
        Caption = '&About MP2 Encoder...'
        OnClick = About1Click
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
