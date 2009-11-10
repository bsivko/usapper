#if !defined(_FIELD__FIELD_HPP__INCLUDED_)
#define _FIELD__FIELD_HPP__INCLUDED_

#include "field/element.hpp"

#include <vector>

namespace field {

//! Информация о поле для генерации.
struct info_t {
	//! Размер по X. Только для прямоугольных полей.
	int m_size_x;
	//! Размер по Y. Только для прямоугольных полей.
	int m_size_y;
	//! Число бомб.
	int m_bomb_number;
	//! Число элементов (вообще). Для сетевых полей.
	int m_elements_number;
	//! Размер в пикселах по X. Только для сетевых полей.
	int m_size_px_x;
	//! Размер в пикселах по Y. Только для сетевых полей.
	int m_size_px_y;
	//! Размер одного элемента по X в пикселах.
	int m_element_size_x;
	//! Размер одного элемента по Y в пикселах.
	int m_element_size_y;
};

//! Класс всего поля.
class field_t {

	public:

        //! Тип всех внутренних элементов.
        typedef std::vector<element_t> elements_t;

		field_t( const info_t & info );

		//! Доступ к всем элементам поля.
		elements_t &
		elements() {
			return m_elements;
		}

        //! Получить элемент по 'клику мышой'.
        /*!
            \param x X мыши.
            \param y Y мыши.
            \return индекс на найденный, если найден. Иначе -1.
        */
        int
        get_element_by_click( int x, int y );

		//! Доступ к всем элементам поля.
		const elements_t &
		elements() const {
			return m_elements;
		}


        //! Добавить элемент в поле.
        /*!
            \note копия формируется через STL-конструктор копирования.
            \note связи между элементами должны формироваться извне вручную.
        */
        void
        add_element( const element_t & element );

        info_t
        info() const {
            return m_info;
        }

        void
        set_info( const info_t & info ) {
            m_info = info;
        }

        //! Число рядом стоящих бомб.
        //! Считает число бомб каждый раз, обходом всех соседей.
        int
        count_of_near_bombs( int index ) const;

        //! Число рядом стоящих флагов.
        //! Считает число флагов каждый раз, обходом всех соседей.
        int
        count_of_near_flags( int index ) const;

        //! Число рядом неоткрытых клеток.
        //! Считает число неоткрытых клеток каждый раз, обходом всех соседей.
        int
        count_of_near_not_open( int index ) const;

        //! Рекурсивно открыть клетку (по 0-м).
        /*!
            \retval true если открыта бомба.
        */
        bool
        open( int index );

        //! Открыть все пустые без флага, которые рядом.
        /*!
            \retval true если открыта бомба.
        */
        bool
        open_near( int index );

        void
        open_all() {
            for( elements_t::iterator it = m_elements.begin();
            it != m_elements.end();
            ++it ) {
                it->open();
            }
        }

        //! Сбросить для всех выделение.
        void
        uncheck_all();

        //! Выделить элемент.
        void
        check( int index );

        //! Выделить всех соседей элемента.
        void
        check_near( int index );

        //! Общее число флагов.
        int
        count_of_all_flags();

        //! Выполнено все поле или нет.
        bool
        is_complete();

	private:

		elements_t m_elements;

        //! Информация, которая использовалась при генерации поля.
        info_t m_info;
};

} // namespace field

#endif