
#include "general_math.h"

const float Math::PI = 4.0f * atan(1.0f); // tan(pi/4) = 1
const float Math::PI_HALVES = 0.50f * Math::PI;
const float Math::PI_THIRDS = Math::PI * 0.3333333333333f;
const float Math::PI_FOURTHS = 0.25f * Math::PI;
const float Math::PI_SIXTHS = Math::PI * 0.6666666666667f;
const float Math::PI_2 = 2.00f * Math::PI;
const float Math::PI_DIV180 = Math::PI / 180.0f;
const float Math::PI_INVx180 = 180.0f / Math::PI;
const float Math::PI_INV = 1.0f / Math::PI;
const float Math::ZERO = (float)1e-7;

// -----------------------------------------------------------------------
// Default Constructor
Math::Math() {}