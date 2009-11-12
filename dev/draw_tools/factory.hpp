#if !defined(_DRAW_TOOLS__FACTORY_HPP__INCLUDED_)
#define _DRAW_TOOLS__FACTORY_HPP__INCLUDED_

#include <stdexcept>
#include <string>
#include <stdlib.h>

#include "draw_tools/builder/classic.hpp"
#include "draw_tools/builder/triangle.hpp"
#include "draw_tools/builder/sixangle.hpp"
#include "draw_tools/builder/fiveangle.hpp"
#include "draw_tools/builder/net.hpp"


namespace draw_tools {

//! Множество типов инструментов для рисования.
enum type_t {

	//! Классический сапер - квадратное поле.
	classic,

    //! Паркетные треугольники.
    triangle,

    //! Паркетные шестиугольники.
    sixangle,

    //! Паркетные пятиугольники.
    fiveangle,

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

			if ( type == triangle ) {
				static draw_tools::builder::triangle_t triangle;
				return triangle;
			}

			if ( type == sixangle ) {
				static draw_tools::builder::sixangle_t sixangle;
				return sixangle;
			}

			if ( type == fiveangle ) {
				static draw_tools::builder::fiveangle_t fiveangle;
				return fiveangle;
			}

			if ( type == net ) {
				static draw_tools::builder::net_t net;
				return net;
			}

			char error[10];
			itoa( type, error, 10 );

			throw std::runtime_error(
                std::string("Unknown type of draw tool:") + error );
		}
};

} // namespace draw_tools

#endif