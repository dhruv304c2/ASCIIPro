#include "Core/Viewport/Viewport.h"
#include "Math/Vector2D.h"
#include <algorithm>

#define VERTICAL_OUTLINE L'┃'
#define HORIZONTAL_OUTLINE L'━' 
#define TOP_LEFT_CORNER_OUTLINE L'┏'
#define TOP_RIGHT_CORNER_OUTLINE L'┓'
#define BOTTOM_LEFT_CORNER_OUTLINE L'┗'
#define BOTTOM_RIGHT_CORNER_OUTLINE L'┛'


Viewport::Viewport(int const& width, int const& height, Vector2D<int> const& origin): 
    m_width(width),
    m_height(height),
    m_origin(origin) {

    buffer = new wchar_t*[m_height];
    for(int i=0; i < m_height; i++){
	buffer[i] = new wchar_t[m_width];
	std::fill(buffer[i], buffer[i] + m_width, L' ');
    }
}

Viewport::~Viewport() {}

void Viewport::clearViewportBuffer(){
    for(int i=0; i < m_height; i++){
	std::fill(buffer[i], buffer[i] + m_width, L' ');
    }
}

void Viewport::resize(int const& width, int const& height){
    m_width = width;
    m_height = height;

    buffer = new wchar_t*[m_height];
    for(int i=0; i < m_height; i++){
	buffer[i] = new wchar_t[m_width];
	std::fill(buffer[i], buffer[i] + m_width, L' ');
    }

    on_resize.trigger();
}

void Viewport::setOrigin(Vector2D<int> origin){
    m_origin = origin;
}

Vector2D<int> Viewport::origin(){
    return m_origin;
}

Vector2D<int> Viewport::topRight(){
    return m_origin + Vector2D<int>(m_width, 0);
}

Vector2D<int> Viewport::bottomLeft(){
    return  m_origin + Vector2D<int>(0, m_height);
}

Vector2D<int> Viewport::bottomRight(){
    return  m_origin + Vector2D<int>(m_width,m_height);
}

int Viewport::width(){
    return m_width;
}

int Viewport::height(){
    return m_height;
}

void Viewport::writeToBuffer(wchar_t** buffer, int const& width, int const& height){
    int start_i = std::max(m_origin.y,0);
    int end_i = std::min(m_origin.y + m_height, height);

    int start_j = std::max(m_origin.x,0);
    int end_j = std::min(m_origin.x + m_width, width);

    for(int i = start_i; i < end_i; i++){
	for(int j = start_j; j < end_j; j++){

	    //////////////////////////// WRITE OUTLINE
	    if(i == start_i){
		if(j == start_j){
		    buffer[i][j] = TOP_LEFT_CORNER_OUTLINE;
		    continue;
		}
		if(j == end_j-1){
		    buffer[i][j] = TOP_RIGHT_CORNER_OUTLINE;
		    continue;
		}

		buffer[i][j] = HORIZONTAL_OUTLINE;
		continue;
	    }

	    if(i == end_i-1){
		if(j == start_j){
		    buffer[i][j] = BOTTOM_LEFT_CORNER_OUTLINE;
		    continue;
		}
		if(j == end_j-1){
		    buffer[i][j] = BOTTOM_RIGHT_CORNER_OUTLINE;
		    continue;
		}

		buffer[i][j] = HORIZONTAL_OUTLINE;
		continue;
	    }

	    if(j == start_j || j == end_j-1){
		buffer[i][j] = VERTICAL_OUTLINE;
		continue;
	    }
	    /////////////////////////////////// FINISHED ADDING OUTLINE

	    // Fill the buffer, ensuring indices stay valid
            int local_i = i - std::max(m_origin.y, 0);
            int local_j = j - std::max(m_origin.x, 0);
            if (local_i >= 0 && local_i < m_height && local_j >= 0 && local_j < m_width) {
                buffer[i][j] = this->buffer[local_i][local_j];
            } else {
                buffer[i][j] = L' '; 
            }
	}
    }
}
