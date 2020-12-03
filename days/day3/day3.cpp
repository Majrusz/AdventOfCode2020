// Created by Majrusz on 03/12/2020. All rights reserved.

#include "day3.h"

void aoc::day3::start() {
	std::vector< std::string > lines{ loadFile< std::string >( "days/day3/input.txt" ) };

	size_t treesCounters[ 5 ] {
		countTrees( lines, 1, 1 ),
		countTrees( lines, 3, 1 ),
		countTrees( lines, 5, 1 ),
		countTrees( lines, 7, 1 ),
		countTrees( lines, 1, 2 )
	};

	for( auto &counter : treesCounters )
		std::cout << counter << std::endl;

	std::cout << "Product: " << std::accumulate( std::begin( treesCounters ), std::end( treesCounters ), static_cast< size_t >( 1 ), std::multiplies() ) << std::endl;
}

size_t aoc::day3::countTrees( std::vector< std::string > &lines, int horizontalShift, int verticalShift ) {
	size_t currentIndex{}, treesCounter{};
	for( auto it{ lines.begin() }; it != lines.end(); it += verticalShift ) {
		auto &line = *it;

		if( line.empty() )
			break;

		if( line[ currentIndex ] == tree )
			treesCounter++;

		currentIndex = ( currentIndex+horizontalShift )%line.size();
	}

	return treesCounter;
}
