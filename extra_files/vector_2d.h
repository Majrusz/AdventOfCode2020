// Created by Majrusz on 20/12/2020. All rights reserved.

#pragma once

#include "vector.h"

namespace aoc {
	struct Vector2D : public Vector< 2 > {
		Vector2D( double x, double y );

		template< typename Type >
		Vector2D( Type x, Type y ) : Vector2D{ static_cast< double >( x ), static_cast< double >( y ) } {}

		Vector2D( const Vector2D &vector2D );

		Vector2D &rotate( Angle angle, const Vector2D &origin = Vector2D{ 1.0, 0.0 } );

		friend std::ostream &operator<<( std::ostream &stream, const aoc::Vector2D &vector ) {
			return operator<<( stream, dynamic_cast< const aoc::Vector< 2 >& >( vector ) );
		}

		double &x{ this->coordinates[ 0 ] }, &y{ this->coordinates[ 1 ] };
		static const Vector2D &zero;
	};
}
