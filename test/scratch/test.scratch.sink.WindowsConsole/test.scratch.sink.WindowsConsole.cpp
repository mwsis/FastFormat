/* /////////////////////////////////////////////////////////////////////////
 * File:    test.scratch.sink.WindowsConsole.cpp
 *
 * Purpose: Implementation file for the test.scratch.sink.WindowsConsole project.
 *
 * Created: 6th January 2011
 * Updated: 11th August 2024
 *
 * ////////////////////////////////////////////////////////////////////// */


/* /////////////////////////////////////////////////////////////////////////
 * includes
 */

/* FastFormat Header Files */
#include <fastformat/sinks/WindowsConsole.hpp>
#include <fastformat/ff.hpp>

/* STLSoft Header Files */
#include <winstl/error/error_desc.hpp>

/* Standard C++ Header Files */
#include <exception>
#include <iostream>

/* Standard C Header Files */
#include <stdio.h>
#include <stdlib.h>


/* /////////////////////////////////////////////////////////////////////////
 * main()
 */

static int main_(int /* argc */, char** /*argv*/)
{
    /* . */
    ff::writeln(std::cout, "a regular output line");

    auto s = ff::sinks::WindowsConsole(FOREGROUND_RED);

    ff::writeln(s, "a regular output line");

    ff::writeln(std::cout, "another regular output line");


    return EXIT_SUCCESS;
}

int main(int argc, char** argv)
{
    try
    {
        return main_(argc, argv);
    }
    catch (std::exception& x)
    {
        fprintf(stderr, "Unhandled error: %s\n", x.what());
    }
    catch (...)
    {
        fprintf(stderr, "Unhandled unknown error\n");
    }

    return EXIT_FAILURE;
}


/* ///////////////////////////// end of file //////////////////////////// */

