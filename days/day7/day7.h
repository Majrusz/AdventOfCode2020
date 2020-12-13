// Created by Majrusz on 07/12/2020. All rights reserved.

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
#include "is_number.h"

namespace aoc::day7 {
	struct Bag {
		std::string color{};
		std::vector< std::pair< std::string, size_t > > content{};
	};
	using Bags = std::vector< Bag >;
	using BagsMap = std::map< std::string, Bag >;
	using CountersMap = std::map< std::string, long long >;

	void start();

	BagsMap toMap( const Bags &bags );

	CountersMap generateCountersMap( const Bags &bags );

	size_t findColor( const std::string &color, const Bags &bags );

	size_t calculateBagCapacity( const std::string &color, const Bags &bags );

	std::istream &operator>>( std::istream &input, Bag &bag );
}
