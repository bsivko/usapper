#include "field/field.hpp"

namespace field {

field_t::field_t( const info_t & info ) : m_info(info) {
}

void
field_t::add_element( const element_t & element ) {
    m_elements.push_back( element );
}

int
field_t::get_element_by_click( int x, int y ) {

	for( unsigned int i = 0; i < m_elements.size(); ++i ) {

        element_t & it = m_elements[i];

        const int lx = it.x() - m_info.m_element_size_x / 2 + 1;
        const int ly = it.y() - m_info.m_element_size_y / 2 + 1;
        const int rx = it.x() + m_info.m_element_size_x / 2 - 1;
        const int ry = it.y() + m_info.m_element_size_y / 2 - 1;

		if ( (x > lx) && (x < rx) && (y > ly) && (y < ry) )
		{
			return static_cast<int>(i);
		}
	}

    return -1;
}

int
field_t::count_of_near_bombs( int index ) const {

    int result = 0;

    element_t element = m_elements[index];

    for( unsigned int i = 0; i < element.near_elements().size(); ++i ) {

        if ( m_elements[ element.near_elements()[i] ].is_bomb() ) {
            ++result;
        }
    }

    return result;
}

int
field_t::count_of_near_flags( int index ) const {

    int result = 0;

    element_t element = m_elements[index];

    for( unsigned int i = 0; i < element.near_elements().size(); ++i ) {

        if ( m_elements[ element.near_elements()[i] ].is_flag() ) {
            ++result;
        }
    }

    return result;
}

int
field_t::count_of_near_not_open( int index ) const {

    int result = 0;

    element_t element = m_elements[index];

    for( unsigned int i = 0; i < element.near_elements().size(); ++i ) {

        if ( !(m_elements[ element.near_elements()[i] ].is_open()) ) {
            ++result;
        }
    }

    return result;
}

//! –екурсивно открыть клетку (по 0-м).
bool
field_t::open( int index ) {

    m_elements[index].open();
    if ( m_elements[index].is_bomb() )
        return true;
    if ( count_of_near_bombs(index) != 0 )
        return false;

    std::vector <int> to_open;
    std::vector <int> new_to_open;
    to_open.push_back( index );

    do {
        new_to_open.clear();
        for( unsigned int i = 0; i < to_open.size(); ++i ) {
            for( unsigned int j = 0; j < m_elements[to_open[i]].near_elements().size(); ++j ) {
                int l = m_elements[to_open[i]].near_elements()[j];
                if ( !(m_elements[l].is_open()) ) {
                    m_elements[l].open();
                    if ( count_of_near_bombs(l) == 0 ) {
                        new_to_open.push_back( l );
                    }
                }
            }
        }
        to_open = new_to_open;
    }
    while( new_to_open.size() > 0 );

    return false;
}

//! –екурсивно открыть клетку (по 0-м).
bool
field_t::open_near( int index ) {

    bool result = false;

    for(
        unsigned int i = 0;
        i < m_elements[index].near_elements().size();
        ++i ) {

        int l = m_elements[index].near_elements()[i];

        // Ёлемент должен быть открыт,
        if ( !m_elements[l].is_open() ) {
            // без флага.
            if ( !m_elements[l].is_flag() ) {
                result |= open( l );
            }
        }
    }

    return result;
}

void
field_t::uncheck_all() {

	for( unsigned int i = 0; i < m_elements.size(); ++i ) {
        m_elements[i].unset_check();
    }
}

void
field_t::check( int index ) {
    m_elements[index].set_check();
}

void
field_t::check_near( int index ) {

    for(
        unsigned int i = 0;
        i < m_elements[index].near_elements().size();
        ++i ) {

        m_elements[m_elements[index].near_elements()[i]].set_check();
    }
}

int
field_t::count_of_all_flags() {

    int result = 0;

    for( unsigned int i = 0; i < m_elements.size(); ++i ) {
        if (m_elements[i].is_flag()) {
            ++result;
        }
    }

    return result;
}

bool
field_t::is_complete() {

    // ”словие выполнени€ - открыты все клетки, где нет бомб.
    for( unsigned int i = 0; i < m_elements.size(); ++i ) {
        // »щем хот€ бы одну клетку, в которой нет бомбы и она не открыта.
        if ( !m_elements[i].is_open() && !m_elements[i].is_bomb() ) {
            return false;
        }
    }

    return true;
}


} // namespace field

