// Created by Majrusz on 16/12/2020. All rights reserved.

#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <functional>

namespace aoc::day16 {
    struct Range {
        size_t min{}, max{};
    };
    struct Ranges {
        std::string name{};
        Range data[ 2 ]{};
    };
    struct Tickets {
        std::vector< size_t > ids{};
    };
    struct InputType {
        std::vector< Ranges > ranges{};
        Tickets your{};
        std::vector< Tickets > nearby{};
    };

    void start();

    bool isInRange( size_t ticket, const Ranges &ranges );

    bool isInRanges( size_t ticket, const std::vector< Ranges > &ranges );

    void removeAllInvalidTickets( InputType &input );

    std::vector< size_t > findPermutation( InputType &input );

    InputType loadFile( const std::string &filename );
}