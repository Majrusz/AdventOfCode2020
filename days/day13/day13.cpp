// Created by Majrusz on 13/12/2020. All rights reserved.

#include "day13.h"

void aoc::day13::start() {
	BusStop busStop{ loadFile< BusStop >( "days/day13/input.txt" ).front() };

	Bus minimumWaitTimeBus{ busStop.getMinimumTime() };
	std::cout << minimumWaitTimeBus.id * minimumWaitTimeBus.timeToWait << std::endl;
	std::cout << busStop.findPattern() << std::endl;
}

std::istream &aoc::day13::operator>>( std::istream &input, aoc::day13::BusStop &busStop ) {
	std::string timestamp{}, buses{};

	input >> timestamp >> buses;

	busStop.timestamp = std::stol( timestamp );

	while( !buses.empty() ) {
		size_t index{ buses.find( ',' ) };
		std::string element{ buses.substr( 0, index ) };

		busStop.buses.emplace_back( isNumber( element ) ? std::stol( element ) : -1 );

		buses.erase( 0, index + 1 );

		if( index == std::string::npos )
			break;
	}

	return input;
}

size_t aoc::day13::BusStop::getTimeToWait( size_t time ) const {
	return time - this->timestamp % time;
}

aoc::day13::Bus aoc::day13::BusStop::getMinimumTime() const {
	size_t minimumTime{ 999999999L };

	for( long current : this->buses )
		if( current != -1 && getTimeToWait( current ) < getTimeToWait( minimumTime ) )
			minimumTime = current;

	return Bus{ minimumTime, getTimeToWait( minimumTime ) };
}

size_t aoc::day13::BusStop::findPattern() const {
	size_t testTimestamp{};
	size_t multiplier{ static_cast< size_t >( this->buses[ 0 ] ) };
	for( size_t index = 1; index < this->buses.size(); index++ ) {
		long bus{ this->buses[ index ] };
		if( bus == -1 )
			continue;

		while( ( testTimestamp % bus ) != ( bus - index % bus ) )
			testTimestamp += multiplier;

		multiplier *= static_cast< size_t >( bus );
	}

	return testTimestamp;
}
