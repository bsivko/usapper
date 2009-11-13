#include "field/element.hpp"

#include <stdlib.h>
#include "global_options.hpp"

namespace field {

element_t::element_t( int x, int y, bool is_bomb ) :
    m_x( x )
,   m_y( y )
,   m_is_open( false )
,   m_is_bomb( is_bomb )
,   m_is_flag( false )
,   m_checked( false )
,   m_type( 0 )
,   m_data( 0 )  {
    set_blink( 0 );
}

void
element_t::open() {
    m_is_open = true;
//    m_is_flag = false;
    set_blink( global_options_t::get_instance().blink_time() );
}


void
element_t::add_near_element( int i ) {

    for(
        std::vector<int>::iterator it = m_near_elements.begin();
        it != m_near_elements.end();
        ++it ) {

        // Присутствует уже элемент.
        if ( *it==i )
            return;
    }

    m_near_elements.push_back(i);
}

//! Мигает клетка или нет.
bool
element_t::is_blink() const {
    return ( m_blink_time > clock() );
}

        //! Установить мигание клетки на заданное число секунд.
void
element_t::set_blink( int sec ) {
    m_blink_time = clock() +  sec * CLOCKS_PER_SEC;
}


} // namespace field

