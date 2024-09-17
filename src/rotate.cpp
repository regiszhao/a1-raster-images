#include "rotate.h"

void rotate(
  const std::vector<unsigned char> & input,
  const int width,
  const int height,
  const int num_channels,
  std::vector<unsigned char> & rotated)
{
  rotated.resize(height*width*num_channels);

  ////////////////////////////////////////////////////////////////////////////
  // loop through pixels
  for (int row = 0; row < height; row++) {

	  // find destination column
	  int dest_col = row;

	  for (int col = 0; col < width; col++) {

		  // find destination row (iterates bottom to top)
		  int dest_row = width - 1 - col;

		  // identify source and dest pixels
		  int src_pixel = row * width + col;
		  int dest_pixel = dest_row * height + dest_col;

		  // set dest subpixel to source subpixel for each in num channels
		  for (int subpixel = 0; subpixel < num_channels; subpixel++) {
			  int src_subpixel = src_pixel * num_channels + subpixel;
			  int dest_subpixel = dest_pixel * num_channels + subpixel;
			  rotated[dest_subpixel] = input[src_subpixel];
		  }
	  }
  }

  ////////////////////////////////////////////////////////////////////////////
}
