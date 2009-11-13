//---------------------------------------------------------------------------

#ifndef mainH
#define mainH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Menus.hpp>

#include "global_options.hpp"
#include "field/field.hpp"
#include "field/generators/interface.hpp"
#include "draw_tools/builder/abstract.hpp"
#include "draw_tools/interface.hpp"
#include <ExtCtrls.hpp>
#include <Dialogs.hpp>
#include <ComCtrls.hpp>
#include <ExtDlgs.hpp>
//---------------------------------------------------------------------------
class TMain_Form : public TForm
{
__published:	// IDE-managed Components
    TMainMenu *MainMenu1;
    TMenuItem *Game1;
    TMenuItem *Classic1;
    TMenuItem *Beginner1;
    TMenuItem *Intermediate1;
    TMenuItem *Professional1;
    TMenuItem *Exit1;
    TMenuItem *Settings1;
    TMenuItem *Info1;
    TMenuItem *Help1;
    TMenuItem *About1;
    TImage *Image1;
    TImage *ImageFon;
    TTimer *Timer1;
    TMenuItem *OptNear;
    TMenuItem *OptThis;
    TMenuItem *OptBlinkTime;
    TMenuItem *N1;
    TMenuItem *OptMono;
    TMenuItem *OptSnow;
    TMenuItem *OptStars;
    TColorDialog *ColorDialog1;
    TMenuItem *Custom1;
    TMenuItem *Records1;
    TTimer *Timer2;
    TMenuItem *Parket1;
    TMenuItem *Triangle1;
    TMenuItem *Sixangle1;
    TMenuItem *Name1;
    TMenuItem *NewGame;
    TStatusBar *StatusBar1;
    TMenuItem *Fiveangle1;
    TMenuItem *Graph1;
    TMenuItem *StatNet1;
    TMenuItem *ChessHorse1;
    TMenuItem *Labirint1;
    TMenuItem *OptOpalesce;
    TMenuItem *OptLoad;
    TOpenPictureDialog *OpenPictureDialog1;
    void __fastcall Exit1Click(TObject *Sender);
    void __fastcall Beginner1Click(TObject *Sender);
    void __fastcall Intermediate1Click(TObject *Sender);
    void __fastcall Professional1Click(TObject *Sender);
    void __fastcall FormMouseDown(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y);
    void __fastcall Timer1Timer(TObject *Sender);
    void __fastcall FormMouseMove(TObject *Sender, TShiftState Shift,
          int X, int Y);
    void __fastcall OptNearClick(TObject *Sender);
    void __fastcall OptThisClick(TObject *Sender);
    void __fastcall OptBlinkTimeClick(TObject *Sender);
    void __fastcall OptMonoClick(TObject *Sender);
    void __fastcall OptSnowClick(TObject *Sender);
    void __fastcall OptStarsClick(TObject *Sender);
    void __fastcall Custom1Click(TObject *Sender);
    void __fastcall Records1Click(TObject *Sender);
    void __fastcall About1Click(TObject *Sender);
    void __fastcall Help1Click(TObject *Sender);
    void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
    void __fastcall Timer2Timer(TObject *Sender);
    void __fastcall Triangle1Click(TObject *Sender);
    void __fastcall FormMouseUp(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y);
    void __fastcall Name1Click(TObject *Sender);
    void __fastcall NewGameClick(TObject *Sender);
    void __fastcall Sixangle1Click(TObject *Sender);
    void __fastcall Fiveangle1Click(TObject *Sender);
    void __fastcall StatNet1Click(TObject *Sender);
    void __fastcall ChessHorse1Click(TObject *Sender);
    void __fastcall Labirint1Click(TObject *Sender);
    void __fastcall OptOpalesceClick(TObject *Sender);
    void __fastcall OptLoadClick(TObject *Sender);
private:	// User declarations

    //! ��� �� ����� ����, � ������� �� ������ � �������.
    /*!
        \attention new/delete �������������� ��������� ����.
    */
    field::field_t * m_field;

    //! ���������� ���������, � ������� �������� �� ������ ��������� ����.
    draw_tools::interface_t * m_draw_tool;

    //! ���������� ������������� ����, � ������� ��������
    //! �� ��������� ���� � ����������.
    field::generators::interface_t * m_generator;

    //! �������� ������� � ���������� ����.
    void
    clear_old_game() {
        if (m_field) {
            delete m_field;
            m_field = 0;
        }
    }

    //! ������ �� X ������ ��������, ���� ����������� ��-����.
    const static int c_element_x = 19;
    //! ������ �� Y ������ ��������, ���� ����������� ��-����.
    const static int c_element_y = 19;
    //! ��������, ������������� ������� ����.
    const static int c_dy_menu = 18;
    //! ������� ����� ����� �� �������.
    const static int c_level_score = 100;

    //! ������������ ����.
    void
    draw_field();

    //! ����� ������ (���� ������� �� ����� ��������).
    void
    kill_miner();

    //! ���������� ���� (����� ��������).
    void
    start_game();

    //! ��������� ���� (����� ��������).
    void
    end_game();

    //! �������� ���������� �����.
    void
    refresh_info();

    //! ������� �������.
    void
    level_complete();

    //! ���������� ������������ ����.
    void
    start_classic();

    void
    clear_gametype_checks();

public:		// User declarations
    //! � ����� ��������� ������ ��������� ����.
    enum game_condition_t {
        //! �������� ��������.
        wait,
        //! ��������� ��������� �������.
        one_level,
        //! ���������� ����� �������.
        multiple_level,
        //! ���������������� ���� (� ��������� ����������� ��� ������)
        custom
    };

private:
    //! � ����� ��������� ������ ��������� ����.
    game_condition_t m_game_condition;

    //! ��� ���� ��� ������ (��������).
    std::string m_game_type;

    //! ����� ������ (��� ����������).
    int m_level;

    //! ��� ������.
    std::string m_name;

    //! ������� ������� ����� ����� � ���� (������).
    int m_game_time;

    //! ������� ������� ����� ����� �� ������ (������).
    int m_level_time;

    //! ������� ���� ��� ��� (�������� �� ����� ��� �������� ����� ��������).
    bool m_game_is_active;

    //! ������� ������� ��� ��� ���.
    //! ������������ ����� ����������� ������ ������.
    bool m_level_is_active;

    //! ���������� �����.
    int m_score;

    //! �������� ����� � ���� ������ ��:��:��.
    std::string
    str_time( int time );

    std::string m_high_score_filename;

    //! ������ ����������.
    bool m_first_refresh;

    bool m_is_init_help;

    std::string m_help_filename;

    //! Info �� ����.
    field::info_t m_info;

    __fastcall TMain_Form(TComponent* Owner);
};

//---------------------------------------------------------------------------
extern PACKAGE TMain_Form *Main_Form;
//---------------------------------------------------------------------------
#endif
