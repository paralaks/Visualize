object FormTexturedSurfacePropertiesForm: TFormTexturedSurfacePropertiesForm
  Left = 732
  Top = 122
  Width = 450
  Height = 168
  Caption = 'Textured surface properties'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  Position = poMainFormCenter
  OnCreate = FormCreate
  PixelsPerInch = 96
  TextHeight = 13
  object Panel1: TPanel
    Left = 2
    Top = 2
    Width = 439
    Height = 135
    TabOrder = 0
    object GroupBox1: TGroupBox
      Left = 8
      Top = 8
      Width = 425
      Height = 89
      Caption = 'Plane and positioning'
      TabOrder = 0
      object Label1: TLabel
        Left = 383
        Top = 58
        Width = 34
        Height = 14
        AutoSize = False
        Caption = '-1'
      end
      object RadioButton1: TRadioButton
        Left = 56
        Top = 24
        Width = 73
        Height = 17
        Caption = 'X-Y plane'
        TabOrder = 0
      end
      object RadioButton2: TRadioButton
        Left = 168
        Top = 24
        Width = 73
        Height = 17
        Caption = 'Y-Z plane'
        TabOrder = 1
      end
      object RadioButton3: TRadioButton
        Left = 296
        Top = 24
        Width = 81
        Height = 17
        Caption = 'X-Z plane'
        TabOrder = 2
      end
      object StaticText1: TStaticText
        Left = 8
        Top = 56
        Width = 91
        Height = 17
        Caption = 'Position on plane: '
        TabOrder = 3
      end
      object ScrollBar1: TScrollBar
        Left = 104
        Top = 58
        Width = 273
        Height = 14
        PageSize = 0
        TabOrder = 4
      end
    end
    object Button1: TButton
      Left = 182
      Top = 103
      Width = 75
      Height = 25
      Caption = 'OK'
      TabOrder = 1
      OnClick = Button1Click
    end
  end
end
