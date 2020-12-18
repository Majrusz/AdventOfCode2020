// Created by Majrusz on 18/12/2020. All rights reserved.

#include "day17.h"

void aoc::day17::start() {
	Grid3D grid3d{ Grid3D::loadGridFromFile( "input.txt" ) };

	for( size_t i{}; i < 6; i++ )
		grid3d.play();

	std::cout << "3D: " << grid3d.countElements() << std::endl;

	Grid4D grid4d{ Grid4D::loadGridFromFile( "input.txt" ) };

	for( size_t i{}; i < 6; i++ )
		grid4d.play();

	std::cout << "4D: " << grid4d.countElements() << std::endl;
}

aoc::day17::Grid3D::Grid3D( const aoc::day17::Grid3D &copy ) {
	size_t amountOfElements{ power( copy.currentSize, 3 ) };

	this->currentSize = copy.currentSize;
	this->points = new int8_t[ amountOfElements ];

	for( size_t i{}; i < amountOfElements; i++ )
		this->points[ i ] = copy.points[ i ];
}

void aoc::day17::Grid3D::setElement( aoc::day17::Grid3D::Point3D point, int8_t value ) {
	this->points[ point.x + point.y * this->currentSize + point.z * power( this->currentSize, 2 ) ] = value;
}

int8_t aoc::day17::Grid3D::getElement( aoc::day17::Grid3D::Point3D point ) const {
	return this->points[ point.x + point.y * this->currentSize + point.z * power( this->currentSize, 2 ) ];
}

void aoc::day17::Grid3D::increaseSize() {
	Grid3D copy{ *this };

	generateEmptyGrid( this->currentSize + 2 );

	for( size_t z{}; z < copy.currentSize; z++ )
		for( size_t y{}; y < copy.currentSize; y++ )
			for( size_t x{}; x < copy.currentSize; x++ )
				this->setElement( { x + 1, y + 1, z + 1 }, copy.getElement( { x, y, z } ) );
}

aoc::day17::Grid3D aoc::day17::Grid3D::countNeighbours() const {
	Grid3D neighbours{};
	neighbours.generateEmptyGrid( this->currentSize );

	for( size_t z{}; z < this->currentSize; z++ )
		for( size_t y{}; y < this->currentSize; y++ )
			for( size_t x{}; x < this->currentSize; x++ )
				for( long zz{ -1 }; zz <= 1; zz++ )
					for( long yy{ -1 }; yy <= 1; yy++ )
						for( long xx{ -1 }; xx <= 1; xx++ ) {
							if( xx == 0 && yy == 0 && zz == 0 )
								continue;

							Point3D neighbour{ x + xx, y + yy, z + zz };
							auto isInRange{ [ & ]( size_t position ) -> bool {
								return ( 0 <= position & position < this->currentSize );
							} };

							if( isInRange( neighbour.x ) && isInRange( neighbour.y ) && isInRange( neighbour.z ) && getElement( neighbour ) != 0 )
								neighbours.setElement( { x, y, z }, neighbours.getElement( { x, y, z } )+1 );
						}

	return neighbours;
}

void aoc::day17::Grid3D::play() {
	increaseSize();
	Grid3D neighbours{ countNeighbours() };
	Grid3D copy{ *this };
	generateEmptyGrid( this->currentSize );

	for( size_t z{}; z < this->currentSize; z++ )
		for( size_t y{}; y < this->currentSize; y++ )
			for( size_t x{}; x < this->currentSize; x++ ) {
				long neighboursCount{ neighbours.getElement( { x, y, z } ) };
				bool elementIsActive{ copy.getElement( { x, y, z } ) != 0 };
				if( elementIsActive )
					setElement( { x, y, z }, ( neighboursCount == 2 || neighboursCount == 3 ) ? 1 : 0 );
				else
					setElement( { x, y, z }, ( neighboursCount == 3 ) ? 1 : 0 );
			}
}

std::ostream &aoc::day17::operator<<( std::ostream &stream, const aoc::day17::Grid3D &grid ) {
	for( size_t z{}; z < grid.currentSize; z++ ) {
		std::cout << "Z: " << z << std::endl;
		for( size_t y{}; y < grid.currentSize; y++ ) {
			for( size_t x{}; x < grid.currentSize; x++ )
				std::cout << ( grid.getElement( { x, y, z } ) == 0 ? '.' : '#' ) << '\t';

			std::cout << std::endl;
		}
		std::cout << std::endl;
	}

	return stream;
}

aoc::day17::Grid3D aoc::day17::Grid3D::loadGridFromFile( const std::string &filename ) {
	std::ifstream file{ "../days/day17/" + filename };
	Grid3D grid{};
	std::string input{};

	if( !file ) {
		std::cout << "Error when loading \"" << filename << "\" file!" << std::endl;
		return grid;
	}

	size_t y{};
	while( file >> input ) {
		if( grid.currentSize == 1 )
			grid.generateEmptyGrid( input.size() );

		for( size_t x{}; x < grid.currentSize; x++ )
			grid.setElement( { x, y, grid.currentSize/2 }, input[ x ] == '#' ? 1 : 0 );

		y++;
	}

	return grid;
}

aoc::day17::Grid4D::Grid4D( const aoc::day17::Grid4D &copy ) {
	size_t amountOfElements{ power( copy.currentSize, 4 ) };

	this->currentSize = copy.currentSize;
	this->points = new int8_t[ amountOfElements ];

	for( size_t i{}; i < amountOfElements; i++ )
		this->points[ i ] = copy.points[ i ];
}

aoc::day17::Grid4D aoc::day17::Grid4D::loadGridFromFile( const std::string &filename ) {
	std::ifstream file{ "../days/day17/" + filename };
	Grid4D grid{};
	std::string input{};

	if( !file ) {
		std::cout << "Error when loading \"" << filename << "\" file!" << std::endl;
		return grid;
	}

	size_t y{};
	while( file >> input ) {
		if( grid.currentSize == 1 )
			grid.generateEmptyGrid( input.size() );

		for( size_t x{}; x < grid.currentSize; x++ )
			grid.setElement( { x, y, grid.currentSize/2, grid.currentSize/2 }, input[ x ] == '#' ? 1 : 0 );

		y++;
	}

	return grid;
}

size_t aoc::day17::Grid4D::getIndex( const Point4D &point ) const {
	return point.x + point.y * this->currentSize + point.z * power( this->currentSize, 2 ) + point.w * power( this->currentSize, 3 );
}

void aoc::day17::Grid4D::setElement( aoc::day17::Grid4D::Point4D point, int8_t value ) {
	this->points[ getIndex( point ) ] = value;
}

int8_t aoc::day17::Grid4D::getElement( aoc::day17::Grid4D::Point4D point ) const {
	return this->points[ getIndex( point ) ];
}

void aoc::day17::Grid4D::increaseSize() {
	Grid4D copy{ *this };

	generateEmptyGrid( this->currentSize + 2 );

	for( size_t w{}; w < copy.currentSize; w++ )
		for( size_t z{}; z < copy.currentSize; z++ )
			for( size_t y{}; y < copy.currentSize; y++ )
				for( size_t x{}; x < copy.currentSize; x++ )
					this->setElement( { x + 1, y + 1, z + 1, w + 1 }, copy.getElement( { x, y, z, w } ) );
}

aoc::day17::Grid4D aoc::day17::Grid4D::countNeighbours() const {
	Grid4D neighbours{};
	neighbours.generateEmptyGrid( this->currentSize );

	for( size_t w{}; w < this->currentSize; w++ )
		for( size_t z{}; z < this->currentSize; z++ )
			for( size_t y{}; y < this->currentSize; y++ )
				for( size_t x{}; x < this->currentSize; x++ )
					for( long ww{ -1 }; ww <= 1; ww++ )
						for( long zz{ -1 }; zz <= 1; zz++ )
							for( long yy{ -1 }; yy <= 1; yy++ )
								for( long xx{ -1 }; xx <= 1; xx++ ) {
									if( xx == 0 && yy == 0 && zz == 0 && ww == 0 )
										continue;

									Point4D neighbour{ x + xx, y + yy, z + zz, w + ww };
									auto isInRange{ [ & ]( size_t position ) -> bool {
										return ( 0 <= position & position < this->currentSize );
									} };

									if( isInRange( neighbour.x ) && isInRange( neighbour.y ) && isInRange( neighbour.z ) && isInRange( neighbour.w ) && getElement( neighbour ) != 0 )
										neighbours.setElement( { x, y, z, w }, neighbours.getElement( { x, y, z, w } )+1 );
								}

	return neighbours;
}

void aoc::day17::Grid4D::play() {
	increaseSize();
	Grid4D neighbours{ countNeighbours() };
	Grid4D copy{ *this };
	generateEmptyGrid( this->currentSize );

	for( size_t w{}; w < this->currentSize; w++ )
		for( size_t z{}; z < this->currentSize; z++ )
			for( size_t y{}; y < this->currentSize; y++ )
				for( size_t x{}; x < this->currentSize; x++ ) {
					long neighboursCount{ neighbours.getElement( { x, y, z, w } ) };
					bool elementIsActive{ copy.getElement( { x, y, z, w } ) != 0 };
					if( elementIsActive )
						setElement( { x, y, z, w }, ( neighboursCount == 2 || neighboursCount == 3 ) ? 1 : 0 );
					else
						setElement( { x, y, z, w }, ( neighboursCount == 3 ) ? 1 : 0 );
				}
}