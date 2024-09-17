#include "demosaic.h"

int solveBayerPixelRGB(
	const std::vector<unsigned char>& bayer,
	int bayer_colour,
	int row, int col,
	int width, int height,
	int colour_to_solve);


void demosaic(
  const std::vector<unsigned char> & bayer,
  const int & width,
  const int & height,
  std::vector<unsigned char> & rgb)
{
  rgb.resize(width*height*3);

  ////////////////////////////////////////////////////////////////////////////
  // GBRG pattern
  int pattern[2]; // pattern for each row
  ////////////////////////////////////////////////////////////////////////////
  // loop through pixels of bayer
  for (int row = 0; row < height; row++) {
	  if (row % 2) {
		  pattern[0] = 0; pattern[1] = 1; // if row is odd, pattern is RG
	  }
	  else {
		  pattern[0] = 1; pattern[1] = 2; // if row is even, pattern is GB
	  }

	  for (int col = 0; col < width; col++) {
		  int which_pixel = row * width + col;
		  int bayer_colour = pattern[col % 2];

		  // loop through subpixels of rgb
		  for (int subpixel = 0; subpixel < 3; subpixel++) {
			  rgb[which_pixel*3 + subpixel] = solveBayerPixelRGB(bayer, bayer_colour, row, col, width, height, subpixel);
		  }


	  }
  }
  ////////////////////////////////////////////////////////////////////////////
}




// function that takes in a pixel's bayer colour, coordinates (row and col), image width and height,
// rgb colour to solve for
// returns value to use for that rgb colour
int solveBayerPixelRGB(
	const std::vector<unsigned char>& bayer,
	int bayer_colour,
	int row, int col,
	int width, int height,
	int colour_to_solve)
{
	int which_pixel = row * width + col;
	int total_pixels = width * height;

	// if pixel's bayer colour is same as rgb colour to solve for, return bayer value
	if (bayer_colour == colour_to_solve) {
		return bayer[which_pixel];
	}

	// if pixel's bayer colour is not the same as rgb to solve...
	// keep list of pixel numbers to average data from
	std::vector<int> pixels_to_avg;

	// if colour to solve is green
	if (colour_to_solve == 1) { 
		// cross + (get top, bottom, left, right)
		pixels_to_avg.assign({which_pixel - width, which_pixel + width, which_pixel - 1, which_pixel + 1}); 
	}
	// if bayer colour is blue or red
	else if (bayer_colour == 0 || bayer_colour == 2) {
		// diagonal x (get top left, top right, bottom left, bottom right)
		pixels_to_avg.assign({which_pixel-width-1, which_pixel-width+1, which_pixel+width-1, which_pixel+width+1});
	}
	// if bayer colour is green
	else {
		// if (even row and solve blue) or (odd row and solve red)
		if ((row % 2 == 0) && (colour_to_solve == 2) || (row % 2 == 1) && (colour_to_solve == 0)) {
			// left and right
			pixels_to_avg.assign({which_pixel - 1, which_pixel + 1});
		}
		else {
			// top and bottom
			pixels_to_avg.assign({ which_pixel - width, which_pixel + width });
		}
	}

	// calculate average of values found at pixels_to_avg
	float total = 0;
	int num_pixels = 0;
	int pixel_loc;
	for (auto i = pixels_to_avg.begin(); i != pixels_to_avg.end(); ++i) {
		pixel_loc = *i;
		if ((pixel_loc >= 0) && (pixel_loc < total_pixels)) { // only use pixel if in range
			total += bayer[pixel_loc];
			num_pixels += 1;
		}
	}

	return static_cast<int>(total / num_pixels);

}



// 
// 
// if rgb2slv == green: cross
// else if bayer == blue or red: diags
// else (bayer == green)
//		if (even row and solve blue) or (odd row and solve red): left and right
//		else: top and bottom
//		
// 
// 
// if bayer == blue
	// if rgb2slv == green: cross
	// else if rgb2slv == red: diags
// if bayer == red
	// if rgb2slv == green: cross
	// if rgb2slv == blue: diags
// if bayer == green:
	// if row is even:
		// if rgb2slv == blue: left and right
		// if rgb2slv == red: top and bottom
	// if row is odd:
		// if rgb2slv == blue: top and bottom
		// if rgb2slv == red: left and right