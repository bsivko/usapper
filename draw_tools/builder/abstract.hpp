#if !defined(_DRAW_TOOL__ABSTRACT_HPP__INCLUDED_)
#define _DRAW_TOOL__ABSTRACT_HPP__INCLUDED_

#include <Controls.hpp>
#include <ExtCtrls.hpp>

#include "draw_tools/interface.hpp"

namespace draw_tools {

namespace builder {

//! ����� ������������ ����������� ��� ��������� � C++ Builder.
class abstract_t : public draw_tools::interface_t {

	public:
        //! \class abstract_t ����������� ������� �������� � ������� ����� ���������.
        /*! \class abstract_t
            \note ��� ��������� ���������� ������ �������� ������
            �� ������� ������ �����������, � ��� �����������
            ��� ������ ����� �� ��������.
            \attention ������� image ������ ���� ��������� �� ��������.
        */

        //! ���������� �������.
        void
        set_shadow( TCanvas & canvas, TRect & rect ) {
            m_shadow_canvas = &canvas;
            m_shadow_rect = rect;
        }

        //! ���������� ��������.
        void
        set_main( TCanvas & canvas, TRect & rect ) {
            m_main_canvas = &canvas;
            m_main_rect = rect;
        }

		//! ���������� ���� �� ������� � ����������� � ��������.
		void
		shadow_copy_draw(
			//! ��� ���� ������.
			const field::field_t & field);

		//! ���������� ���� �� �������.
		void
		shadow_draw(
			//! ��� ���� ������.
			const field::field_t & field );

        //! ���������� ��� (� ������� ������).
        void
        draw_backgound();

		//! ����������� �� ���� �� ��������.
		void
		shadow_copy_to_main();

        void
        set_blink( bool blink ) {
            m_blink = blink;
        }

        bool
        blink() const {
            return m_blink;
        }

        void
        set_tick( int tick ) {
            m_tick = tick;
        }

		virtual
		~abstract_t() {}

    protected:
        TCanvas &
        shadow_canvas() {
            return *m_shadow_canvas;
        }

        TCanvas &
        main_canvas() {
            return *m_main_canvas;
        }

    private:
        //! ������� �����.
        TCanvas * m_shadow_canvas;
        //! ������� ��������.
        TRect m_shadow_rect;
        //! �������� �����.
        TCanvas * m_main_canvas;
        //! ������� ��������.
        TRect m_main_rect;

        //! ��������� ������ � ��������� ������� ��� ���.
        bool m_blink;
        int m_tick;
};

} // namespace builder

} // namespace draw_tools

#endif