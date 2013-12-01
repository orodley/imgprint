#include <stdio.h>
#include "color.h"

#define COLORS_SIZE 8

Color colors[COLORS_SIZE] = {
	{   0,   0,   0 }, // BLACK
	{ 205,   0,   0 }, // RED
	{   0, 205,   0 }, // GREEN
	{ 205, 205,   0 }, // YELLOW
	{   0,   0, 238 }, // BLUE
	{ 205,   0, 205 }, // MAGENTA
	{   0, 205, 205 }, // CYAN
	{ 229, 229, 229 }, // WHITE
};

void print_pixel(Term_color col)
{
	char ch = '#';

	switch (col) {
	case BLACK:   ch = ' ';                   break;
	case RED:     fputs(ESC_RED,     stdout); break;
	case GREEN:   fputs(ESC_GREEN,   stdout); break;
	case YELLOW:  fputs(ESC_YELLOW,  stdout); break;
	case BLUE:    fputs(ESC_BLUE,    stdout); break;
	case MAGENTA: fputs(ESC_MAGENTA, stdout); break;
	case CYAN:    fputs(ESC_CYAN,    stdout); break;
	case WHITE:   fputs(ESC_WHITE,   stdout); break;
	}

	putchar(ch);
	fputs(ESC_RESET_COLOR, stdout);
}

Term_color closest_color(Color c)
{
	Term_color closest;
	size_t min_diff = (size_t)-1;
	for (size_t i = 0; i < COLORS_SIZE; i++) {
		// This should be using Lab or something
		Color c2 = colors[i];
		int dr = (int)(c.r - c2.r);
		int dg = (int)(c.g - c2.g);
		int db = (int)(c.b - c2.b);

		unsigned int diff = (dr * dr) + (dg * dg) + (db * db);
		if (diff < min_diff) {
			closest = (Term_color)i;
			min_diff = diff;
		}
	}

	return closest;
}
