#include "field/generators/tetris.hpp"
#include "global_options.hpp"

#include <vector>
#include <string>
#include <stdlib.h>

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

        //! ������ � ���������.
        const T &
        get( int x, int y ) const {
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

//! ���������� ���������� � ������� ������� ������� ���������.
int
fill( square_t<int> & square, int x, int y ) {

    if ( square.get(x,y) == -1 )
        return 0;

    int result = 0;

    square.get(x, y) = -2;

    if ( x > 0 ) {
        result += fill( square, x-1, y );
    }
    if ( y > 0 ) {
        result += fill( square, x, y-1 );
    }
    if ( x < square.size_x()-1 ) {
        result += fill( square, x+1, y );
    }
    if ( x > square.size_y()-1 ) {
        result += fill( square, x, y+1 );
    }

    return result;
}

//! ��������� ����� ����������.
/*!
    \return ������, � ������� �������� �����, �� ������� ���������� � ������ ��.
*/
std::vector <int>
get_fills( const square_t<int> & square ) {

    std::vector <int> fills;
    square_t<int> square_copy = square;

    for( int i = 0; i < square_copy.size_x(); ++i ) {
        for( int j = 0; j < square_copy.size_x(); ++j ) {

            if ( square_copy.get(i ,j) == -1 ) {
                fills.push_back( fill(square_copy, i ,j) );
            }
        }
    }

    return fills;
}

void
try_to_add_near(
    const square_t<int> & square,
    int x,
    int y,
    std::vector<coord_t> & near
    ) {

    if ( square.get(x,y) != -1 )
        return;

    for( unsigned int i = 0; i < near.size(); ++i ) {
        if (( near[i].m_x == x ) && ( near[i].m_y == y ))
            // ������� ����������.
            return;
    }
    near.push_back( coord_t(x, y) );
}

field::field_t *
tetris_t::generate( const info_t & info ) {

    randomize();

	// ������ �� �������.
	field::field_t * result = new field::field_t( info );

    square_t<int> square( info.m_size_x, info.m_size_y );
    square.fill( -1 );

    // ����� ���������, next �������� ���������
    // ������ �������� ��� �������� � �������.
    // ���������������� ��� �������.
    int next = 0;

    // ����� ������ � ������ (������ - 4).
    const int c_blocks_count = 4;

    std::vector<element_t> elements;
    // ������������� �� ����� �����.
    elements.resize( info.m_size_x * info.m_size_x / c_blocks_count );

    int center_x = info.m_size_px_x / 2;
    int center_y = info.m_size_px_y / 2;
    int start_x = center_x - (info.m_size_x * (0 + info.m_element_size_x) )/8*3;
    int start_y = center_y - (info.m_size_y * info.m_element_size_y);

    // ������ ������� ���.
    for( unsigned int i = 0; i < elements.size(); ++i ) {
        elements[i].set_type(-1);
    }

    while(true) {
        // �������� � ������.
        square_t<int> square_copy = square;
        std::vector<coord_t> * blocks = new std::vector<coord_t>();

        // ���� ��������� ����.
        int x;
        int y;
        do {
            x = random( square_copy.size_x() );
            y = random( square_copy.size_y() );
        }
        while( square_copy.get(x, y) != -1 );

        // ������ ������.
        std::vector<coord_t> near;
        near.push_back( coord_t(x, y) );
        blocks->push_back( coord_t(x, y) );
        square_copy.get(x, y) = next;
        for(int i = 1; i < c_blocks_count; ++i) {

            for( unsigned int j = 0; j < blocks->size(); ++j ) {
                int x = (*blocks)[j].m_x;
                int y = (*blocks)[j].m_y;

                // �����.
                if ( x > 0 ) {
                    try_to_add_near( square_copy, x-1, y, near );
                }
                // ������.
                if ( x < square_copy.size_x()-1 ) {
                    try_to_add_near( square_copy, x+1, y, near );
                }
                // �����.
                if ( y > 0 ) {
                    try_to_add_near( square_copy, x, y-1, near );
                }
                // ����.
                if ( y < square_copy.size_y()-1 ) {
                    try_to_add_near( square_copy, x, y+1, near );
                }
            }
            // ����� �����.
            if ( near.size() > 0 ) {
                int index = random( near.size() );
                // ���������� �� ����������.
                blocks->push_back( coord_t( near[index] ) );
                square_copy.get( near[index].m_x, near[index].m_y ) = next;
            }
        }

        // �� ���������� ������.
        // ������ ���������, ��� ����� � ��������� �� �����
        // ��������� ���� ������ �� �������� ��� �������.
        bool we_can = true;
        std::vector <int> values = get_fills( square_copy );
        for(
            std::vector <int>::iterator it = values.begin();
            it != values.end();
            ++it ) {

            if (*it % c_blocks_count != 0) {
                we_can = false;
                break;
            }
        }
        // ������ ������ ���������?
        if (we_can) {
            // ��. �������� �� ������� ����� square.
            square = square_copy;
            elements[next].set_data( blocks );
            ++next;
        }
        else {
            delete blocks;
        }

        // ���� �����������?
        if (elements.size() == next)
            break;
    }

    // ������������� ����������.
	for( unsigned int i = 0; i < elements.size(); ++i ) {

        coord_t coord =
            (*static_cast<std::vector<coord_t> *>(elements[i].data()))[0];

        elements[i].set_x(
   			start_x + info.m_element_size_x / 2 + coord.m_x * info.m_element_size_x );
        elements[i].set_y(
  	    	start_y + info.m_element_size_y / 2 + coord.m_y * info.m_element_size_y );
	}

    // ������� �����.
    /*
    for( unsigned int i = 0; i < elements.size(); ++i ) {

        // � ��������.
        switch( i % 4 ) {
            case 0 :
                set_link( i, i+1, elements );
                set_link( i, i+2, elements );
                set_link( i, i+3, elements );
                break;
            case 1 :
                break;
            case 2 :
                break;
            case 3 :
                set_link( i, i-1, elements );
                set_link( i, i-2, elements );
                break;
        }

        int j = info.m_size_x;

        // �������.
        switch( i % 4 ) {
            case 0 :
                set_link( i, i-j+2, elements );
                set_link( i, i-j+3, elements );
                if ( i % info.m_size_x != 0 ) {
                    set_link( i, i-j-4+3, elements );
                    set_link( i, i-j-4+1, elements );
                    set_link( i, i-4+1, elements );
                }
                break;
            case 1 :
                // �����.
                set_link( i, i-j, elements );
                if ( (i+3) % info.m_size_x != 0 ) {
                    // �����.
                    set_link( i, i-j+4+1, elements );
                    // ������.
                    set_link( i, i+4+1, elements );
                    set_link( i, i+j+4+1, elements );
                }
                break;
            case 2 :
                // �����.
                set_link( i, i-j, elements );
                break;
            case 3 :
                set_link( i, i+j-2, elements );
                if ( (i+1) % info.m_size_x != 0 ) {
                    set_link( i, i+4-1, elements );
                    set_link( i, i+j+4-1, elements );
                }
                break;
        }

/*
        // ������������.
        if ( i >= static_cast<unsigned int>(info.m_size_x) ) {
            set_link( i, i - 2*info.m_size_x, elements );
        }

        // ��������������.
//        if ( i % info.m_size_x != 0  ) {

            if ( (i / info.m_size_x) % 2 == 0 ) {
                if ( i >= static_cast<unsigned int>(info.m_size_x) ) {
                    set_link( i, i - info.m_size_x, elements );
                }
                set_link( i, i + info.m_size_x, elements );
            }
            else {
                if ( (i+1) % info.m_size_x != 0 ) {
                    if ( i >= static_cast<unsigned int>(info.m_size_x)  ) {
                        set_link( i, i - info.m_size_x + 1, elements );
                    }
                    set_link( i, i + info.m_size_x + 1, elements );
                }
            }
//        }

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


