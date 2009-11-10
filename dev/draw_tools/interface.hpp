#if !defined(_DRAW_TOOL__INTERFACE_HPP__INCLUDED_)
#define _DRAW_TOOL__INTERFACE_HPP__INCLUDED_

#include "field/field.hpp"

namespace draw_tools {

//! ��������� ��� ��������� �������� �� ����.
class interface_t {

	public:
		//! ���������� ����.
		virtual void
		draw( 
			//! ��� ���� ������.
			const field::field_t & field ) = 0;

		virtual
		~interface_t() {}
};

} // namespace draw_tools

#endif