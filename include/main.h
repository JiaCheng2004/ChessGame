#pragma once

#ifndef MAIN_H_
#define MAIN_H_

#include <../include/chess.h>
#include <cstdlib>
#include <ctype.h>
#include <getopt.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define CLEAR_SCREEN "\033[1;1H\033[2J"

void print_usage() {
    std::cerr << "Usage: ChessGame [options]" << std::endl;
    std::cerr << "Options:" << std::endl;
    std::cerr << "  --verbose, --debug, -verbose, -debug, -v, -V, -d, -D : Show "
                 "all details and debug information."
              << std::endl;
    std::cerr << "  --test, -test, -t, -T <filename> : Test the program with the "
                 "specified input file."
              << std::endl;
    std::cerr << "  --ai, --bot, -ai, -bot <AI_name> : Play against the specified AI." << std::endl;
    exit(EXIT_FAILURE);
}

void getInput(std::string &buf) {
    while (true) {
        std::cin >> buf;
        std::transform(buf.begin(), buf.end(), buf.begin(), ::toupper);
        if (buf == "UNDO")
            return;
        if (buf.length() == 2 && inBound(buf[0] - 'A') && inBound(buf[1] - '1'))
            break;
        std::cout << "Only accept input rows and colum [A-H][1-8]" << std::endl;
    }
}

#endif