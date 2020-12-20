// Created by Majrusz on 20/12/2020. All rights reserved.

#pragma once

#include <cstdint>
#include <cmath>
#include <iostream>

#include "angle.h"

namespace aoc {
	template< size_t N >
	struct Vector {
		double calculateDistance( const Vector< N > &origin = Vector< N >{} ) const;

		double dotProduct( const Vector< N > &vector ) const;

		Angle calculateAngle( const Vector< N > &vector = Vector< N >{ 1.0 } ) const;

		double coordinates[ N ]{};
	};
}

template< size_t N >
std::ostream &operator<<( std::ostream &stream, const aoc::Vector< N > &vector ) {
	stream << '(';
	for( size_t index{}; index < N; index++ ) {
		stream << vector.coordinates[ index ];
		if( index < N-1 )
			stream << ',';
	}
	stream << ')';

	return stream;
}

#include "vector.inl"