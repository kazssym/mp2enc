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
      Caption = #12501#12449#12452#12523'(&F)'
      object Open1: TMenuItem
        Caption = #38283#12367'(&O)...'
        ShortCut = 16463
        OnClick = Open1Click
      end
      object Close1: TMenuItem
        Caption = #38281#12376#12427'(&C)'
        Enabled = False
        OnClick = Close1Click
      end
      object N1: TMenuItem
        Caption = '-'
      end
      object Encode1: TMenuItem
        Caption = #12456#12531#12467#12540#12489'(&E)'
        Enabled = False
        ShortCut = 16453
        OnClick = Encode1Click
      end
      object EncodeAs1: TMenuItem
        Caption = #21517#21069#12434#20184#12369#12390#12456#12531#12467#12540#12489'(&N)...'
        Enabled = False
        OnClick = EncodeAs1Click
      end
      object N2: TMenuItem
        Caption = '-'
      end
      object Exit1: TMenuItem
        Caption = #32066#20102'(&X)'
        OnClick = Exit1Click
      end
    end
    object Tools1: TMenuItem
      Caption = #12484#12540#12523'(&T)'
      object NewProfile1: TMenuItem
        Caption = #26032#35215#12503#12525#12501#12449#12452#12523'(&N)'
        Enabled = False
      end
      object SaveProfile1: TMenuItem
        Caption = #12503#12525#12501#12449#12452#12523#12434#20445#23384'(&S)'
        Enabled = False
      end
      object DeleteProfile1: TMenuItem
        Caption = #12503#12525#12501#12449#12452#12523#12434#21066#38500'(&D)'
        Enabled = False
      end
    end
    object Help1: TMenuItem
      Caption = #12504#12523#12503'(&H)'
      object About1: TMenuItem
        Caption = 'MP2 Encoder '#12398#12496#12540#12472#12519#12531#24773#22577'(&A)...'
        OnClick = About1Click
      end
    end
  end
  object OpenDialog1: TOpenDialog
    Filter = 'Wave '#12501#12449#12452#12523'|*.wav|'#12377#12409#12390#12398#12501#12449#12452#12523'|*.*'
    Left = 32
    Top = 256
  end
  object SaveDialog1: TSaveDialog
    DefaultExt = 'mp2'
    Filter = 'MP2 '#12501#12449#12452#12523'|*.mp2|'#12377#12409#12390#12398#12501#12449#12452#12523'|*.*'
    Left = 64
    Top = 256
  end
end
