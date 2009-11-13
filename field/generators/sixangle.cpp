#include "field/generators/sixangle.hpp"

#include <vector>

namespace field {

namespace generators {

void
set_link(
    unsigned int i
,   unsigned int j
,   std::vector<field::element_t> & elements ) {

    if ((i < elements.size()) && (j < elements.size())) {
        elements.at(i).near_elements().push_back( j );
        elements.at(j).near_elements().push_back( i );
    }
}


field::field_t *
sixangle_t::generate( const info_t & info ) {

	// Объект на возврат.
	field::field_t * result = new field::field_t( info );

    std::vector<element_t> elements;

    int center_x = info.m_size_px_x / 2;
    int center_y = info.m_size_px_y / 2;
    int start_x = center_x - (info.m_size_x * (-1 + info.m_element_size_x) )*3/4;
    int start_y = center_y - (info.m_size_y * info.m_element_size_y)/4;

	for( int j = 0; j < info.m_size_y; ++j ) {
    	for( int i = 0; i < info.m_size_x; ++i ) {

            int x =
                start_x - info.m_element_size_x / 4 + i * info.m_element_size_x / 2 * 3 +
                i * 1 - (i / 2)*3;
            int y =
                start_y + info.m_element_size_y / 2 +
                j * info.m_element_size_y / 2 +
                j * 0;

            if ( j % 2 == 1) {
                x += info.m_element_size_x - 7;
            }

            elements.push_back( element_t( x, y ) );
		}
	}

    // Создаем связи.

    for( unsigned int i = 0; i < elements.size(); ++i ) {

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


