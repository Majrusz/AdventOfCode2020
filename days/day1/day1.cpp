// Created by Majrusz on 02/12/2020. All rights reserved.

#include "day1.h"

void aoc::day1::start() {
	std::vector< int > numbers{ aoc::loadFile< int >( "days/day1/input.txt" ) };

	findProductOfTwoNumbers( numbers );
	findProductOfThreeNumbers( numbers );
}

void aoc::day1::findProductOfTwoNumbers( const std::vector< int > &numbers ) {
	for( auto it1 = numbers.begin(); it1 != numbers.end(); it1++ )
		for( auto it2 = it1; it2 != numbers.end(); it2++ )
			if( int a{ *it1 }, b{ *it2 }; a + b == 2020 ) {
				std::cout << a << " * " << b << " = " << a * b << std::endl;

				return;
			}
}

void aoc::day1::findProductOfThreeNumbers( const std::vector< int > &numbers ) {
	for( auto it1 = numbers.begin(); it1 != numbers.end(); it1++ )
		for( auto it2 = it1; it2 != numbers.end(); it2++ )
			for( auto it3 = it2; it3 != numbers.end(); it3++ )
				if( int a{ *it1 }, b{ *it2 }, c{ *it3 }; a + b + c == 2020 ) {
					std::cout << a << " * " << b << " * " << c << " = " << a * b * c << std::endl;
					return;
				}
}
