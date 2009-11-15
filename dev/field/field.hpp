#if !defined(_FIELD__FIELD_HPP__INCLUDED_)
#define _FIELD__FIELD_HPP__INCLUDED_

#include "field/element.hpp"

#include <vector>

namespace field {

//! ���������� � ���� ��� ���������.
struct info_t {
	//! ������ �� X. ������ ��� ������������� �����.
	int m_size_x;
	//! ������ �� Y. ������ ��� ������������� �����.
	int m_size_y;
	//! ����� ����.
	int m_bomb_number;
	//! ����� ��������� (������). ��� ������� �����.
	int m_elements_number;
	//! ������ � �������� �� X. ������ ��� ������� �����.
	int m_size_px_x;
	//! ������ � �������� �� Y. ������ ��� ������� �����.
	int m_size_px_y;
	//! ������ ������ �������� �� X � ��������.
	int m_element_size_x;
	//! ������ ������ �������� �� Y � ��������.
	int m_element_size_y;
    //! �������� �� ���������� ������������.
    int m_tag;
};

//! ��������� ����������� ����.
struct think_result_t {

    //! ��� ������.
    enum type_t {
        //! ������� ��������� �������.
        open_element,
        //! ���������� ����.
        set_flag,
        //! ��� �������. ������������ ������.
        no_solution,
        //! �� ���� ������ ������� (�������� ���� ���������).
        cant_do,
        //! ������ � ���� (����������� ������������� �����).
        error
    };

    think_result_t( int index, type_t result ) :
    m_index( index ), m_result(result)
    { }

    //! �������, � �������� ��������� ���������.
    int m_index;
    //! ��� ���������.
    type_t m_result;



};

//! ����� ����� ����.
class field_t {

	public:

        //! ��� ���� ���������� ���������.
        typedef std::vector<element_t> elements_t;

		field_t( const info_t & info );

		//! ������ � ���� ��������� ����.
		elements_t &
		elements() {
			return m_elements;
		}

        //! �������� ������� �� '����� �����'.
        /*!
            \param x X ����.
            \param y Y ����.
            \return ������ �� ���������, ���� ������. ����� -1.
        */
        int
        get_element_by_click( int x, int y );

		//! ������ � ���� ��������� ����.
		const elements_t &
		elements() const {
			return m_elements;
		}


        //! �������� ������� � ����.
        /*!
            \note ����� ����������� ����� STL-����������� �����������.
            \note ����� ����� ���������� ������ ������������� ����� �������.
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

        //! ����� ����� ������� ����.
        //! ������� ����� ���� ������ ���, ������� ���� �������.
        int
        count_of_near_bombs( int index ) const;

        //! ����� ����� ������� ������.
        //! ������� ����� ������ ������ ���, ������� ���� �������.
        int
        count_of_near_flags( int index ) const;

        //! ����� ����� ���������� ������.
        //! ������� ����� ���������� ������ ������ ���, ������� ���� �������.
        int
        count_of_near_not_open( int index ) const;

        //! ���������� ������� ������ (�� 0-�).
        /*!
            \retval true ���� ������� �����.
        */
        bool
        open( int index );

        //! ������� ��� ������ ��� �����, ������� �����.
        /*!
            \retval true ���� ������� �����.
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

        //! �������� ��� ���� ���������.
        void
        uncheck_all();

        //! �������� �������.
        void
        check( int index );

        //! �������� ���� ������� ��������.
        void
        check_near( int index );

        //! ����� ����� ������.
        int
        count_of_all_flags();

        //! ��������� ��� ���� ��� ���.
        bool
        is_complete();

        //! �������� ���� �����.
        think_result_t
        think();

	private:

		elements_t m_elements;

        //! ����������, ������� �������������� ��� ��������� ����.
        info_t m_info;
};

} // namespace field

#endif