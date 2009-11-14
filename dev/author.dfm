object F_Author: TF_Author
  Left = 383
  Top = 251
  BorderIcons = [biSystemMenu]
  BorderStyle = bsDialog
  Caption = #1040#1074#1090#1086#1088#1089#1090#1074#1086
  ClientHeight = 296
  ClientWidth = 292
  Color = clBlack
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  OnClose = FormClose
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object Memo1: TMemo
    Left = 0
    Top = 0
    Width = 185
    Height = 296
    Align = alLeft
    Alignment = taCenter
    BorderStyle = bsNone
    Color = clBlack
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWhite
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    Lines.Strings = (
      'USapper'
      ''
      #1055#1086' '#1084#1086#1090#1080#1074#1072#1084' Minesweeper'
      ''
      'C'#1086#1079#1076#1072#1085#1072' '#1074' '#1088#1072#1084#1082#1072#1093' '#1082#1086#1085#1082#1091#1088#1089#1072' '
      'IGDC #52'
      'http://igdc.ru'
      ''
      #1040#1074#1090#1086#1088
      #1057#1080#1074#1082#1086' '#1041#1086#1088#1080#1089
      ''
      #1055#1086#1078#1077#1083#1072#1085#1080#1103' '#1080' '#1079#1072#1084#1077#1095#1072#1085#1080#1103' '
      #1086#1090#1087#1088#1072#1074#1083#1103#1090#1100' '#1087#1086' '#1072#1076#1088#1077#1089#1091':'
      'bsivko@gmail.com'
      ''
      #1058#1077#1089#1090#1080#1088#1086#1074#1097#1080#1082#1080
      #1052#1080#1093#1072#1080#1083' '#1041#1077#1088#1077#1089#1090#1086#1074
      #1053#1072#1090#1072#1083#1100#1103' '#1052#1072#1089#1083#1080#1075#1072#1085
      ''
      #1042#1077#1088#1089#1080#1103' 1.4'
      ''
      'Copyright 2009')
    ParentFont = False
    TabOrder = 0
  end
  object Timer1: TTimer
    Enabled = False
    Interval = 50
    OnTimer = Timer1Timer
    Left = 208
    Top = 64
  end
end
