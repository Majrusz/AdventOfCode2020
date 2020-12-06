// Created by Majrusz on 06/12/2020. All rights reserved.

#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

#include "file_loader.h"

namespace aoc::day6 {
	struct Person {
		using Answers = std::vector< char >;
		Answers answers{};
	};
	using Group = std::vector< Person >;
	using Groups = std::vector< Group >;

	void start();

	Person::Answers mergeAnswers( const Group &group );

	Person::Answers::iterator getUniqueAnswers( Person::Answers &allAnswers );

	size_t countUniqueAnswers( const Group &group );

	size_t countUniqueAnswers( const Groups &groups );

	size_t countAnswersToWhichEveryoneReplied( const Group &group );

	size_t countAnswersToWhichEveryoneReplied( const Groups &groups );

	std::istream &operator>>( std::istream &input, Group &group );
}

