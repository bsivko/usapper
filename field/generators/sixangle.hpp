#if !defined(_FIELD__GENERATORS__SIXANGLE_HPP__INCLUDED_)
#define _FIELD__GENERATORS__SIXANGLE_HPP__INCLUDED_

#include "field/generators/abstract.hpp"

namespace field {

namespace generators {

//! Класс генератора паркета из треугольников.
class sixangle_t : public field::generators::abstract_t {

	public:
		virtual field::field_t *
		generate( const info_t & info );

};

} // namespace generators

} // namespace field

#endif