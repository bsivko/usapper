#include "field/generators/classic.hpp"

#include <vector>

namespace field {

namespace generators {

field::field_t *
classic_t::generate( const info_t & info ) {

	// ������ �� �������.
	field::field_t * result = new field::field_t( info );

    std::vector<element_t> elements;

    int center_x = info.m_size_px_x / 2;
    int center_y = info.m_size_px_y / 2;
    int start_x = center_x - (info.m_size_x * info.m_element_size_x)/2;
    int start_y = center_y - (info.m_size_y * info.m_element_size_y)/2;

	for( int i = 0; i < info.m_size_x; ++i ) {
		for( int j = 0; j < info.m_size_y; ++j ) {
            elements.push_back( element_t(
 	    			start_x + info.m_element_size_x / 2 + i * info.m_element_size_x
     	    	,	start_y + info.m_element_size_y / 2 + j * info.m_element_size_y
                )
            );
		}
	}

    // ������� �����.

    // ������ �����.
    for( unsigned int i = 0; i < elements.size(); ++i ) {
        if ( ((i+1) % info.m_size_y) != 0 ) {
            // ������.
            elements.at(i).near_elements().push_back( i + 1 );
            // �����.
            elements.at(i+1).near_elements().push_back( i );
        }
    }
    // ������������.
    for( unsigned int i = 0; i < elements.size() - info.m_size_y; ++i ) {
        // ����.
        elements.at(i).near_elements().push_back( i + info.m_size_y );
        // �����.
        elements.at(i + info.m_size_y).near_elements().push_back( i );
    }

    // ��������� ������-����.
    for( unsigned int i = 0; i < elements.size() - info.m_size_y; ++i ) {
        if ( ((i+1) % info.m_size_y) != 0 ) {
            // ������-����.
            elements.at(i).near_elements().push_back( i + 1 + info.m_size_y );
            // �����-�����.
            elements.at( i + 1 + info.m_size_y ).near_elements().push_back( i );
        }
    }

    // ��������� �����-����.
    for( unsigned int i = 0; i < elements.size() - info.m_size_y; ++i ) {
        if ( ((i+1) % info.m_size_y) != 0 ) {
            // ������-����.
            elements.at(i + 1).near_elements().push_back( i + info.m_size_y );
            // �����-�����.
            elements.at(i + info.m_size_y).near_elements().push_back( i + 1 );
        }
    }

    // ��� �������� ���������� � result.
	for( unsigned int i = 0; i < elements.size(); ++i ) {
        result->add_element(
            elements[i]
        );
    }

    return result;
}


} // namespace generators

} // namespace field


