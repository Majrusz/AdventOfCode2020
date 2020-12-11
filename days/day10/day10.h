// Created by Majrusz on 11/12/2020. All rights reserved.

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

namespace aoc::day10 {
	using Adapters = std::vector< size_t >;
	struct Counters {
		size_t jolt1{}, jolt3{};
	};

	void start();

	Counters findChain( const Adapters &adapters );

	size_t findPermutationAmount( const Adapters &adapters );
}

