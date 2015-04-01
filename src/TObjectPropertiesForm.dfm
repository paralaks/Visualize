object FormObjectPropertiesForm: TFormObjectPropertiesForm
  Left = 454
  Top = 119
  Width = 400
  Height = 280
  Caption = 'Object properties'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  FormStyle = fsStayOnTop
  OldCreateOrder = False
  Position = poMainFormCenter
  OnClose = FormClose
  OnCreate = FormCreate
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object Panel1: TPanel
    Left = 2
    Top = 2
    Width = 388
    Height = 247
    TabOrder = 0
    OnClick = Panel1Click
    object GroupBox1: TGroupBox
      Left = 6
      Top = 45
      Width = 376
      Height = 89
      Caption = 'Color components '
      TabOrder = 1
      OnClick = GroupBox1Click
      object Label1: TLabel
        Left = 344
        Top = 18
        Width = 25
        Height = 14
        AutoSize = False
        Caption = '0'
      end
      object Label2: TLabel
        Left = 344
        Top = 42
        Width = 25
        Height = 14
        AutoSize = False
        Caption = '0'
      end
      object Label3: TLabel
        Left = 344
        Top = 64
        Width = 25
        Height = 14
        AutoSize = False
        Caption = '0'
      end
      object StaticText1: TStaticText
        Left = 8
        Top = 18
        Width = 33
        Height = 17
        Caption = 'Red : '
        TabOrder = 0
      end
      object StaticText2: TStaticText
        Left = 8
        Top = 42
        Width = 42
        Height = 17
        Caption = 'Green : '
        TabOrder = 1
      end
      object StaticText3: TStaticText
        Left = 8
        Top = 64
        Width = 34
        Height = 17
        Caption = 'Blue : '
        TabOrder = 2
      end
      object TrackBar1: TTrackBar
        Left = 56
        Top = 16
        Width = 273
        Height = 17
        Orientation = trHorizontal
        Frequency = 1
        Position = 0
        SelEnd = 0
        SelStart = 0
        TabOrder = 3
        TickMarks = tmBottomRight
        TickStyle = tsAuto
        OnChange = TrackBar1Change
      end
      object TrackBar2: TTrackBar
        Left = 56
        Top = 40
        Width = 273
        Height = 17
        Orientation = trHorizontal
        Frequency = 1
        Position = 0
        SelEnd = 0
        SelStart = 0
        TabOrder = 4
        TickMarks = tmBottomRight
        TickStyle = tsAuto
        OnChange = TrackBar2Change
      end
      object TrackBar3: TTrackBar
        Left = 56
        Top = 64
        Width = 273
        Height = 17
        Orientation = trHorizontal
        Frequency = 1
        Position = 0
        SelEnd = 0
        SelStart = 0
        TabOrder = 5
        TickMarks = tmBottomRight
        TickStyle = tsAuto
        OnChange = TrackBar3Change
      end
    end
    object GroupBox4: TGroupBox
      Left = 6
      Top = 143
      Width = 376
      Height = 65
      Caption = 'Shininess and Transparency '
      TabOrder = 2
      OnClick = GroupBox4Click
      object Label4: TLabel
        Left = 344
        Top = 18
        Width = 25
        Height = 14
        AutoSize = False
        Caption = '0'
      end
      object Label5: TLabel
        Left = 343
        Top = 40
        Width = 26
        Height = 14
        AutoSize = False
        Caption = '0'
      end
      object StaticText4: TStaticText
        Left = 10
        Top = 18
        Width = 52
        Height = 17
        Caption = 'Shininess:'
        TabOrder = 0
      end
      object StaticText5: TStaticText
        Left = 11
        Top = 40
        Width = 72
        Height = 17
        Caption = 'Transparency:'
        TabOrder = 1
      end
      object TrackBar4: TTrackBar
        Left = 88
        Top = 16
        Width = 241
        Height = 17
        Orientation = trHorizontal
        Frequency = 1
        Position = 0
        SelEnd = 0
        SelStart = 0
        TabOrder = 2
        TickMarks = tmBottomRight
        TickStyle = tsAuto
        OnChange = TrackBar4Change
      end
      object TrackBar5: TTrackBar
        Left = 88
        Top = 40
        Width = 241
        Height = 17
        Orientation = trHorizontal
        Frequency = 1
        Position = 0
        SelEnd = 0
        SelStart = 0
        TabOrder = 3
        TickMarks = tmBottomRight
        TickStyle = tsAuto
        OnChange = TrackBar5Change
      end
    end
    object Button1: TButton
      Left = 150
      Top = 215
      Width = 75
      Height = 25
      Caption = 'OK'
      TabOrder = 4
      OnClick = Button1Click
    end
    object StaticText6: TStaticText
      Left = 56
      Top = 16
      Width = 80
      Height = 17
      Caption = 'Object'#39's name : '
      TabOrder = 3
    end
    object Edit1: TEdit
      Left = 136
      Top = 15
      Width = 177
      Height = 21
      TabOrder = 0
      OnChange = Edit1Change
      OnClick = Edit1Click
    end
  end
end
