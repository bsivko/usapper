#include "field/field.hpp"

#include <stdlib.h>

namespace field {

field_t::field_t( const info_t & info ) : m_info(info) {
}

void
field_t::add_element( const element_t & element ) {
    m_elements.push_back( element );
}

int
field_t::get_element_by_click( int x, int y ) {

	int lower_distance = 100;
	int result = -1;

	for( unsigned int i = 0; i < m_elements.size(); ++i ) {

		element_t & it = m_elements[i];

        if (it.blocks().size() == 0) {

    		// Дистанции храним как квадраты, нам важно только сравнение их.
	    	int distance = (it.x() - x)*(it.x() - x) + (it.y() - y) * (it.y() - y);

    		const int lx = it.x() - m_info.m_element_size_x / 2 + 1;
	    	const int ly = it.y() - m_info.m_element_size_y / 2 + 1;
		    const int rx = it.x() + m_info.m_element_size_x / 2 - 1;
    		const int ry = it.y() + m_info.m_element_size_y / 2 - 1;

    		if ( (x > lx) && (x < rx) && (y > ly) && (y < ry) )
	    	{
		    	if ( distance < lower_distance )
    			{
	    			result =  static_cast<int>(i);
		    		lower_distance = distance;
    			}
	    	}
        }
        else {
        	for( unsigned int j = 0; j < it.blocks().size(); ++j ) {

                int e_x = (it.blocks()[j].m_x - it.blocks()[0].m_x) * m_info.m_element_size_x + it.x();
                int e_y = (it.blocks()[j].m_y - it.blocks()[0].m_y) * m_info.m_element_size_y + it.y();

        		// Дистанции храним как квадраты, нам важно только сравнение их.
	        	int distance = (e_x - x)*(e_x - x) + (e_y - y) * (e_y - y);

        		const int lx = e_x - m_info.m_element_size_x / 2 + 1;
	          	const int ly = e_y - m_info.m_element_size_y / 2 + 1;
	    	    const int rx = e_x + m_info.m_element_size_x / 2 - 1;
        		const int ry = e_y + m_info.m_element_size_y / 2 - 1;

    	        if ( (x > lx) && (x < rx) && (y > ly) && (y < ry) )
    	    	{
	    	    	if ( distance < lower_distance )
    	    		{
	    	    		result =  static_cast<int>(i);
    		    		lower_distance = distance;
        			}
	    	    }

            }
        }
	}

	return result;
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

//! Рекурсивно открыть клетку (по 0-м).
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

//! Рекурсивно открыть клетку (по 0-м).
bool
field_t::open_near( int index ) {

    bool result = false;

    for(
        unsigned int i = 0;
        i < m_elements[index].near_elements().size();
        ++i ) {

        int l = m_elements[index].near_elements()[i];

        // Элемент должен быть открыт,
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

    // Условие выполнения - открыты все клетки, где нет бомб.
    for( unsigned int i = 0; i < m_elements.size(); ++i ) {
        // Ищем хотя бы одну клетку, в которой нет бомбы и она не открыта.
        if ( !m_elements[i].is_open() && !m_elements[i].is_bomb() ) {
            return false;
        }
    }

    return true;
}

think_result_t
field_t::think() {

    std::vector <think_result_t> results;

    for( unsigned int i = 0; i < m_elements.size(); ++i ) {

        int near_bombs = count_of_near_bombs( i );
        int near_not_open = count_of_near_not_open( i );
        int near_flags = count_of_near_flags( i );

        if (
            // Элемент открыт.
            m_elements[i].is_open() &&
            // Число рядом стоящих мин равно числу флагов.
            ( near_bombs == near_flags ) &&
            // И при этом есть что открывать.
            ( near_not_open > near_flags )
            ) {

            // Открываем любой не открытый без флага.
            for( unsigned int j = 0; j < m_elements[i].near_elements().size(); ++j ) {
                int index = m_elements[i].near_elements()[j];
                if ( !m_elements[index].is_open() && !m_elements[index].is_flag() ) {
                    results.push_back(
                        think_result_t( index, think_result_t::open_element ) );
                }
            }
        }

        if (
            // Элемент открыт.
            m_elements[i].is_open() &&
            // Число закрытых равно числу бомб.
            ( near_bombs == near_not_open ) &&
            // И при этом есть куда ставить флаги.
            ( near_not_open > near_flags )
        )
        {
            // Ставим флаг в любом неоткрытом без флага.
            for( unsigned int j = 0; j < m_elements[i].near_elements().size(); ++j ) {
                int index = m_elements[i].near_elements()[j];
                if ( !m_elements[index].is_open() && !m_elements[index].is_flag() ) {
                    results.push_back(
                        think_result_t( index, think_result_t::set_flag )
                    );
                }
            }
        }

        if (
            // Элемент открыт.
            m_elements[i].is_open() &&
            // Число флагов больше числа рядом стоящих мин.
            ( near_flags > near_bombs )
         ) {
            return think_result_t( i, think_result_t::error );
        }
    }

    // Ничего не нашли.
    if (results.size() == 0) {

        // Можем ли мы вернуть что-то?
        bool can_to_return = false;
        for( unsigned int i = 0; i < m_elements.size(); ++i ) {
            if  ( !m_elements[i].is_open() && !m_elements[i].is_flag() ) {
                can_to_return = true;
            }
        }

        int number = -1;

        if ( !can_to_return ) {
            return think_result_t( -1, think_result_t::cant_do );
        }
        do {
            number = random( m_elements.size() );
        }
        while( m_elements[number].is_open() || m_elements[number].is_flag() );

        return think_result_t( number, think_result_t::no_solution );
    }

    return results[ random(results.size()) ];
}

} // namespace field

