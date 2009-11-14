object Main_Form: TMain_Form
  Left = 191
  Top = 120
  BorderIcons = [biSystemMenu, biMinimize]
  BorderStyle = bsSingle
  Caption = #1057#1072#1087#1105#1088
  ClientHeight = 542
  ClientWidth = 784
  Color = clSilver
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Palatino Linotype'
  Font.Style = []
  Menu = MainMenu1
  OldCreateOrder = False
  Position = poDefaultSizeOnly
  OnClose = FormClose
  OnMouseDown = FormMouseDown
  OnMouseMove = FormMouseMove
  OnMouseUp = FormMouseUp
  PixelsPerInch = 96
  TextHeight = 16
  object Image1: TImage
    Left = 0
    Top = 0
    Width = 784
    Height = 512
    Align = alClient
    Visible = False
  end
  object ImageFon: TImage
    Left = 0
    Top = 0
    Width = 784
    Height = 512
    Align = alClient
    Stretch = True
    Visible = False
  end
  object StatusBar1: TStatusBar
    Left = 0
    Top = 512
    Width = 784
    Height = 30
    Color = clSilver
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -16
    Font.Name = 'Palatino Linotype'
    Font.Style = [fsBold]
    Panels = <
      item
        Width = 100
      end
      item
        Width = 100
      end
      item
        Width = 100
      end
      item
        Width = 100
      end
      item
        Width = 100
      end>
    SimplePanel = False
    SimpleText = '123'
    UseSystemFont = False
  end
  object MainMenu1: TMainMenu
    Left = 552
    Top = 72
    object Game1: TMenuItem
      Caption = #1048#1075#1088#1072
      object NewGame: TMenuItem
        Caption = #1053#1086#1074#1072#1103
        OnClick = NewGameClick
      end
      object Classic1: TMenuItem
        Caption = #1050#1083#1072#1089#1089#1080#1095#1077#1089#1082#1072#1103
        object Beginner1: TMenuItem
          Caption = #1053#1072#1095#1080#1085#1072#1102#1097#1080#1081
          Checked = True
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
      object Parket1: TMenuItem
        Caption = #1055#1072#1088#1082#1077#1090#1085#1072#1103
        object Triangle1: TMenuItem
          Caption = #1058#1088#1077#1091#1075#1086#1083#1100#1085#1080#1082#1080
          OnClick = Triangle1Click
        end
        object Sixangle1: TMenuItem
          Caption = #1064#1077#1089#1090#1080#1091#1075#1086#1083#1100#1085#1080#1082#1080
          OnClick = Sixangle1Click
        end
        object Fiveangle1: TMenuItem
          Caption = #1063#1077#1090#1099#1088#1077#1093#1091#1075#1086#1083#1100#1085#1080#1082#1080
          OnClick = Fiveangle1Click
        end
      end
      object Graph1: TMenuItem
        Caption = #1043#1088#1072#1092#1086#1074#1072#1103
        object StatNet1: TMenuItem
          Caption = #1057#1090#1072#1090#1080#1095#1077#1089#1082#1072#1103' '#1089#1077#1090#1100
          OnClick = StatNet1Click
        end
        object ChessHorse1: TMenuItem
          Caption = #1064#1072#1093#1084#1072#1090#1085#1099#1081' '#1082#1086#1085#1100
          OnClick = ChessHorse1Click
        end
        object Labirint1: TMenuItem
          Caption = #1051#1072#1073#1080#1088#1080#1085#1090
          OnClick = Labirint1Click
        end
      end
      object Block1: TMenuItem
        Caption = #1041#1083#1086#1082#1086#1074#1072#1103
        object Duplex1: TMenuItem
          Caption = #1044#1091#1073#1083#1100
          OnClick = Duplex1Click
        end
        object Triplex1: TMenuItem
          Caption = #1058#1088#1080#1087#1083#1077#1082#1089
          OnClick = Triplex1Click
        end
        object Tetris1: TMenuItem
          Caption = #1058#1077#1090#1088#1080#1089
          OnClick = Tetris1Click
        end
      end
      object Exit1: TMenuItem
        Caption = #1042#1099#1093#1086#1076
        OnClick = Exit1Click
      end
    end
    object Settings1: TMenuItem
      Caption = #1053#1072#1089#1090#1088#1086#1081#1082#1080
      object Name1: TMenuItem
        Caption = #1055#1088#1077#1076#1089#1090#1072#1074#1080#1090#1100#1089#1103
        OnClick = Name1Click
      end
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
        object OptOpalesce: TMenuItem
          Caption = #1055#1077#1088#1077#1083#1080#1074
          Checked = True
          RadioItem = True
          OnClick = OptOpalesceClick
        end
        object OptLoad: TMenuItem
          Caption = #1047#1072#1075#1088#1091#1079#1080#1090#1100' '#1080#1079' '#1092#1072#1081#1083#1072
          RadioItem = True
          OnClick = OptLoadClick
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
    OnTimer = Timer2Timer
    Left = 496
    Top = 144
  end
  object OpenPictureDialog1: TOpenPictureDialog
    Left = 392
    Top = 120
  end
end
