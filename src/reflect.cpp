#include "reflect.h"
#include <cmath>

void reflect(
  const std::vector<unsigned char> & input,
  const int width,
  const int height,
  const int num_channels,
  std::vector<unsigned char> & reflected)
{
  reflected.resize(width*height*num_channels);
  ////////////////////////////////////////////////////////////////////////////
  // loop through pixels of image
  for (int row = 0; row < height; row++) {
	for (int col = 0; col < width; col++) {

		// identify source and destination pixel
		int src_pixel = row * width + col;
		int dest_pixel = row * width + (width - 1 - col);

		// set dest subpixel to source subpixel for each in num channels
		for (int subpixel = 0; subpixel < num_channels; subpixel++) {
			int src_subpixel = src_pixel * num_channels + subpixel;
			int dest_subpixel = dest_pixel * num_channels + subpixel;
			reflected[dest_subpixel] = input[src_subpixel];
		}
	}

  }
  
  ////////////////////////////////////////////////////////////////////////////
}
