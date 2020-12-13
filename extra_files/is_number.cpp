// Created by Majrusz on 13/12/2020. All rights reserved.

#include "is_number.h"

bool aoc::isNumber( const std::string &text ) {
	return !text.empty() && std::all_of( std::begin( text ), std::end( text ), ::isdigit );
}