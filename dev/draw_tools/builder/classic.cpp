#include "draw_tools/builder/classic.hpp"

namespace draw_tools {

namespace builder {

void
classic_t::drawer_t::draw_number( int x, int y, int number, bool check ) {

    if (check) {
        m_canvas.Pen->Color = clBlue;
    }
    else {
        m_canvas.Pen->Color = clBlack;
    }

    // Поле.
    m_canvas.Brush->Color = clSilver;
    if (number == 0) {
        m_canvas.Brush->Color = clGray;
    }
    m_canvas.Rectangle(
        x - m_info.m_element_size_x / 2
    ,   y - m_info.m_element_size_y / 2
    ,   x + m_info.m_element_size_x / 2
    ,   y + m_info.m_element_size_y / 2 );

    // Число.
    const TColor colors[9] = {
        /*0*/ clWhite, clBlue, clGreen, clRed,
        /*4*/ clPurple, clNavy, clAqua, clMaroon,
        /*8*/ clBlack
    };

    if ( number <= 8 ) {
        m_canvas.Font->Color = colors[ number ];
    }
    else {
        m_canvas.Font->Color = clBlack;
    }
    m_canvas.Font->Style = TFontStyles()<< fsBold;
    if (number == 0) return;
    m_canvas.Font->Size = 8;
    m_canvas.TextOutA(
        x - m_info.m_element_size_x / 2 + 5
    ,   y - m_info.m_element_size_y / 2 + 2
    ,   IntToStr(number) );
}

void
classic_t::drawer_t::draw_unknown( int x, int y, bool check ) {

    if (check) {
        m_canvas.Pen->Color = clBlue;
    }
    else {
        m_canvas.Pen->Color = clGray;
    }

    m_canvas.Brush->Color = clSilver;
    m_canvas.Rectangle(
        x - m_info.m_element_size_x / 2
    ,   y - m_info.m_element_size_y / 2
    ,   x + m_info.m_element_size_x / 2
    ,   y + m_info.m_element_size_y / 2 );
}

void
classic_t::drawer_t::draw_flag( int x, int y, bool check ) {

    if (check) {
        m_canvas.Pen->Color = clBlue;
    }
    else {
        m_canvas.Pen->Color = clGray;
    }

    m_canvas.Brush->Color = clSilver;
    m_canvas.Rectangle(
        x - m_info.m_element_size_x / 2
    ,   y - m_info.m_element_size_y / 2
    ,   x + m_info.m_element_size_x / 2
    ,   y + m_info.m_element_size_y / 2 );

    m_canvas.Pen->Color = clMaroon;
    m_canvas.Brush->Color = clRed;

    m_canvas.MoveTo( x-4, y-6 );
    m_canvas.LineTo( x-4, y+6 );
    m_canvas.MoveTo( x-5, y-6 );
    m_canvas.LineTo( x-5, y+6 );

    m_canvas.Pen->Color = clRed;
    TPoint points[3];
    points[0] = Point(x-3, y-6);
    points[1] = Point(x+3, y-4);
    points[2] = Point(x-3, y-2);
    m_canvas.Polygon(points, 3);
}

void
classic_t::drawer_t::draw_explode_bomb( int x, int y, bool check ) {

    if (check) {
        m_canvas.Pen->Color = clBlue;
    }
    else {
        m_canvas.Pen->Color = clBlack;
    }

    m_canvas.Brush->Color = clSilver;
    m_canvas.Rectangle(
        x - m_info.m_element_size_x / 2
    ,   y - m_info.m_element_size_y / 2
    ,   x + m_info.m_element_size_x / 2
    ,   y + m_info.m_element_size_y / 2 );

    m_canvas.Pen->Color = clRed;

    m_canvas.MoveTo( x-4, y-4 );
    m_canvas.LineTo( x+5, y+5 );
    m_canvas.MoveTo( x-4, y+4 );
    m_canvas.LineTo( x+5, y-5 );

    m_canvas.MoveTo( x-6, y );
    m_canvas.LineTo( x+7, y );
    m_canvas.MoveTo( x, y+6 );
    m_canvas.LineTo( x, y-7 );
}

//! Нарисовать связь между точками.
void
classic_t::drawer_t::draw_link( int x1, int y1, int x2, int y2 ) {
    m_canvas.Pen->Color = clBlue;
    m_canvas.MoveTo( x1, y1 );
    m_canvas.LineTo( x2, y2 );
}


void
classic_t::draw(
	const field::field_t & field ) {

    // Этим рисовальщиком рисуем.
    drawer_t drawer(
        // Рисуем в тени.
        this->shadow_canvas()
    ,   field.info()
    ,   blink() );

    // Рисуются только сами поля, без связующих элементов графа.
    drawer.draw_elements( field );

//    drawer.draw_net( field );
}


} // namespace builder

} // namespace draw_tools

