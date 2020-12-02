// Created by Majrusz on 02/12/2020. All rights reserved.

#include "day2.h"

void aoc::day2::start() {
	Records records{ aoc::loadFile< Record >( "days/day2/input.txt" ) };

	std::cout << countValidPasswords(records) << std::endl;
	std::cout << countValidPasswords2(records) << std::endl;
}

size_t aoc::day2::countValidPasswords( aoc::day2::Records &records ) {
	size_t counter{};

	for( auto &record : records ) {
		auto letterOccurrenceCount{ std::count( std::begin( record.password ), std::end( record.password ), record.letter ) };

		if( record.min <= letterOccurrenceCount && letterOccurrenceCount <= record.max )
			counter++;
	}

	return counter;
}

size_t aoc::day2::countValidPasswords2( aoc::day2::Records &records ) {
	size_t counter{};

	for( auto &record : records ) {
		unsigned letterOccurrenceCount{ 0 };
		letterOccurrenceCount += static_cast< unsigned >( record.password[ record.min-1 ] == record.letter );
		letterOccurrenceCount += static_cast< unsigned >( record.password[ record.max-1 ] == record.letter );

		if( letterOccurrenceCount == 1 )
			counter++;
	}

	return counter;
}

std::istream &aoc::day2::operator>>( std::istream &input, aoc::day2::Record &record ) {
	std::string temporary;

	input >> temporary;
	if( temporary.empty() )
		return input;
	size_t index{ temporary.find( '-' ) };
	record.min = std::stoi( temporary.substr( 0, index ) );
	record.max = std::stoi( temporary.substr( index+1 ) );

	input >> temporary;
	record.letter = temporary[ 0 ];

	input >> record.password;

	return input;
}
