#if !defined(_FIELD__ELEMENT_HPP__INCLUDED_)
#define _FIELD__ELEMENT_HPP__INCLUDED_

#include <vector>

#include <time.h>

namespace field {

//! Класс единичных объектов одного поля.
class element_t {

	public:

		element_t( int x = 0, int y = 0, bool is_bomb = false );

		int
		x() const {
			return m_x;
		}

		int
		y() const {
			return m_y;
		}

        void
		set_x( int x ) {
			m_x = x;
		}

        void
		set_y( int y ) {
			m_x = y;
		}

		bool
		is_open() const {
			return m_is_open;
		}

		//! Открыть клетку.
		void
		open();

		//! Закрыть клетку.
		void
		close() {
			m_is_open = false;
		}

        bool
        is_bomb() const {
            return m_is_bomb;
        }

		void
		set_bomb() {
			m_is_bomb = true;
		}

        bool
        is_flag() const {
            return m_is_flag;
        }

        void
        set_flag() {
            m_is_flag = true;
        }

        void
        unset_flag() {
            m_is_flag = false;
        }

        //! Добавляет соседний элемент.
        //! \note Если такой элемент уже есть, то повсторного добавления не происходит.
        /*!
            \param i элемент на добавление, index вектора.
        */
        void
        add_near_element( int i );

        std::vector<int> &
        near_elements() {
            return m_near_elements;
        }

        bool
        checked() const {
            return m_checked;
        }

        void
        set_check() {
            m_checked = true;
        }

        void
        unset_check() {
            m_checked = false;
        }

        //! Мигает клетка или нет.
        /*!
            \retval true мигает.
        */
        bool
        is_blink() const;

        //! Установить мигание клетки на заданное число секунд.
        void
        set_blink( int sec );

        //! Тип элемента.
        int
        type() const {
            return m_type;
        }

        void
        set_type( int type ) {
            m_type = type;
        }

	private:

		//! Положение центра по X в px.
		int m_x;
		//! Положение центра по Y в px.
		int m_y;

		//! Открыта клетка игроком или нет.
		bool m_is_open;

		//! Присутствует в клетке бомба или нет.
        //! \warning не использовать при формировании хэша (и оператора <).
		bool m_is_bomb;

        //! Пометил пользовател флажком или нет.
        bool m_is_flag;

        //! Выделен элемент или нет.
        bool m_checked;

        //! Конечное время для блинка.
        clock_t m_blink_time;

        //! Тип элемента. Задается пользователем по своему усмотрению.
        int m_type;

        //! Элементы-соседи.
        std::vector<int> m_near_elements;
};

} // namespace field

#endif