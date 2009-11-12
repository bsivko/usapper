#if !defined(_DRAW_TOOL__BUILDER__CLASSIC_HPP__INCLUDED_)
#define _DRAW_TOOL__BUILDER__CLASSIC_HPP__INCLUDED_

#include "draw_tools/builder/abstract.hpp"
#include "draw_tools/builder/interface_drawer.hpp"
#include "draw_tools/builder/abstract_drawer.hpp"

namespace draw_tools {

namespace builder {

//! Инструмента для рисования в C++ Builder, классика.
class classic_t : public abstract_t {

    //! Рисовальщик на канве.
    class drawer_t : public abstract_drawer_t {
        public:
            drawer_t( TCanvas & canvas, const field::info_t & info, bool blink ) :
            abstract_drawer_t(blink), m_info(info), m_canvas(canvas) {

            }

            //! Нарисовать число.
            virtual void
            draw_number( const field::element_t & element, int number );

            //! Нарисовать неизвестное поле.
            virtual void
            draw_unknown( const field::element_t & element );

            //! Нарисовать флажок.
            virtual void
            draw_flag( const field::element_t & element );

            //! Нарисовать взорванную бомбу.
            virtual void
            draw_explode_bomb( const field::element_t & element );

    		//! Нарисовать ошибку установки флага.
    		virtual void
	    	draw_flag_error( const field::element_t & element );

    		//! Нарисовать связь между точками.
    		virtual void
	    	draw_link(
                const field::element_t & element1
            ,   const field::element_t & element2 );

            const field::info_t & m_info;
            TCanvas & m_canvas;
    };

	public:
		//! Нарисовать поле на канве.
		virtual void
		draw(
			//! Это поле рисуем.
			const field::field_t & field );

		virtual
		~classic_t() {}
};

} // namespace builder

} // namespace draw_tools


#endif