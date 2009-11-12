#include "field/generators/chess_horse.hpp"

#include <vector>
#include <math.h>
namespace field {

namespace generators {

field::field_t *
chess_horse_t::generate( const info_t & info ) {

	// Объект на возврат.
	field::field_t * result = new field::field_t( info );

    std::vector<element_t> elements;

    int center_x = info.m_size_px_x / 2;
    int center_y = info.m_size_px_y / 2;
    int start_x = center_x - (info.m_size_x * info.m_element_size_x)/2;
    int start_y = center_y - (info.m_size_y * info.m_element_size_y)/2;

	for( int i = 0; i < info.m_size_x; ++i ) {
		for( int j = 0; j < info.m_size_y; ++j ) {
            elements.push_back( element_t(
 	    			start_x + info.m_element_size_x / 2 + i * info.m_element_size_x
     	    	,	start_y + info.m_element_size_y / 2 + j * info.m_element_size_y
                )
            );
		}
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

            int horse_sqr = info.m_element_size_x * info.m_element_size_x * 5;

            if ( abs(distance_sqr - horse_sqr) < 0.01 ) {
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


