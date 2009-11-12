#if !defined(_DRAW_TOOL__BUILDER__FIVEANGLE_HPP__INCLUDED_)
#define _DRAW_TOOL__BUILDER__FIVEANGLE_HPP__INCLUDED_

#include "draw_tools/builder/abstract.hpp"
#include "draw_tools/builder/interface_drawer.hpp"
#include "draw_tools/builder/abstract_drawer.hpp"

#include <Types.hpp>

namespace draw_tools {

namespace builder {

//! Инструмента для рисования в C++ Builder, классика.
class fiveangle_t : public abstract_t {

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

    		//! Нарисовать связь между точками.
    		virtual void
	    	draw_link(
                const field::element_t & element1
            ,   const field::element_t & element2 );

            const field::info_t & m_info;
            TCanvas & m_canvas;

            static const int c_size_x = 18;
            static const int c_size_y = 18;

            //! Нарисовать пятиугольник.
            void
            draw_fiveangle( TCanvas & canvas, const field::element_t & element  ) {

                canvas.Pen->Width = 2;

                int x = element.x();
                int y = element.y();

                Types::TPoint points[5];

                if (element.type() == 0)
                    points[0] = Point( x - 3*c_size_x/2, y - c_size_y/2 );
                else
                if (element.type() == 2)
                    points[0] = Point( x - c_size_x/2, y - 3*c_size_y/2 );
                else
                    points[0] = Point( x - c_size_x/2, y - c_size_y/2 );

                if (element.type() == 1)
                    points[2] = Point( x + c_size_x/2, y + 3*c_size_y/2 );
                else
                if (element.type() == 3)
                    points[2] = Point( x + 3*c_size_x/2, y + c_size_y/2 );
                else
                    points[2] = Point( x + c_size_x/2, y + c_size_y/2 );

                points[1] = Point( x + c_size_x/2, y - c_size_y/2 );
                points[3] = Point( x - c_size_x/2, y + c_size_y/2 );
                points[4] = points[0];
                canvas.Polygon( points, 5 );
                canvas.Pen->Width = 1;

                return;
            }
    };

	public:
		//! Нарисовать поле на канве.
		virtual void
		draw(
			//! Это поле рисуем.
			const field::field_t & field );

		virtual
		~fiveangle_t() {}
    private:
        void
        set_link(
            unsigned int i
        ,   unsigned int j
        ,   std::vector<field::element_t> & elements );
};

} // namespace builder

} // namespace draw_tools


#endif