// Created by Majrusz on 02/12/2020. All rights reserved.

#pragma once

#include <string>
#include <fstream>
#include <iostream>
#include <vector>

#include "file_loader.h"

namespace aoc::day1 {
	void start();

	void findProductOfTwoNumbers( const std::vector< int > &numbers );

	void findProductOfThreeNumbers( const std::vector< int > &numbers );
};