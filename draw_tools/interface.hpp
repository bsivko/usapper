#if !defined(_DRAW_TOOL__INTERFACE_HPP__INCLUDED_)
#define _DRAW_TOOL__INTERFACE_HPP__INCLUDED_

#include "field/field.hpp"

namespace draw_tools {

//! Интерфейс для рисования объектов на поле.
class interface_t {

	public:
		//! Нарисовать поле.
		virtual void
		draw( 
			//! Это поле рисуем.
			const field::field_t & field ) = 0;

		virtual
		~interface_t() {}
};

} // namespace draw_tools

#endif