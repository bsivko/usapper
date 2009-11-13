//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include <Types.hpp>

#include "score_table.h"
#include "high_scores/high_scores.hpp"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TF_Score_Table *F_Score_Table;
//---------------------------------------------------------------------------
__fastcall TF_Score_Table::TF_Score_Table(TComponent* Owner)
    : TForm(Owner), m_first_refresh(false) {

}

void
TF_Score_Table::set_tables(
    const high_scores::tables_t & tables
) {
    m_tables = tables;
    ComboBox1->Items->Clear();
    for(
        std::map<std::string, high_scores::one_table_t>::iterator it =
            m_tables.m_tables.begin();
        it != m_tables.m_tables.end();
        ++it
    ) {
        ComboBox1->Items->Add( (it->first).c_str() );
    }
    ComboBox1->Text = ComboBox1->Items[0][0];

    show_table(
        ComboBox1->Text.c_str()
    ,   m_tables.m_tables.begin()->second );
}

void
TF_Score_Table::show_table(
    const std::string & game_type
,   const high_scores::one_table_t & one_table ) {

    Canvas->Pen->Color = clSilver;
    Canvas->Brush->Color = clSilver;
    Canvas->Rectangle( 0, 0, Width, Height );

    Canvas->Font->Color = clBlack;
    Canvas->Pen->Color = clBlack;
    Canvas->Brush->Color = clSilver;

    Canvas->TextOutA(
        ComboBox1->Left,
        ComboBox1->Top - 2 * abs(Canvas->Font->Size),
        "Таблицы рекордов:" );

    Caption = game_type.c_str();

    // Позиция записей номера по вертикали.
    const int c_x_number = 10;
    // Позиция записей имен по вертикали.
    const int c_x_name = 100;
    // Позиция записей очков по вертикали.
    const int c_x_score = 200;
    // Позиция записей времени по вертикали.
    const int c_x_time = 270;
    // Позиция записей жив или нет по вертикали.
    const int c_x_alive = 30;

    // Позиция отображения строчки по вертикали.
    int y_pos = 60;

    int number = 1;

    Canvas->Font->Style = TFontStyles()<< fsBold << fsUnderline;

    Canvas->TextOutA( c_x_number, y_pos, "N'" );
    Canvas->TextOutA( c_x_name, y_pos, "Имя" );
    Canvas->TextOutA( c_x_score, y_pos, "Очки" );
    Canvas->TextOutA( c_x_time, y_pos, "Время" );
    Canvas->TextOutA( c_x_alive, y_pos, "В живых" );

    Canvas->Font->Style = TFontStyles()<< fsBold;

    for(
        std::vector<high_scores::record_t>::const_iterator it =
            one_table.m_records.begin();
        it != one_table.m_records.end();
        ++it ) {

        y_pos += 16;

        Canvas->Font->Color = clBlack;
        Canvas->Pen->Color = clBlack;
        Canvas->Brush->Color = clSilver;

        Canvas->TextOutA( c_x_number, y_pos, IntToStr(number) + "." );
        Canvas->TextOutA( c_x_name, y_pos, it->m_name.c_str() );
        Canvas->TextOutA( c_x_score, y_pos, IntToStr(it->m_score) );
        Canvas->TextOutA( c_x_time, y_pos, it->m_time.c_str() );
        if (!it->m_alive) {
            Canvas->Pen->Color = clBlack;
            Canvas->MoveTo(c_x_alive, y_pos + 10);
            Canvas->LineTo(c_x_alive + 10, y_pos + 10);

            Canvas->Brush->Color = clGray;
            Types::TPoint points[9];
            points[0] = Point( c_x_alive + 1, y_pos + 10 );
            points[1] = Point( c_x_alive + 1, y_pos + 3  );
            points[2] = Point( c_x_alive + 2, y_pos + 1  );
            points[3] = Point( c_x_alive + 4, y_pos + 0  );
            points[4] = Point( c_x_alive + 6, y_pos + 0  );
            points[5] = Point( c_x_alive + 7, y_pos + 1  );
            points[6] = Point( c_x_alive + 8, y_pos + 2  );
            points[7] = Point( c_x_alive + 8, y_pos + 10 );
            points[8] = Point( c_x_alive + 1, y_pos + 10 );
            Canvas->Polygon(points, 8);

            Canvas->Pixels[c_x_alive + 3][ y_pos + 4 ] = clBlack;
            Canvas->Pixels[c_x_alive + 4][ y_pos + 3 ] = clBlack;
            Canvas->Pixels[c_x_alive + 5][ y_pos + 5 ] = clBlack;
            Canvas->Pixels[c_x_alive + 6][ y_pos + 4 ] = clBlack;

            Canvas->Brush->Color = clBtnFace;
        }
        else {
            Canvas->Pen->Color = clRed;
            Canvas->Brush->Color = clRed;
            Types::TPoint points[16];
            points[ 0] = Point( c_x_alive + 5, y_pos + 10 );
            points[ 1] = Point( c_x_alive + 0, y_pos + 5  );
            points[ 2] = Point( c_x_alive + 0, y_pos + 3  );
            points[ 3] = Point( c_x_alive + 1, y_pos + 2  );
            points[ 4] = Point( c_x_alive + 3, y_pos + 2  );
            points[ 5] = Point( c_x_alive + 4, y_pos + 3  );
            points[ 6] = Point( c_x_alive + 4, y_pos + 4  );
            points[ 7] = Point( c_x_alive + 5, y_pos + 5 );
            points[ 8] = Point( c_x_alive + 6, y_pos + 4  );
            points[ 9] = Point( c_x_alive + 6, y_pos + 3  );
            points[10] = Point( c_x_alive + 7, y_pos + 2  );
            points[11] = Point( c_x_alive + 9, y_pos + 2  );
            points[12] = Point( c_x_alive + 10, y_pos + 3  );
            points[13] = Point( c_x_alive + 10, y_pos + 5  );
            points[14] = Point( c_x_alive + 5, y_pos + 10 );
            Canvas->Polygon(points, 14);
        }

        ++number;
    }
}
//---------------------------------------------------------------------------
void __fastcall TF_Score_Table::ComboBox1Change(TObject *Sender)
{
    std::string name = ComboBox1->Items[0][ComboBox1->ItemIndex].c_str();

    show_table(
        name
    ,   m_tables.m_tables[name] );
}
//---------------------------------------------------------------------------

void
TF_Score_Table::first_refresh() {
    m_first_refresh = true;
}

void __fastcall TF_Score_Table::Timer1Timer(TObject *Sender)
{
    if ( m_first_refresh ) {
        m_first_refresh = false;

        ComboBox1->Items[0][ComboBox1->ItemIndex] =
            m_tables.m_tables.begin()->first.c_str();

        ComboBox1Change(Sender);
    }
}
//---------------------------------------------------------------------------

