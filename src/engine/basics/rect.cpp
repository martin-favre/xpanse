#include "rect.hpp"

Rect::Rect(
    float _x,
    float _y,
    float _w,
    float _h):
	x(_x),
	y(_y),
	w(_w),
	h(_h) {}

SDL_Rect Rect::get_sdl_rect() const{
	return SDL_Rect{
		int(round(x)),
		int(round(y)),
		int(round(w)),
		int(round(h))};
}

std::ostream & operator <<(std::ostream & stream, const Rect & p){
	stream << "(" << p.x << "," << p.y << "," << p.w << "," << p.h <<  ")";
	return stream;
}