// Created by Majrusz on 07/12/2020. All rights reserved.

#include "day7.h"

void aoc::day7::start() {
	Bags bags{ loadFile< Bag >( "days/day7/input.txt" ) };

	std::cout << findColor( "shiny gold", bags ) << std::endl;
	std::cout << calculateBagCapacity( "shiny gold", bags ) << std::endl;
}

aoc::day7::BagsMap aoc::day7::toMap( const Bags &bags ) {
	BagsMap map{};

	for( const Bag &bag : bags )
		map[ bag.color ] = bag;

	return map;
}

aoc::day7::CountersMap aoc::day7::generateCountersMap( const Bags &bags ) {
	CountersMap countersMap{};

	for( auto &bag : bags )
		countersMap[ bag.color ] = -1LL;

	return countersMap;
}

size_t aoc::day7::findColor( const std::string &color, const Bags &bags ) {
	BagsMap bagsMap{ toMap( bags ) };
	CountersMap countersMap{ generateCountersMap( bags ) };

	std::function< void( const std::string & ) > count;
	count = [&]( const std::string &currentColor ) {
		if( countersMap[ currentColor ] != -1 )
			return;

		if( bagsMap[ currentColor ].content.empty() ) {
			countersMap[ currentColor ] = 0;
			return;
		}

		bool found{};

		for( auto &child : bagsMap[ currentColor ].content ) {
			if( countersMap[ child.first ] == -1 )
				count( child.first );

			if( countersMap[ child.first ] > 0 ) {
				found = true;
			}

			if( child.first == color )
				found = true;
		}

		countersMap[ currentColor ] = found ? 1 : 0;
	};

	for( auto &bag : bags )
		count( bag.color );

	return std::accumulate( std::begin( countersMap ), std::end( countersMap ), 0, []( auto &sum, auto &b ) { return sum + b.second; } );
}

std::istream &aoc::day7::operator>>( std::istream &input, Bag &bag ) {
	std::string line{};

	auto isNumber{ []( const std::string &text ) -> bool {
		return !text.empty() && std::all_of( std::begin( text ), std::end( text ), ::isdigit );
	} };
	auto getColor{ []( std::stringstream &stream ) -> std::string {
		std::string color{}, text{};
		stream >> text;
		color += text + " ";
		stream >> text;
		color += text;
		return color;
	} };

	std::getline( input, line );

	if( line.empty() )
		return input;

	std::stringstream stream{ line };
	std::string text{};

	bag.color = getColor( stream );

	while( !stream.eof() ) {
		stream >> text;

		if( isNumber( text ) )
			bag.content.emplace_back( std::pair< std::string, size_t >{ getColor( stream ), static_cast< size_t >( std::stoll( text ) ) } );
	}

	return input;
}

size_t aoc::day7::calculateBagCapacity( const std::string &color, const aoc::day7::Bags &bags ) {
	BagsMap bagsMap{ toMap( bags ) };
	CountersMap countersMap{ generateCountersMap( bags ) };

	std::function< size_t( const std::string & ) > count;
	count = [&]( const std::string &currentColor ) -> size_t {
		size_t sum{};

		for( auto &child : bagsMap[ currentColor ].content ) {
			if( countersMap[ child.first ] == -1 )
				count( child.first );

			sum += ( countersMap[ child.first ]+1 ) * child.second;
		}

		return ( countersMap[ currentColor ] = sum );
	};

	return count( color );
}

