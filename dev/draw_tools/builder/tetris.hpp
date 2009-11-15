#if !defined(_DRAW_TOOL__BUILDER__TETRIS_HPP__INCLUDED_)
#define _DRAW_TOOL__BUILDER__TETRIS_HPP__INCLUDED_

#include "draw_tools/builder/abstract.hpp"
#include "draw_tools/builder/interface_drawer.hpp"
#include "draw_tools/builder/abstract_drawer.hpp"

#include <Types.hpp>

#include <vector>
#include "global_options.hpp"

namespace draw_tools {

namespace builder {

//! Инструмента для рисования в C++ Builder, классика.
class tetris_t : public abstract_t {

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

            static const int c_size_x = 18;
            static const int c_size_y = 18;

            //! Нарисовать фигуру.
            void
            draw_tetris( TCanvas & canvas, const field::element_t & element  ) {

                std::vector<coord_t> blocks = element.blocks();

                int start_x = element.x();
                int start_y = element.y();

                // Рисуем все блоковые квадраты.
                for( unsigned int i = 0; i < blocks.size(); ++i ) {

                    int x = (blocks[i].m_x - blocks[0].m_x) * m_info.m_element_size_x + start_x;
                    int y = (blocks[i].m_y - blocks[0].m_y) * m_info.m_element_size_y + start_y;

                    canvas.Rectangle(
                        x - m_info.m_element_size_x / 2
                    ,   y - m_info.m_element_size_y / 2
                    ,   x + m_info.m_element_size_x / 2
                    ,   y + m_info.m_element_size_y / 2 );
                }

                canvas.Pen->Color = canvas.Brush->Color;
                canvas.Pen->Width = 16;

                // Рисуем все смежные соединения.
                for( unsigned int i = 0; i < blocks.size(); ++i ) {
                    for( unsigned int j = i+1; j < blocks.size(); ++j ) {
                        // 2 блока соседни?
                        if (
                            abs(blocks[i].m_x - blocks[j].m_x) +
                            abs(blocks[i].m_y - blocks[j].m_y)
                            == 1
                            )
                        {
                            canvas.MoveTo(
                               (blocks[i].m_x - blocks[0].m_x) * m_info.m_element_size_x + start_x
                            ,  (blocks[i].m_y - blocks[0].m_y) * m_info.m_element_size_x + start_y );
                            canvas.LineTo(
                                (blocks[j].m_x - blocks[0].m_x) * m_info.m_element_size_x + start_x
                            ,   (blocks[j].m_y - blocks[0].m_y) * m_info.m_element_size_x + start_y);
                        }
                    }
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
		~tetris_t() {}
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