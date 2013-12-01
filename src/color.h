#include <stdint.h>

#define ESC_RESET_COLOR "\x1B[0m"
#define ESC_RED         "\x1B[31m"
#define ESC_GREEN       "\x1B[32m"
#define ESC_YELLOW      "\x1B[33m"
#define ESC_BLUE        "\x1B[34m"
#define ESC_MAGENTA     "\x1B[35m"
#define ESC_CYAN        "\x1B[36m"
#define ESC_WHITE       "\x1B[37m"

typedef enum Term_color
{
	BLACK,
	RED,
	GREEN,
	YELLOW,
	BLUE,
	MAGENTA,
	CYAN,
	WHITE
} Term_color;

typedef struct Color
{
	uint8_t r;
	uint8_t g;
	uint8_t b;
} Color;

void print_pixel(Term_color col);
Term_color closest_color(Color c);
