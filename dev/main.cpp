//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include <stdlib.h>

#include <stdexcept>
#include <fstream>
#include <stdlib.h>

#include "draw_tools/factory.hpp"
#include "field/generators/factory.hpp"
#include "field/generators/classic.hpp"
#include "draw_tools/builder/abstract.hpp"
#include "high_scores/high_scores.hpp"

#include <vector>

#include "main.h"
#include "score_table.h"
#include "author.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TMain_Form *Main_Form;
//---------------------------------------------------------------------------
__fastcall TMain_Form::TMain_Form(TComponent* Owner)
    : TForm(Owner), m_game_condition( wait ), m_game_type( "" ), m_level(0),
    m_game_is_active( false ), m_high_score_filename("sapper.scr"),
    m_first_refresh(true), m_help_filename( "help.htm" )
{
	randomize();
}
//---------------------------------------------------------------------------
void __fastcall TMain_Form::Exit1Click(TObject *Sender)
{
    Close();
}

//! Получить время в виде строки ЧЧ:ММ:СС.
std::string
TMain_Form::str_time( int time ) {

    String sec = IntToStr(time % 60);
    if (sec.Length() == 1) sec = "0" + sec;

    String min = IntToStr(time % 3600 / 60);
    if (min.Length() == 1) min = "0" + min;

    String hour = IntToStr(time / 60 / 60);
    if (hour.Length() == 1) hour = "0" + hour;

    return (hour + ":" + min + ":" + sec).c_str();
}
//---------------------------------------------------------------------------
void __fastcall TMain_Form::Beginner1Click(TObject *Sender)
{
    clear_old_game();
    start_game();

    // Генерируем поле.
    m_generator = &
        field::generators::factory_t::get_instance(
            field::generators::classic
        );

    // Данные для Beginner.
    field::info_t info;
    info.m_element_size_x = c_element_x;
    info.m_element_size_y = c_element_y;
    info.m_size_x = 9;
    info.m_size_y = 9;
    info.m_bomb_number = 10;
    info.m_size_px_x = Image1->Width;
    info.m_size_px_y = Image1->Height - c_dy_menu;

    m_game_type = "Классика: начинающие";
    m_game_condition = one_level;

    // Генерируем поле.
    m_field = m_generator->generate( info );

    // Формируем интерфейс для рисования поля.
    m_draw_tool = &
        draw_tools::factory_t::get_instance(
            draw_tools::classic
        );

    static_cast<draw_tools::builder::abstract_t*>
        (m_draw_tool)->set_shadow(
            *(Image1->Canvas)
        ,   TRect( 0, 0, Image1->Width, Image1->Height) );

    static_cast<draw_tools::builder::abstract_t*>
        (m_draw_tool)->set_main(
            *(Main_Form->Canvas)
        ,   TRect( Image_Info->Width, 0, Image1->Width + Image_Info->Width, Image1->Height) );

    // Рисуем поле.
    draw_field();
}


void
TMain_Form::draw_field()
{
    if (m_draw_tool) {
        static_cast<draw_tools::builder::abstract_t*>
            (m_draw_tool)->draw_backgound();

        if (m_field) {
            static_cast<draw_tools::builder::abstract_t*>
                (m_draw_tool)->shadow_copy_draw( *m_field );
        }
    }
}
//---------------------------------------------------------------------------
void __fastcall TMain_Form::Image1MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
    if (!m_game_is_active)
        // Игра неактивна.
        return;

    int index = m_field->get_element_by_click( X, Y );

    if ( index == -1 )
        // Клик в никуда.
        return;

    // Смотрим что за клик.
    if (Button == mbLeft) {

        int score = m_field->count_of_near_bombs( index );
        m_score += m_field->count_of_near_bombs( index );
        if ( score == 0 ) {
            m_score += 10;
        }

        if (m_field->open( index )) {
            kill_miner();
            return;
        }
        m_field->count_of_near_bombs( index );
    }
    else if (Button == mbRight) {
        if ( m_field->elements()[index].is_flag() ) {
            m_field->elements()[index].unset_flag();
        }
        else {
            m_field->elements()[index].set_flag();
        }
    }
    else if (Button == mbMiddle) {
        // Функция средней кнопки.
        // Только для открытых клеток.
        if ( m_field->elements()[index].is_open() ) {
            // Число рядом стоящих флагов равно числу, написанному в клетке.
            if ( m_field->count_of_near_flags( index ) == m_field->count_of_near_bombs( index ) ) {

                // Считаем, сколько получит очков игрок.
                // Индексы соседей.
                std::vector<int> v_near = m_field->elements()[index].near_elements();
                for(unsigned int i = 0; i < v_near.size(); ++i) {
                    if ( !m_field->elements()[v_near[i]].is_open() ) {
                        m_score += m_field->count_of_near_bombs(i);
                    }
                }
                // Пытаемся открыть все пустые клетки.
                if (m_field->open_near( index )) {
                    kill_miner();
                    return;
                }
            }
        }
    }

    draw_field();
}
//---------------------------------------------------------------------------
void __fastcall TMain_Form::Intermediate1Click(TObject *Sender)
{
    clear_old_game();
    start_game();

    // Генерируем поле.
    m_generator = &
        field::generators::factory_t::get_instance(
            field::generators::classic
        );

    // Данные для Intermediate.
    field::info_t info;
    info.m_element_size_x = c_element_x;
    info.m_element_size_y = c_element_y;
    info.m_size_x = 16;
    info.m_size_y = 16;
    info.m_bomb_number = 40;
    info.m_size_px_x = Image1->Width;
    info.m_size_px_y = Image1->Height - c_dy_menu;

    m_game_type = "Классика: любители";
    m_game_condition = one_level;

    // Генерируем поле.
    m_field = m_generator->generate( info );

    // Формируем интерфейс для рисования поля.
    m_draw_tool = &
        draw_tools::factory_t::get_instance(
            draw_tools::classic
        );

    static_cast<draw_tools::builder::abstract_t*>
        (m_draw_tool)->set_shadow(
            *(Image1->Canvas)
        ,   TRect( 0, 0, Image1->Width, Image1->Height) );

    static_cast<draw_tools::builder::abstract_t*>
        (m_draw_tool)->set_main(
            *(Main_Form->Canvas)
        ,   TRect( Image_Info->Width, 0, Image1->Width + Image_Info->Width, Image1->Height) );

    // Рисуем поле.
    draw_field();
}
//---------------------------------------------------------------------------
void __fastcall TMain_Form::Professional1Click(TObject *Sender)
{
    clear_old_game();
    start_game();

    // Генерируем поле.
    m_generator = &
        field::generators::factory_t::get_instance(
            field::generators::classic
        );

    // Данные для Professional.
    field::info_t info;
    info.m_element_size_x = c_element_x;
    info.m_element_size_y = c_element_y;
    info.m_size_x = 30;
    info.m_size_y = 16;
    info.m_bomb_number = 99;
    info.m_size_px_x = Image1->Width;
    info.m_size_px_y = Image1->Height - c_dy_menu;

    m_game_type = "Классика: профессионалы";
    m_game_condition = one_level;

    // Генерируем поле.
    m_field = m_generator->generate( info );

    // Формируем интерфейс для рисования поля.
    m_draw_tool = &
        draw_tools::factory_t::get_instance(
            draw_tools::classic
        );

    static_cast<draw_tools::builder::abstract_t*>
        (m_draw_tool)->set_shadow(
            *(Image1->Canvas)
        ,   TRect( 0, 0, Image1->Width, Image1->Height) );

    static_cast<draw_tools::builder::abstract_t*>
        (m_draw_tool)->set_main(
            *(Main_Form->Canvas)
        ,   TRect( Image_Info->Width, 0, Image1->Width + Image_Info->Width, Image1->Height) );

    // Рисуем поле.
    draw_field();

}

void
TMain_Form::kill_miner() {

    m_game_is_active = false;

    m_field->open_all();
    m_field->uncheck_all();

    draw_field();

    if ( m_game_condition == one_level ) {
        try {
            // Сохраняем результат.
            high_scores::high_scores_t::get_instance().add_record(
                m_high_score_filename
            ,   high_scores::record_t(
                    m_name
                ,   m_score
                ,   str_time( m_level_time )
                ,   false
                )
            ,   m_game_type
            );
        }
        catch( std::runtime_error & ex ) {
            ShowMessage(
                String("Ошибка при записи результата в таблицу рекордов. ") +
                "Причина:\n" +
                ex.what()
            );
        }

        // Останавливем игровой процесс.
        end_game();
    }

}

//---------------------------------------------------------------------------

void __fastcall TMain_Form::FormMouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
    Image1MouseDown( Sender, Button, Shift, X - Image_Info->Width, Y );
}
//---------------------------------------------------------------------------

void
TMain_Form::start_game() {
    Beginner1->Enabled = false;
    Intermediate1->Enabled = false;
    Professional1->Enabled = false;
    Quest1->Enabled = false;
    EndGame1->Enabled = true;
    Custom1->Enabled = false;

    AnsiString InputString = InputBox("Вход в игру", "Ваше имя (до 10 символов)?", "");
    InputString = InputString.Trim();
    if (InputString.Length() == 0) {
        InputString = "Инкогнито";
    }
    if (InputString.Length() > 10) {
        InputString = InputString.SubString(0, 10);
    }
    m_name = InputString.c_str();

    m_score = 0;

    Main_Form->Refresh();

    m_game_is_active = true;

    refresh_info();
}

void
TMain_Form::end_game() {

//    clear_old_game();

    Beginner1->Enabled = true;
    Intermediate1->Enabled = true;
    Professional1->Enabled = true;
    Quest1->Enabled = true;
    EndGame1->Enabled = false;
    Custom1->Enabled = true;

    m_game_is_active = false;
    m_level_time = 0;
    m_level = 0;
    m_score = 0;
    m_name = "";
    m_game_time = 0;
}

void
TMain_Form::refresh_info() {
    Main_Form->Canvas->Brush->Color = clSilver;
    Main_Form->Canvas->Pen->Color = clWhite;
    Main_Form->Canvas->Rectangle( 0, 0, Image_Info->Width, Image_Info->Height );
    Main_Form->Canvas->Rectangle( 2, 2, Image_Info->Width-2, Image_Info->Height-2 );
    Main_Form->Canvas->Rectangle( 4, 4, Image_Info->Width-4, Image_Info->Height-4 );

    // Высота строки.
    const int c_height = 16;

    Main_Form->Canvas->Font->Color = clBlack;
    Main_Form->Canvas->TextOutA( 8, 8 + 0*c_height, "Играет:" );
    Main_Form->Canvas->TextOutA( 8, 8 + 1*c_height, m_name.c_str() );

    Main_Form->Canvas->TextOutA( 8, 8 + 2*c_height, "Очки:" );
    Main_Form->Canvas->TextOutA( 8, 8 + 3*c_height, IntToStr(m_score) );

    Main_Form->Canvas->TextOutA( 8, 8 + 4*c_height, "Время:" );
    Main_Form->Canvas->TextOutA( 8, 8 + 5*c_height, str_time( m_level_time ).c_str() );

    String bombs = "-";
    if (m_field) {
        bombs = m_field->info().m_bomb_number;
    }
    Main_Form->Canvas->TextOutA( 8, 8 + 6*c_height, "Бомб: " + bombs );

    String flags = "-";
    if (m_field) {
        flags = m_field->count_of_all_flags();
    }
    Main_Form->Canvas->TextOutA( 8, 8 + 7*c_height, "Флагов: " + flags );
}


void __fastcall TMain_Form::EndGame1Click(TObject *Sender)
{
    end_game();
}
//---------------------------------------------------------------------------



void __fastcall TMain_Form::Timer1Timer(TObject *Sender)
{
    static tick = 0;
    ++tick;

    if (tick % 10 == 0) {
        // 1 Секунда.
        if (m_game_is_active) {
            ++m_level_time;
            ++m_game_time;
            refresh_info();
        }

        if ( m_field ) {
            if (m_field->is_complete() && m_game_is_active) {
                // Игрок прошел уровень.
                m_game_is_active = false;
                ShowMessage("Поле расчищено!");
                level_complete();
            }
        }
    }

    if (m_draw_tool) {
        static_cast<draw_tools::builder::abstract_t*>
            (m_draw_tool)->set_blink( (tick / 3) % 3 == 0 );

        static_cast<draw_tools::builder::abstract_t*>
            (m_draw_tool)->set_tick( tick );
    }

    if (m_first_refresh) {
        refresh_info();
        m_first_refresh = false;
    }

    draw_field();
}
//---------------------------------------------------------------------------



void __fastcall TMain_Form::FormMouseMove(TObject *Sender,
      TShiftState Shift, int X, int Y)
{
    if (!m_game_is_active)
        // Игра неактивна.
        return;

    X -= Image_Info->Width;

    int index = m_field->get_element_by_click( X, Y );

    if ( index == -1 ) {
        // Под мышой нет элементов.
        m_field->uncheck_all();
        return;
    }

    if (OptNear->Checked) {
        m_field->check_near(index);
    }

    if (OptThis->Checked) {
        m_field->check(index);
    }

    draw_field();
}
//---------------------------------------------------------------------------

void __fastcall TMain_Form::OptNearClick(TObject *Sender)
{
    OptNear->Checked = !OptNear->Checked;
    Main_Form->Refresh();
    refresh_info();
}
//---------------------------------------------------------------------------

void
TMain_Form::level_complete() {

    m_field->uncheck_all();
    draw_field();

    // Если уровень один, то завершаем игру с записей в таблицу рекордов.
    // Если несколько, то переходим к следующему.

    if ( m_game_condition == one_level ) {

        m_score +=
            m_field->info().m_bomb_number * m_field->info().m_bomb_number
            /
            (10 + m_level_time);

        // Дополнительные очки за флаги.
        for( unsigned int i = 0; i < m_field->elements().size(); ++i ) {
            if (
                m_field->elements()[i].is_flag() &&
                m_field->elements()[i].is_bomb()
            ) {
                m_score += 5;
            }
        }

        refresh_info();

        try {
            // Сохраняем результат.
            high_scores::high_scores_t::get_instance().add_record(
                m_high_score_filename
            ,   high_scores::record_t(
                    m_name
                ,   m_score
                ,   str_time( m_level_time )
                ,   true
                )
            ,   m_game_type
            );
        }
        catch( std::runtime_error & ex ) {
            ShowMessage(
                String("Ошибка при записи результата в таблицу рекордов. ") +
                "Причина:\n" +
                ex.what()
            );
        }

        // Останавливем игровой процесс.
        end_game();
    }
}

void __fastcall TMain_Form::OptThisClick(TObject *Sender)
{
    OptThis->Checked = !OptThis->Checked;
    Main_Form->Refresh();
    refresh_info();
}
//---------------------------------------------------------------------------

void __fastcall TMain_Form::OptBlinkTimeClick(TObject *Sender)
{
    try {
        AnsiString InputString = InputBox(
            "Настройки",
            "Введите время мерцания \n(целое число в секундах)",
            IntToStr( global_options_t::get_instance().blink_time() )
        );
        InputString = InputString.Trim();
        global_options_t::get_instance().set_blink_time( StrToInt(InputString) );
    }
    catch( EConvertError & ex ) {
        ShowMessage( "Ошибка преобразования. \nВводить нужно корректные данные.");
    }

    Main_Form->Refresh();
    refresh_info();
}
//---------------------------------------------------------------------------

void __fastcall TMain_Form::OptMonoClick(TObject *Sender)
{
    if ( ColorDialog1->Execute() ) {
        global_options_t::get_instance().set_background_color( ColorDialog1->Color );
        global_options_t::get_instance().set_background_type( global_options_t::mono );
        OptMono->Checked = true;
    }
    Main_Form->Refresh();
    refresh_info();
}
//---------------------------------------------------------------------------

void __fastcall TMain_Form::OptSnowClick(TObject *Sender)
{
    global_options_t::get_instance().set_background_type( global_options_t::snow );
    OptSnow->Checked = true;
    Main_Form->Refresh();
    refresh_info();
}
//---------------------------------------------------------------------------

void __fastcall TMain_Form::OptStarsClick(TObject *Sender)
{
    global_options_t::get_instance().set_background_type( global_options_t::stars );
    OptStars->Checked = true;
    Main_Form->Refresh();
    refresh_info();
}
//---------------------------------------------------------------------------

void __fastcall TMain_Form::Custom1Click(TObject *Sender)
{
    try {
        AnsiString InputString = InputBox(
            "Настройки",
            "Размер поля по горизонтали \n(натуральное число до 32)",
            "30"
        );
        InputString = InputString.Trim();
        int size_x = StrToInt(InputString);
        if ((size_x < 1) || (size_x > 32)) {
            throw std::runtime_error( "Значение по горизонтали вне диапазона 1..32" );
        }

        InputString = InputBox(
            "Настройки",
            "Размер поля по вертикали \n(натуральное число до 24)",
            "16"
        );
        InputString = InputString.Trim();
        int size_y = StrToInt(InputString);
        if ((size_y < 1) || (size_y > 24)) {
            throw std::runtime_error( "Значение по горизонтали вне диапазона 1..24" );
        }

        String bombs = IntToStr(size_x * size_y);

        InputString = InputBox(
            "Настройки",
            "Число бомб \n(все должны поместиться на поле, не более " + bombs +")",
            "70"
        );
        InputString = InputString.Trim();
        int bomb_count = StrToInt(InputString);
        if ((bomb_count < 0) || (bomb_count > StrToInt(bombs) )) {
            throw std::runtime_error( "Некорретное число бомб." );
        }

        // Данные есть. Стартуем.

        clear_old_game();
        start_game();

        // Генерируем поле.
        m_generator = &
            field::generators::factory_t::get_instance(
                field::generators::classic
            );

        // Данные для Custom.
        field::info_t info;
        info.m_element_size_x = c_element_x;
        info.m_element_size_y = c_element_y;
        info.m_size_x = size_x;
        info.m_size_y = size_y;
        info.m_bomb_number = bomb_count;
        info.m_size_px_x = Image1->Width;
        info.m_size_px_y = Image1->Height - c_dy_menu;

        m_game_condition = custom;
        m_game_type = "Классика: произвольное поле";

        // Генерируем поле.
        m_field = m_generator->generate( info );

        // Формируем интерфейс для рисования поля.
        m_draw_tool = &
            draw_tools::factory_t::get_instance(
                draw_tools::classic
            );

        static_cast<draw_tools::builder::abstract_t*>
            (m_draw_tool)->set_shadow(
                *(Image1->Canvas)
            ,   TRect( 0, 0, Image1->Width, Image1->Height) );

        static_cast<draw_tools::builder::abstract_t*>
            (m_draw_tool)->set_main(
                *(Main_Form->Canvas)
            ,   TRect( Image_Info->Width, 0, Image1->Width + Image_Info->Width, Image1->Height) );

        // Рисуем поле.
        draw_field();
    }
    catch( EConvertError & ex ) {
        ShowMessage( "Ошибка преобразования. \nВводить нужно корректные данные.");
    }
    catch( std::runtime_error & ex ) {
        ShowMessage( String("Ошибка преобразования: ") + ex.what() );
    }
    Main_Form->Refresh();
    refresh_info();
}
//---------------------------------------------------------------------------


void __fastcall TMain_Form::Records1Click(TObject *Sender)
{
    high_scores::tables_t tables;

    try {
        tables = high_scores::high_scores_t::get_instance().get_info(
            m_high_score_filename
        );
    }
    catch( std::runtime_error & ex ) {
        ShowMessage(
            String("Ошибка при получении данных из таблицы рекордов. ") +
            "Причина:\n" +
            ex.what()
        );
    }

    if (tables.m_tables.size() == 0) {
        ShowMessage(
        "На данный момент нет ни одного результата.\n"
            "Вы можете стать первым!");
        return;
    }
    else {
        F_Score_Table->set_tables( tables );
        F_Score_Table->first_refresh();
        F_Score_Table->ShowModal();
    }
}
//---------------------------------------------------------------------------


void __fastcall TMain_Form::About1Click(TObject *Sender)
{
    F_Author->Timer1->Enabled = true;
    F_Author->ShowModal();
    F_Author->Timer1->Enabled = false;
}
//---------------------------------------------------------------------------

void __fastcall TMain_Form::Help1Click(TObject *Sender)
{
    if ( !m_is_init_help ) {
        m_is_init_help = true;

        TResourceStream *res = new TResourceStream(
            0,
            "help",
            "Custom"
        );
        res->SaveToFile( m_help_filename.c_str() );
        delete res;

        ShellExecute(0, "open", m_help_filename.c_str(), 0, 0, SW_SHOW);
    }
}
//---------------------------------------------------------------------------


void __fastcall TMain_Form::FormClose(TObject *Sender,
      TCloseAction &Action)
{
    if (m_is_init_help) {
        DeleteFile( m_help_filename.c_str()  );
    }
}
//---------------------------------------------------------------------------

