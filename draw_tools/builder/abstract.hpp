#if !defined(_DRAW_TOOL__ABSTRACT_HPP__INCLUDED_)
#define _DRAW_TOOL__ABSTRACT_HPP__INCLUDED_

#include <Controls.hpp>
#include <ExtCtrls.hpp>

#include "draw_tools/interface.hpp"

namespace draw_tools {

namespace builder {

//! Класс абстрактного инструмента для рисования в C++ Builder.
class abstract_t : public draw_tools::interface_t {

	public:
        //! \class abstract_t Обязательно указать основной и теневой экран рисования.
        /*! \class abstract_t
            \note при рисовании конкретный объект иерархии рисует
            на теневом экране изображение, а эта абстракиций
            уже делает копию на основной.
            \attention размеры image должны быть идентичны по пикселам.
        */

        //! Установить теневой.
        void
        set_shadow( TCanvas & canvas, TRect & rect ) {
            m_shadow_canvas = &canvas;
            m_shadow_rect = rect;
        }

        //! Установить основной.
        void
        set_main( TCanvas & canvas, TRect & rect ) {
            m_main_canvas = &canvas;
            m_main_rect = rect;
        }

		//! Нарисовать поле на теневом и скопировать в основное.
		void
		shadow_copy_draw(
			//! Это поле рисуем.
			const field::field_t & field);

		//! Нарисовать поле на теневом.
		void
		shadow_draw(
			//! Это поле рисуем.
			const field::field_t & field );

        //! Нарисовать фон (в теневом экране).
        void
        draw_backgound();

		//! Скопировать из тени на основное.
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
        //! Теневая канва.
        TCanvas * m_shadow_canvas;
        //! Теневой источник.
        TRect m_shadow_rect;
        //! Основная канва.
        TCanvas * m_main_canvas;
        //! Теневой приемник.
        TRect m_main_rect;

        //! Находимся сейчас в состоянии подмига или нет.
        bool m_blink;
        int m_tick;
};

} // namespace builder

} // namespace draw_tools

#endif