#include "field/generators/tetris.hpp"
#include "coord.hpp"

#include <vector>
#include <string>
#include <stdlib.h>

#include <fstream>

namespace field {

namespace generators {

//! Класс двумерного массива.
template <class T>
class square_t {

    public:
        square_t( int size_x, int size_y ) :
            m_size_x( size_x )
        ,   m_size_y( size_y )
        ,   m_square( size_x*size_y ) {

        }

        //! Доступ к элементам.
        T &
        get( int x, int y ) {
            try {
                return m_square.at( x + m_size_x * y );
            }
            catch( std::exception & ex ) {
                std::string str = ex.what();
            }
        }

        //! Доступ к элементам.
        const T &
        get( int x, int y ) const {
            try {
                return m_square.at( x + m_size_x * y );
            }
            catch( std::exception & ex ) {
                std::string str = ex.what();
            }
        }

        int
        size_x() const {
            return m_size_x;
        }

        int
        size_y() const {
            return m_size_y;
        }

        //! Заполнить массив константой.
        void
        fill( const T & value ) {
            for(
                std::vector<T>::iterator it = m_square.begin();
                it != m_square.end();
                ++it
                 )  {

                *it = value;
            }
        }

    private:
        std::vector<T> m_square;

        int m_size_x;
        int m_size_y;
};

//! Произвести заполнение и вернуть сколько позиций заполнено.
int
fill( square_t<int> & square, int x, int y ) {

    if ( square.get(x,y) == -2 )
        return 0;

    if ( square.get(x,y) != -1 )
        return 0;

    int result = 1;

    square.get(x, y) = -2;

    if ( x > 0 ) {
        result += fill( square, x-1, y );
    }
    if ( y > 0 ) {
        result += fill( square, x, y-1 );
    }
    if ( x < square.size_x()-1 ) {
        result += fill( square, x+1, y );
    }
    if ( y < square.size_y()-1 ) {
        result += fill( square, x, y+1 );
    }

    return result;
}

//! Посчитать число заполнений.
/*!
    \return вектор, в котором записаны числа, по сколько заполнений в каждом из.
*/
std::vector <int>
get_fills( const square_t<int> & square ) {

    std::vector <int> fills;
    square_t<int> square_copy = square;

    for( int i = 0; i < square_copy.size_x(); ++i ) {
        for( int j = 0; j < square_copy.size_y(); ++j ) {

            if ( square_copy.get(i ,j) == -1 ) {
                fills.push_back( fill(square_copy, i ,j) );
            }
        }
    }

    return fills;
}

void
try_to_add_near(
    const square_t<int> & square,
    int x,
    int y,
    std::vector<coord_t> & near
    ) {

    if ( square.get(x,y) != -1 )
        return;

    for( unsigned int i = 0; i < near.size(); ++i ) {
        if (( near[i].m_x == x ) && ( near[i].m_y == y ))
            // Найдено совпадение.
            return;
    }

    if ( y != square.size_y() - 1 ) {
        if (square.get( x, y + 1 ) == -1)
            return;
    }

    near.push_back( coord_t(x, y) );
}

//! Попытаться добавить линк.
void
tetris_t::try_to_add_link(
    std::vector<element_t> & elements, int l1, int l2 ) {

    if (l1 == l2)
        return;

    // Проверяем есть ли уже такой линк.
    std::vector<int> near1 = elements[l1].near_elements();
    for( unsigned int i = 0; i < near1.size(); ++i ) {
        if (near1[i] == l2) {
            return;
        }
    }
    std::vector<int> near2 = elements[l2].near_elements();
    for( unsigned int i = 0; i < near2.size(); ++i ) {
        if (near1[i] == l1) {
            return;
        }
    }
    set_link( l1, l2, elements );
}

field::field_t *
tetris_t::generate( const info_t & info ) {

    randomize();

    // Алгоритм эвристический. Потому не всегда получает решение.
    // TODO : через отдельную функцию.
    int fatal_count = 500;

	// Объект на возврат.
	field::field_t * result = new field::field_t( info );

    square_t<int> square( info.m_size_x, info.m_size_y );
    square.fill( -1 );

    // Когда заполняем, next означает следующий
    // индекс элемента при введении в систему.
    // Инкрементировать при вставке.
    int next = 0;

    // Число блоков в фигуре (тетрис - 4).
    const int c_blocks_count = info.m_tag;

    std::vector<element_t> elements;
    // Устанавливаем по числу фигур.
    elements.resize( info.m_size_x * info.m_size_y / c_blocks_count );

    int center_x = info.m_size_px_x / 2;
    int center_y = info.m_size_px_y / 2;
    int start_x = center_x - (info.m_size_x * info.m_element_size_x)/2;
    int start_y = center_y - (info.m_size_y * info.m_element_size_y)/2;

    // Задаем никакой тип.
    for( unsigned int i = 0; i < elements.size(); ++i ) {
        elements[i].set_type(-1);
    }

    // Стартовые точки вставки фигур.
    std::vector <coord_t> start_points;
    start_points.reserve( square.size_x() );
    for( int i = 0; i < square.size_x(); ++i ) {
        start_points.push_back( coord_t( i, square.size_y()-1 ) );
    }

    bool min_is_on = true;

    while(true) {
        // Работаем с копией.
        square_t<int> square_copy = square;
        std::vector<coord_t> blocks;

        // Ищем свободное поле.
        int x;
        int y;
        bool choosed = false;
        do {
            // Выбираем стартовую точку.
            int c;
            choosed = false;
            // Готовим стартовые точки.
            int min_choose = 0;
            for( unsigned int  i = 0; i < start_points.size(); ++i ) {

                // Свистаем всех наверх.
                while(
                    ( start_points[i].m_y >= 0 )
                    &&
                    ( square_copy.get( start_points[i].m_x, start_points[i].m_y ) != -1 )
                ) {
                    --start_points[i].m_y;
                }

                // Ищем самое дно.
                if (( start_points[i].m_y > min_choose ) && ( start_points[i].m_y >= 0 )) {
                    min_choose = start_points[i].m_y;
                }
            }
            // Удаляем все -1.
            for( unsigned int  i = 0; i < start_points.size(); ++i ) {
                if (start_points[i].m_y == -1) {
                    start_points.erase( &start_points[i] );
                    --i;
                }
            }
            if (start_points.size() == 0)
                break;

            do {
                c = random(start_points.size());
                if (!min_is_on) {
                    break;
                }
            }
            while( start_points[c].m_y != min_choose );

            x = start_points[c].m_x;
            y = start_points[c].m_y;
            choosed = true;
        }
        while( !choosed );

        // Рисуем фигуру.
        std::vector<coord_t> near;
        near.push_back( coord_t(x, y) );
        blocks.push_back( coord_t(x, y) );
        square_copy.get(x, y) = next;
        for(int i = 1; i < c_blocks_count; ++i) {

            for( unsigned int j = 0; j < blocks.size(); ++j ) {
                int x = blocks[j].m_x;
                int y = blocks[j].m_y;

                // Влево.
                if ( x > 0 ) {
                    try_to_add_near( square_copy, x-1, y, near );
                }
                // Вправо.
                if ( x < square_copy.size_x()-1 ) {
                    try_to_add_near( square_copy, x+1, y, near );
                }
                // Вверх.
                if ( y > 0 ) {
                    try_to_add_near( square_copy, x, y-1, near );
                }
                // Вниз.
                if ( y < square_copy.size_y()-1 ) {
                    try_to_add_near( square_copy, x, y+1, near );
                }
            }

            for( unsigned int  i = 0; i < near.size(); ++i ) {
                if (square_copy.get( near[i].m_x, near[i].m_y ) != -1) {
                    near.erase( &near[i] );
                    --i;
                }
            }

            // Берем любой.
            if ( near.size() > 0 ) {
                int index;
                do {
                    index = random( near.size() );
                }
                while( square_copy.get( near[index].m_x, near[index].m_y ) != -1 );
                // Используем по назначению.
                blocks.push_back( coord_t( near[index] ) );
                square_copy.get( near[index].m_x, near[index].m_y ) = next;
            }
        }

        // Мы нарисовали фигуру.
        // Теперь проверяем, что после её рисования мы можем
        // заполнить поле такими же фигурами без остатка.
        bool we_can = true;

        // Достугнут нулевой уровень в стартовых точках?
        bool blocks_null_y = false;
        for( unsigned int i = 0; i < blocks.size(); ++i ) {
            if ( blocks[i].m_y == 0 ) {
                blocks_null_y = true;
                break;
            }
        }
        // Необходимость проверки заливок поля.
        if (
            ( static_cast<int>(start_points.size()) < square.size_x() )
            ||
            ( blocks_null_y ) ) {

            std::vector <int> values = get_fills( square_copy );
            for(
                std::vector <int>::iterator it = values.begin();
                it != values.end();
                ++it ) {

                if (*it % c_blocks_count != 0) {
                    we_can = false;
                    min_is_on = false;
                    --fatal_count;
                    if (fatal_count < 0) {
                        delete result;
                        return generate(info);
                    }
                    break;
                }
            }
        }

        // Сборка фигуры корректна?
        if (we_can) {
            // Да. Заменяем на рабочую копию square.
            square = square_copy;
            elements[next].blocks() = blocks;
            ++next;
            fatal_count = 200;
        }

        // Поле закончилось?
        if ( elements.size() == static_cast<unsigned int>(next) )
            break;
    }

    // Устанавливаем координаты.
	for( unsigned int i = 0; i < elements.size(); ++i ) {

        coord_t coord = elements[i].blocks()[0];

        elements[i].set_x(
   			start_x + info.m_element_size_x / 2 + coord.m_x * info.m_element_size_x );
        elements[i].set_y(
  	    	start_y + info.m_element_size_y / 2 + coord.m_y * info.m_element_size_y );
	}

    // Создаем связи.
    for( int i = 0; i < square.size_x(); ++i ) {
        for( int j = 0; j < square.size_y(); ++j ) {

            if ( i > 0 ) {
                try_to_add_link( elements, square.get( i, j ), square.get( i-1, j ) );
                if ( j > 0 ) {
                    try_to_add_link( elements, square.get( i, j ), square.get( i-1, j-1 ) );
                }
                if ( j < square.size_y()-1 ) {
                    try_to_add_link( elements, square.get( i, j ), square.get( i-1, j+1 ) );
                }
            }
            if ( j > 0 ) {
                try_to_add_link( elements, square.get( i, j ), square.get( i, j-1 ) );
            }
            if ( i < square.size_x()-1 ) {
                try_to_add_link( elements, square.get( i, j ), square.get( i+1, j ) );
                if ( j > 0 ) {
                    try_to_add_link( elements, square.get( i, j ), square.get( i+1, j-1 ) );
                }
                if ( j < square.size_y()-1 ) {
                    try_to_add_link( elements, square.get( i, j ), square.get( i+1, j+1 ) );
                }
            }
            if ( j < square.size_y()-1 ) {
                try_to_add_link( elements, square.get( i, j ), square.get( i, j+1 ) );
            }

        }
    }

    // Все элементы отправляем в result.
	for( unsigned int i = 0; i < elements.size(); ++i ) {
        result->add_element(
            elements[i]
        );
    }

    return result;
}


} // namespace generators

} // namespace field


