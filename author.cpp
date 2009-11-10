//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include <math>

#include "author.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TF_Author *F_Author;
//---------------------------------------------------------------------------
__fastcall TF_Author::TF_Author(TComponent* Owner)
    : TForm(Owner)
{
}
//---------------------------------------------------------------------------

void __fastcall TF_Author::FormClose(TObject *Sender, TCloseAction &Action)
{
//    Timer1->Enabled = false;
}
//---------------------------------------------------------------------------

void __fastcall TF_Author::FormShow(TObject *Sender)
{
//        Timer1->Enabled = true;
}
//---------------------------------------------------------------------------

void __fastcall TF_Author::Timer1Timer(TObject *Sender)
{
    const int c_number = 50;
    const int c_number_lines = 3;
    const int c_r = 40;
    const int c_rh = 3;
    const float c_speed = 10.0;
    const float c_height = Height - 60;

    static int time = 0;
    ++time;

    for( int i = 0; i < c_number; ++i ) {

        for( int j = 1; j <= c_number_lines; ++j ) {

        float dj = 2*j*3.14/c_number_lines;

        Canvas->Pixels
            [ Memo1->Width + 10 + c_r * ( 1 + cos((time-1+i*1.5)/c_speed + dj) ) ]
            [ 15 + i*c_height/c_number + c_rh * sin((time-1+i*1.5)/c_speed + dj) ]
            = clBlack;

        Canvas->Pixels
            [ Memo1->Width + 10 + c_r * ( 1 + cos( (time+i*1.5)/c_speed + dj) ) ]
            [ 15 + i*c_height/c_number  + c_rh * sin((time+i*1.5)/c_speed + dj) ]
            = clWhite;
        }
    }

//    Refresh();

}
//---------------------------------------------------------------------------
