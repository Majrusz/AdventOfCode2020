// Created by Majrusz on 12/12/2020. All rights reserved.

#include "day11.h"

void aoc::day11::start() {
	Columns columns{ loadFile< Row >( "days/day11/input.txt" ) };

	while( true ) {
		if( !columns.applyThirdRule() )
			break;

		if( !columns.applyFourthRule() )
			break;
	}

	std::cout << columns.countOccupiedSeats() << std::endl;
}

std::istream &aoc::day11::operator>>( std::istream &input, aoc::day11::Row &row ) {
	std::string text{};

	std::getline( input, text );

	for( auto &character : text )
		switch( character ) {
			case 'L':
				row.seats.push_back( Row::SeatType::Empty );
				break;
			case '#':
				row.seats.push_back( Row::SeatType::Occupied );
				break;
			default:
				row.seats.push_back( Row::SeatType::Floor );
		}

	return input;
}

size_t aoc::day11::Columns::countOccupiedAdjacentSeats( long x, long y ) const {
	size_t counter{};
	size_t maximumX{ this->rows[ y ].seats.size() }, maximumY{ this->rows.size() };

	for( long j = -1; j <= 1; j++ )
		for( long i = -1; i <= 1; i++ ) {
			if( i == 0 && j == 0 )
				continue;

			long xx{ x + i }, yy{ y + j };

			if( 0 <= xx && xx < maximumX && 0 <= yy && yy < maximumY )
				if( get( xx, yy ) == Row::SeatType::Occupied )
					counter++;
		}

	return counter;
}

size_t aoc::day11::Columns::countOccupiedAdjacentSeats2( long x, long y ) const {
	size_t counter{};
	size_t maximumX{ this->rows[ y ].seats.size() }, maximumY{ this->rows.size() };

	for( long j = -1; j <= 1; j++ )
		for( long i = -1; i <= 1; i++ ) {
			if( i == 0 && j == 0 )
				continue;

			long xx{ x }, yy{ y };

			while( true ) {
				xx += i;
				yy += j;

				if( 0 <= xx && xx < maximumX && 0 <= yy && yy < maximumY ) {
					if( Row::SeatType type{ get( xx, yy ) }; type == Row::SeatType::Occupied ) {
						counter++;
						break;
					} else if( type == Row::SeatType::Empty )
						break;
					else
						continue;
				} else
					break;
			}
		}

	return counter;
}

bool aoc::day11::Columns::applyFirstRule() {
	struct Point {
		long x, y;
	};
	std::vector< Point > points{};

	for( long y = 0; y < this->rows.size(); y++ )
		for( long x = 0; x < this->rows[ y ].seats.size(); x++ )
			if( this->get( x, y ) == Row::SeatType::Empty && this->countOccupiedAdjacentSeats( x, y ) == 0 )
				points.push_back( Point{ x, y } );

	if( points.empty() )
		return false;

	for( const Point &point : points )
		this->get( point.x, point.y ) = Row::SeatType::Occupied;

	return true;
}

bool aoc::day11::Columns::applySecondRule() {
	struct Point {
		long x, y;
	};
	std::vector< Point > points{};

	for( long y = 0; y < this->rows.size(); y++ )
		for( long x = 0; x < this->rows[ y ].seats.size(); x++ )
			if( this->get( x, y ) == Row::SeatType::Occupied && this->countOccupiedAdjacentSeats( x, y ) >= 4 )
				points.push_back( Point{ x, y } );

	if( points.empty() )
		return false;

	for( const Point &point : points )
		this->get( point.x, point.y ) = Row::SeatType::Empty;

	return true;
}

bool aoc::day11::Columns::applyThirdRule() {
	struct Point { long x, y; };
	std::vector< Point > points{};

	for( long y = 0; y < this->rows.size(); y++ )
		for( long x = 0; x < this->rows[ y ].seats.size(); x++ )
			if( this->get( x, y ) == Row::SeatType::Empty && this->countOccupiedAdjacentSeats2( x, y ) == 0 )
				points.push_back( Point{ x, y } );

	if( points.empty() )
		return false;

	for( const Point &point : points )
		this->get( point.x, point.y ) = Row::SeatType::Occupied;

	return true;
}

bool aoc::day11::Columns::applyFourthRule() {
	struct Point { long x, y; };
	std::vector< Point > points{};

	for( long y = 0; y < this->rows.size(); y++ )
		for( long x = 0; x < this->rows[ y ].seats.size(); x++ )
			if( this->get( x, y ) == Row::SeatType::Occupied && this->countOccupiedAdjacentSeats2( x, y ) >= 5 )
				points.push_back( Point{ x, y } );

	if( points.empty() )
		return false;

	for( const Point &point : points )
		this->get( point.x, point.y ) = Row::SeatType::Empty;

	return true;
}

std::ostream &aoc::day11::operator<<( std::ostream &stream, const aoc::day11::Columns &columns ) {
	for( auto &r : columns.rows ) {
		for( auto &s : r.seats )
			stream << ( s == Row::SeatType::Empty ? 'L' : ( s == Row::SeatType::Occupied ? '#' : '.' ) );
		stream << std::endl;
	}

	return stream;
}

size_t aoc::day11::Columns::countOccupiedSeats() const {
	size_t counter{};

	for( auto &row : this->rows )
		for( auto &seat : row.seats )
			if( seat == Row::SeatType::Occupied )
				counter++;

	return counter;
}
