#include "Rect.h"

Rect::Rect(int l, int t, int r, int b) {
	left = l;
	top = t;
	right = r;
	bottom = b;
}

bool Rect::PtInRect(Point p) {

}

bool Rect::IntersectRect(Rect* checkRect, Rect* objRect) {

}

void Rect::SetRect(int l, int t, int r, int b) {
	left = l;
	top = t;
	right = r;
	bottom = b;
}