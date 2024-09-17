#include "rgb_to_gray.h"

void rgb_to_gray(
  const std::vector<unsigned char> & rgb,
  const int width,
  const int height,
  std::vector<unsigned char> & gray)
{
  gray.resize(height*width);

  ////////////////////////////////////////////////////////////////////////////
  // loop through pixels
  for (int row = 0; row < height; row++) {
	  for (int col = 0; col < width; col++) {
		  // get rgb values
		  int which_pixel = row * width + col;
		  int r = rgb[which_pixel * 3];
		  int g = rgb[which_pixel * 3 + 1];
		  int b = rgb[which_pixel * 3 + 2];

		  // use ntsc luminance formula to convert to grayscale value
		  // https://support.ptc.com/help/mathcad/r10.0/en/index.html#page/PTC_Mathcad_Help/example_grayscale_and_color_in_images.html
		  int gray_val = static_cast<int>((0.299 * r) + (0.587 * g) + (0.114 * b));
		  gray[which_pixel] = gray_val; // assign to gray array
	  }
  }
  
  ////////////////////////////////////////////////////////////////////////////
}


