// Created by Majrusz on 13/12/2020. All rights reserved.

#pragma once

#include <vector>

#include "file_loader.h"
#include "is_number.h"

namespace aoc::day13 {
	struct Bus {
		size_t id, timeToWait;
	};
	struct BusStop {
		size_t timestamp{};
		std::vector< long > buses{};

		size_t getTimeToWait( size_t time ) const;

		Bus getMinimumTime() const;

		size_t findPattern() const;
	};

	void start();

	std::istream &operator>>( std::istream &input, BusStop &busStop );
}

