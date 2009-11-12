#include "field/generators/abstract.hpp"

#include <stdexcept>
#include <string>
#include <stdlib.h>

#include <vector>

namespace field {

namespace generators {

void
abstract_t::set_bombs( field::field_t & field, int number ) {

    using field::field_t::elements_t;

	elements_t & elements = field.elements();

	// Считаем число свободных.
	int count = 0;
	for( elements_t::iterator it = elements.begin();
		it != elements.end();
		++it ) {

		if ( !it->is_bomb() )
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
	for( elements_t::iterator it = elements.begin();
		it != elements.end();
		++it ) {

		if ( !it->is_bomb() )
		{
			if (to_fill[pos])
			{
                // Cast допустим, так как set сформирован на основании hash'a,
                // без участия is_bomb.
                element_t & element = const_cast<element_t &>(*it);
				element.set_bomb();
			}
			++pos;
		}
	}
}

} // namespace generators

} // namespace field


