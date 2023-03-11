#include <stdio.h>
#include "graphics.h"
#pragma comment(lib,"graphics.lib")
using namespace std;

void drawLine(int coord[], int color = 15)
{
	setcolor(color);
	line(coord[0], coord[1], coord[2], coord[3]);
	setcolor(15);
}



void plotPixel(int coord[], int color = 15) {
	int x1 = coord[0];
	int y1 = coord[1];
	int x2 = coord[2];
	int y2 = coord[3];
	const int deltaX = abs(x2 - x1);
	const int deltaY = abs(y2 - y1);
	const int signX = x1 < x2 ? 1 : -1;
	const int signY = y1 < y2 ? 1 : -1;
	int error = 0;
	int deltaErr = ((deltaX > deltaY) ? deltaY : deltaX) +1;
	putpixel(x2, y2, color);
	if (deltaX > deltaY) {
		for (x1; x1 != x2; (x2 > x1) ? x1++ : x1--) {
			putpixel(x1, y1, color);
			error += deltaErr;
			if (error >= deltaX + 1) {
				y1 += signY;
				error = error - (deltaX + 1);
			}
		}
	}
	else {
		for (y1; y1 != y2; (y2 > y1) ? y1++ : y1--) {
			putpixel(x1, y1, color);
			error += deltaErr;
			if (error >= deltaY + 1) {
				x1 += signX;
				error = error - (deltaY + 1);
			}
		}
	}
	setcolor(15);
}

void rotate(int* coord, int deg)
{
	int x1 = coord[0];
	int x2 = coord[2];
	int y1 = coord[1];
	int y2 = coord[3];
	double theta = ((deg * 3.14) / 180);
	coord[2] = x1 + ((x2 - x1) * cos(theta)) - ((y2 - y1) * sin(theta));
	coord[3] = y1 + ((x2 - x1) * sin(theta)) + ((y2 - y1) * cos(theta));
}

// отображение выбранной прямой
void show_selected(int ab) {
	if (!ab)
		outtext(_strdup("Выбранный отрезок: CD"));
	else
		outtext(_strdup("Выбранный отрезок: AB"));
}

void scale_line(int* coord) {
	int x1 = coord[0];
	int x2 = coord[2];
	int y1 = coord[1];
	int y2 = coord[3];
	int dx = (x2 - x1) * 0.5;
	int dy = (y2 - y1) * 0.5;
	coord[2] = x2 + dx;
	coord[3] = y2 + dy;
}

void zoom_out(int* coord) {
	int x1 = coord[0];
	int x2 = coord[2];
	int y1 = coord[1];
	int y2 = coord[3];
	int dx = (x2 - x1) * 0.5;
	int dy = (y2 - y1) * 0.5;
	coord[2] = x2 - dx;
	coord[3] = y2 - dy;
}
void clear_and_draw_head(int selected_line) {
	clearviewport();
	show_selected(selected_line);
	outtextxy(0, 20, _strdup("Стрелки - перемещение; R - поворот; I - Увеличить размер; O - Уменьшить размер; Tab - Сменить выбор линии."));

}
int main()
{
	int i;
	char c;
	int selected_ab = 1; // Изначальный выбор отрезка
	initwindow(900, 500); // Инициализация окна
	int line_ab_coord[4]{ 100, 100, 100, 200 }; // Отрисовка отрезка AB
	int main_point_ab[2]{ 0, 0 };
	int line_cd_coord[4]{ 200, 100, 200, 200 }; // Отрисовка отрезка CD
	drawLine(line_ab_coord, 12);
	plotPixel(line_cd_coord);
	outtext(_strdup("Выбранный отрезок: AB"));
	outtextxy(0, 20, _strdup("Стрелки - перемещение; R - поворот; I - Увеличить размер; O - Уменьшить размер; Tab - Сменить выбор линии."));

	do
	{
		c = (char)getch();
		switch (c) {
		case (9):
			if (selected_ab) {
				selected_ab = 0;
				clear_and_draw_head(selected_ab);
				plotPixel(line_cd_coord,12);
				drawLine(line_ab_coord);
			}
			else {
				selected_ab = 1;
				clear_and_draw_head(selected_ab);
				drawLine(line_ab_coord,12);
				plotPixel(line_cd_coord);
			}
			break;
		case 'i': case'I':
			clear_and_draw_head(selected_ab);
			if (!selected_ab) {
				scale_line(line_cd_coord);
				plotPixel(line_cd_coord,12);
				drawLine(line_ab_coord);
			}
			else {
				scale_line(line_ab_coord);
				drawLine(line_ab_coord,12);
				plotPixel(line_cd_coord);
			}
			break;
		case 'o': case 'O':
			clear_and_draw_head(selected_ab);
			if (!selected_ab) {
				zoom_out(line_cd_coord);
				plotPixel(line_cd_coord,12);
				drawLine(line_ab_coord);
			}
			else {
				zoom_out(line_ab_coord);
				drawLine(line_ab_coord,12);
				plotPixel(line_cd_coord);
			}
			break;
		case 'r':case'R':
			clear_and_draw_head(selected_ab);
			if (!selected_ab)
			{
				rotate(line_cd_coord, 10);
				plotPixel(line_cd_coord,12);
				drawLine(line_ab_coord);
			}
			else
			{
				rotate(line_ab_coord, 10);
				drawLine(line_ab_coord,12);
				plotPixel(line_cd_coord);
			}
			break;
		case KEY_UP:
			clear_and_draw_head(selected_ab);
			if (!selected_ab) {
				line_cd_coord[1] -= 15;
				line_cd_coord[3] -= 15;
				plotPixel(line_cd_coord, 12);
				drawLine(line_ab_coord);
			}
			else {
				line_ab_coord[1] -= 15;
				line_ab_coord[3] -= 15;
				drawLine(line_ab_coord,12);
				plotPixel(line_cd_coord);
			}
			break;
		case KEY_LEFT:
			clear_and_draw_head(selected_ab);
			if (!selected_ab) {
				line_cd_coord[0] -= 15;

				line_cd_coord[2] -= 15;
				plotPixel(line_cd_coord,12);
				drawLine(line_ab_coord);
			}
			else {
				line_ab_coord[0] -= 15;
				line_ab_coord[2] -= 15;
				drawLine(line_ab_coord, 12);
				plotPixel(line_cd_coord);
			}
			break;
		case KEY_RIGHT:
			clear_and_draw_head(selected_ab);
			if (!selected_ab) {
				line_cd_coord[0] += 15;
				line_cd_coord[2] += 15;
				plotPixel(line_cd_coord,12);
				drawLine(line_ab_coord);
			}
			else {
				line_ab_coord[0] += 15;
				line_ab_coord[2] += 15;
				drawLine(line_ab_coord, 12);
				plotPixel(line_cd_coord);
			}
			break;
		case KEY_DOWN:
			clear_and_draw_head(selected_ab);
			if (!selected_ab) {
				line_cd_coord[1] += 15;
				line_cd_coord[3] += 15;
				plotPixel(line_cd_coord,12);
				drawLine(line_ab_coord);
			}
			else {
				line_ab_coord[1] += 15;
				line_ab_coord[3] += 15;
				drawLine(line_ab_coord,12);
				plotPixel(line_cd_coord);
			}
			break;
		}
	} while ((c != 'x') && (c != 'X'));	closegraph();}		