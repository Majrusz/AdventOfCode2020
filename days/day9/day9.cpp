// Created by Majrusz on 09/12/2020. All rights reserved.

#include "day9.h"

void aoc::day9::start() {
	Elements elements{ loadFile< size_t >( "days/day9/input.txt" ) };

	std::cout << "Broken element: " << findBrokenElement( elements ) << std::endl;
	std::cout << "Encryption weakness: " << findEncryptionWeakness( elements ) << std::endl;
}

bool aoc::day9::isAnyTwoPreviousElementsSummableTo( const Elements &elements, size_t index ) {
	for( size_t i{ index-1 }; ( index - i ) <= ( groupSize+1 ); i-- )
		for( size_t j{ i-1 }; ( index - j ) <= ( groupSize+1 ); j-- )
			if( elements[ i ] + elements[ j ] == elements[ index ] )
				return true;

	return false;
}

size_t aoc::day9::findBrokenElement( const Elements &elements ) {
	for( size_t i{ groupSize }; i < elements.size(); i++ )
		if( !isAnyTwoPreviousElementsSummableTo( elements, i ) )
			return elements[ i ];

	throw std::logic_error( "There is no broken element!" );
}

size_t aoc::day9::findEncryptionWeakness( const aoc::day9::Elements &elements ) {
	size_t brokenNumber{ findBrokenElement( elements ) };
	Elements contiguousSetOfNumbers{};

	for( size_t i{ 0 }; i < elements.size(); i++ ) {
		contiguousSetOfNumbers.clear();
		for( size_t j{ i }; j < elements.size(); j++ ) {
			contiguousSetOfNumbers.push_back( elements[ j ] );

			size_t sum{ std::accumulate( std::begin( contiguousSetOfNumbers ), std::end( contiguousSetOfNumbers ), size_t( 0 ) ) };
			if( sum > brokenNumber )
				break;
			else if( contiguousSetOfNumbers.size() > 1 && sum == brokenNumber ) {
				size_t minimum{ *std::min_element( std::begin( contiguousSetOfNumbers ), std::end( contiguousSetOfNumbers ) ) };
				size_t maximum{ *std::max_element( std::begin( contiguousSetOfNumbers ), std::end( contiguousSetOfNumbers ) ) };

				return minimum + maximum;
			}
		}
	}

	throw std::logic_error( "There is no encryption weakness!" );
}


