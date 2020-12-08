// Created by Majrusz on 08/12/2020. All rights reserved.

#include "day8.h"

void aoc::day8::start() {
	Instructions instructions{ loadFile< Instruction >( "days/day8/input.txt" ) };

	std::cout << valueBeforeAnySecondCall( instructions ) << std::endl;
	resetInstructions( instructions );
	std::cout << valueWithFix( instructions ) << std::endl;
}

std::istream &aoc::day8::operator>>( std::istream &input, Instruction &instruction ) {
	std::string text{};

	input >> text;
	input >> instruction.value;

	if( text == "acc" )
		instruction.operation = Instruction::OperationType::ACC;
	else if( text == "jmp" )
		instruction.operation = Instruction::OperationType::JMP;
	else
		instruction.operation = Instruction::OperationType::NOP;

	return input;
}

long aoc::day8::valueBeforeAnySecondCall( Instructions &instructions ) {
	long counter{};

	for( long currentID{}; currentID < instructions.size(); ) {
		Instruction &instruction{ instructions[ currentID ] };

		currentID += onCall( instruction, counter );

		if( instruction.timesCalled > 1 ) {
			currentID += reverseCall( instruction, counter );
			return counter;
		}
	}

	throw std::logic_error( "Wrong input!" );
}

long aoc::day8::valueWithFix( Instructions &instructions ) {
	long counter{};
	std::vector< Instruction* > history{};
	long fixedOnIndex{ -1 };

	auto swap{ []( Instruction &instruction ){
		if( instruction.operation == Instruction::OperationType::NOP ) {
			instruction.operation = Instruction::OperationType::JMP;
		} else if( instruction.operation == Instruction::OperationType::JMP ) {
			instruction.operation = Instruction::OperationType::NOP;
		}
	} };

	for( size_t currentID{}; currentID < instructions.size(); ) {
		Instruction &instruction{ instructions[ currentID ] };

		if( instruction.timesCalled == 0 ) {
			// std::cout << currentID << ":" << counter << '\t' << "(" << instruction.timesCalled << '\t' << fixedOnIndex << ")" << std::endl;
			currentID += onCall( instruction, counter );
			history.push_back( &instruction );
		} else {
			for( auto it{ history.rbegin() }; it != history.rend(); it = history.rbegin() ) {
				Instruction &lastInstruction{ **it };

				currentID += reverseCall( lastInstruction, counter );

				// std::cout << "\tRepair " << currentID << ":" << counter << '\t' << "(" << fixedOnIndex << ")" << std::endl;

				if( fixedOnIndex == -1 && lastInstruction.operation != Instruction::OperationType::ACC ) {
					swap( lastInstruction );
					fixedOnIndex = currentID;
				} else if( currentID == fixedOnIndex ) {
					swap( lastInstruction );
					fixedOnIndex = -1;
				}

				history.pop_back();

				if( fixedOnIndex == currentID )
					break;
			}
		}
	}

	return counter;
}

void aoc::day8::resetInstructions( Instructions &instructions ) {
	std::for_each( std::begin( instructions ), std::end( instructions ), []( Instruction &instruction ){ instruction.timesCalled = 0; } );
}

long aoc::day8::onCall( Instruction &instruction, long &counter ) {
	instruction.timesCalled++;

	if( instruction.operation == Instruction::OperationType::ACC )
		counter += instruction.value;
	else if( instruction.operation == Instruction::OperationType::JMP )
		return instruction.value;

	return 1;
}

long aoc::day8::reverseCall( Instruction &instruction, long &counter ) {
	instruction.timesCalled--;

	if( instruction.operation == Instruction::OperationType::ACC )
		counter -= instruction.value;
	else if( instruction.operation == Instruction::OperationType::JMP )
		return -instruction.value;

	return -1;
}
