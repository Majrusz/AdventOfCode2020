// Created by Majrusz on 18/12/2020. All rights reserved.

#pragma once

#include <cmath>
#include <algorithm>
#include <iostream>

#include "file_loader.h"

namespace aoc::day17{
	template< size_t amountOfDimensions >
	struct Grids {
		Grids();

		~Grids();

		void generateEmptyGrid( size_t size );

		size_t countElements() const;

		static size_t power( size_t base, size_t exponent ) {
			size_t amountOfElements{ 1 };
			for( size_t n{}; n < exponent; n++ )
				amountOfElements *= base;
			return amountOfElements;
		}

		int8_t *points{};
		size_t currentSize{ 1 };
	};

	struct Grid3D : Grids< 3 > {
		Grid3D() = default;

		Grid3D( const Grid3D &copy );

		struct Point3D {
			size_t x{}, y{}, z{};
		};

		void setElement( Point3D point, int8_t value );

		[[nodiscard]] int8_t getElement( Point3D point ) const;

		void increaseSize();

		Grid3D countNeighbours() const;

		void play();

		friend std::ostream &operator<<( std::ostream &stream, const Grid3D &grid );

		static Grid3D loadGridFromFile( const std::string &filename );
	};

	struct Grid4D : Grids< 4 > {
		struct Point4D {
			size_t x{}, y{}, z{}, w{};
		};

		static Grid4D loadGridFromFile( const std::string &filename );

		size_t getIndex( const Point4D &point ) const;

		Grid4D() = default;

		Grid4D( const Grid4D &copy );

		void setElement( Point4D point, int8_t value );

		[[nodiscard]] int8_t getElement( Point4D point ) const;

		void increaseSize();

		Grid4D countNeighbours() const;

		void play();
	};

	void start();
}

#include "day17.inl"