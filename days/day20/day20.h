// Created by Majrusz on 20/12/2020. All rights reserved.

#pragma once

#include <map>

#include "file_loader.h"
#include "vector.h"
#include "vector_2d.h"

namespace aoc::day20 {
	struct Tile {
		Tile &rotate();

		Tile &flip();

		Tile &calculateEdges();

		std::vector< std::string > lines{};
		int64_t id{};
		int64_t edges[ 4 ]{};

		static int64_t edgeIDCounter;
		static std::map< std::string, size_t > edgeIDs;
	};
	using Tiles = std::vector< Tile >;

	void start();

	std::map< size_t, size_t > findConnections( Tiles &tiles );

	int64_t multiplyCorners( Tiles &tiles );

	std::ostream &operator<<( std::ostream &stream, const Tile &tile );

	std::istream &operator>>( std::istream &input, Tile &tile );
}

