#include "field/generators/abstract.hpp"

#include <stdexcept>
#include <string>
#include <stdlib.h>

#include <vector>

namespace field {

namespace generators {

void
abstract_t::set_link(
    int i
,   int j
,   std::vector<field::element_t> & elements ) {

    if (
        (i < static_cast<int>(elements.size())) &&
        (j < static_cast<int>(elements.size()))
    ) {
        if (( i >= 0 ) && (j >= 0)) {
            elements.at(i).near_elements().push_back( j );
            elements.at(j).near_elements().push_back( i );
        }
    }
}

void
abstract_t::set_bombs( field::field_t & field, int index ) {

    using field::field_t::elements_t;

    int number = field.info().m_bomb_number;

	elements_t & elements = field.elements();

	// Считаем число свободных.
	int count = 0;
	for( unsigned int i = 0; i < elements.size(); ++i ) {

		if ( (!elements[i].is_bomb()) && ( static_cast<int>(i) != index ) )
		{
			++count;
		}
	}

	if ( count < number ) {
		// Столько не влезет.
		char str_count[10];
		itoa( count, str_count, 10 );
		char str_number[10];
		itoa( number, str_number, 10 );

		throw std::runtime_error(
			std::string(
                "Trying to insert impossible count of bombs.")
            +	" Free space: " + str_count
	    	+	" Trying to insert: " + str_number
		);
	}

	// Формируем массив на заполнение.
	std::vector<bool> to_fill;
	to_fill.reserve( count );
	for( int i = 0; i < count; ++i )
		to_fill.push_back( false );

	for( int i = 0; i < number; ++i) {
		int pos;
		do {
			pos = random( count );
		}
		while( true == to_fill[pos] );
		to_fill[pos] = true;
	}

	// Согласно сформированному массиву ставим бомбы во множестве.
	int pos = 0;
	for( unsigned int i = 0; i < elements.size(); ++i ) {

		if ( (!elements[i].is_bomb()) && ( static_cast<int>(i) != index ) )
		{
			if (to_fill[pos])
			{
				elements[i].set_bomb();
			}
			++pos;
		}
	}
}

} // namespace generators

} // namespace field


