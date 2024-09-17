#include "simulate_bayer_mosaic.h"

void simulate_bayer_mosaic(
  const std::vector<unsigned char> & rgb,
  const int & width,
  const int & height,
  std::vector<unsigned char> & bayer)
{
  bayer.resize(width*height);

  // GBRG pattern
  int pattern[2]; // pattern for each row
  ////////////////////////////////////////////////////////////////////////////
  // loop through pixels
  for (int row = 0; row < height; row++) {
	  if (row % 2) {
		  pattern[0] = 0; pattern[1] = 1; // if row is odd, pattern is RG
	  }
	  else {
		  pattern[0] = 1; pattern[1] = 2; // if row is even, pattern is GB
	  }

	  for (int col = 0; col < width; col++) {
		  int which_pixel = row * width + col;
		  int subpixel_to_use = pattern[col % 2];
		  bayer[which_pixel] = rgb[which_pixel * 3 + subpixel_to_use];
	  }
  }
  




  ////////////////////////////////////////////////////////////////////////////
}
