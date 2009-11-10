#if !defined(_DRAW_TOOL__INTERFACE_DRAWER_HPP__INCLUDED_)
#define _DRAW_TOOL__INTERFACE_DRAWER_HPP__INCLUDED_

namespace draw_tools {

namespace builder {

//! Абстрактный рисовальщик (набор методов, требуемых для рисования).
class interface_drawer_t {

	public:
		//! Нарисовать число.
		virtual void
		draw_number( int x, int y, int number, bool check = false ) = 0;

		//! Нарисовать неизвестное поле.
		virtual void
		draw_unknown( int x, int y, bool check = false ) = 0;

		//! Нарисовать флажок.
		virtual void
		draw_flag( int x, int y, bool check = false ) = 0;

		//! Нарисовать взорванную бомбу.
		virtual void
		draw_explode_bomb( int x, int y, bool check = false ) = 0;

		//! Нарисовать связь между точками.
		virtual void
		draw_link( int x1, int y1, int x2, int y2 ) = 0;

		virtual
		~interface_drawer_t() {}

};

} // namespace builder

} // namespace draw_tools


#endif