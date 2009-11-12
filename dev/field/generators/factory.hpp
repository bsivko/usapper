#if !defined(_FIELD_GENERATORS__FACTORY_HPP__INCLUDED_)
#define _FIELD_GENERATORS__FACTORY_HPP__INCLUDED_

#include <stdexcept>
#include <string>
#include <stdlib.h>

#include "field/generators/classic.hpp"
#include "field/generators/triangle.hpp"
#include "field/generators/sixangle.hpp"
#include "field/generators/fiveangle.hpp"
#include "field/generators/stat_net.hpp"
#include "field/generators/chess_horse.hpp"

namespace field {

namespace generators {

//! Множество типов инструментов для генерирования.
enum type_t {

	//! Классический сапер - квадратное поле.
	classic,

    //! Паркетные треугольники.
    triangle,

    //! Паркетные шестиугольники.
    sixangle,

    //! Паркетные пятиугольники.
    fiveangle,

    //! Статическая сеть.
    stat_net,

    //! Шахматный конь.
    chess_horse,

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

			if ( type == triangle ) {
				static field::generators::triangle_t triangle;
				return triangle;
			}

			if ( type == sixangle ) {
				static field::generators::sixangle_t sixangle;
				return sixangle;
			}

			if ( type == fiveangle ) {
				static field::generators::fiveangle_t fiveangle;
				return fiveangle;
			}

			if ( type == stat_net ) {
				static field::generators::stat_net_t stat_net;
				return stat_net;
			}

			if ( type == chess_horse ) {
				static field::generators::chess_horse_t chess_horse;
				return chess_horse;
			}

			char error[10];
			itoa( type, error, 10 );

			throw std::runtime_error(
                std::string("Unknown type of field generator:") + error );
		}
};

} // namespace generators

} // namespace field

#endif