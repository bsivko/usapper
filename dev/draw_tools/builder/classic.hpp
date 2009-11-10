#if !defined(_DRAW_TOOL__ABSTRACT_BUILDER_HPP__INCLUDED_)
#define _DRAW_TOOL__ABSTRACT_BUILDER_HPP__INCLUDED_

#include "draw_tools/builder/abstract.hpp"
#include "draw_tools/builder/interface_drawer.hpp"
#include "draw_tools/builder/abstract_drawer.hpp"

namespace draw_tools {

namespace builder {

//! ����������� ��� ��������� � C++ Builder, ��������.
class classic_t : public abstract_t {

    //! ����������� �� �����.
    class drawer_t : public abstract_drawer_t {
        public:
            drawer_t( TCanvas & canvas, const field::info_t & info, bool blink ) :
            abstract_drawer_t(blink), m_info(info), m_canvas(canvas) {

            }

            //! ���������� �����.
            virtual void
            draw_number( int x, int y, int number, bool check = false );

            //! ���������� ����������� ����.
            virtual void
            draw_unknown( int x, int y, bool check = false );

            //! ���������� ������.
            virtual void
            draw_flag( int x, int y, bool check = false );

            //! ���������� ���������� �����.
            virtual void
            draw_explode_bomb( int x, int y, bool check = false );

    		//! ���������� ����� ����� �������.
    		virtual void
	    	draw_link( int x1, int y1, int x2, int y2 );

            const field::info_t & m_info;
            TCanvas & m_canvas;
    };

	public:
		//! ���������� ���� �� �����.
		virtual void
		draw(
			//! ��� ���� ������.
			const field::field_t & field );

		virtual
		~classic_t() {}
};

} // namespace builder

} // namespace draw_tools


#endif