// Created by Majrusz on 12/12/2020. All rights reserved.

#pragma once

#include <vector>
#include <algorithm>

#include "file_loader.h"

namespace aoc::day11 {
	struct Row {
		enum class SeatType {
			Floor, Empty, Occupied
		};

		SeatType &operator[]( size_t i ) { return this->seats[ i ]; }

		const SeatType &operator[]( size_t i ) const { return this->seats[ i ]; }

		std::vector< SeatType > seats{};
	};
	struct Columns {
		size_t countOccupiedAdjacentSeats( long x, long y ) const;

		size_t countOccupiedAdjacentSeats2( long x, long y ) const;

		Row::SeatType &get( long x, long y ) { return this->rows[ y ][ x ]; }

		const Row::SeatType &get( long x, long y ) const { return this->rows[ y ][ x ]; }

		bool applyFirstRule();

		bool applySecondRule();

		bool applyThirdRule();

		bool applyFourthRule();

		size_t countOccupiedSeats() const;

		friend std::ostream &operator<<( std::ostream &stream, const Columns &columns );

		std::vector< Row > rows{};
	};

	void start();

	std::istream &operator>>( std::istream &input, Row &row );
}
