// Created by Majrusz on 03/12/2020. All rights reserved.

#pragma once

#include <string>
#include <iostream>
#include <algorithm>
#include <numeric>

#include "file_loader.h"

namespace aoc::day3 {
	const char tree{ '#' }, nothing{ '.' };

	void start();

	size_t countTrees( std::vector< std::string > &lines, int horizontalShift, int verticalShift );
}
