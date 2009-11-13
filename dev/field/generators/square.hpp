#if !defined(_FIELD__GENERATORS__SQUARE_HPP__INCLUDED_)
#define _FIELD__GENERATORS__SQUARE_HPP__INCLUDED_

namespace field {

namespace generators {

#include <vector>

//! Класс двумерного массива.
template <typename T>
class square_t {

    public:
        square_t( int size_x, int size_y );

        square_t( const square_t<T> & square );

        const square_t<T> &
        operator = (const square_t<T> & square);

        //! Доступ к элементам.
        T &
        get( int x, int y );

        int
        size_x();

        int
        size_y();

        //! Заполнить массив константой.
        void
        fill( const T & value );

    private:
        std::vector<T> m_square;

        int m_size_x;
        int m_size_y;
};

struct coord_t {
    int m_x;
    int m_y;
    coord_t( int x, int y ) : m_x(x), m_y(y) {
    }
};

} // namespace generators

} // namespace field

#endif