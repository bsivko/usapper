#include "draw_tools/builder/sixangle.hpp"

namespace draw_tools {

namespace builder {

void
sixangle_t::drawer_t::draw_number(
    const field::element_t & element, int number ) {

    if (element.checked()) {
        m_canvas.Pen->Color = clBlue;
    }
    else {
        m_canvas.Pen->Color = clBlack;
    }

    // ����.
    m_canvas.Brush->Color = clSilver;
    if (number == 0) {
        m_canvas.Brush->Color = clGray;
    }
    draw_sixangle( m_canvas, element );

    // �����.
    const TColor colors[12] = {
        /*0*/ clWhite, clBlue, clGreen, clRed,
        /*4*/ clPurple, clNavy, clAqua, clMaroon,
        /*8*/ clBlack, clBlack, clBlack, clBlack
    };

    if ( number <= 7 ) {
        m_canvas.Font->Color = colors[ number ];
    }
    else {
        m_canvas.Font->Color = clBlack;
    }
    m_canvas.Font->Style = TFontStyles()<< fsBold;
    if (number == 0) return;
    m_canvas.Font->Size = 6;
    m_canvas.TextOutA(
        element.x() - 3
    ,   element.y() - 6
    ,   IntToStr(number) );
}

void
sixangle_t::drawer_t::draw_unknown( const field::element_t & element ) {

    if (element.checked()) {
        m_canvas.Pen->Color = clBlue;
    }
    else {
        m_canvas.Pen->Color = clGray;
    }

    m_canvas.Brush->Color = clSilver;
    draw_sixangle( m_canvas, element );
}

void
sixangle_t::drawer_t::draw_flag( const field::element_t & element ) {

    if (element.checked()) {
        m_canvas.Pen->Color = clBlue;
    }
    else {
        m_canvas.Pen->Color = clBlack;
    }

    m_canvas.Brush->Color = clSilver;
    draw_sixangle( m_canvas, element );

    int x = element.x() + 2;
    int y = element.y();

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
sixangle_t::drawer_t::draw_explode_bomb( const field::element_t & element ) {

    if (element.checked()) {
        m_canvas.Pen->Color = clBlue;
    }
    else {
        m_canvas.Pen->Color = clBlack;
    }

    m_canvas.Brush->Color = clSilver;
    draw_sixangle( m_canvas, element );

    m_canvas.Pen->Color = clRed;

    int x = element.x() + 2;
    int y = element.y();
    
    m_canvas.MoveTo( x-4, y-4 );
    m_canvas.LineTo( x+5, y+5 );
    m_canvas.MoveTo( x-4, y+4 );
    m_canvas.LineTo( x+5, y-5 );

    m_canvas.MoveTo( x-6, y );
    m_canvas.LineTo( x+7, y );
    m_canvas.MoveTo( x, y+6 );
    m_canvas.LineTo( x, y-7 );
}

//! ���������� ����� ����� �������.
void
sixangle_t::drawer_t::draw_link(
    const field::element_t & element1
,   const field::element_t & element2 ) {

    m_canvas.Pen->Color = clBlue;
    m_canvas.MoveTo( element1.x(), element1.y() );
    m_canvas.LineTo( element2.x(), element2.y() );
}

void
sixangle_t::drawer_t::draw_flag_error( const field::element_t & element ) {
    draw_flag( element );

    m_canvas.Pen->Color = clYellow;
    m_canvas.Pen->Width = 2;

    int x = element.x();
    int y = element.y();

    m_canvas.MoveTo( x-5, y-5 );
    m_canvas.LineTo( x+5, y+5 );
    m_canvas.MoveTo( x-5, y+5 );
    m_canvas.LineTo( x+5, y-5 );

    m_canvas.Pen->Width = 1;
}

void
sixangle_t::draw(
	const field::field_t & field ) {

    // ���� ������������� ������.
    drawer_t drawer(
        // ������ � ����.
        this->shadow_canvas()
    ,   field.info()
    ,   blink() );

    // �������� ������ ���� ����, ��� ��������� ��������� �����.
    drawer.draw_elements( field );
//    drawer.draw_net( field );
}


} // namespace builder

} // namespace draw_tools

