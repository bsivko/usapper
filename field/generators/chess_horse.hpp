#if !defined(_FIELD__GENERATORS__CHESS_HORSE_HPP__INCLUDED_)
#define _FIELD__GENERATORS__CHESS_HORSE_HPP__INCLUDED_

#include "field/generators/abstract.hpp"

namespace field {

namespace generators {

//! Класс генератора поля с шахматным конем.
class chess_horse_t : public field::generators::abstract_t {

	public:
		virtual field::field_t *
		generate( const info_t & info );

};

} // namespace generators

} // namespace field

#endif