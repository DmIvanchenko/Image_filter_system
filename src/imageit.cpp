//=============================================================================
// Name        : imageit.cpp
// Authors     : Arnoldas Rauba, Daria Shmielova, Dmytro Ivanchenko, Vlad Piven
// Compiler    : g++
// C++ version : C++17
// Description : Hello World in C++, Ansi-style
//=============================================================================

#include <vips/vips8>

#include "debug/debug.h"
#include "frontend/frontend.h"

using namespace std;
using namespace vips;
using namespace backend;

int main(int argc, char **argv) {
    // DO NOT DELETE
    if (VIPS_INIT(argv[0])) {
        vips_error_exit("Unable to start VIPS");
    }
    if (argc == 2 && strcmp("-d", argv[1]) == 0) {
        debug::cli_frontend();
    } else {
        frontend_main(argc, argv);
    }

    return 0;
}
