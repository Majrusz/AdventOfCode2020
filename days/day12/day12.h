// Created by Majrusz on 12/12/2020. All rights reserved.

#pragma once

#include <vector>
#include <cmath>

#include "file_loader.h"

namespace aoc::day12 {
	struct Vector { long x, y; };
	struct Instruction {
		enum class MoveType {
			North, South, East, West, Left, Right, Forward
		} type{ MoveType::East };

		static MoveType characterToMoveType( char character );

		long value{};
	};
	using Instructions = std::vector< Instruction >;

	void start();

	Vector navigate( const Instructions &instructions );

	Vector navigateWithWaypoint( const Instructions &instructions );

	std::istream &operator>>( std::istream &input, Instruction &instruction );
}