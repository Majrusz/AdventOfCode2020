// Created by Majrusz on 18/12/2020. All rights reserved.

#pragma once

#include <cmath>
#include <algorithm>
#include <iostream>
#include <sstream>

#include "file_loader.h"

namespace aoc::day18 {
	using SizeType = unsigned long long;

	struct Line {
		[[nodiscard]] SizeType calculate( SizeType ( *method )( const std::string &equation ) ) const;

		static SizeType part1Method( const std::string &string );

		static SizeType part2Method( const std::string &string );

		std::string value{};
	};
	using Lines = std::vector< Line >;

	void start();

	std::istream &operator>>( std::istream &input, Line &line );
}