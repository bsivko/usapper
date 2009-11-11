#include "field/generators/triangle.hpp"

#include <vector>

namespace field {

namespace generators {

field::field_t *
triangle_t::generate( const info_t & info ) {

	// Объект на возврат.
	field::field_t * result = new field::field_t( info );

    std::vector<element_t> elements;

    int center_x = info.m_size_px_x / 2;
    int center_y = info.m_size_px_y / 2;
    int start_x = center_x - (info.m_size_x * info.m_element_size_x)/2;
    int start_y = center_y - (info.m_size_y * info.m_element_size_y)/4;

	for( int j = 0; j < info.m_size_y; ++j ) {
    	for( int i = 0; i < info.m_size_x; ++i ) {

            int x =
                start_x - info.m_element_size_x / 4 + i * (2 + info.m_element_size_x) +
                // Смещение четных рядов.
                (j % 2) * info.m_element_size_x / 2;
            int y =
                start_y + info.m_element_size_y / 2 + (j / 2) * info.m_element_size_y;

            if ( (j/2) % 2 == 1) {
                if (j % 2 == 0) {
                    x += info.m_element_size_x / 2;
                }
                if (j % 2 == 1) {
                    x -= info.m_element_size_x / 2;
                }
            }

            element_t element( x, y );

            element.set_type( !(j % 2) );
            elements.push_back( element );
		}
	}

    // Создаем связи.

    // Горизонтальные.
    for( unsigned int i = 0; i < elements.size(); ++i ) {

        int p = (i * 2) % 2;

        switch ( (i / info.m_size_x) % 4 ) {
            // Первая с вертикали V.
            case 0: {
//                if ( ( i + 1 ) % info.m_size_x != 0 ) {
                    // Вправо.
                    unsigned int l = i + info.m_size_x;
                    if (l < elements.size()) {
                        elements.at(i).near_elements().push_back( l );
                        elements.at(l).near_elements().push_back( i );
                    }
//                }

               if ( (i + 0) % info.m_size_x != 0 ) {
                    // Влево.
                    unsigned int l = i + info.m_size_x - 1;
                    if (l < elements.size()) {
                        elements.at(i).near_elements().push_back( l );
                        elements.at(l).near_elements().push_back( i );
                    }
                }

                break;
            }
            case 3: {
                // Четвертая с вертикали из 4ки (Л).
//                if ( (i + 1) % info.m_size_x != 0 ) {
                    // Вправо.
                    unsigned int l = i - info.m_size_x;
                    if (l < elements.size()) {
                        elements.at(i).near_elements().push_back( l );
                        elements.at(l).near_elements().push_back( i );
                    }
//                }

                if ( i % info.m_size_x != 0 ) {
                    // Влево.
                    unsigned int l = i - info.m_size_x - 1;
                    if (l < elements.size()) {
                        elements.at(i).near_elements().push_back( l );
                        elements.at(l).near_elements().push_back( i );
                    }
                }
                break;
            }
        }
    }

    // Все элементы отправляем в result.
	for( unsigned int i = 0; i < elements.size(); ++i ) {
        result->add_element(
            elements[i]
        );
    }

    // Ставим бомбы.
	set_bombs( *result, info.m_bomb_number );

    return result;
}


} // namespace generators

} // namespace field


