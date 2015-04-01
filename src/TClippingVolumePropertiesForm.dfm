object FormClippingVolumePropertiesForm: TFormClippingVolumePropertiesForm
  Left = 354
  Top = 237
  Width = 460
  Height = 418
  Caption = 'Clipping volume properties'
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
    Width = 368
    Height = 383
    Caption = 'Panel1'
    TabOrder = 0
    OnClick = Panel1Click
    object GroupBox1: TGroupBox
      Left = 5
      Top = 52
      Width = 356
      Height = 89
      Caption = 'Reference corner position '
      TabOrder = 0
      OnClick = GroupBox1Click
      object Label1: TLabel
        Left = 320
        Top = 18
        Width = 27
        Height = 14
        AutoSize = False
        Caption = '0'
      end
      object Label2: TLabel
        Left = 320
        Top = 42
        Width = 27
        Height = 14
        AutoSize = False
        Caption = '0'
      end
      object Label3: TLabel
        Left = 320
        Top = 64
        Width = 27
        Height = 14
        AutoSize = False
        Caption = '0'
      end
      object StaticText5: TStaticText
        Left = 8
        Top = 18
        Width = 20
        Height = 17
        Caption = 'X : '
        TabOrder = 0
      end
      object StaticText6: TStaticText
        Left = 8
        Top = 42
        Width = 20
        Height = 17
        Caption = 'Y : '
        TabOrder = 1
      end
      object StaticText7: TStaticText
        Left = 8
        Top = 64
        Width = 20
        Height = 17
        Caption = 'Z : '
        TabOrder = 2
      end
      object TrackBar1: TTrackBar
        Left = 32
        Top = 16
        Width = 282
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
      object TrackBar3: TTrackBar
        Left = 32
        Top = 64
        Width = 282
        Height = 17
        Orientation = trHorizontal
        Frequency = 1
        Position = 0
        SelEnd = 0
        SelStart = 0
        TabOrder = 4
        TickMarks = tmBottomRight
        TickStyle = tsAuto
        OnChange = TrackBar3Change
      end
      object TrackBar2: TTrackBar
        Left = 32
        Top = 40
        Width = 282
        Height = 17
        Orientation = trHorizontal
        Frequency = 1
        Position = 0
        SelEnd = 0
        SelStart = 0
        TabOrder = 5
        TickMarks = tmBottomRight
        TickStyle = tsAuto
        OnChange = TrackBar2Change
      end
    end
    object GroupBox2: TGroupBox
      Left = 5
      Top = 148
      Width = 356
      Height = 89
      Caption = 'Volume dimensions '
      TabOrder = 1
      OnClick = GroupBox2Click
      object Label4: TLabel
        Left = 320
        Top = 18
        Width = 27
        Height = 14
        AutoSize = False
        Caption = '0'
      end
      object Label5: TLabel
        Left = 320
        Top = 42
        Width = 27
        Height = 14
        AutoSize = False
        Caption = '0'
      end
      object Label6: TLabel
        Left = 320
        Top = 64
        Width = 27
        Height = 14
        AutoSize = False
        Caption = '0'
      end
      object StaticText1: TStaticText
        Left = 8
        Top = 18
        Width = 41
        Height = 17
        Caption = 'Width : '
        TabOrder = 0
      end
      object StaticText2: TStaticText
        Left = 8
        Top = 42
        Width = 44
        Height = 17
        Caption = 'Height : '
        TabOrder = 1
      end
      object StaticText3: TStaticText
        Left = 8
        Top = 64
        Width = 42
        Height = 17
        Caption = 'Depth : '
        TabOrder = 2
      end
      object TrackBar6: TTrackBar
        Left = 50
        Top = 63
        Width = 264
        Height = 17
        Orientation = trHorizontal
        Frequency = 1
        Position = 0
        SelEnd = 0
        SelStart = 0
        TabOrder = 3
        TickMarks = tmBottomRight
        TickStyle = tsAuto
        OnChange = TrackBar6Change
      end
      object TrackBar5: TTrackBar
        Left = 50
        Top = 39
        Width = 264
        Height = 17
        Orientation = trHorizontal
        Frequency = 1
        Position = 0
        SelEnd = 0
        SelStart = 0
        TabOrder = 4
        TickMarks = tmBottomRight
        TickStyle = tsAuto
        OnChange = TrackBar5Change
      end
      object TrackBar4: TTrackBar
        Left = 50
        Top = 15
        Width = 264
        Height = 17
        Orientation = trHorizontal
        Frequency = 1
        Position = 0
        SelEnd = 0
        SelStart = 0
        TabOrder = 5
        TickMarks = tmBottomRight
        TickStyle = tsAuto
        OnChange = TrackBar4Change
      end
    end
    object Button1: TButton
      Left = 144
      Top = 351
      Width = 75
      Height = 25
      Caption = 'OK'
      TabOrder = 2
      OnClick = Button1Click
    end
    object StaticText4: TStaticText
      Left = 30
      Top = 21
      Width = 123
      Height = 17
      Caption = 'Clipping volume'#39's name : '
      TabOrder = 3
    end
    object Edit1: TEdit
      Left = 158
      Top = 20
      Width = 177
      Height = 21
      TabOrder = 4
      OnChange = Edit1Change
      OnClick = Edit1Click
    end
    object GroupBox3: TGroupBox
      Left = 8
      Top = 248
      Width = 353
      Height = 97
      Caption = 'The objects to be affected '
      TabOrder = 5
      object CheckListBox1: TCheckListBox
        Left = 8
        Top = 16
        Width = 337
        Height = 73
        ItemHeight = 13
        TabOrder = 0
        OnClick = CheckListBox1Click
      end
    end
  end
end
