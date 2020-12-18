// Created by Majrusz on 16/12/2020. All rights reserved.

#include "day16.h"

void aoc::day16::start() {
	InputType input{ loadFile( "input.txt" ) };
	size_t counter{};

	for( auto &tickets : input.nearby )
		for( auto &ticket : tickets.ids )
			if( !isInRanges( ticket, input.ranges ) )
				counter += ticket;

	for( auto &ticket : input.your.ids )
		if( !isInRanges( ticket, input.ranges ) )
			counter += ticket;

	std::cout << "Counter: " << counter << std::endl;

	removeAllInvalidTickets( input );

	size_t counter2{};

	for( auto &tickets : input.nearby )
		for( auto &ticket : tickets.ids )
			if( !isInRanges( ticket, input.ranges ) )
				counter2 += ticket;

	for( auto &ticket : input.your.ids )
		if( !isInRanges( ticket, input.ranges ) )
			counter2 += ticket;

	std::cout << "Counter: " << counter2 << std::endl;

	auto permutation{ findPermutation( input ) };
	for( auto &el : permutation )
		std::cout << el << ", ";
	std::cout << std::endl;

	for( auto &el : input.your.ids )
		std::cout << el << ", ";
	std::cout << std::endl;

	size_t output{ 1 };
	for( size_t i{}; i < input.your.ids.size(); i++ ) {
		// std::cout << i << ". " << input.ranges[ permutation[ i ] ].name << std::endl;

		if( permutation[ i ] < 6 ) {
			output *= input.your.ids[ i ];
			std::cout << i << " (" << input.your.ids[ i ] << "), ";
		}
	}
	std::cout << output << std::endl;
}

aoc::day16::InputType aoc::day16::loadFile( const std::string &filename ) {
	std::ifstream file{ "../days/day16/" + filename };
	InputType input{};

	if( !file ) {
		std::cout << "Error when loading \"" << filename << "\" file!" << std::endl;
		return input;
	}

	std::string text{ ' ' };
	enum class LoadType {
		Ranges, YourTickets, NearbyTickets
	} current{ LoadType::Ranges };
	while( true ) {
		std::getline( file, text );

		if( text.empty() ) {
			current = ( current == LoadType::Ranges ) ? LoadType::YourTickets : LoadType::NearbyTickets;
			continue;
		}
		switch( current ) {
			case LoadType::Ranges: {
				Ranges ranges{ text.substr( 0, text.find( ':' ) ) };

				std::stringstream stream{ text.substr( text.find( ':' ) + 2 ) };
				for( size_t i{}; i < 2; i++ ) {
					stream >> text;
					size_t index{ text.find( '-' ) };

					ranges.data[ i ].min = std::stoull( text.substr( 0, index ) );
					ranges.data[ i ].max = std::stoull( text.substr( index + 1 ) );

					stream >> text;
				}
				input.ranges.push_back( ranges );
			}
				break;

			case LoadType::YourTickets: {
				std::stringstream stream{ text };
				Tickets tickets{};
				size_t index{};
				while( ( index = text.find( ',' ) ) != std::string::npos ) {
					tickets.ids.push_back( std::stoull( text.substr( 0, index ) ) );
					text = text.substr( index + 1 );
					if( text.find( ',' ) == std::string::npos )
						tickets.ids.push_back( std::stoull( text ) );
				}
				if( !tickets.ids.empty() )
					input.your = tickets;
			}
				break;

			case LoadType::NearbyTickets: {
				std::stringstream stream{ text };
				Tickets tickets{};
				size_t index{};
				while( ( index = text.find( ',' ) ) != std::string::npos ) {
					tickets.ids.push_back( std::stoull( text.substr( 0, index ) ) );
					text = text.substr( index + 1 );
					if( text.find( ',' ) == std::string::npos )
						tickets.ids.push_back( std::stoull( text ) );
				}
				if( !tickets.ids.empty() )
					input.nearby.push_back( tickets );
			}
				break;
		}

		if( file.eof() )
			break;
	}

	file.close();

	return input;
}

bool aoc::day16::isInRanges( size_t ticket, const std::vector< Ranges > &ranges ) {
	for( auto &range : ranges )
		if( isInRange( ticket, range ) )
			return true;

	return false;
}

bool aoc::day16::isInRange( size_t ticket, const aoc::day16::Ranges &range ) {
	for( size_t i{}; i < 2; i++ )
		if( range.data[ i ].min <= ticket && ticket <= range.data[ i ].max )
			return true;

	return false;
}

void aoc::day16::removeAllInvalidTickets( aoc::day16::InputType &input ) {
	input.nearby.erase( std::remove_if( std::begin( input.nearby ), std::end( input.nearby ), [ & ]( Tickets &tickets ) {
		for( auto &ticket : tickets.ids )
			if( !isInRanges( ticket, input.ranges ) )
				return true;

		return false;
	} ), std::end( input.nearby ) );
}

std::vector< size_t > aoc::day16::findPermutation( aoc::day16::InputType &input ) {
	std::vector< std::vector< size_t > > possibleIndexes( input.your.ids.size(), std::vector< size_t >{} );

	for( size_t r{}; r < input.ranges.size(); r++ )
		for( size_t i{}; i < possibleIndexes.size(); i++ )
			if( isInRange( input.your.ids[ i ], input.ranges[ r ] ) )
				possibleIndexes[ i ].push_back( r );

	for( size_t r{}; r < input.ranges.size(); r++ )
		for( size_t i{}; i < possibleIndexes.size(); i++ )
			for( size_t t{}; t < input.nearby.size(); t++ )
				if( !isInRange( input.nearby[ t ].ids[ i ], input.ranges[ r ] ) )
					possibleIndexes[ i ].erase( std::find( std::begin( possibleIndexes[ i ] ), std::end( possibleIndexes[ i ] ), r ) );

	std::vector< size_t > permutation{};
	while( !possibleIndexes.empty() ) {
		size_t foundElement{};
		for( size_t i{}; i < possibleIndexes.size(); i++ ) {
			if( possibleIndexes[ i ].size() == 1 ) {
				foundElement = possibleIndexes[ i ].front();
				possibleIndexes.erase( std::begin( possibleIndexes ) + i );
				break;
			}
		}
		for( auto &indexes : possibleIndexes )
			indexes.erase( std::find( std::begin( indexes ), std::end( indexes ), foundElement ) );

		permutation.push_back( foundElement );
	}

	return permutation;
}
