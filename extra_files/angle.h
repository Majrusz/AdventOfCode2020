// Created by Majrusz on 20/12/2020. All rights reserved.

#pragma once

#include <cmath>

namespace aoc {
	struct Angle {
		operator double() const;

		double radians{};
		static constexpr double pi{ 3.14159265358979323846 };
	};

	struct Degrees : public Angle {
		explicit constexpr Degrees( double degrees ) : Angle{ degrees * Angle::pi / 180.0 } {
		}
	};

	struct Radians : public Angle {
		explicit constexpr Radians( double radians ) : Angle{ radians } {
		}
	};
}

constexpr aoc::Degrees operator"" _deg( long double degrees ) {
	return aoc::Degrees{ static_cast< double >( degrees ) };
}

constexpr aoc::Radians operator"" _rad( long double radians ) {
	return aoc::Radians{ static_cast< double >( radians ) };
}