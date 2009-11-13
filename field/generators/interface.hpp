#if !defined(_FIELD__GENERATORS__INTERFACE_HPP__INCLUDED_)
#define _FIELD__GENERATORS__INTERFACE_HPP__INCLUDED_

#include "field/field.hpp"

namespace field {

namespace generators {

//! Интерфейс для генерирования объектов на поле.
class interface_t {

	public:
		//! Сгенерировать поле.
		/*!
			\attention delete на контроле вызывающего.
		*/
		virtual field::field_t *
		generate( const info_t & info ) = 0;

        //! Установить мины.
        /*!
            \param index номер элемента, по которому сделан клик.
                В него мины не ставить.

            \param field поле, на котором ставим мины.
        */
        virtual void
        set_bombs( field::field_t & field, int index ) = 0;

		virtual
		~interface_t() {}
};

} // namespace generators

} // namespace field

#endif