#include "field/generators/tetris.hpp"

#include <vector>

namespace field {

namespace generators {

field::field_t *
tetris_t::generate( const info_t & info ) {

	// Объект на возврат.
	field::field_t * result = new field::field_t( info );

    std::vector<element_t> elements;

    int center_x = info.m_size_px_x / 2;
    int center_y = info.m_size_px_y / 2;
    int start_x = center_x - (info.m_size_x * (0 + info.m_element_size_x) )/8*3;
    int start_y = center_y - (info.m_size_y * info.m_element_size_y);

	for( int j = 0; j < info.m_size_y; ++j ) {
    	for( int i = 0; i < info.m_size_x; ++i ) {

            int x =
                start_x + info.m_element_size_x / 2 + 3*(i/4) * info.m_element_size_x +
                (i / 4) * 3;
            int y =
                start_y + info.m_element_size_y / 2 + j * info.m_element_size_y * 2 +
                j*3;

            // Позиция центра в четверке.
            switch( i % 4 ) {
                case 0 :
                    x += info.m_element_size_x + 1;
                    break;
                case 1 :
                    x += 2*info.m_element_size_x + 2;
                    break;
                case 2 :
                    y += info.m_element_size_y + 1;
                    break;
                case 3 :
                    x += info.m_element_size_x + 1;
                    y += info.m_element_size_y + 1;
                    break;
            }

            element_t element( x, y );
            element.set_type( i % 4 );
            elements.push_back( element );
		}
	}

    // Создаем связи.

    for( unsigned int i = 0; i < elements.size(); ++i ) {

        // В четверке.
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

        // Внешние.
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
                // Вверх.
                set_link( i, i-j, elements );
                if ( (i+3) % info.m_size_x != 0 ) {
                    // Вверх.
                    set_link( i, i-j+4+1, elements );
                    // Вправо.
                    set_link( i, i+4+1, elements );
                    set_link( i, i+j+4+1, elements );
                }
                break;
            case 2 :
                // Вверх.
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
        // Вертикальные.
        if ( i >= static_cast<unsigned int>(info.m_size_x) ) {
            set_link( i, i - 2*info.m_size_x, elements );
        }

        // Горизонтальные.
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
*/
    }

    // Все элементы отправляем в result.
	for( unsigned int i = 0; i < elements.size(); ++i ) {
        result->add_element(
            elements[i]
        );
    }

    return result;
}


} // namespace generators

} // namespace field


