#include "rgb_to_hsv.h"
#include <algorithm>
#include <cmath>

void rgb_to_hsv(
  const double r,
  const double g,
  const double b,
  double & h,
  double & s,
  double & v)
{
  ////////////////////////////////////////////////////////////////////////////
  // formula from wikipedia
	// find Cmax, Cmin, delta_C
	double c_max = std::max({ r, g, b });
	double c_min = std::min({ r, g, b });
	double delta_c = c_max - c_min;

	// hue calculation
	if (delta_c == 0) {
		h = 0;
	}
	else if (c_max == r) {
		h = 60 * fmod(((g - b) / delta_c), 6);
	}
	else if (c_max == g) {
		h = 60 * (((b - r) / delta_c) + 2);
	}
	else {
		h = 60 * (((r - g) / delta_c) + 4);
	}

	// check for rollover
	if (h < 0) {
		h += 360;
	}
	else if (h >= 360) {
		h -= 360;
	}

	// saturation calculation
	if (c_max == 0) {
		s = 0;
	}
	else {
		s = delta_c / c_max;
	}

	// value calculation
	v = c_max;

  ////////////////////////////////////////////////////////////////////////////
}
