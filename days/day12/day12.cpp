// Created by Majrusz on 12/12/2020. All rights reserved.

#include "day12.h"

void aoc::day12::start() {
	Instructions instructions{ loadFile< Instruction >( "days/day12/input.txt" ) };

	auto position{ navigate( instructions ) };

	std::cout << "Navigate\nManhattan length: " << ( std::abs( position.x ) + std::abs( position.y ) ) << std::endl;

	auto position2{ navigateWithWaypoint( instructions ) };

	std::cout << "Navigate with waypoint\nManhattan length: " << ( std::abs( position2.x ) + std::abs( position2.y ) ) << std::endl;
}

aoc::day12::Instruction::MoveType aoc::day12::Instruction::characterToMoveType( char character ) {
	switch( character ) {
		case 'N':
			return MoveType::North;
		case 'S':
			return MoveType::South;
		case 'E':
			return MoveType::East;
		case 'W':
			return MoveType::West;
		case 'L':
			return MoveType::Left;
		case 'R':
			return MoveType::Right;
		case 'F':
			return MoveType::Forward;
		default:
			return MoveType::East;
	}
}

aoc::day12::Vector aoc::day12::navigate( const Instructions &instructions ) {
	Vector position{}, direction{ 1, 0 };
	const double pi{ std::acos( -1 ) };
	double currentAngle{};

	auto apply{ [ & ]( const Instruction &instruction ){
		Vector localDirection{ direction };

		switch( instruction.type ) {
			case Instruction::MoveType::North:
				localDirection = Vector{ 0, 1 };
				break;
			case Instruction::MoveType::South:
				localDirection = Vector{ 0, -1 };
				break;
			case Instruction::MoveType::East:
				localDirection = Vector{ 1, 0 };
				break;
			case Instruction::MoveType::West:
				localDirection = Vector{ -1, 0 };
				break;
			case Instruction::MoveType::Left:
				currentAngle += instruction.value / 180.0 * pi;
				direction = Vector{ static_cast< long >( std::round( std::cos( currentAngle ) ) ), static_cast< long >( std::round( std::sin( currentAngle ) ) ) };
				return;
			case Instruction::MoveType::Right:
				currentAngle -= instruction.value / 180.0 * pi;
				direction = Vector{ static_cast< long >( std::round( std::cos( currentAngle ) ) ), static_cast< long >( std::round( std::sin( currentAngle ) ) ) };
				return;
			default:
				break;
		}

		position.x += localDirection.x * instruction.value;
		position.y += localDirection.y * instruction.value;
	} };

	for( auto &instruction : instructions )
		apply( instruction );

	return position;
}

aoc::day12::Vector aoc::day12::navigateWithWaypoint( const aoc::day12::Instructions &instructions ) {
	Vector position{}, waypoint{ 10, 1 };
	const double pi{ std::acos( -1 ) };
	double currentAngle{};

	auto distance{ []( Vector a, Vector b = Vector{ 0, 0 } ) -> double {
		return std::sqrt( std::pow( b.x - a.x, 2 ) + std::pow( b.y - a.y, 2 ) );
	} };
	auto updateAngle{ [ & ]( double angle ){
		double dotProduct{ std::acos( waypoint.x / distance( waypoint ) ) };
		if( waypoint.y <= 0 )
			dotProduct = 2.0 * pi - dotProduct;
		currentAngle = dotProduct + angle / 180.0 * pi;
	} };
	auto apply{ [ & ]( const Instruction &instruction ){
		Vector localDirection{};

		switch( instruction.type ) {
			case Instruction::MoveType::North:
				localDirection = Vector{ 0, 1 };
				break;
			case Instruction::MoveType::South:
				localDirection = Vector{ 0, -1 };
				break;
			case Instruction::MoveType::East:
				localDirection = Vector{ 1, 0 };
				break;
			case Instruction::MoveType::West:
				localDirection = Vector{ -1, 0 };
				break;
			case Instruction::MoveType::Left:
				updateAngle( instruction.value );
				waypoint = Vector{ static_cast< long >( std::round( distance( waypoint ) * std::cos( currentAngle ) ) ), static_cast< long >( std::round( distance( waypoint ) * std::sin( currentAngle ) ) ) };
				return;
			case Instruction::MoveType::Right:
				updateAngle( -instruction.value );
				waypoint = Vector{ static_cast< long >( std::round( distance( waypoint ) * std::cos( currentAngle ) ) ), static_cast< long >( std::round( distance( waypoint ) * std::sin( currentAngle ) ) ) };
				return;
			default:
				break;
		}

		if( localDirection.x != 0 || localDirection.y != 0 ) {
			waypoint.x += localDirection.x * instruction.value;
			waypoint.y += localDirection.y * instruction.value;
		} else {
			position.x += waypoint.x * instruction.value;
			position.y += waypoint.y * instruction.value;
		}
	} };

	for( auto &instruction : instructions )
		apply( instruction );

	return position;
}

std::istream &aoc::day12::operator>>( std::istream &input, aoc::day12::Instruction &instruction ) {
	std::string text{};

	input >> text;

	instruction.type = Instruction::characterToMoveType( text[ 0 ] );
	instruction.value = std::stol( text.substr( 1 ) );

	return input;
}
