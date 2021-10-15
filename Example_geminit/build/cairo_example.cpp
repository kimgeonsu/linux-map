#include "cairo_example.h"

int main(int argc, char *argv[]) {
	Graphics *g;
	g = new Graphics("/dev/fb0");

	Pen p;
	Color color(0, 0, 0);
	Font font;
	Brush brush;
	std::string *str = "Geminit Hello! 1234567890";

	//선 그리기
	g->DrawLine(&p, 10, 10, 110, 10);
	g->DrawLine(&p, 110, 10, 110, 110);
	g->DrawLine(&p, 110, 110, 10, 110);
	g->DrawLine(&p, 10, 110, 10, 10);

	//사각형 그리기
	g->DrawRectangle(&p, 120, 10, 100, 100);

	//지정 위치에 문자 및 숫자 표시
	g->DrawString(str, -1, &font, PointF(10, 130), &brush);

	//문자, 숫자에 대한 폰트 및 크기 지정
	font = Font("Arial", 30);
	g->DrawString(str, -1, &font, PointF(10, 160), &brush);

	//선, 도형 두께 지정
	p = Pen(color, 3.0);
	g->DrawLine(&p, 10, 170, 60, 170);
	g->DrawRectangle(&p, 10, 180, 30, 30);

	//도형 내부 채우기
	g->FillRectangle(&brush, 230, 10, 100, 100);

	g->~Graphics();

	return 0;
}
