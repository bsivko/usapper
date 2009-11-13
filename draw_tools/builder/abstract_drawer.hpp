#if !defined(_DRAW_TOOL__ABSTRACT_DRAWER_HPP__INCLUDED_)
#define _DRAW_TOOL__ABSTRACT_DRAWER_HPP__INCLUDED_

#include "draw_tools/builder/interface_drawer.hpp"
#include "field/field.hpp"

namespace draw_tools {

namespace builder {

//! ����������� �����������.
class abstract_drawer_t : public interface_drawer_t {

	public:
        abstract_drawer_t( bool blink = false ) : m_blink( blink ) { }

		//! ���������� ����.
		void
		draw_elements( const field::field_t & field );

		//! ���������� �����.
		void
		draw_net( const field::field_t & field );

		virtual
		~abstract_drawer_t() {}

    private:
        bool m_blink;
};

} // namespace builder

} // namespace draw_tools


#endif