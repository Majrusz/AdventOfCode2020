// Created by Majrusz on 15/12/2020. All rights reserved.

#include "day15.h"

void aoc::day15::start() {
	std::vector< size_t > input{ 0,6,1,7,2,19,20 };

	part1( input );
	part2( input );
}

void aoc::day15::part1( std::vector< size_t > numbers ) {
	constexpr size_t maxSize{ 2020 };
	numbers.reserve( maxSize );

	while( numbers.size() < maxSize )
		if( std::count( std::begin( numbers ), std::end( numbers ), numbers.back() ) == 1 )
			numbers.push_back( 0 );
		else {
			auto lastOccurrence{ std::find_if( std::rbegin( numbers )+1, std::rend( numbers ), [&]( auto i ){ return i == numbers.back(); } ) };
			numbers.push_back( std::distance( std::rbegin( numbers ), lastOccurrence ) );
		}

	std::cout << numbers.back() << std::endl;
}

void aoc::day15::part2( std::vector< size_t > numbers ) {
	constexpr size_t maxSize{ 30000000 };
	numbers.reserve( maxSize );

	std::map< size_t, size_t > indexes{};
	auto updateMap = [&]( size_t value, size_t index ){
		indexes[ value ] = index;
	};
	auto updateMapLast = [&]( size_t value ){
		updateMap( value, numbers.size()-1 );
	};

	for( size_t i{}; i < numbers.size(); i++ )
		updateMap( numbers[ i ], i );

	while( numbers.size() < maxSize ) {
		size_t value{ numbers.back() };
		size_t newValue{ indexes.find( value ) == std::end( indexes ) ? 0 : ( numbers.size() - 1 - indexes[ value ] ) };

		updateMapLast( value );
		numbers.push_back( newValue );
	}

	std::cout << numbers.back() << std::endl;
}
