#if !defined(_FIELD_GENERATORS__FACTORY_HPP__INCLUDED_)
#define _FIELD_GENERATORS__FACTORY_HPP__INCLUDED_

#include <stdexcept>
#include <string>
#include <stdlib.h>

#include "field/generators/classic.hpp"
#include "field/generators/triangle.hpp"
#include "field/generators/sixangle.hpp"
#include "field/generators/fiveangle.hpp"
#include "field/generators/stat_net.hpp"
#include "field/generators/chess_horse.hpp"
#include "field/generators/labirint.hpp"
#include "field/generators/tetris.hpp"


namespace field {

namespace generators {

//! ��������� ����� ������������ ��� �������������.
enum type_t {

	//! ������������ ����� - ���������� ����.
	classic,

    //! ��������� ������������.
    triangle,

    //! ��������� ��������������.
    sixangle,

    //! ��������� �������������.
    fiveangle,

    //! ����������� ����.
    stat_net,

    //! ��������� ����.
    chess_horse,

	//! ��������.
	labirint,

    //! ������.
    tetris,

	//! ������� ���� ������.
	net
};

//! ������� ��� ������������� �������� �� ����.
class factory_t {

	public:
		//! �������� ������ ��� ������������� ���������������� ����.
		/*!
			\throw � ������, ���� ������� ����������� ���.
		*/
		static interface_t &
		get_instance( const type_t & type ) {

			if ( type == classic ) {
				static field::generators::classic_t singleton;
				return singleton;
			}

			if ( type == triangle ) {
				static field::generators::triangle_t singleton;
				return singleton;
			}

			if ( type == sixangle ) {
				static field::generators::sixangle_t singleton;
				return singleton;
			}

			if ( type == fiveangle ) {
				static field::generators::fiveangle_t singleton;
				return singleton;
			}

			if ( type == stat_net ) {
				static field::generators::stat_net_t singleton;
				return singleton;
			}

			if ( type == chess_horse ) {
				static field::generators::chess_horse_t singleton;
				return singleton;
			}

			if ( type == labirint ) {
				static field::generators::labirint_t singleton;
				return singleton;
			}

			if ( type == tetris ) {
				static field::generators::tetris_t singleton;
				return singleton;
			}


			char error[10];
			itoa( type, error, 10 );

			throw std::runtime_error(
                std::string("Unknown type of field generator:") + error );
		}
};

} // namespace generators

} // namespace field

#endif