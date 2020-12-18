// Created by Majrusz on 18/12/2020. All rights reserved.

#include "day18.h"

void aoc::day18::start() {
	Lines lines{ loadFile< Line >( "days/day18/input.txt" ) };

	SizeType total{};
	for( auto &line : lines )
		total += line.calculate( &Line::part1Method );

	std::cout << "Sum of every line: " << total << std::endl;

	// Line line{ "5 + (8 * 3 + 9 + 3 * 4 * 3)" };
	// std::cout << line.calculate( &Line::part2Method ) << std::endl;

	SizeType total2{};
	for( auto &line : lines )
		total2 += line.calculate( &Line::part2Method );

	std::cout << "Sum of every line (2nd method): " << total2 << std::endl;
}

aoc::day18::SizeType aoc::day18::Line::calculate( SizeType ( *method )( const std::string &equation ) ) const {
	std::string temporary{ this->value };

	SizeType index{};
	while( ( index = temporary.find( '(' ) ) != std::string::npos ) {
		SizeType bracketCounter{ 1 }, currentIndex{ index };

		while( bracketCounter > 0 ) {
			currentIndex++;

			if( char element{ temporary[ currentIndex ] }; element == '(' )
				bracketCounter++;
			else if( element == ')' )
				bracketCounter--;
		}

		Line subline{ temporary.substr( index+1, currentIndex - ( index + 1 ) ) };
		temporary = temporary.substr( 0, index ) + std::to_string( subline.calculate( method ) ) + temporary.substr( currentIndex+1 );
	}

	return method( temporary );
}

aoc::day18::SizeType aoc::day18::Line::part1Method( const std::string &string ) {
	std::stringstream stream{ string };
	SizeType a{}, b{};
	char op{};

	stream >> a;
	do {
		stream >> op >> b;

		if( op == '+' )
			a += b;
		else if( op == '*' )
			a *= b;

	} while( !stream.eof() );

	return a;
}

aoc::day18::SizeType aoc::day18::Line::part2Method( const std::string &string ) {
	std::stringstream stream{ string };
	std::string temporary{};
	SizeType a{}, b{};
	char op{};

	std::cout << string << std::endl;
	stream >> a;
	do {
		stream >> op >> b;

		if( op == '+' )
			a += b;
		else if( op == '*' ) {
			temporary += std::to_string( a ) + " * ";
			a = b;
		}

	} while( !stream.eof() );
	if( temporary.empty() )
		return a;

	temporary += std::to_string( a );

	std::stringstream stream2{ temporary };
	stream2 >> a;
	do {
		stream2 >> op >> b;

		a *= b;
	} while( !stream2.eof() );

	return a;
}

std::istream &aoc::day18::operator>>( std::istream &input, aoc::day18::Line &line ) {
	getline( input, line.value );
	return input;
}