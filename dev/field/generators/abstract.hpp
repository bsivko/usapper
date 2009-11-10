#if !defined(_FIELD__GENERATORS__ABSTRACT_HPP__INCLUDED_)
#define _FIELD__GENERATORS__ABSTRACT_HPP__INCLUDED_

#include "field/generators/interface.hpp"

namespace field {

namespace generators {

//! Класс абстрактного генератора.  Содержит общую функциональность.
class abstract_t : public field::generators::interface_t {

	public:
		//! Усановить заданное число бомб в указанном поле.
		//! \throw если бомбы не устанавливаются (поле пустое или ставить некуда бомбы).
		static void
		set_bombs( field::field_t & field, int number );
};

} // namespace generators

} // namespace field

#endif