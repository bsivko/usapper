#if !defined(_GLOBAL_OPTIONS__INCLUDED_)
#define _GLOBAL_OPTIONS__INCLUDED_

class global_options_t {

	public:

		//! Тип фона.
		enum background_type_t {
			// Монохромный цвет.
			mono
            // Картинка.
        ,   picture
			// Снег.
		,	snow
			// Звезды.
		,	stars
		};

		long
		background_color() const;

		void
		set_background_color( long color );

		background_type_t
		background_type() const;

		void
		set_background_type( const background_type_t & background_type );

		int
		blink_time() const;

		//! Установить время мерцания.
		void
		set_blink_time( int sec );

		static global_options_t &
		get_instance();

	private:
		//! Время мерцания (в сек).
		int m_blink_time;

		//! Тип фона.
		background_type_t m_background_type;

		//! Цвет фона для моно.
		long m_background_color;

		// Singleton.
		global_options_t() : 
			m_blink_time(0)
		,	m_background_color(0)
		,	m_background_type(mono) 
		{}

};

#endif