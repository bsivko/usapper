//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include <stdlib.h>

#include <stdexcept>
#include <fstream>
#include <stdlib.h>

#include "draw_tools/factory.hpp"
#include "field/generators/factory.hpp"
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
    m_first_refresh(true), m_help_filename( "help.htm" ), m_name("Инкогнито"),
    m_level_is_active( false )
{
    global_options_t::get_instance().set_background_type(
        global_options_t::picture );

    set_opalesce( clBlue, clBlack );

    const int c_name_width = 240;
    StatusBar1->Panels->Items[0]->Width = c_name_width;
    for( int i = 1; i < StatusBar1->Panels->Count; ++i ) {
        StatusBar1->Panels->Items[i]->Width =
            ( Width - c_name_width ) / ( StatusBar1->Panels->Count - 1);
    }

    Beginner1Click(0);
    NewGameClick(0);
	randomize();
}
//---------------------------------------------------------------------------
void __fastcall TMain_Form::Exit1Click(TObject *Sender)
{
    Close();
}

void
TMain_Form::set_opalesce( const TColor & top, const TColor & bottom ) {

    // Формируем картинку в виде перелива.
    ImageFon->Width = Width;
    ImageFon->Height = Height;
    int top_red = (top & 0x0ff0000) / 0x010000;
    int top_green = (top & 0x000ff00) / 0x0100;
    int top_blue = (top & 0x00000ff) / 0x01;

    int bottom_red = (bottom & 0x0ff0000) / 0x010000;
    int bottom_green = (bottom & 0x000ff00) / 0x0100;
    int bottom_blue = (bottom & 0x00000ff) / 0x01;

    for( int i = 0; i < Height; ++i) {

        int red_value = top_red * (Height - i) / Height + bottom_red * i / Height;
        int green_value = top_green * (Height - i) / Height + bottom_green * i / Height;
        int blue_value = top_blue * (Height - i) / Height + bottom_blue * i / Height;

        ImageFon->Canvas->Pen->Color = TColor(
            red_value * 0x010000 + green_value * 0x0100 + blue_value * 0x01);
        ImageFon->Canvas->MoveTo(0, i);
        ImageFon->Canvas->LineTo(Width, i);
    }

}

//! Получить время в виде строки ЧЧ:ММ:СС.
std::string
TMain_Form::str_time( int time ) {

    String sec = IntToStr(time % 60);
    while (sec.Length() <= 1) sec = "0" + sec;

    String min = IntToStr(time % 3600 / 60);
    while (min.Length() <= 1) min = "0" + min;

    String hour = IntToStr(time / 60 / 60);
    while (hour.Length() <= 1) hour = "0" + hour;

    return (hour + ":" + min + ":" + sec).c_str();
}
//---------------------------------------------------------------------------
void __fastcall TMain_Form::Beginner1Click(TObject *Sender)
{
    if ( m_game_is_active ) {
        end_game();
    }
    clear_gametype_checks();
    Beginner1->Checked = true;

    // Данные для Beginner.
    m_info.m_element_size_x = c_element_x;
    m_info.m_element_size_y = c_element_y;
    m_info.m_size_x = 9;
    m_info.m_size_y = 9;
    m_info.m_bomb_number = 10;
    m_info.m_size_px_x = Image1->Width;
    m_info.m_size_px_y = Image1->Height - c_dy_menu;

    m_game_type = "Классика: начинающие";
    m_game_condition = one_level;

    NewGameClick( Sender );
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
void __fastcall TMain_Form::Intermediate1Click(TObject *Sender)
{
    if ( m_game_is_active ) {
        end_game();
    }
    clear_gametype_checks();
    Intermediate1->Checked = true;

    // Данные для Intermediate.
    m_info.m_element_size_x = c_element_x;
    m_info.m_element_size_y = c_element_y;
    m_info.m_size_x = 16;
    m_info.m_size_y = 16;
    m_info.m_bomb_number = 40;
    m_info.m_size_px_x = Image1->Width;
    m_info.m_size_px_y = Image1->Height - c_dy_menu;

    m_game_type = "Классика: любители";
    m_game_condition = one_level;

    NewGameClick( Sender );
}
//---------------------------------------------------------------------------
void __fastcall TMain_Form::Professional1Click(TObject *Sender)
{
    if ( m_game_is_active ) {
        end_game();
    }
    clear_gametype_checks();
    Professional1->Checked = true;

    // Данные для Professional.
    m_info.m_element_size_x = c_element_x;
    m_info.m_element_size_y = c_element_y;
    m_info.m_size_x = 30;
    m_info.m_size_y = 16;
    m_info.m_bomb_number = 99;
    m_info.m_size_px_x = Image1->Width;
    m_info.m_size_px_y = Image1->Height - c_dy_menu;

    m_game_type = "Классика: профессионалы";
    m_game_condition = one_level;

    NewGameClick( Sender );
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
    if (!m_game_is_active) {
        NewGameClick( Sender );
        // Игра неактивна.
        return;
    }

    int index = m_field->get_element_by_click( X, Y );

    if ( index == -1 )
        // Клик в никуда.
        return;

    // Смотрим что за клик.
    if (Button == mbLeft) {

        if (!m_level_is_active) {
            m_level_is_active = true;
            // Необхидимо расставить мины.
            m_generator->set_bombs( *m_field, index );
        }

        // По флагу кликать бесполезно.
        if ( !m_field->elements()[index].is_flag() ) {
            if (m_field->open( index )) {
                kill_miner();
                return;
            }

            int score = m_field->count_of_near_bombs( index );
            m_score += score;
            if ( score == 0 ) {
                m_score += 10;
            }
            refresh_info();
        }
    }
    else if (Button == mbRight) {
        if ( m_field->elements()[index].is_flag() ) {
            m_field->elements()[index].unset_flag();
        }
        else {
            if ( !m_field->elements()[index].is_open() ) {
                m_field->elements()[index].set_flag();
            }
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

void
TMain_Form::start_game() {
    m_score = 0;
    Main_Form->Refresh();
    m_game_is_active = true;
    m_level_is_active = false;
    refresh_info();
}

void
TMain_Form::end_game() {
    m_game_is_active = false;      
    m_level_is_active = false;
    m_level_time = 0;
    m_level = 0;
    m_score = 0;
    m_game_time = 0;
}

void
TMain_Form::refresh_info() {

    StatusBar1->Panels->Items[0]->Text =
        String("Играет: ") + m_name.c_str();

    StatusBar1->Panels->Items[1]->Text =
        String("Очки: ") + IntToStr(m_score);

    StatusBar1->Panels->Items[2]->Text =
        String("Время: ") + str_time( m_level_time ).c_str();

    String bombs = "-";
    String flags = "-";
    if (m_field) {
        bombs = m_field->info().m_bomb_number - m_field->count_of_all_flags();
    }
    StatusBar1->Panels->Items[3]->Text =
        String("Мин: ") + bombs;

//    StatusBar1->Panels->Items[4]->Text =
//        String("Флагов: ") + flags;
}

void __fastcall TMain_Form::Timer1Timer(TObject *Sender)
{
    static tick = 0;
    ++tick;

    if (tick % 10 == 0) {

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

    int index = m_field->get_element_by_click( X, Y );

    m_field->uncheck_all();

    if ( index == -1 ) {
        // Под мышой нет элементов.
        draw_field();
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

    if ( m_game_condition == one_level ) {

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
    else {
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

        String bombs = IntToStr(size_x * size_y) - 1;

        InputString = InputBox(
            "Настройки",
            "Число мин \n"
            "(все должны поместиться на поле + одна клетка, не более " + bombs +")",
            "70"
        );
        InputString = InputString.Trim();
        int bomb_count = StrToInt(InputString);
        if ((bomb_count < 1) || (bomb_count > StrToInt(bombs) )) {
            throw std::runtime_error( "Некорретное число мин." );
        }

        // Данные есть. Стартуем.
        if ( m_game_is_active ) {
            end_game();
        }

        // Данные для Custom.
        m_info.m_element_size_x = c_element_x;
        m_info.m_element_size_y = c_element_y;
        m_info.m_size_x = size_x;
        m_info.m_size_y = size_y;
        m_info.m_bomb_number = bomb_count;
        m_info.m_size_px_x = Image1->Width;
        m_info.m_size_px_y = Image1->Height - c_dy_menu;

        m_game_condition = custom;
        m_game_type = "Классика: произвольное поле";

        NewGameClick( Sender );
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

void
TMain_Form::start_classic() {

    // Генерируем поле.
    m_generator = &
        field::generators::factory_t::get_instance(
            field::generators::classic
        );

    // Формируем интерфейс для рисования поля.
    m_draw_tool = &
        draw_tools::factory_t::get_instance(
            draw_tools::classic
        );
}


void __fastcall TMain_Form::Records1Click(TObject *Sender)
{
    high_scores::tables_t tables;

    try {
        tables = high_scores::high_scores_t::get_instance().get_info(
            m_high_score_filename
        );

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
    catch( std::runtime_error & ex ) {
        ShowMessage(
            String("Ошибка при получении данных из таблицы рекордов. ") +
            "Причина:\n" +
            ex.what()
        );
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

void __fastcall TMain_Form::Timer2Timer(TObject *Sender)
{
    // 1 Секунда.
    if (m_game_is_active && m_level_is_active) {
        ++m_level_time;
        ++m_game_time;
        refresh_info();
    }
}
//---------------------------------------------------------------------------

void __fastcall TMain_Form::Triangle1Click(TObject *Sender)
{
    if ( m_game_is_active ) {
        end_game();
    }
    clear_gametype_checks();
    Triangle1->Checked = true;

    // Данные для Triangle.
    m_info.m_element_size_x = 27;
    m_info.m_element_size_y = 24;
    m_info.m_size_x = 20;
    m_info.m_size_y = 30;
    m_info.m_bomb_number = 90;
    m_info.m_size_px_x = Image1->Width;
    m_info.m_size_px_y = Image1->Height - c_dy_menu;

    m_game_type = "Паркет: треугольники";
    m_game_condition = one_level;

    NewGameClick( Sender );
}
//---------------------------------------------------------------------------

void __fastcall TMain_Form::FormMouseUp(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
//    ShowMessage(  m_field->get_element_by_click( X- Image_Info->Width, Y ) );
}
//---------------------------------------------------------------------------

void __fastcall TMain_Form::Name1Click(TObject *Sender)
{
    AnsiString InputString = InputBox(
        "Настройки пользователя",
        "Ваше имя (до 10 символов)?",
        m_name.c_str() );
    InputString = InputString.Trim();
    if (InputString.Length() == 0) {
        InputString = "Инкогнито";
    }
    if (InputString.Length() > 10) {
        InputString = InputString.SubString(0, 10);
    }
    m_name = InputString.c_str();

    refresh_info();
}
//---------------------------------------------------------------------------

void __fastcall TMain_Form::NewGameClick(TObject *Sender)
{
    if ( m_game_is_active ) {
        end_game();
    }

    bool standard_field_create = true;

    clear_old_game();

    if ( m_game_type == "Классика: начинающие" ) {
        start_classic();
    }
    else
    if ( m_game_type == "Классика: любители" ) {
        start_classic();
    }
    else
    if ( m_game_type == "Классика: профессионалы" ) {
        start_classic();
    }
    else
    if ( m_game_type == "Классика: произвольное поле" ) {
        start_classic();
    }
    else
    if ( m_game_type == "Паркет: треугольники" ) {

        // Генерируем поле.
        m_generator = &
            field::generators::factory_t::get_instance(
            field::generators::triangle
            );

        // Формируем интерфейс для рисования поля.
        m_draw_tool = &
            draw_tools::factory_t::get_instance(
                draw_tools::triangle
            );
    }
    else
    if ( m_game_type == "Паркет: шестиугольники" ) {

        // Генерируем поле.
        m_generator = &
            field::generators::factory_t::get_instance(
            field::generators::sixangle
            );

        // Формируем интерфейс для рисования поля.
        m_draw_tool = &
            draw_tools::factory_t::get_instance(
                draw_tools::sixangle
            );
    }
    else
    if ( m_game_type == "Паркет: четырехугольники" ) {

        // Генерируем поле.
        m_generator = &
            field::generators::factory_t::get_instance(
            field::generators::fiveangle
            );

        // Формируем интерфейс для рисования поля.
        m_draw_tool = &
            draw_tools::factory_t::get_instance(
                draw_tools::fiveangle
            );
    }
    else
    if ( m_game_type == "Графы: статическая сеть" ) {

        // Генерируем поле.
        m_generator = &
            field::generators::factory_t::get_instance(
            field::generators::stat_net
            );

         // Формируем интерфейс для рисования поля.
        m_draw_tool = &
            draw_tools::factory_t::get_instance(
                draw_tools::net
            );
    }
    else
    if ( m_game_type == "Графы: шахматный конь" ) {

        // Генерируем поле.
        m_generator = &
            field::generators::factory_t::get_instance(
            field::generators::chess_horse
            );

         // Формируем интерфейс для рисования поля.
        m_draw_tool = &
            draw_tools::factory_t::get_instance(
                draw_tools::classic
            );
    }
    else
    if ( m_game_type == "Графы: лабиринт" ) {

        // Генерируем поле.
        m_generator = &
            field::generators::factory_t::get_instance(
            field::generators::labirint
            );

         // Формируем интерфейс для рисования поля.
        m_draw_tool = &
            draw_tools::factory_t::get_instance(
                draw_tools::classic
            );
    }
    else
    if (
        ( m_game_type == "Блоковая: тетрис" ) ||
        ( m_game_type == "Блоковая: триплекс" ) ||
        ( m_game_type == "Блоковая: дубль" )
        )
         {

        // Генерируем поле.
        m_generator = &
            field::generators::factory_t::get_instance(
            field::generators::tetris
            );

        // Формируем интерфейс для рисования поля.
        m_draw_tool = &
            draw_tools::factory_t::get_instance(
                draw_tools::tetris
            );
    }
    else return;

    if (standard_field_create) {

        m_field = m_generator->generate( m_info );

        static_cast<draw_tools::builder::abstract_t*>
            (m_draw_tool)->set_shadow(
                *(Image1->Canvas)
            ,   TRect( 0, 0, Image1->Width, Image1->Height) );

        static_cast<draw_tools::builder::abstract_t*>
            (m_draw_tool)->set_main(
                *(Main_Form->Canvas)
        ,   TRect( 0, 0, Image1->Width, Image1->Height) );

        static_cast<draw_tools::builder::abstract_t*>
            (m_draw_tool)->set_fon( ImageFon );
    }

    start_game();
}

void
TMain_Form::clear_gametype_checks() {
    Beginner1->Checked = false;
    Intermediate1->Checked = false;
    Professional1->Checked = false;
    Triangle1->Checked = false;
    Sixangle1->Checked = false;
    Custom1->Checked = false;
    Fiveangle1->Checked = false;
    StatNet1->Checked = false;
    ChessHorse1->Checked = false;
    Labirint1->Checked = false;
    Tetris1->Checked = false;
    Triplex1->Checked = false;
    Duplex1->Checked = false;
}

//---------------------------------------------------------------------------

void __fastcall TMain_Form::Sixangle1Click(TObject *Sender)
{
    if ( m_game_is_active ) {
        end_game();
    }
    clear_gametype_checks();
    Sixangle1->Checked = true;

    // Данные для Sixangle.
    m_info.m_element_size_x = 27;
    m_info.m_element_size_y = 27;
    m_info.m_size_x = 18;
    m_info.m_size_y = 30;
    m_info.m_bomb_number = 100;
    m_info.m_size_px_x = Image1->Width;
    m_info.m_size_px_y = Image1->Height - c_dy_menu;

    m_game_type = "Паркет: шестиугольники";
    m_game_condition = one_level;

    NewGameClick( Sender );
}
//---------------------------------------------------------------------------

void __fastcall TMain_Form::Fiveangle1Click(TObject *Sender)
{
    if ( m_game_is_active ) {
        end_game();
    }
    clear_gametype_checks();
    Fiveangle1->Checked = true;

    // Данные для Fiveangle.
    m_info.m_element_size_x = 18;
    m_info.m_element_size_y = 18;
    m_info.m_size_x = 40;
    m_info.m_size_y = 12;
    m_info.m_bomb_number = 80;
    m_info.m_size_px_x = Image1->Width;
    m_info.m_size_px_y = Image1->Height - c_dy_menu;

    m_game_type = "Паркет: четырехугольники";
    m_game_condition = one_level;

    NewGameClick( Sender );
}
//---------------------------------------------------------------------------

void __fastcall TMain_Form::StatNet1Click(TObject *Sender)
{
    if ( m_game_is_active ) {
        end_game();
    }
    clear_gametype_checks();
    StatNet1->Checked = true;

    // Данные для StatNet.
    m_info.m_element_size_x = 18;
    m_info.m_element_size_y = 18;
    m_info.m_size_x = 0;
    m_info.m_size_y = 0;
    m_info.m_bomb_number = 80;
    m_info.m_elements_number = 400;
    m_info.m_size_px_x = Image1->Width;
    m_info.m_size_px_y = Image1->Height - c_dy_menu;

    m_game_type = "Графы: статическая сеть";
    m_game_condition = one_level;

    NewGameClick( Sender );
}
//---------------------------------------------------------------------------

void __fastcall TMain_Form::ChessHorse1Click(TObject *Sender)
{
    if ( m_game_is_active ) {
        end_game();
    }
    clear_gametype_checks();
    ChessHorse1->Checked = true;

    // Данные для ChessHorse.
    m_info.m_element_size_x = 18;
    m_info.m_element_size_y = 18;
    m_info.m_size_x = 24;
    m_info.m_size_y = 24;
    m_info.m_bomb_number = 100;
    m_info.m_size_px_x = Image1->Width;
    m_info.m_size_px_y = Image1->Height - c_dy_menu;

    m_game_type = "Графы: шахматный конь";
    m_game_condition = one_level;

    NewGameClick( Sender );
}
//---------------------------------------------------------------------------


void __fastcall TMain_Form::Labirint1Click(TObject *Sender)
{
    if ( m_game_is_active ) {
        end_game();
    }
    clear_gametype_checks();
    Labirint1->Checked = true;

    // Данные для Labirint.
    m_info.m_element_size_x = 18;
    m_info.m_element_size_y = 18;
    m_info.m_size_x = 35;
    m_info.m_size_y = 25;
    m_info.m_bomb_number = 80;
    m_info.m_size_px_x = Image1->Width;
    m_info.m_size_px_y = Image1->Height - c_dy_menu;

    m_game_type = "Графы: лабиринт";
    m_game_condition = one_level;

    NewGameClick( Sender );
}
//---------------------------------------------------------------------------

void __fastcall TMain_Form::OptOpalesceClick(TObject *Sender)
{
    // Пользователь выбирает цвета.
    ShowMessage(
        "Выберите два цвета перелива.\n"
        "Первый будет сверху, второй - снизу.\n"
        "Отмена любого из цветов вызовет отмену установки нового фона." );

    TColor top;
    TColor bottom;

    if (ColorDialog1->Execute()) {
        top = ColorDialog1->Color;
    }
    else return;
    if (ColorDialog1->Execute()) {
        bottom = ColorDialog1->Color;
    }
    else return;

    set_opalesce( top, bottom );

    global_options_t::get_instance().set_background_type(
        global_options_t::picture );

    OptOpalesce->Checked = true;
    Main_Form->Refresh();
    refresh_info();
}
//---------------------------------------------------------------------------

void __fastcall TMain_Form::OptLoadClick(TObject *Sender)
{
    if (OpenPictureDialog1->Execute()) {

        try {
            ImageFon->Picture->LoadFromFile( OpenPictureDialog1->FileName );

            OptLoad->Checked = true;

            global_options_t::get_instance().set_background_type(
                global_options_t::picture );
        }
        catch( EInvalidGraphic & ex ) {
            ShowMessage(
                "Неподдерживаемый формат изображения.\n"
                "Рекомендуемый формат: BMP OS/2 24bit" );
        }
    }
}
//---------------------------------------------------------------------------

void __fastcall TMain_Form::Tetris1Click(TObject *Sender)
{
    if ( m_game_is_active ) {
        end_game();
    }
    clear_gametype_checks();
    Tetris1->Checked = true;

    // Данные для Tetris.
    m_info.m_element_size_x = 18;
    m_info.m_element_size_y = 18;
    m_info.m_size_x = 40;
    m_info.m_size_y = 26;
    m_info.m_bomb_number = 80;
    m_info.m_size_px_x = Image1->Width;
    m_info.m_size_px_y = Image1->Height - c_dy_menu;
    // Тетрис.
    m_info.m_tag = 4;

    m_game_type = "Блоковая: тетрис";
    m_game_condition = one_level;

    NewGameClick( Sender );
}
//---------------------------------------------------------------------------

void __fastcall TMain_Form::Duplex1Click(TObject *Sender)
{
    if ( m_game_is_active ) {
        end_game();
    }
    clear_gametype_checks();
    Duplex1->Checked = true;

    // Данные для Duplex.
    m_info.m_element_size_x = 18;
    m_info.m_element_size_y = 18;
    m_info.m_size_x = 40;
    m_info.m_size_y = 26;
    m_info.m_bomb_number = 100;
    m_info.m_size_px_x = Image1->Width;
    m_info.m_size_px_y = Image1->Height - c_dy_menu;
    // Duplex.
    m_info.m_tag = 2;

    m_game_type = "Блоковая: дубль";
    m_game_condition = one_level;

    NewGameClick( Sender );
}
//---------------------------------------------------------------------------

void __fastcall TMain_Form::Triplex1Click(TObject *Sender)
{
    if ( m_game_is_active ) {
        end_game();
    }
    clear_gametype_checks();
    Triplex1->Checked = true;

    // Данные для Triplex.
    m_info.m_element_size_x = 18;
    m_info.m_element_size_y = 18;
    m_info.m_size_x = 40;
    m_info.m_size_y = 27;
    m_info.m_bomb_number = 100;
    m_info.m_size_px_x = Image1->Width;
    m_info.m_size_px_y = Image1->Height - c_dy_menu;
    // Triplex.
    m_info.m_tag = 3;

    m_game_type = "Блоковая: триплекс";
    m_game_condition = one_level;

    NewGameClick( Sender );
}
//---------------------------------------------------------------------------

