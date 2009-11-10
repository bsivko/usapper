object Main_Form: TMain_Form
  Left = 190
  Top = 112
  BorderIcons = [biSystemMenu, biMinimize]
  BorderStyle = bsSingle
  Caption = 'Miner'
  ClientHeight = 542
  ClientWidth = 784
  Color = clSilver
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  Menu = MainMenu1
  OldCreateOrder = False
  Position = poDefaultSizeOnly
  OnClose = FormClose
  OnMouseDown = FormMouseDown
  OnMouseMove = FormMouseMove
  PixelsPerInch = 96
  TextHeight = 13
  object Image1: TImage
    Left = 89
    Top = 0
    Width = 695
    Height = 542
    Align = alClient
    Visible = False
    OnMouseDown = Image1MouseDown
  end
  object Image2: TImage
    Left = 89
    Top = 0
    Width = 695
    Height = 542
    Align = alClient
    Visible = False
    OnMouseDown = Image1MouseDown
  end
  object Image_Info: TImage
    Left = 0
    Top = 0
    Width = 89
    Height = 542
    Align = alLeft
    Visible = False
  end
  object MainMenu1: TMainMenu
    Left = 552
    Top = 72
    object Game1: TMenuItem
      Caption = #1048#1075#1088#1072
      object Classic1: TMenuItem
        Caption = #1050#1083#1072#1089#1089#1080#1095#1077#1089#1082#1072#1103
        object Beginner1: TMenuItem
          Caption = #1053#1072#1095#1080#1085#1072#1102#1097#1080#1081
          OnClick = Beginner1Click
        end
        object Intermediate1: TMenuItem
          Caption = #1051#1102#1073#1080#1090#1077#1083#1100
          OnClick = Intermediate1Click
        end
        object Professional1: TMenuItem
          Caption = #1055#1088#1086#1092#1077#1089#1089#1080#1086#1085#1072#1083
          OnClick = Professional1Click
        end
        object Custom1: TMenuItem
          Caption = #1055#1088#1086#1080#1079#1074#1086#1083#1100#1085#1072#1103
          OnClick = Custom1Click
        end
      end
      object Quest1: TMenuItem
        Caption = #1050#1074#1077#1089#1090
      end
      object EndGame1: TMenuItem
        Caption = #1047#1072#1082#1086#1085#1095#1080#1090#1100
        Enabled = False
        OnClick = EndGame1Click
      end
      object Exit1: TMenuItem
        Caption = #1042#1099#1093#1086#1076
        OnClick = Exit1Click
      end
    end
    object Settings1: TMenuItem
      Caption = #1053#1072#1089#1090#1088#1086#1081#1082#1080
      object OptNear: TMenuItem
        Caption = #1042#1099#1076#1077#1083#1077#1085#1080#1077' '#1089#1086#1089#1077#1076#1085#1080#1093' '#1082#1083#1077#1090#1086#1082
        OnClick = OptNearClick
      end
      object OptThis: TMenuItem
        Caption = #1042#1099#1076#1077#1083#1077#1085#1080#1077' '#1082#1091#1088#1089#1086#1088#1085#1086#1081' '#1082#1083#1077#1090#1082#1080
        Checked = True
        OnClick = OptThisClick
      end
      object OptBlinkTime: TMenuItem
        Caption = #1059#1089#1090#1072#1085#1086#1074#1080#1090#1100' '#1074#1088#1077#1084#1103' '#1084#1077#1088#1094#1072#1085#1080#1103
        OnClick = OptBlinkTimeClick
      end
      object N1: TMenuItem
        Caption = #1060#1086#1085
        object OptMono: TMenuItem
          Caption = #1052#1086#1085#1086#1083#1080#1090#1085#1099#1081
          Checked = True
          RadioItem = True
          OnClick = OptMonoClick
        end
        object OptSnow: TMenuItem
          Caption = #1057#1085#1077#1075
          RadioItem = True
          OnClick = OptSnowClick
        end
        object OptStars: TMenuItem
          Caption = #1047#1074#1077#1079#1076#1099
          RadioItem = True
          OnClick = OptStarsClick
        end
      end
    end
    object Info1: TMenuItem
      Caption = #1048#1085#1092#1086#1088#1084#1072#1094#1080#1103
      object Help1: TMenuItem
        Caption = #1055#1086#1084#1086#1097#1100
        OnClick = Help1Click
      end
      object Records1: TMenuItem
        Caption = #1056#1077#1082#1086#1088#1076#1089#1084#1077#1085#1099
        OnClick = Records1Click
      end
      object About1: TMenuItem
        Caption = #1054#1073' '#1072#1074#1090#1086#1088#1077
        OnClick = About1Click
      end
    end
  end
  object Timer1: TTimer
    Interval = 50
    OnTimer = Timer1Timer
    Left = 496
    Top = 104
  end
  object ColorDialog1: TColorDialog
    Ctl3D = True
    Left = 280
    Top = 64
  end
  object Timer2: TTimer
    Left = 376
    Top = 32
  end
end
