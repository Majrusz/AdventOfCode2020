// Created by Majrusz on 05/12/2020. All rights reserved.

#include "day5.h"

void aoc::day5::start() {
	 Records records{ aoc::loadFile< std::string >( "days/day5/input.txt" ) };

	 std::cout << "Max seat ID: " << *getMaxElement( records ) << std::endl;
	 std::cout << "Missing ID: " << findMissingID( records ) << std::endl;
}

size_t aoc::day5::calculatePosition( const std::string &record, char lowerHalf, char upperHalf, size_t startIndex, size_t nElements ) {
	size_t position{};
	for( size_t i = startIndex; i < startIndex+nElements; i++ )
		position += record[ i ] == upperHalf ? 1u << ( startIndex+nElements-( i+1 ) ) : 0;

	return position;
}

size_t aoc::day5::getRow( const std::string &record ) {
	return calculatePosition( record, 'F', 'B', 0, 7 );
}

size_t aoc::day5::getColumn( const std::string &record ) {
	return calculatePosition( record, 'L', 'R', 7, 3 );
}

size_t aoc::day5::getSeatID( const std::string &record ) {
	return getRow( record ) * 8 + getColumn( record );
}

std::vector< size_t > aoc::day5::generateIDs( const aoc::day5::Records &records ) {
	std::vector< size_t > seatIDs{};

	std::for_each( std::begin( records ), std::end( records ), [&]( const std::string &record ){ seatIDs.emplace_back( getSeatID( record ) ); } );

	return seatIDs;
}

std::vector< size_t >::iterator aoc::day5::getMaxElement( const aoc::day5::Records &records ) {
	auto seatIDs{ generateIDs( records ) };

	return std::max_element( std::begin( seatIDs ), std::end( seatIDs ) );
}

size_t aoc::day5::findMissingID( const aoc::day5::Records &records ) {
	auto seatIDs{ generateIDs( records ) };

	std::sort( std::begin( seatIDs ), std::end( seatIDs ) );

	for( size_t id{}; true; id++ )
		if( seatIDs[ 1 ]+id != seatIDs[ id+1 ] )
			return seatIDs[ 1 ]+id;
}



