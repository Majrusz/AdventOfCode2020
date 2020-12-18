// Created by Majrusz on 18/12/2020. All rights reserved.

#include "day17.h"

template< size_t amountOfDimensions >
aoc::day17::Grids< amountOfDimensions >::Grids() {
	generateEmptyGrid( 1 );
}

template< size_t amountOfDimensions >
aoc::day17::Grids< amountOfDimensions >::~Grids() {
	delete[] this->points;
}

template< size_t amountOfDimensions >
void aoc::day17::Grids< amountOfDimensions >::generateEmptyGrid( size_t size ) {
	if( this->points )
		delete[] this->points;

	size_t amountOfElements{ power( size, amountOfDimensions ) };

	this->currentSize = size;
	this->points = new int8_t[amountOfElements];
	std::fill_n( this->points, amountOfElements, 0 );
}

template< size_t amountOfDimensions >
size_t aoc::day17::Grids< amountOfDimensions >::countElements() const {
	return std::count_if( this->points, this->points + power( this->currentSize, amountOfDimensions ), []( auto x ) -> bool {
		return ( x != 0 );
	} );
}
