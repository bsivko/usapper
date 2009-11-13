#include "draw_tools/builder/abstract.hpp"

#include "global_options.hpp"

#include <stdlib.h>
#include <time.h>

namespace draw_tools {

namespace builder {

void
abstract_t::draw_backgound() {

    static int tick = m_tick;

    switch ( global_options_t::get_instance().background_type() ) {
        case global_options_t::mono : {

            m_shadow_canvas->Brush->Color = TColor(
                global_options_t::get_instance().background_color()
            );
            m_shadow_canvas->Pen->Color = TColor(
                global_options_t::get_instance().background_color()
            );

            m_shadow_canvas->Rectangle( m_shadow_rect );

            break;
        }
        case global_options_t::snow : {

            // Число снежинок.
            static const int c_quantity = 200;

            // Скорости и положения.
            static float x[c_quantity];
            static float y[c_quantity];
            static float vx[c_quantity];
            static float vy[c_quantity];

            static init_snow = true;
            if (init_snow) {
                init_snow = false;
                for( int i = 0; i < c_quantity; ++i ) {
                    x[i] = random( m_shadow_rect.Width() );
                    y[i] = random( m_shadow_rect.Height() );
                    vx[i] = random(5) - 2;
                    vy[i] = random(5) + 1;
                }
            }

            // Обрабатываем динамику.
            if ( m_tick != tick ) {
                for( int i = 0; i < c_quantity; ++i ) {
                    // Летим.
                    x[i] += vx[i];
                    y[i] += vy[i];

                    // Пробиваем дно.
                    while (y[i] > m_shadow_rect.Height()) {
                        y[i] -= m_shadow_rect.Height();
                    }

                    // Меняем траекторию.
                    vx[i] = (random(100)/100.0 - 0.5) + vx[i]*0.9;
                }
            }

            // Очищаем фон.
            m_shadow_canvas->Brush->Color = clBlack;
            m_shadow_canvas->Pen->Color = clBlack;

            m_shadow_canvas->Rectangle( m_shadow_rect );

            // Рисуем снег.
            for( int i = 0; i < c_quantity; ++i ) {
                m_shadow_canvas->Pixels[x[i]][y[i]] = clWhite;
            }

            tick = m_tick;

            break;
        }
        case global_options_t::stars : {

            // Число звезд.
            static const int c_quantity = 300;
            static const int c_period = 500;

            // Положения и состояния.
            static int x[c_quantity];
            static int y[c_quantity];
            static int condition[c_quantity];
            static TColor color[c_quantity];

            static init_stars = true;
            if (init_stars) {
                init_stars = false;
                for( int i = 0; i < c_quantity; ++i ) {
                    x[i] = random( m_shadow_rect.Width() );
                    y[i] = random( m_shadow_rect.Height() );
                    condition[i] = random( c_period );
                    color[i] = TColor(random(0x01000000));
                }
            }

            // Обрабатываем динамику.
            if ( m_tick != tick ) {
                for( int i = 0; i < c_quantity; ++i ) {
                    condition[i] = (condition[i] + 1) % c_period;
                    if ( condition[i] == 0 ) {
                        x[i] = random( m_shadow_rect.Width() );
                        y[i] = random( m_shadow_rect.Height() );
                    }
                }
            }

            // Очищаем фон.
            m_shadow_canvas->Brush->Color = clBlack;
            m_shadow_canvas->Pen->Color = clBlack;

            m_shadow_canvas->Rectangle( m_shadow_rect );

            // Рисуем звезды.
            for( int i = 0; i < c_quantity; ++i ) {
                if (condition[i] < c_period / 2) {
                    // Звезда сидит в танке.
                }
                else if (condition[i] < c_period / 5 * 4) {
                    // Маленькая точка.
                    m_shadow_canvas->Pixels[x[i]][y[i]] = color[i];
                }
                else if (condition[i] < c_period / 20 * 19) {
                    // Горим.
                    if (condition[i] % 2 == 0) {
                        m_shadow_canvas->Pixels[x[i]][y[i]] = color[i];
                        m_shadow_canvas->Pixels[x[i]][y[i]+1] = color[i];
                        m_shadow_canvas->Pixels[x[i]][y[i]-1] = color[i];
                        m_shadow_canvas->Pixels[x[i]+1][y[i]] = color[i];
                        m_shadow_canvas->Pixels[x[i]-1][y[i]] = color[i];
                    }
                    else {
                        m_shadow_canvas->Pixels[x[i]][y[i]] = color[i];
                        m_shadow_canvas->Pixels[x[i]+1][y[i]+1] = color[i];
                        m_shadow_canvas->Pixels[x[i]-1][y[i]-1] = color[i];
                        m_shadow_canvas->Pixels[x[i]-1][y[i]+1] = color[i];
                        m_shadow_canvas->Pixels[x[i]+1][y[i]-1] = color[i];
                    }
                }

            }
            break;
        }
    }
    tick = m_tick;
}

void
abstract_t::shadow_copy_draw(
	const field::field_t & field) {

   shadow_draw( field );
   shadow_copy_to_main();
}

void
abstract_t::shadow_draw(
	const field::field_t & field ) {

    this->draw( field );
}

void
abstract_t::shadow_copy_to_main() {
    m_main_canvas->CopyRect( m_main_rect, m_shadow_canvas, m_shadow_rect );
}

} // namespace builder

} // namespace draw_tools


