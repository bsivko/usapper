#if !defined(_COORD_HPP__INCLUDED_)
#define _COORD_HPP__INCLUDED_

struct coord_t {
    int m_x;
    int m_y;
//    coord_t() : m_x(-1), m_y(-1) {
//    }	
    coord_t( int x, int y ) : m_x(x), m_y(y) {
    }
};

#endif