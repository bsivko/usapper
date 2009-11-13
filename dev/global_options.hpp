#if !defined(_GLOBAL_OPTIONS__INCLUDED_)
#define _GLOBAL_OPTIONS__INCLUDED_

class global_options_t {

	public:

		//! ��� ����.
		enum background_type_t {
			// ����������� ����.
			mono
            // ��������.
        ,   picture
			// ����.
		,	snow
			// ������.
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

		//! ���������� ����� ��������.
		void
		set_blink_time( int sec );

		static global_options_t &
		get_instance();

	private:
		//! ����� �������� (� ���).
		int m_blink_time;

		//! ��� ����.
		background_type_t m_background_type;

		//! ���� ���� ��� ����.
		long m_background_color;

		// Singleton.
		global_options_t() : 
			m_blink_time(0)
		,	m_background_color(0)
		,	m_background_type(mono) 
		{}

};

#endif