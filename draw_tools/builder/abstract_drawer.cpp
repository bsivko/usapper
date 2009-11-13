#include "draw_tools/builder/abstract_drawer.hpp"

namespace draw_tools {

namespace builder {

void
abstract_drawer_t::draw_elements( const field::field_t & field ) {

    using field::field_t::elements_t;

    const elements_t & elements = field.elements();

	for( unsigned int i = 0; i < elements.size(); ++i ) {

        elements_t::const_iterator it = &elements[i];

        if ( m_blink && it->is_blink() ) {
            draw_unknown( *it );
            continue;
        }

        // Неоткрытое поле.
        if (!it->is_open()) {
            if (it->is_flag()) {
                draw_flag( *it );
            }
            else {
                draw_unknown( *it );
            }
            continue;
        }

        // Поле уже открыто.

        // Бомба.
        if ( it->is_bomb() ) {
            draw_explode_bomb( *it );
            continue;
        }

        // Остается только число.
        draw_number( *it, field.count_of_near_bombs(i) );
    }
}

void
abstract_drawer_t::draw_net( const field::field_t & field ) {

    using field::field_t::elements_t;

    elements_t & elements = field.elements();

	for( unsigned int i = 0; i < elements.size(); ++i ) {
    	for( unsigned int j = 0; j < elements[i].near_elements().size(); ++j ) {
            draw_link(
                elements[i]
            ,   elements[elements[i].near_elements()[j]]
            );
        }
    }
}

} // namespace builder

} // namespace draw_tools

