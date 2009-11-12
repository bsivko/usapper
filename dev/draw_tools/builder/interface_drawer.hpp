#if !defined(_DRAW_TOOL__INTERFACE_DRAWER_HPP__INCLUDED_)
#define _DRAW_TOOL__INTERFACE_DRAWER_HPP__INCLUDED_

#include "field/element.hpp"

namespace draw_tools {

namespace builder {

//! ����������� ����������� (����� �������, ��������� ��� ���������).
class interface_drawer_t {

	public:
		//! ���������� �����.
		virtual void
		draw_number( const field::element_t & element, int number ) = 0;

		//! ���������� ����������� ����.
		virtual void
		draw_unknown( const field::element_t & element ) = 0;

		//! ���������� ������.
		virtual void
		draw_flag( const field::element_t & element ) = 0;

		//! ���������� ���������� �����.
		virtual void
		draw_explode_bomb( const field::element_t & element ) = 0;

		//! ���������� ������ ��������� �����.
		virtual void
		draw_flag_error( const field::element_t & element ) = 0;

		//! ���������� ����� ����� �������.
		virtual void
		draw_link(
            const field::element_t & element1
        ,   const field::element_t & element2 ) = 0;

		virtual
		~interface_drawer_t() {}
};

} // namespace builder

} // namespace draw_tools


#endif