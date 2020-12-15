// Created by Majrusz on 14/12/2020. All rights reserved.

#include "day14.h"

void aoc::day14::start() {
	{
		Groups groups{ loadFile< Group >( "days/day14/input.txt" ) };

		std::map< size_t, Bits > bits{};
		for( auto &group : groups ) {
			group.applyMask();
			for( auto &element : group.bits )
				bits[ element.first ] = element.second;
		}

		std::cout << std::accumulate( std::begin( bits ), std::end( bits ), 0ULL, []( auto &a, auto &b ) { return a + b.second.to_ullong(); } )
			<< std::endl;
	}
	{
		Groups2 groups2 = loadFile< Group2 >( "days/day14/input.txt" );

		std::map< size_t, Bits > bits2{};
		for( auto &group2 : groups2 ) {
			group2.applyMask2();
			for( auto &element : group2.bits )
				bits2[ element.first ] = element.second;
		}

		std::cout << std::accumulate( std::begin( bits2 ), std::end( bits2 ), 0ULL, []( auto &a, auto &b ) { return a + b.second.to_ullong(); } )
			<< std::endl;
	}
}

void aoc::day14::Group::applyMask() {
	for( size_t i = 0; i < this->mask.size(); i++ )
		if( ::isdigit( this->mask[ i ] ) )
			for( auto &value : this->bits )
				value.second.set( this->mask.size() - ( i+1 ), this->mask[ i ] - '0' );
}

/*void aoc::day14::Group::applyMask2() {
	std::function< void( std::string, size_t ) > generate;
	std::vector< std::string > addresses{};

	generate = [&]( std::string mask, size_t index ){
		for(; index < mask.size(); index++ )
			if( ! ::isdigit( mask[ index ] ) ) {
				std::string copy{ mask };

				mask[ index ] = '0';
				copy[ index ] = '1';

				generate( copy, index+1 );
			}

		addresses.push_back( mask );
	};

	decltype( this->bits ) copyOfBits{};
	for( auto &value : this->bits ) {
		addresses.clear();

		std::string previousAddress{ Bits{ value.first }.to_string() };
		std::string newAddress( 36, '-' );
		std::cout << previousAddress << std::endl << this->mask << std::endl;

		for( size_t i = 0; i < this->mask.size(); i++ )
			newAddress[ i ] = this->mask[ i ] == '0' ? previousAddress[ i ] : this->mask[ i ];

		std::cout << newAddress << std::endl << std::endl;
		generate( newAddress, 0 );

		for( auto &address : addresses )
			copyOfBits[ Bits{ address }.to_ullong() ] = value.second;
	}

	this->bits = copyOfBits;
}*/

std::istream &aoc::day14::operator>>( std::istream &input, aoc::day14::Group &group ) {
	std::string text{};

	std::getline( input, text );
	group.mask = text.substr( text.find( '=' )+2 );

	while( true ) {
		std::istream::pos_type readPosition = input.tellg();

		getline( input, text );
		if( text.find( "mask" ) == std::string::npos ) {
			size_t numberStart{ text.find('[')+1 };
			size_t numberEnd{ text.find( ']' ) };

			size_t memory{ std::stoull( text.substr( numberStart, numberEnd-numberStart ) ) };
			size_t value{ std::stoull( text.substr( text.find( '=' )+2 ) ) };

			group.bits[ memory ] = Bits{ value };

			if( input.eof() )
				break;
		} else {
			input.seekg( readPosition, std::ios_base::beg );
			break;
		}
	}

	return input;
}

std::istream &aoc::day14::operator>>( std::istream &input, aoc::day14::Group2 &group2 ) {
	std::string text{};

	std::getline( input, text );
	group2.mask = text.substr( text.find( '=' )+2 );

	while( true ) {
		std::istream::pos_type readPosition = input.tellg();

		getline( input, text );
		if( text.find( "mask" ) == std::string::npos ) {
			size_t numberStart{ text.find('[')+1 };
			size_t numberEnd{ text.find( ']' ) };

			size_t memory{ std::stoull( text.substr( numberStart, numberEnd-numberStart ) ) };
			size_t value{ std::stoull( text.substr( text.find( '=' )+2 ) ) };

			group2.pairs.push_back( std::pair< size_t, Bits >( memory, Bits{ value } ) );

			if( input.eof() )
				break;
		} else {
			input.seekg( readPosition, std::ios_base::beg );
			break;
		}
	}

	return input;
}

void aoc::day14::Group2::applyMask2() {
	std::function< void( std::string, size_t ) > generate;
	std::vector< std::string > addresses{};

	generate = [&]( std::string mask, size_t index ){
		for(; index < mask.size(); index++ )
			if( ! ::isdigit( mask[ index ] ) ) {
				std::string copy{ mask };

				mask[ index ] = '0';
				copy[ index ] = '1';

				generate( copy, index+1 );
			}

		addresses.push_back( mask );
	};

	decltype( this->bits ) copyOfBits{};
	for( auto &value : this->pairs ) {
		addresses.clear();

		std::string previousAddress{ Bits{ value.first }.to_string() };
		std::string newAddress( 36, '-' );
		std::cout << previousAddress << std::endl << this->mask << std::endl;

		for( size_t i = 0; i < this->mask.size(); i++ )
			newAddress[ i ] = this->mask[ i ] == '0' ? previousAddress[ i ] : this->mask[ i ];

		std::cout << newAddress << std::endl << std::endl;
		generate( newAddress, 0 );

		for( auto &address : addresses )
			copyOfBits[ Bits{ address }.to_ullong() ] = value.second;
	}

	this->bits = copyOfBits;
}
