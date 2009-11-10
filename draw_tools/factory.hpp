#if !defined(_DRAW_TOOLS__FACTORY_HPP__INCLUDED_)
#define _DRAW_TOOLS__FACTORY_HPP__INCLUDED_

#include <stdexcept>
#include <string>
#include <stdlib.h>

#include "draw_tools/builder/classic.hpp"

namespace draw_tools {

//! Множество типов инструментов для рисования.
enum type_t {

	//! Классический сапер - квадратное поле.
	classic,

	//! Сетевое поле сапера.
	net
};

//! Фабрика для рисования объектов на поле.
class factory_t {

	public:
		//! Получить объект для рисования соответствующего типа.
		/*!
			\throw в случае, если передан неизвестный тип.
		*/
		static interface_t &
		get_instance( const type_t & type ) {

			if ( type == classic ) {
				static draw_tools::builder::classic_t classic;
				return classic;
			}

			char error[10];
			itoa( type, error, 10 );

			throw std::runtime_error( std::string("Unknown type of draw tool:") + error );
		}
};

} // namespace draw_tools

#endif