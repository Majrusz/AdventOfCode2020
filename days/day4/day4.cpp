// Created by Majrusz on 05/12/2020. All rights reserved.

#include "day4.h"

void aoc::day4::start() {
	Records records{ aoc::loadFile< Record >( "days/day4/input.txt" ) };

	auto counter{ std::count_if( std::begin( records ), std::end( records ), isValidPassport2 ) };

	std::cout << "Valid passwords: " << counter << std::endl;
}

std::istream &aoc::day4::operator>>( std::istream &input, aoc::day4::Record &record ) {
	std::string line{}, text{};

	while( std::getline( input, line ) ) {
		if( line.empty() )
			break;

		std::istringstream temporary{ line };
		while( temporary >> text ) {
			size_t index{ text.find( ':' ) };

			std::string key{ text.substr( 0, index ) };
			std::string value{ text.substr( index + 1 ) };
			record.data[ key ] = value;
		}
	}

	return input;
}

bool aoc::day4::isValidPassport( const aoc::day4::Record &passport ) {
	auto &data{ passport.data };
	size_t size{ data.size() };

	return ( size == 8 ) || ( size == 7 && ( data.find( "cid" ) == data.end() ) );
}

bool aoc::day4::isValidPassport2( const aoc::day4::Record &passport ) {
	auto &data{ passport.data };
	size_t size{ data.size() };

	auto hasValue{ [&]( const std::string &key ) -> bool { return passport.data.find( key ) != passport.data.end(); } };
	if( isValidPassport( passport ) ) {
		if( hasValue( "byr" ) )
			if( int birthYear{ std::stoi( data.at( "byr" ) ) }; !( 1920 <= birthYear && birthYear <= 2002 ) )
				return false;

		if( hasValue( "iyr" ) )
			if( int issueYear{ std::stoi( data.at( "iyr" ) ) }; !( 2010 <= issueYear && issueYear <= 2020 ) )
				return false;

		if( hasValue( "eyr" ) )
			if( int expirationYear{ std::stoi( data.at( "eyr" ) ) }; !( 2020 <= expirationYear && expirationYear <= 2030 ) )
				return false;

		if( hasValue( "hgt" ) ) {
			std::string value{ data.at( "hgt" ) };

			if( size_t index{ value.find( "cm" ) }; index != std::string::npos ) {
				if( int height{ std::stoi( data.at( "hgt" ).substr( 0, index ) ) }; !( 150 <= height && height <= 193 ) )
					return false;
			} else if( size_t index{ value.find( "in" ) }; index != std::string::npos ) {
				if( int height{ std::stoi( data.at( "hgt" ).substr( 0, index ) ) }; !( 59 <= height && height <= 76 ) )
					return false;
			} else
				return false;
		}

		if( hasValue( "hcl" ) ) {
			std::string value{ data.at( "hcl" ) };

			if( value.size() != 7 )
				return false;

			for( size_t i = 1; i < 7; i++ )
				if( char character{ value[ i ] }; !( 'a' <= character && character <= 'f' ) && !( '0' <= character && character <= '9' ) )
					return false;
		}

		if( hasValue( "ecl" ) ) {
			std::string value{ data.at( "ecl" ) };

			bool isValid{};
			for( auto &validValue : { "amb", "blu", "brn", "gry", "grn", "hzl", "oth" } )
				if( ( isValid = ( value == validValue ) ) )
					break;

			if( !isValid )
				return false;
		}

		if( hasValue( "pid" ) ) {
			std::string value{ data.at( "pid" ) };

			if( value.size() != 9 )
				return false;
		}

		return true;
	}

	return false;
}
