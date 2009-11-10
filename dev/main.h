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
    TMenuItem *Quest1;
    TMenuItem *Exit1;
    TMenuItem *Settings1;
    TMenuItem *Info1;
    TMenuItem *Help1;
    TMenuItem *About1;
    TImage *Image1;
    TImage *Image2;
    TMenuItem *EndGame1;
    TImage *Image_Info;
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
    void __fastcall Exit1Click(TObject *Sender);
    void __fastcall Beginner1Click(TObject *Sender);
    void __fastcall Image1MouseDown(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y);
    void __fastcall Intermediate1Click(TObject *Sender);
    void __fastcall Professional1Click(TObject *Sender);
    void __fastcall FormMouseDown(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y);
    void __fastcall EndGame1Click(TObject *Sender);
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
private:	// User declarations

    //! Это то самое поле, с которым мы играем с игроком.
    /*!
        \attention new/delete контролируется полностью нами.
    */
    field::field_t * m_field;

    //! Инструмент рисования, с помощью которого мы рисуем различным поля.
    draw_tools::interface_t * m_draw_tool;

    //! Инструмент генерирования поля, с помощью которого
    //! мы формируем поле с элементами.
    field::generators::interface_t * m_generator;

    //! Очистить объекты с предыдущей игры.
    void
    clear_old_game() {
        if (m_field) {
            delete m_field;
            m_field = 0;
        }
    }

    //! Размер по X одного элемента, если исользуется не-граф.
    const static int c_element_x = 19;
    //! Размер по Y одного элемента, если исользуется не-граф.
    const static int c_element_y = 19;
    //! Смещение, обусловленное верхним меню.
    const static int c_dy_menu = 18;
    //! Базовое число очков за уровень.
    const static int c_level_score = 100;

    //! Перерисовать поле.
    void
    draw_field();

    //! Убить минера (если нарваля на бомбу например).
    void
    kill_miner();

    //! Стартовать игру (общие действия).
    void
    start_game();

    //! Закончить игру (общие действия).
    void
    end_game();

    //! Обновить информацию слева.
    void
    refresh_info();

    //! Пройден уровень.
    void
    level_complete();

public:		// User declarations
    //! В каком состоянии сейчас находится игра.
    enum game_condition_t {
        //! Ожидание действия.
        wait,
        //! Стартовал одиночный уровень.
        one_level,
        //! Стартовала серия уровней.
        multiple_level,
        //! Пользовательская игра (с заданными параметрами без зачета)
        custom
    };

private:
    //! В каком состоянии сейчас находится игра.
    game_condition_t m_game_condition;

    //! Тип игры или уровня (название).
    std::string m_game_type;

    //! Номер уровня (для мультиигры).
    int m_level;

    //! Имя игрока.
    std::string m_name;

    //! Сколько времени всего игрок в игре (секунд).
    int m_game_time;

    //! Сколько времени всего игрок на уровне (секунд).
    int m_level_time;

    //! Активна игра или нет (например на паузе или ожидание между уровнями).
    bool m_game_is_active;

    //! Количество очков.
    int m_score;

    //! Получить время в виде строки ЧЧ:ММ:СС.
    std::string
    str_time( int time );

    std::string m_high_score_filename;

    //! Первое обновление.
    bool m_first_refresh;

    bool m_is_init_help;

    std::string m_help_filename;

    __fastcall TMain_Form(TComponent* Owner);
};

//---------------------------------------------------------------------------
extern PACKAGE TMain_Form *Main_Form;
//---------------------------------------------------------------------------
#endif
