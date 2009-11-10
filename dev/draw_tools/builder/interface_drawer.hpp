#if !defined(_DRAW_TOOL__INTERFACE_DRAWER_HPP__INCLUDED_)
#define _DRAW_TOOL__INTERFACE_DRAWER_HPP__INCLUDED_

namespace draw_tools {

namespace builder {

//! ����������� ����������� (����� �������, ��������� ��� ���������).
class interface_drawer_t {

	public:
		//! ���������� �����.
		virtual void
		draw_number( int x, int y, int number, bool check = false ) = 0;

		//! ���������� ����������� ����.
		virtual void
		draw_unknown( int x, int y, bool check = false ) = 0;

		//! ���������� ������.
		virtual void
		draw_flag( int x, int y, bool check = false ) = 0;

		//! ���������� ���������� �����.
		virtual void
		draw_explode_bomb( int x, int y, bool check = false ) = 0;

		//! ���������� ����� ����� �������.
		virtual void
		draw_link( int x1, int y1, int x2, int y2 ) = 0;

		virtual
		~interface_drawer_t() {}

};

} // namespace builder

} // namespace draw_tools


#endif