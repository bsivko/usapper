#if !defined(_FIELD__GENERATORS__ABSTRACT_HPP__INCLUDED_)
#define _FIELD__GENERATORS__ABSTRACT_HPP__INCLUDED_

#include "field/generators/interface.hpp"

namespace field {

namespace generators {

//! ����� ������������ ����������.  �������� ����� ����������������.
class abstract_t : public field::generators::interface_t {

	public:
		//! ��������� �������� ����� ���� � ��������� ����.
		//! \throw ���� ����� �� ��������������� (���� ������ ��� ������� ������ �����).
		static void
		set_bombs( field::field_t & field, int number );
};

} // namespace generators

} // namespace field

#endif