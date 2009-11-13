#if !defined(_DRAW_TOOL__BUILDER__TRIANGLE_HPP__INCLUDED_)
#define _DRAW_TOOL__BUILDER__TRIANGLE_HPP__INCLUDED_

#include "draw_tools/builder/abstract.hpp"
#include "draw_tools/builder/interface_drawer.hpp"
#include "draw_tools/builder/abstract_drawer.hpp"

#include <Types.hpp>

namespace draw_tools {

namespace builder {

//! Инструмента для рисования в C++ Builder, классика.
class triangle_t : public abstract_t {

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

            static const int c_size_x = 15;
            static const int c_size_y = 12;

            //! Нарисовать треугольник.
            void
            draw_triangle( TCanvas & canvas, const field::element_t & element  ) {

                canvas.Pen->Width = 2;

                int x = element.x();
                int y = element.y();
                if ( element.type() == 0 ) {
                    Types::TPoint points[4];
                    points[0] = Point(x, y-c_size_y);
                    points[1] = Point(x+c_size_x, y+c_size_y);
                    points[2] = Point(x-c_size_x, y+c_size_y);
                    points[3] = Point(x, y-c_size_y);
                    canvas.Polygon( points, 3 );
                }
                else if ( element.type() == 1 ) {
                    Types::TPoint points[4];
                    points[0] = Point(x, y+c_size_y);
                    points[1] = Point(x+c_size_x, y-c_size_y);
                    points[2] = Point(x-c_size_x, y-c_size_y);
                    points[3] = Point(x, y+c_size_y);
                    canvas.Polygon( points, 3 );
                }
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
		~triangle_t() {}
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