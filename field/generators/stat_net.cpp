#include "field/generators/stat_net.hpp"

#include <vector>
#include <stdlib.h>
namespace field {

namespace generators {

field::field_t *
stat_net_t::generate( const info_t & info ) {

	// Объект на возврат.
	field::field_t * result = new field::field_t( info );

    std::vector<element_t> elements;

	for( int i = 0; i < info.m_elements_number; ++i ) {

            int x;
            int y;
            bool is_free = false;
            do {
                x =
                    info.m_element_size_x / 2 +
                    random( info.m_size_px_x - info.m_element_size_x );
                y =
                    info.m_element_size_y / 2 +
                    random( info.m_size_px_y - info.m_element_size_y );

                // Есть ли рядом элементы?
                is_free = true;
            	for( int j = 0; j < i; ++j ) {
                    int distance_sqr =
                        (x - elements[j].x()) * (x - elements[j].x()) +
                        (y - elements[j].y()) * (y - elements[j].y());

                    int limit_sqr = (info.m_element_size_x * 1.2);
                    limit_sqr *= limit_sqr;

                    if ( distance_sqr < limit_sqr ) {
                        is_free = false;
                        break;
                    }
                }
            }
            while( !is_free );

            elements.push_back( element_t( x, y ) );
	}

    // Создаем связи.
    for( unsigned int i = 0; i < elements.size(); ++i ) {
        for( unsigned int j = i+1; j < elements.size(); ++j ) {

            int distance_sqr =
                (elements[i].x() - elements[j].x()) *
                (elements[i].x() - elements[j].x())
                +
                (elements[i].y() - elements[j].y()) *
                (elements[i].y() - elements[j].y());

            int limit_sqr = (info.m_element_size_x * 2.6);
            limit_sqr *= limit_sqr;

            if ( distance_sqr < limit_sqr ) {
                set_link( i, j, elements );
            }
        }
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


