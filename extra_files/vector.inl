// Created by Majrusz on 20/12/2020. All rights reserved.

#include "vector.h"

template< size_t N >
double aoc::Vector< N >::calculateDistance( const Vector< N > &origin ) const {
	double distance{};

	for( size_t index{}; index < N; index++ )
		distance += std::pow( this->coordinates[ index ] - origin.coordinates[ index ], 2 );

	return std::sqrt( distance );
}

template< size_t N >
double aoc::Vector< N >::dotProduct( const Vector< N > &vector ) const {
	double product{};

	for( size_t index{}; index < N; index++ )
		product += this->coordinates[ index ] * vector.coordinates[ index ];

	return product;
}

template< size_t N >
aoc::Angle aoc::Vector< N >::calculateAngle( const Vector< N > &vector ) const {
	Radians radians{ std::acos( dotProduct( vector ) / ( calculateDistance() * vector.calculateDistance() ) ) };

	if( this->coordinates[ N-1 ] < 0.0 )
		radians = Radians{ 2 * Angle::pi - radians };

	return radians;
}
