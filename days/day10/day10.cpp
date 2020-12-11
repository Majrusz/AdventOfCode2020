// Created by Majrusz on 11/12/2020. All rights reserved.

#include "day10.h"

using namespace aoc::day10;

void aoc::day10::start() {
	Adapters adapters{ loadFile< size_t >( "days/day10/input.txt" ) };

	std::sort( std::begin( adapters ), std::end( adapters ) );
	size_t maximum{ adapters.back() };

	std::cout << maximum << std::endl;

	Counters output{ findChain( adapters ) };
	std::cout << "Jolt1 * Jolt3: " << output.jolt1 * output.jolt3 << std::endl;

	std::cout << findPermutationAmount( adapters ) << std::endl;
}

Counters aoc::day10::findChain( const Adapters &adapters ) {
	Counters counters{ 1, 1 };
	size_t size{ adapters.size() };

	for( size_t i = 0; i < size; i++ ) {
		size_t current{ adapters[ i ] };
		size_t next{ adapters[ i + 1 ] };

		if( size_t difference{ next - current }; difference <= 3 )
			( difference == 1 ? counters.jolt1 : counters.jolt3 ) += 1;
	}

	return counters;
}

size_t aoc::day10::findPermutationAmount( const Adapters &adapters ) {
	size_t counter{ 1 };

	Adapters trueAdapters{ adapters };
	trueAdapters.emplace( trueAdapters.begin(), 0 );
	trueAdapters.emplace( trueAdapters.end(), adapters.back()+3 );

	std::vector< size_t > forbiddenIndexes{};

	std::function< void( size_t, const std::vector< size_t >& ) > call;
	call = [&]( size_t index, const std::vector< size_t > &forbiddenIndexes ){
		size_t size{ trueAdapters.size() };
		if( index < size )
			call( index + 1, forbiddenIndexes );

		if( !( 1 <= index && index < size-1 ) )
			return;

		size_t previous{ index-1 }, next{ index+1 };

		while( std::find( std::begin( forbiddenIndexes ), std::end( forbiddenIndexes ), previous ) != forbiddenIndexes.end() )
			previous--;

		while( std::find( std::begin( forbiddenIndexes ), std::end( forbiddenIndexes ), next ) != forbiddenIndexes.end() )
			next++;

		// std::cout << " " << previous << ":" << next << std::endl;
		if( trueAdapters[ next ] - trueAdapters[ previous ] <= 3 ) {
			std::vector< size_t > copyOfIndexes{ forbiddenIndexes };
			copyOfIndexes.push_back( index );
			counter++;

			call( index + 1, copyOfIndexes );
		}
	};

	call( {}, {} );

	return counter;
}
