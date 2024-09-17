#include "hsv_to_rgb.h"
#include <cmath>

void hsv_to_rgb(
  const double h,
  const double s,
  const double v,
  double & r,
  double & g,
  double & b)
{
  ////////////////////////////////////////////////////////////////////////////
	// formula from wikipedia
	double c = v * s;
	double x = c * ( 1 - abs( fmod((h/60), 2) - 1 ) );
	double m = v - c;
	
	// r', g', b'
	if (h >= 0 && h < 60) {
		r = c; g = x; b = 0;
	}
	else if (h >= 60 && h < 120) {
		r = x; g = c; b = 0;
	}
	else if (h >= 120 && h < 180) {
		r = 0; g = c; b = x;
	}
	else if (h >= 180 && h < 240) {
		r = 0; g = x, b = c;
	}
	else if (h >= 240 && h < 300) {
		r = x; g = 0; b = c;
	}
	else if (h >= 300 && h < 360) {
		r = c; g = 0; b = x;
	}

	r += m; g += m; b += m;


  ////////////////////////////////////////////////////////////////////////////
}
