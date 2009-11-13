#include "field/generators/labirint.hpp"
#include "global_options.hpp"

#include <vector>
#include <math.h>
#include <list>
#include <stdlib.h>
#include <string>

namespace field {

namespace generators {

//! ����� ���������� �������.
template <class T>
class square_t {

    public:
        square_t( int size_x, int size_y ) :
            m_size_x( size_x )
        ,   m_size_y( size_y )
        ,   m_square( size_x*size_y ) {

        }

        //! ������ � ���������.
        T &
        get( int x, int y ) {
            try {
                return m_square.at( x + m_size_x * y );
            }
            catch( std::exception & ex ) {
                std::string str = ex.what();
            }
        }

        int
        size_x() {
            return m_size_x;
        }

        int
        size_y() {
            return m_size_y;
        }

        //! ��������� ������ ����������.
        void
        fill( const T & value ) {
            for(
                std::vector<T>::iterator it = m_square.begin();
                it != m_square.end();
                ++it
                 )  {

                *it = value;
            }
        }

    private:
        std::vector<T> m_square;

        int m_size_x;
        int m_size_y;
};

field::field_t *
labirint_t::generate( const info_t & info ) {

    randomize();

	// ������ �� �������.
	field::field_t * result = new field::field_t( info );

    // ������ ��������.
    square_t<int> square( info.m_size_x, info.m_size_y );
    square.fill( -1 );
    // ����� ���������, next �������� ���������
    // ������ �������� ��� �������� � �������.
    // ���������������� ��� �������.
    int next = 0;

    // ���������� ���������, �� ������� ������ ������.
    std::list <coord_t> coords;

    // ��������� ������� ������.
	for( int i = 0; i < info.m_size_x; ++i ) {
        square.get( i, 0 ) = next++;
        square.get( i, info.m_size_y - 1 ) = next++;
    }
	for( int i = 1; i < info.m_size_y-1; ++i ) {
        square.get( 0, i ) = next++;
        square.get( info.m_size_x - 1, i ) = next++;
    }

    // ��������� ��, ������� ����� ���������.
	for( int i = 1; i < info.m_size_x/2; ++i ) {
        coords.push_back( coord_t(2*i, 0) );
        coords.push_back( coord_t(2*i, info.m_size_y-1) );
    }
	for( int i = 1; i < info.m_size_y/2; ++i ) {
        coords.push_back( coord_t(0, 2*i) );
        coords.push_back( coord_t(info.m_size_x-1, 2*i) );
    }

    while(coords.size() > 0) {

        // �������� ��������� �������.
        int index = random( coords.size() );

        std::list <coord_t>::iterator it = coords.begin();
        for( int i = 1; i < index; ++i )
            ++it;

        // �������, ��� � ���� ���� �����.
        std::vector<coord_t> near;
        // �����.
        if (( it->m_x > 0 ) && ( square.get(it->m_x-2, it->m_y) == -1 )) {
            near.push_back( coord_t(it->m_x-2, it->m_y) );
        }
        // ������.
        if (( it->m_x < square.size_x()-1 ) && ( square.get(it->m_x+2, it->m_y) == -1 )) {
            near.push_back( coord_t(it->m_x+2, it->m_y) );
        }
        // �����.
        if (( it->m_y > 0 ) && ( square.get(it->m_x, it->m_y-2) == -1 )) {
            near.push_back( coord_t(it->m_x, it->m_y-2) );
        }
        // ����.
        if (( it->m_y < square.size_y()-1 ) && ( square.get(it->m_x, it->m_y+2) == -1 )) {
            near.push_back( coord_t(it->m_x, it->m_y+2) );
        }

        if ( near.size() == 0 ) {
            // ������ �� �����. ������� �������� �������.
            coords.erase( it );
            continue;
        }

        // �����. �������� ���������.
        int way = random( near.size() );
        // ��������� ��� ��� ����������������.
        square.get( near[way].m_x, near[way].m_y ) = next++;
        square.get(
            near[way].m_x - (near[way].m_x - it->m_x)/2
        ,   near[way].m_y - (near[way].m_y - it->m_y)/2 ) = next++;

        coords.push_back( coord_t( near[way].m_x, near[way].m_y ) );
    }

    std::vector<element_t> elements;
    // ���-�� ��������� ��������.
    elements.resize( next );

    int center_x = info.m_size_px_x / 2;
    int center_y = info.m_size_px_y / 2;
    int start_x = center_x - (info.m_size_x * info.m_element_size_x)/2;
    int start_y = center_y - (info.m_size_y * info.m_element_size_y)/2;

	for( int i = 0; i < info.m_size_x; ++i ) {
		for( int j = 0; j < info.m_size_y; ++j ) {
            if ( square.get( i, j ) != -1 ) {
                elements[ square.get( i, j ) ] = element_t(
           			start_x + info.m_element_size_x / 2 + i * info.m_element_size_x
            	,	start_y + info.m_element_size_y / 2 + j * info.m_element_size_y
                );
            }
		}
	}

    // ������� �����.
	for( int i = 0; i < info.m_size_x; ++i ) {
		for( int j = 0; j < info.m_size_y; ++j ) {
            if ( square.get( i, j ) != -1 ) {
//                elements[ square.get( i, j ) ]

                // ������.
                {
                    int pos_x = i;
                    int pos_y = j;
                    while( ++pos_x < info.m_size_x ) {
                        if (square.get(pos_x, pos_y) != -1) {
                            set_link(
                                square.get( i, j )
                                ,   square.get( pos_x, pos_y )
                            ,   elements );

                            break;
                        }
                    }
                }

                // ����.
                {
                    int pos_x = i;
                    int pos_y = j;
                    while( ++pos_y < info.m_size_y ) {
                        if (square.get(pos_x, pos_y) != -1) {
                            set_link(
                                square.get( i, j )
                            ,   square.get( pos_x, pos_y )
                           ,   elements );

                            break;
                        }
                    }
                }

                // ������-����.
                {
                    int pos_x = i;
                    int pos_y = j;
                    while(( ++pos_x < info.m_size_x ) && (++pos_y < info.m_size_y)) {
                        if (square.get(pos_x, pos_y) != -1) {
                            set_link(
                                square.get( i, j )
                                ,   square.get( pos_x, pos_y )
                            ,   elements );

                            break;
                        }
                    }
                }
                // �����-����.
                {
                    int pos_x = i;
                    int pos_y = j;
                    while(( --pos_x >= 0 ) && (++pos_y < info.m_size_y)) {
                        if (square.get(pos_x, pos_y) != -1) {
                            set_link(
                                square.get( i, j )
                                ,   square.get( pos_x, pos_y )
                            ,   elements );

                            break;
                        }
                    }
                }
            }
		}
	}

/*    for( unsigned int i = 0; i < elements.size(); ++i ) {
        for( unsigned int j = i+1; j < elements.size(); ++j ) {

            int distance_sqr =
                (elements[i].x() - elements[j].x()) *
                (elements[i].x() - elements[j].x())
                +
                (elements[i].y() - elements[j].y()) *
                (elements[i].y() - elements[j].y());

            int horse_sqr = info.m_element_size_x * info.m_element_size_x * 5;

            if ( abs(distance_sqr - horse_sqr) < 0.01 ) {
                set_link( i, j, elements );
            }
        }
    }
*/
    // ��� �������� ���������� � result.
	for( unsigned int i = 0; i < elements.size(); ++i ) {
        result->add_element(
            elements[i]
        );
    }

    return result;
}


} // namespace generators

} // namespace field


