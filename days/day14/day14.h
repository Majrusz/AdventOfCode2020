// Created by Majrusz on 14/12/2020. All rights reserved.

#pragma once

#include <string>
#include <bitset>
#include <map>
#include <algorithm>
#include <numeric>
#include <functional>

#include "file_loader.h"

namespace aoc::day14 {
	using Bits = std::bitset< 36 >;
	struct Group {
		std::string mask{};
		std::map< size_t, Bits > bits{};

		void applyMask();
	};
	struct Group2 : public Group {
		std::vector< std::pair< size_t, Bits > > pairs{};

		void applyMask2();
	};
	using Groups = std::vector< Group >;
	using Groups2 = std::vector< Group2 >;

	void start();

	std::istream &operator>>( std::istream &input, Group &group );

	std::istream &operator>>( std::istream &input, Group2 &group2 );
}
