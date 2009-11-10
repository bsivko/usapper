#if !defined(_FIELD_GENERATORS__FACTORY_HPP__INCLUDED_)
#define _FIELD_GENERATORS__FACTORY_HPP__INCLUDED_

#include <stdexcept>
#include <string>
#include <stdlib.h>

#include "field/generators/classic.hpp"

namespace field {

namespace generators {

//! ��������� ����� ������������ ��� �������������.
enum type_t {

	//! ������������ ����� - ���������� ����.
	classic,

	//! ������� ���� ������.
	net
};

//! ������� ��� ������������� �������� �� ����.
class factory_t {

	public:
		//! �������� ������ ��� ������������� ���������������� ����.
		/*!
			\throw � ������, ���� ������� ����������� ���.
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