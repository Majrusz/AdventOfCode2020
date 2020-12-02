// Created by Majrusz on 02/12/2020. All rights reserved.

#pragma once

#include <string>
#include <fstream>
#include <iostream>
#include <vector>

namespace aoc {
	template< typename Type >
	std::vector< Type > loadFile( const std::string &filename );
}

template< typename Type >
std::vector< Type > aoc::loadFile( const std::string &filename ) {
	std::ifstream file{ "../" + filename };
	std::vector< Type > objects{};
	Type object{};

	if( !file ) {
		std::cout << "Error when loading \"" << filename << "\" file!" << std::endl;
		return objects;
	}

	while( file >> object )
		objects.push_back( object );

	file.close();

	return objects;
}