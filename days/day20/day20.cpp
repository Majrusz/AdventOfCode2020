// Created by Majrusz on 20/12/2020. All rights reserved.

#include "day20.h"

int64_t aoc::day20::Tile::edgeIDCounter{};
std::map< std::string, size_t > aoc::day20::Tile::edgeIDs;

void aoc::day20::start() {
	Tiles tiles{ loadFile< Tile >( "days/day20/test.txt" ) };

	std::cout << "Size: " << tiles.size() << std::endl;
	std::cout << "Part1: " << multiplyCorners( tiles ) << std::endl;
	//for( auto &connection : findConnections( tiles ) )
		//std::cout << connection.first << ":\t" << connection.second << std::endl;
}

aoc::day20::Tile &aoc::day20::Tile::rotate() {
	Tile copy{ *this };
	int size{ static_cast< int >( this->lines.size() ) };

	for( int y{}; y < size; y++ )
		for( int x{}; x < size; x++ )
			this->lines[ size - ( x+1 ) ][ y ] = copy.lines[ y ][ x ];

	calculateEdges();

	return *this;
}

aoc::day20::Tile &aoc::day20::Tile::flip() {
	Tile copy{ *this };
	int size{ static_cast< int >( this->lines.size() ) };

	for( int y{}; y < size; y++ )
		for( int x{}; x < size; x++ )
			this->lines[ x ][ y ] = copy.lines[ y ][ x ];

	calculateEdges();

	return *this;
}

aoc::day20::Tile &aoc::day20::Tile::calculateEdges() {
	int size{ static_cast< int >( this->lines.size() ) };

	auto addEdge{ [&]( const std::string &edge ){
		if( edgeIDs.find( edge ) == edgeIDs.end() )
			edgeIDs[ edge ] = ++edgeIDCounter;
	} };

	std::string edge{};

	// top
	edge = this->lines.front();
	addEdge( edge );
	this->edges[ 0 ] = edgeIDs[ edge ];

	// right
	edge.clear();
	for( int y{}; y < size; y++ )
		edge.push_back( this->lines[ y ].back() );
	addEdge( edge );
	this->edges[ 1 ] = edgeIDs[ edge ];

	// bottom
	edge = this->lines.back();
	addEdge( edge );
	this->edges[ 2 ] = edgeIDs[ edge ];

	// left
	edge.clear();
	for( int y{}; y < size; y++ )
		edge.push_back( this->lines[ y ].front() );
	addEdge( edge );
	this->edges[ 3 ] = edgeIDs[ edge ];

	return *this;
}

std::map< size_t, size_t > aoc::day20::findConnections( aoc::day20::Tiles &tiles ) {
	std::map< size_t, size_t > connections{};
	for( auto &tile : tiles ) {
		connections[ tile.id ] = 0;
		tile.calculateEdges();
	}

 	for( size_t j{}; j < tiles.size(); j++ )
 		for( size_t i{ j+1 }; i < tiles.size(); i++ ) {
 			Tile copy{ tiles[ i ] };

 			for( size_t k{}; k < 2; k++ ) {
				for( size_t l{}; l < 4; l++ ) {
					bool bottomConnection{ copy.edges[ 0 ] == tiles[ j ].edges[ 2 ] };
					bool topConnection{ copy.edges[ 2 ] == tiles[ j ].edges[ 0 ] };
					bool rightConnection{ copy.edges[ 3 ] == tiles[ j ].edges[ 1 ] };
					bool leftConnection{ copy.edges[ 1 ] == tiles[ j ].edges[ 3 ] };

					if( bottomConnection || topConnection || rightConnection || leftConnection ) {
						// std::cout << tiles[ j ].id << " --- " << copy.id << " (rot: " << l << ") (flip: " << k << ")" << std::endl;
						connections[ tiles[ j ].id ]++;
						connections[ copy.id ]++;
						break;
					}

					copy.rotate();
				}
				copy.flip();
 			}
 		}

 	return connections;
}

std::ostream &aoc::day20::operator<<( std::ostream &stream, const aoc::day20::Tile &tile ) {
	std::cout << "Tile " << tile.id << ":" << std::endl;
	for( auto &line : tile.lines )
		std::cout << line << std::endl;

	return stream;
}

std::istream &aoc::day20::operator>>( std::istream &input, aoc::day20::Tile &tile ) {
	std::string text{};
	std::getline( input, text );

	tile.id = std::stoll( text.substr( text.find( "Tile" )+5, text.find( ':' ) ) );

	std::getline( input, text );
	do {
		tile.lines.push_back( text );
		std::getline( input, text );
	} while( !text.empty() );

	return input;
}

int64_t aoc::day20::multiplyCorners( aoc::day20::Tiles &tiles ) {
	int64_t product{ 1 };

	for( auto &connection : findConnections( tiles ) )
		if( connection.second == 2 )
			product *= connection.first;

	return product;
}
