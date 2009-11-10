#if !defined(_FIELD_GENERATORS__FACTORY_HPP__INCLUDED_)
#define _FIELD_GENERATORS__FACTORY_HPP__INCLUDED_

#include <stdexcept>
#include <string>
#include <stdlib.h>

#include "field/generators/classic.hpp"

namespace field {

namespace generators {

//! Множество типов инструментов для генерирования.
enum type_t {

	//! Классический сапер - квадратное поле.
	classic,

	//! Сетевое поле сапера.
	net
};

//! Фабрика для генерирования объектов на поле.
class factory_t {

	public:
		//! Получить объект для генерирования соответствующего типа.
		/*!
			\throw в случае, если передан неизвестный тип.
		*/
		static interface_t &
		get_instance( const type_t & type ) {

			if ( type == classic ) {
				static field::generators::classic_t classic;
				return classic;
			}

			char error[10];
			itoa( type, error, 10 );

			throw std::runtime_error( std::string("Unknown type of field generator:") + error );
		}
};

} // namespace generators

} // namespace field

#endif