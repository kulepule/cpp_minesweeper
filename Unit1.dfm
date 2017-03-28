object Form1: TForm1
  Left = 843
  Top = 283
  AlphaBlend = True
  BorderStyle = bsSingle
  Caption = 'Saper'
  ClientHeight = 338
  ClientWidth = 305
  Color = clSkyBlue
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  Menu = MainMenu1
  OldCreateOrder = False
  OnClose = FormClose
  PixelsPerInch = 96
  TextHeight = 13
  object StatusBar1: TStatusBar
    Left = 0
    Top = 313
    Width = 305
    Height = 25
    Panels = <
      item
        Text = 'Flagi: 10'
        Width = 100
      end
      item
        Text = 'Czas: 0'
        Width = 50
      end>
    SimplePanel = False
  end
  object MainMenu1: TMainMenu
    Left = 32
    object Gra1: TMenuItem
      Caption = 'Gra'
      object Nowagra1: TMenuItem
        Caption = 'Nowa gra'
        ShortCut = 113
        OnClick = Nowagra1Click
      end
      object Wyj1: TMenuItem
        Caption = 'Ustawienia'
        ShortCut = 114
        OnClick = Wyj1Click
      end
      object Wyjdz1: TMenuItem
        Caption = 'Wyjdz'
        ShortCut = 16499
        OnClick = Wyjdz1Click
      end
    end
    object Informacje1: TMenuItem
      Caption = 'Informacje'
      object Instrukcjagry1: TMenuItem
        Caption = 'Instrukcja gry'
        ShortCut = 112
        OnClick = Instrukcjagry1Click
      end
      object OProjekcie1: TMenuItem
        Caption = 'O Projekcie'
        ShortCut = 123
        OnClick = OProjekcie1Click
      end
    end
  end
  object Timer1: TTimer
    OnTimer = Timer1Timer
  end
end
