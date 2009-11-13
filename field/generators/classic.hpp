#if !defined(_FIELD__GENERATORS__CLASSIC_HPP__INCLUDED_)
#define _FIELD__GENERATORS__CLASSIC_HPP__INCLUDED_

#include "field/generators/abstract.hpp"

namespace field {

namespace generators {

//! ����� ���������� ������������� ����.
class classic_t : public field::generators::abstract_t {

	public:
		virtual field::field_t *
		generate( const info_t & info );

};

} // namespace generators

} // namespace field

#endif