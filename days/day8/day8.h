// Created by Majrusz on 08/12/2020. All rights reserved.

#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

#include "file_loader.h"

namespace aoc::day8 {
	struct Instruction {
		enum class OperationType {
			ACC, JMP, NOP
		};

		OperationType operation{};
		long value{};
		size_t timesCalled{};
	};
	using Instructions = std::vector< Instruction >;

	void start();

	long onCall( Instruction &instruction, long &counter );

	long reverseCall( Instruction &instruction, long &counter );

	long valueBeforeAnySecondCall( Instructions &instructions );

	long valueWithFix( Instructions &instructions );

	void resetInstructions( Instructions &instructions );

	std::istream &operator>>( std::istream &input, Instruction &instruction );
}
