// Created by Majrusz on 19/12/2020. All rights reserved.

#pragma once

#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <functional>
#include <map>

namespace aoc::day19 {
	struct Rule {
		std::vector< size_t > first{}, second{};
		char character{};
	};

	using Messages = std::vector< std::string >;
	struct Input {
		std::map< size_t, Rule > rules{};
		Messages messages{};

		[[nodiscard]] Messages getValidMessages() const;

		[[nodiscard]] size_t countValidMessages() const;
	};

	void start();

	Input loadFromFile( const std::string &filename );
}
