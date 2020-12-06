// Created by Majrusz on 06/12/2020. All rights reserved.

#include "day6.h"

void aoc::day6::start() {
	Groups groups{ aoc::loadFile< Group >( "days/day6/input.txt" ) };

	std::cout << countUniqueAnswers( groups ) << std::endl;
	std::cout << countAnswersToWhichEveryoneReplied( groups ) << std::endl;
}

aoc::day6::Person::Answers aoc::day6::mergeAnswers( const Group &group ) {
	Person::Answers allAnswers{};

	for( auto &person : group )
		std::for_each( std::begin( person.answers ), std::end( person.answers ), [&]( char answer ){ allAnswers.push_back( answer ); } );

	std::sort( std::begin( allAnswers ), std::end( allAnswers ) );

	return allAnswers;
}

aoc::day6::Person::Answers::iterator aoc::day6::getUniqueAnswers( Person::Answers &allAnswers ) {
	return std::unique( std::begin( allAnswers ), std::end( allAnswers ) );
}

size_t aoc::day6::countUniqueAnswers( const Group &group ) {
	Person::Answers allAnswers{ mergeAnswers( group ) };

	return std::distance( std::begin( allAnswers ), getUniqueAnswers( allAnswers ) );
}

size_t aoc::day6::countUniqueAnswers( const Groups &groups ) {
	size_t counter{};

	std::for_each( std::begin( groups ), std::end( groups ), [&]( const Group &group ){ counter += countUniqueAnswers( group ); } );

	return counter;
}

size_t aoc::day6::countAnswersToWhichEveryoneReplied( const Group &group ) {
	Person::Answers allAnswers{ mergeAnswers( group ) };
	Person::Answers uniqueAnswers{ allAnswers };
	Person::Answers::iterator lastUnique{ getUniqueAnswers( uniqueAnswers ) };

	auto counter{
		std::count_if( std::begin( uniqueAnswers ), lastUnique, [&]( char uniqueAnswer ) -> bool {
			return ( std::count_if( std::begin( allAnswers ), std::end( allAnswers ), [&]( char answer ) -> bool {
				return uniqueAnswer == answer;
			} ) == group.size() );
		} )
	};
	return static_cast< size_t >( counter );
}

size_t aoc::day6::countAnswersToWhichEveryoneReplied( const Groups &groups ) {
	size_t counter{};

	std::for_each( std::begin( groups ), std::end( groups ), [&]( const Group &group ){ counter += countAnswersToWhichEveryoneReplied( group ); } );

	return counter;
}

std::istream &aoc::day6::operator>>( std::istream &input, Group &group ) {
	std::string singlePersonAnswers{};

	while( std::getline( input, singlePersonAnswers ) ) {
		if( singlePersonAnswers.empty() )
			break;

		Person person{};
		for( auto &answer : singlePersonAnswers )
			person.answers.push_back( answer );

		group.push_back( person );

		singlePersonAnswers.clear();
	}

	return input;
}
