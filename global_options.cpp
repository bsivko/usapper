#include "global_options.hpp"

long
global_options_t::background_color() const {
	return m_background_color;
}

void
global_options_t::set_background_color( long color ) {
	m_background_color = color;
}

global_options_t::background_type_t
global_options_t::background_type() const {
	return m_background_type;
}

void
global_options_t::set_background_type( const background_type_t & background_type ) {
	m_background_type = background_type;
}

int
global_options_t::blink_time() const {
	return m_blink_time;
}

//! Установить время мерцания.
void
global_options_t::set_blink_time( int sec ) {
	m_blink_time = sec;
}

global_options_t &
global_options_t::get_instance() {
	static global_options_t global_options;
	return global_options;
}
