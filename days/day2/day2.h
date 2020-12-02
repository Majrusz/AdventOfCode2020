// Created by Majrusz on 02/12/2020. All rights reserved.

#pragma once

#include <string>
#include <iostream>
#include <algorithm>

#include "file_loader.h"

namespace aoc::day2 {
	struct Record;
	using Records = std::vector< Record >;

	void start();

	size_t countValidPasswords( Records &records );

	size_t countValidPasswords2( Records &records );

	struct Record {
		int min{}, max{};
		char letter{};
		std::string password{};

		friend std::istream &operator>>( std::istream &input, Record &record );
	};
};
