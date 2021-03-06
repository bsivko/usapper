#if !defined(_DRAW_TOOLS__FACTORY_HPP__INCLUDED_)
#define _DRAW_TOOLS__FACTORY_HPP__INCLUDED_

#include <stdexcept>
#include <string>
#include <stdlib.h>

#include "draw_tools/builder/classic.hpp"
#include "draw_tools/builder/triangle.hpp"
#include "draw_tools/builder/sixangle.hpp"
#include "draw_tools/builder/fiveangle.hpp"
#include "draw_tools/builder/net.hpp"
#include "draw_tools/builder/tetris.hpp"


namespace draw_tools {

//! ��������� ����� ������������ ��� ���������.
enum type_t {

	//! ������������ ����� - ���������� ����.
	classic,

    //! ��������� ������������.
    triangle,

    //! ��������� ��������������.
    sixangle,

    //! ��������� �������������.
    fiveangle,

    //! ������.
    tetris,

	//! ������� ���� ������.
	net
};

//! ������� ��� ��������� �������� �� ����.
class factory_t {

	public:
		//! �������� ������ ��� ��������� ���������������� ����.
		/*!
			\throw � ������, ���� ������� ����������� ���.
		*/
		static interface_t &
		get_instance( const type_t & type ) {

			if ( type == classic ) {
				static draw_tools::builder::classic_t singleton;
				return singleton;
			}

			if ( type == triangle ) {
				static draw_tools::builder::triangle_t singleton;
				return singleton;
			}

			if ( type == sixangle ) {
				static draw_tools::builder::sixangle_t singleton;
				return singleton;
			}

			if ( type == fiveangle ) {
				static draw_tools::builder::fiveangle_t singleton;
				return singleton;
			}

			if ( type == net ) {
				static draw_tools::builder::net_t singleton;
				return singleton;
			}

			if ( type == tetris ) {
				static draw_tools::builder::tetris_t singleton;
				return singleton;
			}

			char error[10];
			itoa( type, error, 10 );

			throw std::runtime_error(
                std::string("Unknown type of draw tool:") + error );
		}
};

} // namespace draw_tools

#endif