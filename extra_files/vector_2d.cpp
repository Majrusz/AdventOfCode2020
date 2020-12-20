// Created by Majrusz on 20/12/2020. All rights reserved.

#include "vector_2d.h"

using namespace aoc;

const Vector2D &Vector2D::zero{ 0.0, 0.0 };

Vector2D::Vector2D( double x, double y ) : Vector< 2 >{ x, y } {}

Vector2D::Vector2D( const Vector2D &vector2D ) : Vector< 2 >{ vector2D.x, vector2D.y } {}

Vector2D &Vector2D::rotate( Angle angle, const Vector2D &origin ) {
	double xCopy{ this->x }, yCopy{ this->y };

	this->x = xCopy * std::cos( angle ) - yCopy * std::sin( angle );
	this->y = xCopy * std::sin( angle ) + yCopy * std::cos( angle );

	return *this;
}

