#include "rgba_to_rgb.h"
#include <iostream>

void rgba_to_rgb(
  const std::vector<unsigned char> & rgba,
  const int & width,
  const int & height,
  std::vector<unsigned char> & rgb)
{
  rgb.resize(height*width*3);
  ////////////////////////////////////////////////////////////////////////////
  // Add your code here
  ////////////////////////////////////////////////////////////////////////////

  // loop through pixels of rgba array
  for (int row = 0; row < height; row++) {
    for (int col = 0; col < width; col++) {

      int which_pixel = row * width + col;

      // get alpha
      double alpha = rgba[which_pixel * 4 + 3] / 255.0;

      // loop through subpixels
      for (int subpixel = 0; subpixel < 3; subpixel++) {
        // assign rgb from rgba
        int which_subpixel_rgba = which_pixel * 4 + subpixel;
        int which_subpixel_rgb = which_pixel * 3 + subpixel;
        rgb[which_subpixel_rgb] = static_cast<int>(rgba[which_subpixel_rgba] * alpha);
      }
    }
  }

}
