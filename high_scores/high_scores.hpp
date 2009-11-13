#if !defined(_HIGH_SCORES__FUNC_HPP__INCLUDED_)
#define _HIGH_SCORES__FUNC_HPP__INCLUDED_

#include <string>
#include <vector>
#include <map>

namespace high_scores {

//! ���� ������.
struct record_t {
    //! ��� ���������.
    std::string m_name;
    //! �����.
    int m_score;
    //! ����� �����������.
    std::string m_time;
    //! ��� �������� ��� ���.
    bool m_alive;

    record_t( const std::string & name
    ,   int score
    ,   const std::string & time
    ,   bool alive ) :
        m_name(name)
    ,   m_score(score)
    ,   m_time(time)
    ,   m_alive(alive)
    { }
};

//! �������� ����� ������� ��������.
struct one_table_t {
    //! ������ ��������.
    std::vector <record_t> m_records;
};

//! ��������� ������ � ���� ������ ���������� �� �������� ��������.
struct tables_t {
    std::map<std::string, one_table_t> m_tables;
    //! ������������ ���� �� ��������� ��������.
    void
    form_me( const std::string & content );

    //! ������������� � ������ ��� ���������� � ����.
    std::string
    get_to_content();
};

//! ����� �� ������ � high-���������.
class high_scores_t {

	public:
		const static int c_max_players_in_table = 10;

		static high_scores_t &
		get_instance();

		//! ���������� �������� ������ � ������� ��������.
		void 
		add_record(
            const std::string & filename
        ,   const record_t & record
        ,   const std::string & game_type
        );

        //! �������� ���������� ������� � ���� ���������.
        tables_t
        get_info( const std::string & filename );

	private:

        //! ��������� ���� �� ������������.
        /*!
            \throw std::runtime_error � ������ ������.
            \return ����������, ���� �������� ������ �������.
        */
        std::string
        verify_file( const std::string & filename );

        //! ������� ������ ������� ��������.
        /*!
            \throw std::runtime_error � ������ ������.
        */
        void
        create_empty_table( const std::string & filename );

        //! ��������� ��� �������������� ����.
        /*!
            \throw std::runtime_error � ������ ������.
        */
        void
        sign_file( const std::string & filename );

        //! �������� ��������� � �������.
        /*!
            \throw std::runtime_error � ������ ������.
        */
        void
        get_content_and_sign(
            const std::string & filename
        ,   std::string & content
        ,   int & sign );

        //! �������� ������� �� �����������.
        int
        make_sign( const std::string & content );

		verify_content( std::string &  );

		//! Singleton.
		high_scores_t() {};
};

} // namespace high_scores

#endif
