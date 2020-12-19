// Created by Majrusz on 19/12/2020. All rights reserved.

#include "day19.h"

void aoc::day19::start() {
	Input input{ loadFromFile( "test2.txt" ) };

	std::cout << input.countValidMessages() << std::endl;

	input.rules[ 8 ].second = std::vector< size_t >{ 42, 8 };
	input.rules[ 11 ].second = std::vector< size_t >{ 42, 11, 31 };

	std::cout << input.countValidMessages() << std::endl;
}

aoc::day19::Messages aoc::day19::Input::getValidMessages() const {
	std::map< size_t, Messages > calculatedMessages{};
	std::map< size_t, size_t > recursiveCalled{};

	for( auto &rule : this->rules ) {
		calculatedMessages[ rule.first ] = Messages{};
		recursiveCalled[ rule.first ] = 0;
	}

	size_t maximumMessageSize{ std::max_element( std::begin( this->messages ), std::end( this->messages ), []( auto &max, auto &message ){
		return max.size() < message.size();
	} )->size()/2 };

	std::function< void( size_t ) > calculate;
	std::function< void( size_t, const std::vector< size_t > & ) > calculatePermutation;
	auto addElement{ [&]( const std::string &message, Messages &currentMessages ){
		if( std::find( std::begin( currentMessages ), std::end( currentMessages ), message ) == std::end( currentMessages ) && message.size() < maximumMessageSize )
			currentMessages.push_back( message );
	} };
	calculate = [&]( size_t index ){
		const Rule &currentRule{ this->rules.at( index ) };
		std::cout << index << std::endl;
		if( char character{ currentRule.character }; character != 0 ) {
			std::cout << '\t' << index << " end" << std::endl;
			calculatedMessages[ index ].push_back( std::string{ character } );
		} else if( calculatedMessages[ index ].empty() ) {
			std::cout << '\t' << index << " first" << std::endl;
			calculatePermutation( index, currentRule.first );
			std::cout << '\t' << index << " second" << std::endl;
			if( !currentRule.second.empty() )
				calculatePermutation( index, currentRule.second );
		}
	};

	calculatePermutation = [&]( size_t currentIndex, const std::vector< size_t > &indexes ){
		for( auto &index : indexes )
			if( calculatedMessages[ index ].empty() ) {
				if( recursiveCalled[ index ] > maximumMessageSize ) {
					calculatedMessages[ currentIndex ].push_back( "" );
					return;
				}

				recursiveCalled[ index ]++;
				calculate( index );
			}

		if( size_t size{ indexes.size() }; size == 1 ) {
			for( auto &message : calculatedMessages[ indexes[ 0 ] ] )
				addElement( message, calculatedMessages[ currentIndex ] );
		} else if( size == 2 ) {
			for( auto &messageA : calculatedMessages[ indexes[ 0 ] ] )
				for( auto &messageB : calculatedMessages[ indexes[ 1 ] ] )
					addElement( messageA + messageB, calculatedMessages[ currentIndex ] );
		} else if( size == 3 ) {
			for( auto &messageA : calculatedMessages[ indexes[ 0 ] ] )
				for( auto &messageB : calculatedMessages[ indexes[ 1 ] ] )
					for( auto &messageC : calculatedMessages[ indexes[ 2 ] ] )
						addElement( messageA + messageB + messageC, calculatedMessages[ currentIndex ] );
		} else
			std::cout << "??\n";
	};

	calculate( 0 );

	return calculatedMessages[ 0 ];
}

size_t aoc::day19::Input::countValidMessages() const {
	size_t counter{};
	auto validMessages{ getValidMessages() };

	for( auto &message : this->messages )
		for( auto &validMessage : validMessages )
			if( message == validMessage ) {
				counter++;
				break;
			}

	return counter;
}

aoc::day19::Input aoc::day19::loadFromFile( const std::string &filename ) {
	std::ifstream file{ "../days/day19/" + filename };
	std::string text{};
	Input input{};

	if( !file ) {
		std::cout << "Error when loading \"" << filename << "\" file!" << std::endl;
		return input;
	}

	while( true ) {
		std::getline( file, text );
		std::stringstream stream{ text };
		size_t index{};
		Rule rule{};

		if( text.empty() )
			break;

		stream >> text;
		index = std::stoull( text.substr( 0, text.find( ':' ) ) );

		bool isLoadingFirstRule{ true };
		while( !stream.eof() ) {
			stream >> text;
			if( text.find( '"' ) != std::string::npos ) {
				rule.character = text.substr( text.find( '"' ) + 1, text.find_last_of( '"' ) )[ 0 ];
				break;
			} else if( text.find( '|' ) != std::string::npos )
				isLoadingFirstRule = false;
			else
				( isLoadingFirstRule ? rule.first : rule.second ).push_back( std::stoull( text ) );
		}

		input.rules[ index ] = rule;
	}

	while( !file.eof() ) {
		std::getline( file, text );
		input.messages.push_back( text );
	}

	return input;
}
