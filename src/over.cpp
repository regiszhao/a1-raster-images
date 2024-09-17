#include "over.h"
#include <iostream>

void over(
  const std::vector<unsigned char> & A,
  const std::vector<unsigned char> & B,
  const int & width,
  const int & height,
  std::vector<unsigned char> & C)
{
  C.resize(A.size());
  ////////////////////////////////////////////////////////////////////////////
  // loop through pixels
  for (int row = 0; row < height; row++) {
	  for (int col = 0; col < width; col++) {
		  int which_pixel = row * width + col;

		  // get alpha values
		  double alpha_a = A[which_pixel * 4 + 3] / 255.0;
		  double alpha_b = B[which_pixel * 4 + 3] / 255.0;
		  // calculate alpha_c
		  double alpha_c = alpha_a + alpha_b * (1 - alpha_a);

		  // calculate and assign each colour in C
		  for (int subpixel = 0; subpixel < 3; subpixel++) {
			  int colour_a = A[which_pixel * 4 + subpixel];
			  int colour_b = B[which_pixel * 4 + subpixel];
			  int colour_c = static_cast<int>(((colour_a * alpha_a) + (colour_b * alpha_b * (1 - alpha_a))) / alpha_c);
			  C[which_pixel * 4 + subpixel] = colour_c;
		  }

		  // assign alpha_c
		  //C[which_pixel * 4 + 3] = 255;
		  C[which_pixel * 4 + 3] = static_cast<int>(alpha_c * 255);

	  }
  }


  ////////////////////////////////////////////////////////////////////////////
}
