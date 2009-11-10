#if !defined(_FIELD__GENERATORS__INTERFACE_HPP__INCLUDED_)
#define _FIELD__GENERATORS__INTERFACE_HPP__INCLUDED_

#include "field/field.hpp"

namespace field {

namespace generators {

//! ��������� ��� ������������� �������� �� ����.
class interface_t {

	public:
		//! ������������� ����.
		/*!
			\attention delete �� �������� �����������.
		*/
		virtual field::field_t *
		generate( const info_t & info ) = 0;

		virtual
		~interface_t() {}
};

} // namespace generators

} // namespace field

#endif