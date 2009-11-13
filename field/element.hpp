#if !defined(_FIELD__ELEMENT_HPP__INCLUDED_)
#define _FIELD__ELEMENT_HPP__INCLUDED_

#include <vector>

#include <time.h>

namespace field {

//! ����� ��������� �������� ������ ����.
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

		//! ������� ������.
		void
		open();

		//! ������� ������.
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

        //! ��������� �������� �������.
        //! \note ���� ����� ������� ��� ����, �� ����������� ���������� �� ����������.
        /*!
            \param i ������� �� ����������, index �������.
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

        //! ������ ������ ��� ���.
        /*!
            \retval true ������.
        */
        bool
        is_blink() const;

        //! ���������� ������� ������ �� �������� ����� ������.
        void
        set_blink( int sec );

        //! ��� ��������.
        int
        type() const {
            return m_type;
        }

        void
        set_type( int type ) {
            m_type = type;
        }

	private:

		//! ��������� ������ �� X � px.
		int m_x;
		//! ��������� ������ �� Y � px.
		int m_y;

		//! ������� ������ ������� ��� ���.
		bool m_is_open;

		//! ������������ � ������ ����� ��� ���.
        //! \warning �� ������������ ��� ������������ ���� (� ��������� <).
		bool m_is_bomb;

        //! ������� ����������� ������� ��� ���.
        bool m_is_flag;

        //! ������� ������� ��� ���.
        bool m_checked;

        //! �������� ����� ��� ������.
        clock_t m_blink_time;

        //! ��� ��������. �������� ������������� �� ������ ����������.
        int m_type;

        //! ��������-������.
        std::vector<int> m_near_elements;
};

} // namespace field

#endif