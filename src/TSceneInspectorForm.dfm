object FormSceneInspectorForm: TFormSceneInspectorForm
  Left = 289
  Top = 162
  Width = 941
  Height = 822
  Caption = 'Scene inspector'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  OnActivate = FormActivate
  OnClose = FormClose
  OnCreate = FormCreate
  OnResize = FormResize
  DesignSize = (
    933
    795)
  PixelsPerInch = 96
  TextHeight = 13
  object Panel0: TPanel
    Left = 0
    Top = 7
    Width = 376
    Height = 18
    Anchors = [akLeft]
    TabOrder = 0
  end
  object Panel2: TPanel
    Left = 0
    Top = 41
    Width = 376
    Height = 144
    TabOrder = 1
    object CheckListBox1: TCheckListBox
      Left = 8
      Top = 32
      Width = 361
      Height = 73
      ItemHeight = 13
      TabOrder = 0
      OnClick = CheckListBox1Click
    end
    object Button1: TButton
      Left = 8
      Top = 112
      Width = 154
      Height = 25
      Caption = 'Modify object'#39's properties'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'Arial'
      Font.Style = []
      ParentFont = False
      TabOrder = 1
      OnClick = Button1Click
    end
    object StaticText1: TStaticText
      Left = 0
      Top = 8
      Width = 93
      Height = 20
      Caption = 'Scene objects'
      Font.Charset = TURKISH_CHARSET
      Font.Color = clWindowText
      Font.Height = -13
      Font.Name = 'Arial'
      Font.Style = [fsBold]
      ParentFont = False
      TabOrder = 2
    end
    object Button2: TButton
      Left = 288
      Top = 112
      Width = 81
      Height = 25
      Caption = 'Add object'
      TabOrder = 3
      OnClick = Button2Click
    end
  end
  object Panel3: TPanel
    Left = 0
    Top = 193
    Width = 376
    Height = 144
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'Arial'
    Font.Style = []
    ParentFont = False
    TabOrder = 2
    Visible = False
    object Button3: TButton
      Left = 8
      Top = 112
      Width = 154
      Height = 25
      Caption = 'Modify volume'#39's properties'
      TabOrder = 0
      OnClick = Button3Click
    end
    object StaticText2: TStaticText
      Left = 0
      Top = 8
      Width = 114
      Height = 20
      Caption = 'Clipping volumes'
      Font.Charset = TURKISH_CHARSET
      Font.Color = clWindowText
      Font.Height = -13
      Font.Name = 'Arial'
      Font.Style = [fsBold]
      ParentFont = False
      TabOrder = 1
    end
    object Button4: TButton
      Left = 288
      Top = 112
      Width = 81
      Height = 25
      Caption = 'Add volume'
      TabOrder = 2
      OnClick = Button4Click
    end
    object ListBox1: TListBox
      Left = 8
      Top = 32
      Width = 361
      Height = 73
      ItemHeight = 14
      TabOrder = 3
      OnClick = ListBox1Click
    end
  end
  object Panel4: TPanel
    Left = 0
    Top = 345
    Width = 376
    Height = 144
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'Arial'
    Font.Style = []
    ParentFont = False
    TabOrder = 3
    Visible = False
    object CheckListBox3: TCheckListBox
      Left = 8
      Top = 32
      Width = 361
      Height = 73
      ItemHeight = 14
      TabOrder = 0
    end
    object StaticText3: TStaticText
      Left = 0
      Top = 8
      Width = 117
      Height = 20
      Caption = 'Textured surfaces'
      Font.Charset = TURKISH_CHARSET
      Font.Color = clWindowText
      Font.Height = -13
      Font.Name = 'Arial'
      Font.Style = [fsBold]
      ParentFont = False
      TabOrder = 1
    end
    object Button5: TButton
      Left = 8
      Top = 112
      Width = 154
      Height = 25
      Caption = 'Modify surface'#39's properties'
      TabOrder = 2
      OnClick = Button5Click
    end
    object Button6: TButton
      Left = 288
      Top = 112
      Width = 81
      Height = 25
      Caption = 'Add surface'
      TabOrder = 3
    end
  end
  object Panel5: TPanel
    Left = 0
    Top = 497
    Width = 376
    Height = 144
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'Arial'
    Font.Style = []
    ParentFont = False
    TabOrder = 4
    Visible = False
    object StaticText4: TStaticText
      Left = 0
      Top = 8
      Width = 76
      Height = 20
      Caption = 'Scene light'
      Font.Charset = TURKISH_CHARSET
      Font.Color = clWindowText
      Font.Height = -13
      Font.Name = 'Arial'
      Font.Style = [fsBold]
      ParentFont = False
      TabOrder = 0
    end
    object GroupBox1: TGroupBox
      Left = 9
      Top = 24
      Width = 361
      Height = 113
      Caption = 'Light direction'
      TabOrder = 1
      object Label1: TLabel
        Left = 328
        Top = 18
        Width = 25
        Height = 14
        AutoSize = False
        Caption = '0'
      end
      object Label2: TLabel
        Left = 328
        Top = 42
        Width = 25
        Height = 14
        AutoSize = False
        Caption = '0'
      end
      object Label3: TLabel
        Left = 328
        Top = 64
        Width = 25
        Height = 14
        AutoSize = False
        Caption = '0'
      end
      object Label4: TLabel
        Left = 328
        Top = 88
        Width = 25
        Height = 14
        AutoSize = False
        Caption = '255'
      end
      object StaticText7: TStaticText
        Left = 8
        Top = 64
        Width = 64
        Height = 18
        Caption = 'Z direction : '
        TabOrder = 0
      end
      object StaticText6: TStaticText
        Left = 8
        Top = 42
        Width = 65
        Height = 18
        Caption = 'Y direction : '
        TabOrder = 1
      end
      object StaticText5: TStaticText
        Left = 8
        Top = 18
        Width = 64
        Height = 18
        Caption = 'X direction : '
        TabOrder = 2
      end
      object StaticText8: TStaticText
        Left = 8
        Top = 87
        Width = 79
        Height = 18
        Caption = 'Light intensity : '
        TabOrder = 3
      end
      object TrackBar5: TTrackBar
        Left = 88
        Top = 88
        Width = 233
        Height = 17
        Max = 255
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
        Left = 72
        Top = 64
        Width = 249
        Height = 17
        Max = 200
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
      object TrackBar3: TTrackBar
        Left = 72
        Top = 40
        Width = 249
        Height = 17
        Max = 200
        Orientation = trHorizontal
        Frequency = 1
        Position = 0
        SelEnd = 0
        SelStart = 0
        TabOrder = 6
        TickMarks = tmBottomRight
        TickStyle = tsAuto
        OnChange = TrackBar3Change
      end
      object TrackBar2: TTrackBar
        Left = 72
        Top = 16
        Width = 249
        Height = 17
        Max = 200
        Orientation = trHorizontal
        Frequency = 1
        Position = 0
        SelEnd = 0
        SelStart = 0
        TabOrder = 7
        TickMarks = tmBottomRight
        TickStyle = tsAuto
        OnChange = TrackBar2Change
      end
    end
  end
  object Memo1: TMemo
    Left = 392
    Top = 64
    Width = 376
    Height = 105
    ScrollBars = ssBoth
    TabOrder = 5
  end
  object Panel7: TPanel
    Left = 392
    Top = 176
    Width = 376
    Height = 313
    TabOrder = 6
    object Image1: TImage
      Left = 8
      Top = 48
      Width = 185
      Height = 217
      OnMouseDown = Image1MouseDown
      OnMouseMove = Image1MouseMove
    end
    object TrackBar1: TTrackBar
      Left = 1
      Top = 4
      Width = 374
      Height = 40
      Orientation = trHorizontal
      ParentShowHint = False
      Frequency = 1
      Position = 0
      SelEnd = 0
      SelStart = 0
      ShowHint = True
      TabOrder = 0
      TickMarks = tmBottomRight
      TickStyle = tsAuto
      OnChange = TrackBar1Change
    end
  end
  object Panel6: TPanel
    Left = 0
    Top = 648
    Width = 376
    Height = 33
    TabOrder = 7
    object Button7: TButton
      Left = 8
      Top = 4
      Width = 121
      Height = 25
      Caption = 'Load image set'
      TabOrder = 0
      OnClick = Button7Click
    end
    object Button8: TButton
      Left = 208
      Top = 4
      Width = 161
      Height = 25
      Caption = 'Generate 3D objects'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsBold]
      ParentFont = False
      TabOrder = 1
      OnClick = Button8Click
    end
  end
  object Panel1: TPanel
    Left = 392
    Top = 512
    Width = 376
    Height = 34
    TabOrder = 8
    DesignSize = (
      376
      34)
    object SpeedButton1: TSpeedButton
      Left = 8
      Top = 6
      Width = 65
      Height = 22
      Anchors = [akLeft, akTop, akBottom]
      GroupIndex = 1
      Caption = 'Objects'
      Flat = True
      OnClick = SpeedButton1Click
    end
    object SpeedButton2: TSpeedButton
      Left = 80
      Top = 6
      Width = 105
      Height = 22
      Anchors = [akLeft, akTop, akBottom]
      GroupIndex = 1
      Caption = 'Clipping volumes'
      Flat = True
      OnClick = SpeedButton2Click
    end
    object SpeedButton3: TSpeedButton
      Left = 190
      Top = 6
      Width = 115
      Height = 22
      Anchors = [akLeft, akTop, akBottom]
      GroupIndex = 1
      Caption = 'Textured surfaces'
      Enabled = False
      Flat = True
      Visible = False
      OnClick = SpeedButton3Click
    end
    object SpeedButton4: TSpeedButton
      Left = 312
      Top = 6
      Width = 54
      Height = 22
      Anchors = [akLeft, akTop, akBottom]
      GroupIndex = 1
      Caption = 'Light'
      Flat = True
      OnClick = SpeedButton4Click
    end
  end
  object OpenDialog1: TOpenDialog
    FileName = 'CT_HEAD.hdr'
    Filter = '*.hdr|*.hdr'
    Left = 24
    Top = 688
  end
end
