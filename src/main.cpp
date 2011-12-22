// main.c
// Template for OpenGL 3.*
// N. Dommanget dommange@univ-mlv.fr

#include "BoidsApplication.h"

#include <stein/math/StreamUtils.h>

#include <iostream>

using namespace std;

int main(int argc, char **argv) {
    try {
        BoidsApplication app;
        app.loop();
        return EXIT_SUCCESS;
    } catch (exception &e) {
        cerr << e.what() << endl;
    } catch (...) {
        cerr << "Something very bad happened..." << endl;
    }
    return EXIT_FAILURE;
}

