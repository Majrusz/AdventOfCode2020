// Created by Majrusz on 05/12/2020. All rights reserved.

#pragma once

#include <sstream>
#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <algorithm>

#include "file_loader.h"

namespace aoc::day4 {
	struct Record;
	using Records = std::vector< Record >;

	void start();

	inline bool isValidPassport( const Record &passport );

	bool isValidPassport2( const Record &passport );

	struct Record {
		using Data = std::map< std::string, std::string >;
		Data data{};
	};

	std::istream &operator>>( std::istream &input, Record &record );
}
