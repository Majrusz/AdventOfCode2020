// Created by Majrusz on 05/12/2020. All rights reserved.

#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

#include "file_loader.h"

namespace aoc::day5 {
	using Records = std::vector< std::string >;

	void start();

	size_t calculatePosition( const std::string &record, char lowerHalf, char upperHalf, size_t startIndex, size_t nElements );

	size_t getRow( const std::string &record );

	size_t getColumn( const std::string &record );

	size_t getSeatID( const std::string &record );

	std::vector< size_t > generateIDs( const Records &records );

	std::vector< size_t >::iterator getMaxElement( const Records &records );

	size_t findMissingID( const Records &records );
}

