#pragma once

#ifndef MAIN_H_
#define MAIN_H_

#include <../include/chess.h>
#include <iostream>
#include <unistd.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <cstdlib>

void print_usage() {
    std::cerr << "Usage: ChessGame [options]" << std::endl;
    std::cerr << "Options:" << std::endl;
    std::cerr << "  --verbose, --debug, -verbose, -debug, -v, -V, -d, -D : Show all details and debug information." << std::endl;
    std::cerr << "  --test, -test, -t, -T <filename> : Test the program with the specified input file." << std::endl;
    std::cerr << "  --ai, --bot, -ai, -bot <AI_name> : Play against the specified AI." << std::endl;
    exit(EXIT_FAILURE);
}

#endif