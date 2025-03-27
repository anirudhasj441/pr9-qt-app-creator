/// @file: main.cpp
///
#include "project_generator.h"
#include <QCoreApplication>
#include <iostream>

//////////////////////////////////////////////////////////////////////////////

/// main() - the once and only.
///
/// @param[in] 
///     Number of commandline arguments passed in.
/// @param[in]
///     Array of char strings containing individual arguments.
int
main( int argc, char** argv ) {
    std::cout << "New project Qt Project generator" << std::endl;
    QCoreApplication app( argc, argv );

    ProjectGenerator pg;
    pg.start();
    
    return app.exec();
}

