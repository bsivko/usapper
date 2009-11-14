#include "high_scores/high_scores.hpp"

#include <stdexcept>
#include <fstream>
#include <sstream>

namespace high_scores {

high_scores_t &
high_scores_t::get_instance() {
	static high_scores_t high_scores;
	return high_scores;
}

std::string
get_to_enter( std::istream & istr ) {
    std::string value = "";
    unsigned char ch = istr.get();
    while( (ch == 13) || (ch == 10) ) {
        ch = istr.get();
    }
    value += ch;
    while( istr ) {
        unsigned char ch = istr.get();
        if (ch == 13) {
            return value;
        }
        value += ch;

        if (istr.eof()) {
            throw std::runtime_error(
                "Ошибка разбора данных таблицы - неожиданный конец файла.");
        }
    }

    return value;
}

void
tables_t::form_me( const std::string & content ) {

    std::istringstream str(content);

    // Общее число таблиц.
    int number_of_tables;

    str >> number_of_tables;

    for( int number = 0; number < number_of_tables; ++number) {
        // Сначала имя таблицы.
        std::string table_name = get_to_enter( str );
        // В эту таблицу собираем данные.
        one_table_t one_table;

        // Число записей в таблице.
        int number_of_records;
        str >> number_of_records;

        for( int i = 0; i < number_of_records; ++i ) {
            // Имя игрока.
            std::string name = get_to_enter( str );
            // Очки.
            int score;
            str >> score;
            // Время.
            std::string time = get_to_enter( str );
            // Жив или нет.
            bool alive;
            str >> alive;

            // Добавляем найденное.
            one_table.m_records.push_back(
                record_t( name, score, time, alive ) );
        }

        if ( m_tables.find(table_name) != m_tables.end() ) {
            // Уже существует таблица с таким именем.
            throw std::runtime_error(
                std::string("Дублированное имя таблиц:'") + table_name + "'" );
        }
        m_tables[table_name] = one_table;
    }
}

std::string
tables_t::get_to_content() {
    std::ostringstream str;

    str << m_tables.size() << ((unsigned char)13);

    for(
        std::map<std::string, one_table_t>::iterator it = m_tables.begin();
        it != m_tables.end();
        ++it ) {

        // Имя таблицы.
        str << it->first << std::endl;
        // Число записей в ней.
        str << it->second.m_records.size() << ((unsigned char)13);

        for(
            std::vector<record_t>::iterator it2 = it->second.m_records.begin();
            it2 != it->second.m_records.end();
            ++it2 ) {

            str << it2->m_name << ((unsigned char)13);
            str << it2->m_score << ((unsigned char)13);
            str << it2->m_time << ((unsigned char)13);
            str << it2->m_alive << ((unsigned char)13);
        }
    }

    str << std::ends;
    return str.str();
}

//! Попытаться добавить запись в таблицу рекордов.
void
high_scores_t::add_record(
	const std::string & filename
,	const record_t & record
,   const std::string & game_type
	) {

    std::ifstream inf( filename.c_str(), std::ios::in );
    if (!inf.good()) {
        inf.close();
        create_empty_table( filename );
    }

    std::string content = verify_file( filename );

    tables_t tables;
    tables.form_me( content );

    if ( tables.m_tables.find( game_type ) != tables.m_tables.end() ) {
        // Такой тип игры уже был.
        one_table_t one_table = tables.m_tables[ game_type ];
        // Добавляем запись согласно очкам.
        // Сначала в конец.
        one_table.m_records.push_back( record );
        // Теперь делаем вставку куда надо.
        int i = one_table.m_records.size() - 1;
        while(
            one_table.m_records[i].m_score
            >
            one_table.m_records[i-1].m_score ) {

            record_t record = one_table.m_records[i];
            one_table.m_records[i] = one_table.m_records[i-1];
            one_table.m_records[i-1] = record;

            --i;

            if (i == 0) break;
        }
        // Удаляем если превышение.
        while ( one_table.m_records.size() > c_max_players_in_table ) {
            one_table.m_records.erase(
                &one_table.m_records[one_table.m_records.size()-1] );
        }

        // Вставили, обработали. Отправляем обратно в map.
        tables.m_tables[ game_type ] = one_table;
    }
    else {
        // Такого типа ещё не было.
        one_table_t one_table;
        one_table.m_records.push_back( record );
        tables.m_tables[ game_type ] = one_table;
    }

    std::string text = tables.get_to_content();
    std::ofstream outf( filename.c_str(), std::ios::out );
    outf << text;
    outf.close();

    sign_file( filename );
}

void
high_scores_t::create_empty_table( const std::string & filename ) {
    std::ofstream outf( filename.c_str(), std::ios::out );
    if ( !outf.good() ) {
        throw std::runtime_error(
            "Ошибка при создании файла '" + filename + "'."
        );
    }
    outf << "0" << ((unsigned char)13);
    outf.close();

    sign_file( filename );
}

std::string
high_scores_t::verify_file( const std::string & filename ) {

    std::string content;
    int sign;
    get_content_and_sign( filename, content, sign );

    if (sign != make_sign( content )) {
        throw std::runtime_error(
            "Файл '" + filename + "' с данными о таблице рекордов поврежден."
        );
    }

    return content;
}

void
high_scores_t::sign_file( const std::string & filename ) {

    std::string content = "";
    // Получаем содержимое.
    {
        std::ifstream inf( filename.c_str(), std::ios::in | std::ios::binary );
        if ( !inf.good() ) {
            throw std::runtime_error(
                "Ошибка при открытии файла '" + filename + "'."
            );
        }
        inf.seekg( 0, std::ios::end );
        int size = inf.tellg();
        inf.seekg( 0, std::ios::beg );

        for( int i = 0; i < size; ++i) {
            content += inf.get();
        }

        inf.close();
    }

    // Подписываем.
    {
        int sign = make_sign( content );
        std::ofstream outf(
            filename.c_str()
        ,   std::ios::out | std::ios::binary | std::ios::app );

        unsigned char bytes[3];
        bytes[0] = sign % 0x0100;
        bytes[1] = (sign / 0x0100) % 0x0100;
        bytes[2] = (sign / 0x010000)% 0x0100;

        outf.put( bytes[0] );
        outf.put( bytes[1] );
        outf.put( bytes[2] );

        outf.close();
    }
}

void
high_scores_t::get_content_and_sign(
    const std::string & filename
,   std::string & content
,   int & sign ) {

    std::ifstream inf( filename.c_str(), std::ios::in | std::ios::binary );
    if ( !inf.good() ) {
        throw std::runtime_error(
            "Ошибка при открытии файла '" + filename + "'."
        );
    }

    inf.seekg( 0, std::ios::end );
    int size = inf.tellg();

    if (size < 5) {
        // Маловато байт в файле.
        throw std::runtime_error(
            "Файл '" + filename + "' с данными о таблице рекордов поврежден."
        );
    }

    inf.seekg( -3, std::ios::end );

    // Байты подписи.
    unsigned char bytes[3];
    bytes[0] = inf.get();
    bytes[1] = inf.get();
    bytes[2] = inf.get();

    // Сначала младшие, потом старшие.
    sign = bytes[0] + bytes[1] * 0x0100 + bytes[2] * 0x010000;

    // А сейчас получаем контент.
    inf.seekg( 0, std::ios::beg );

    content = "";

    for( int i = 0; i < size - 3; ++i ) {
        content += static_cast<unsigned char>(inf.get());
    }
}

int
high_scores_t::make_sign( const std::string & content ) {

    unsigned int value = 3361;
    for( unsigned int i = 0; i < content.size(); ++i ) {

        unsigned int mult = static_cast<unsigned int>(256 + content[i] + i % 101) + 1;

        value *= mult;
        // Ключ - простое число.
        value %= 909091;
    }

    return value;
}

tables_t
high_scores_t::get_info( const std::string & filename ) {

    tables_t result;

    std::ifstream inf( filename.c_str(), std::ios::in );
    if (!inf.good()) {
        inf.close();
        create_empty_table( filename );
    }

    std::string content = verify_file( filename );

    result.form_me( content );

    return result;
}

} // namespace high_scores



