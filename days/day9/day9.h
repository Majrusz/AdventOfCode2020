// Created by Majrusz on 09/12/2020. All rights reserved.

#pragma once

#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>
#include <functional>
#include <numeric>

#include "file_loader.h"

namespace aoc::day9 {
	using Elements = std::vector< size_t >;
	constexpr size_t groupSize{ 25 };

	void start();

	bool isAnyTwoPreviousElementsSummableTo( const Elements &elements, size_t index );

	size_t findBrokenElement( const Elements &elements );

	size_t findEncryptionWeakness( const Elements &elements );
}
