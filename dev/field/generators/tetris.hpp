#if !defined(_FIELD__GENERATORS__TETRIS_HPP__INCLUDED_)
#define _FIELD__GENERATORS__TETRIS_HPP__INCLUDED_

#include "field/generators/abstract.hpp"

namespace field {

namespace generators {

//! Класс генератора паркета из полей тетриса.
class tetris_t : public field::generators::abstract_t {

	public:
		virtual field::field_t *
		generate( const info_t & info );

        //! Попытаться добавить линк.
        void
        try_to_add_link(
            std::vector<element_t> & elements, int l1, int l2 );
};

} // namespace generators

} // namespace field

#endif