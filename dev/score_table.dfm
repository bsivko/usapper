object F_Score_Table: TF_Score_Table
  Left = 893
  Top = 121
  BorderIcons = [biSystemMenu]
  BorderStyle = bsDialog
  Caption = #1058#1072#1073#1083#1080#1094#1072' '#1088#1077#1082#1086#1088#1076#1086#1074
  ClientHeight = 258
  ClientWidth = 371
  Color = clSilver
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  Position = poScreenCenter
  PixelsPerInch = 96
  TextHeight = 13
  object Label1: TLabel
    Left = 8
    Top = 8
    Width = 117
    Height = 13
    Caption = #1058#1072#1073#1083#1080#1094#1099' '#1088#1077#1082#1086#1088#1076#1086#1074':'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
  end
  object Image1: TImage
    Left = 0
    Top = 56
    Width = 371
    Height = 202
    Align = alBottom
  end
  object ComboBox1: TComboBox
    Left = 8
    Top = 24
    Width = 145
    Height = 21
    ItemHeight = 13
    TabOrder = 0
    Text = 'ComboBox1'
    OnChange = ComboBox1Change
  end
  object Timer1: TTimer
    OnTimer = Timer1Timer
    Left = 72
    Top = 144
  end
end
