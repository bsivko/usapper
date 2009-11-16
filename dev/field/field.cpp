#include "field/field.hpp"

#include <stdlib.h>

#include <fstream>

#include <vector>
#include <algorithm>

namespace field {

//! ��������� ������ �������� ��� think'a.
struct one_set_t {

    //! ����� ��� � ���������.
    int m_bombs;

    //! ID ��������� ���������. �������� � ��������������� ����.
    std::vector <int> m_ids;

    one_set_t( int bombs, const std::vector<int> ids ) :
        m_bombs(bombs), m_ids(ids)
    {
        std::sort( m_ids.begin(), m_ids.end() );
    }

    //! ������ ���������.
    one_set_t() : m_bombs(0), m_ids(0) {}

    //! �������� �� �� ��� in � *this ?
    bool
    is_in( const one_set_t & in ) {
        // ����� �� this.
        unsigned int i = 0;
        // ����� �� in.
        unsigned int j = 0;
        while( i < m_ids.size() ) {

            int ids_i = m_ids[i];
            int ids_j = in.m_ids[j];

            while(
                ( j < in.m_ids.size() )&&
                ( i < m_ids.size() )&&
                ( in.m_ids[j] == m_ids[i] ) ) {
                ++j;
                ++i;
            }

            if ( j >= in.m_ids.size() ) {
                return true;
            }

            if ( i >= m_ids.size() ) {
                return false;
            }

            ++i;
        }
        return (j >= in.m_ids.size());
    }

};

//! �������� ��������� �� ������������.
bool
operator != ( const one_set_t & left, const one_set_t & right ) {

    if ( left.m_bombs != right.m_bombs )
        return true;

    if ( left.m_ids.size() != right.m_ids.size() )
        return true;

    for( unsigned int i = 0; i < left.m_ids.size(); ++i ) {
        if ( left.m_ids[i] != right.m_ids[i] )
            return true;
    }

    return false;
}

//! �������� ��������� �� ������������.
bool
operator == ( const one_set_t & left, const one_set_t & right ) {
    return !( left != right );
}

bool
insert_one_set( const one_set_t & to_insert, std::vector< one_set_t > & vec ) {
    if ( std::find( vec.begin(), vec.end(), to_insert ) == vec.end() ) {
        vec.push_back( to_insert );
        return true;
    }
    return false;
}

//! ����� �������� ����� �����������.
/*!
    �� ������ ���������� ������.
    ������������� ��� ��������, ����� ������ ��������� �������� � �����.
*/
one_set_t
operator - ( const one_set_t & left, const one_set_t & right  ) {

    one_set_t result;

    result.m_bombs = left.m_bombs - right.m_bombs;

    unsigned int j = 0;
    for( unsigned int i = 0; i < left.m_ids.size(); ++i ) {

        while(
            ( j < right.m_ids.size() )
            &&
            ( right.m_ids[j] < left.m_ids[i] )
        ) {
            ++j;
        }

        if (
            ( j == right.m_ids.size() )
            ||
            ( right.m_ids[j] != left.m_ids[i] )
        ) {
            result.m_ids.push_back( left.m_ids[i] );
        }
    }

    return result;
}

void
dump_set( std::string & msg, const std::vector<one_set_t> & sets ) {
    std::ofstream dump( "dump", std::ios::out | std::ios::app );
    dump << msg << std::endl;
    for( unsigned int i = 0; i < sets.size(); ++i ) {
        dump << sets[i].m_bombs << "\t";
        for( unsigned int j = 0; j < sets[i].m_ids.size(); ++j ) {
            dump << sets[i].m_ids[j] << "\t";
        }
        dump << std::endl;
    }
    dump.close();
}

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

    		// ��������� ������ ��� ��������, ��� ����� ������ ��������� ��.
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

        		// ��������� ������ ��� ��������, ��� ����� ������ ��������� ��.
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

//! ���������� ������� ������ (�� 0-�).
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

//! ���������� ������� ������ (�� 0-�).
bool
field_t::open_near( int index ) {

    bool result = false;

    for(
        unsigned int i = 0;
        i < m_elements[index].near_elements().size();
        ++i ) {

        int l = m_elements[index].near_elements()[i];

        // ������� ������ ���� ������,
        if ( !m_elements[l].is_open() ) {
            // ��� �����.
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

    // ������� ���������� - ������� ��� ������, ��� ��� ����.
    for( unsigned int i = 0; i < m_elements.size(); ++i ) {
        // ���� ���� �� ���� ������, � ������� ��� ����� � ��� �� �������.
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
            // ������� ������.
            m_elements[i].is_open() &&
            // ����� ����� ������� ��� ����� ����� ������.
            ( near_bombs == near_flags ) &&
            // � ��� ���� ���� ��� ���������.
            ( near_not_open > near_flags )
            ) {

            // ��������� ����� �� �������� ��� �����.
            for( unsigned int j = 0; j < m_elements[i].near_elements().size(); ++j ) {
                int index = m_elements[i].near_elements()[j];
                if ( !m_elements[index].is_open() && !m_elements[index].is_flag() ) {
                    results.push_back(
                        think_result_t( index, think_result_t::open_element ) );
                }
            }
        }

        if (
            // ������� ������.
            m_elements[i].is_open() &&
            // ����� �������� ����� ����� ����.
            ( near_bombs == near_not_open ) &&
            // � ��� ���� ���� ���� ������� �����.
            ( near_not_open > near_flags )
        )
        {
            // ������ ���� � ����� ���������� ��� �����.
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
            // ������� ������.
            m_elements[i].is_open() &&
            // ����� ������ ������ ����� ����� ������� ���.
            ( near_flags > near_bombs )
         ) {
            return think_result_t( i, think_result_t::error );
        }
    }

    // ������ �� �����. ��������� �� ������ ����� ������ AI.
    if (results.size() == 0) {
        // ���� - ����� ��� �� ���������.
        // ������ - ��������� ID ���������, � ������� ���������� ����.
        std::vector<one_set_t> sets;

        // ��������� ���������.
        for( unsigned int i = 0; i < m_elements.size(); ++i ) {
            if  (
                // ��� ������� ��������� �������� ����� ������������ ���� ���������.
                m_elements[i].is_open()
                &&
                // ��� ���� ������� ������ ��������� � ������������ ����������.
                (count_of_near_not_open( i ) > 0)
                &&
                // � ���-�� ����������� �� ������ ����������� �������.
                (count_of_near_flags( i ) < count_of_near_not_open( i ) )
                ) {

                // ���������.

                std::vector <int> ids;
                for( unsigned int j = 0; j < m_elements[i].near_elements().size(); ++j ) {
                    if (
                        (!m_elements[ m_elements[i].near_elements()[j] ].is_open())
                        &&
                        (!m_elements[ m_elements[i].near_elements()[j] ].is_flag())
                    ) {
                        ids.push_back( m_elements[i].near_elements()[j] );
                    }
                }

                // ��������� � ����� �����.
                insert_one_set(
                    one_set_t( count_of_near_bombs( i ) - count_of_near_flags( i ), ids )
                ,   sets
                );
            }
        }

        dump_set( std::string("start"), sets );

        // ������� �������� ���� �������� ���� � ������.
        // ������ ���, ��� ��������� �������� ������.
        bool is_insert = true;
        while( is_insert ) {
            is_insert = false;
            unsigned int size = sets.size();
            for( unsigned int i = 0; i < size; ++i ) {
                for( unsigned int j = 0; j < size; ++j ) {
                    if (i == j) continue;
                    if ( sets[i].is_in( sets[j] ) ) {

                        one_set_t diff = sets[i] - sets[j];

                        // �������� �������� ��� ��������.
                        if (diff.m_ids.size() > 0) {
                            is_insert |= insert_one_set( diff, sets );
                        }
                    }
                }
            }
        }

        dump_set( std::string("proc_diffs"), sets );

        // ������� �� ���������, � ������� ����� ��� ����� ����� ������.
        // ��� ��������, ��� � ��� ��� - ����.
        for( unsigned int i = 0; i < sets.size(); ++i ) {
            if ( static_cast<unsigned int>(sets[i].m_bombs) == sets[i].m_ids.size() ) {
                for( unsigned j = 0; j < sets[i].m_ids.size(); ++j ) {
                    // ���� ��� ����� ����, �� ������� ��� �� �����.
                    if ( !m_elements[sets[i].m_ids[j]].is_flag() ) {
                        results.push_back(
                            think_result_t(
                                sets[i].m_ids[j]
                            ,   think_result_t::set_flag )
                        );
                    }
                }
            }
        }

        // ������� �� ���������, � ������� ����� ��� ����� ����.
        // ��� ��������, ��� � ��� ��� - ��� ���.
        for( unsigned int i = 0; i < sets.size(); ++i ) {
            if ( static_cast<unsigned int>(sets[i].m_bombs) == 0 ) {
                for( unsigned j = 0; j < sets[i].m_ids.size(); ++j ) {
                    results.push_back(
                        think_result_t(
                            sets[i].m_ids[j]
                        ,   think_result_t::open_element )
                    );
                }
            }
        }
    }

    // ������ ������ �� �����.
    if (results.size() == 0) {

        // ����� �� �� ������� ���-��?
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

