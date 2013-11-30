#include <stdint.h>

#define BMP_SIGNATURE 0x424D

typedef struct BMP_header
{
	uint16_t signature;
	uint32_t file_size;
	uint16_t reserved1;
	uint16_t reserved2;
	uint32_t pixels_offset;
} __attribute__((packed)) BMP_header;

typedef struct DIB_header
{
	uint32_t header_size;
	uint32_t width;
	uint32_t height;
	uint16_t planes;
	uint16_t bits_per_pixel;
	uint32_t compression_method;
	uint32_t pixel_array_size;
	uint32_t horizontal_resolution;
	uint32_t vertical_resolution;
	uint32_t num_colors;
	uint32_t num_important_colors;
} __attribute__((packed)) DIB_header;

// Compression methods (used in DIB_header.compression_method)
#define BI_RGB 0       // no compression
#define BI_RLE8 1      // RLE 8-bit/pixel
#define BI_RLE4 2      // RLE 4-bit/pixel
#define BI_BITFIELDS 3 // Bit field or Huffman 1D compression
#define BI_JPEG 4      // JPEG or RLE-24 compression
#define BI_PNG 5       // The bitmap contains a PNG image

int print_bmp(char buf[]);
