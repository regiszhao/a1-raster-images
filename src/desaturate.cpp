#include "desaturate.h"
#include "hsv_to_rgb.h"
#include "rgb_to_hsv.h"
#include <iostream>

void desaturate(
  const std::vector<unsigned char> & rgb,
  const int width,
  const int height,
  const double factor,
  std::vector<unsigned char> & desaturated)
{
  desaturated.resize(rgb.size());
  ////////////////////////////////////////////////////////////////////////////
  // loop through rgb pixels
  for (int row = 0; row < height; row++) {
	  for (int col = 0; col < width; col++) {
		  int which_pixel = row * width + col;

		  // normalize
		  double r = rgb[which_pixel * 3] / 255.0;
		  double g = rgb[which_pixel * 3 + 1] / 255.0;
		  double b = rgb[which_pixel * 3 + 2] / 255.0;

		  // convert to hsv
		  double h = 0;
		  double s = 0;
		  double v = 0;
		  rgb_to_hsv(r, g, b, h, s, v);

		  // desaturate
		  s -= s * factor;


		  // convert back to rgb
		  hsv_to_rgb(h, s, v, r, g, b);

		  // update desaturated.ppm array
		  desaturated[which_pixel * 3] = static_cast<int>(r * 255);
		  desaturated[which_pixel * 3 + 1] = static_cast<int>(g * 255);
		  desaturated[which_pixel * 3 + 2] = static_cast<int>(b * 255);
	  }
  }

  ////////////////////////////////////////////////////////////////////////////
}
