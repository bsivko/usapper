#if !defined(_HIGH_SCORES__FUNC_HPP__INCLUDED_)
#define _HIGH_SCORES__FUNC_HPP__INCLUDED_

#include <string>
#include <vector>
#include <map>

namespace high_scores {

//! Одна запись.
struct record_t {
    //! Имя участника.
    std::string m_name;
    //! Очков.
    int m_score;
    //! Время прохождения.
    std::string m_time;
    //! Жив участник или нет.
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

//! Хранение одной таблицы рекордов.
struct one_table_t {
    //! Записи рекордов.
    std::vector <record_t> m_records;
};

//! Структура хранит в себе полную информацию по таблицам рекордов.
struct tables_t {
    std::map<std::string, one_table_t> m_tables;
    //! Сформировать себя на основании контента.
    void
    form_me( const std::string & content );

    //! Преобразовать в строку для сохранения в файл.
    std::string
    get_to_content();
};

//! Класс по работе с high-скоресами.
class high_scores_t {

	public:
		const static int c_max_players_in_table = 10;

		static high_scores_t &
		get_instance();

		//! Попытаться добавить запись в таблицу рекордов.
		void 
		add_record(
            const std::string & filename
        ,   const record_t & record
        ,   const std::string & game_type
        );

        //! Получить содержимое таблицы в виде структуры.
        tables_t
        get_info( const std::string & filename );

	private:

        //! Проверить файл на корректность.
        /*!
            \throw std::runtime_error в случае ошибок.
            \return содержимое, если проверка прошла успешно.
        */
        std::string
        verify_file( const std::string & filename );

        //! Создать пустую таблицу рекордов.
        /*!
            \throw std::runtime_error в случае ошибок.
        */
        void
        create_empty_table( const std::string & filename );

        //! Подписать уже сформированный файл.
        /*!
            \throw std::runtime_error в случае ошибок.
        */
        void
        sign_file( const std::string & filename );

        //! Получить содежимое и подпись.
        /*!
            \throw std::runtime_error в случае ошибок.
        */
        void
        get_content_and_sign(
            const std::string & filename
        ,   std::string & content
        ,   int & sign );

        //! Получить подпись по содержимому.
        int
        make_sign( const std::string & content );

		verify_content( std::string &  );

		//! Singleton.
		high_scores_t() {};
};

} // namespace high_scores

#endif
