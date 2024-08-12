/* /////////////////////////////////////////////////////////////////////////
 * File:    test.performance.overload.ex.1.cpp
 *
 * Purpose: Implementation file for the test.performance.overload.ex.1 project.
 *
 * Created: 19th October 2008
 * Updated: 11th August 2024
 *
 * ////////////////////////////////////////////////////////////////////// */


//#define FASTFORMAT_NO_USE_JIT_CACHE

/* /////////////////////////////////////////////////////////////////////////
 * includes
 */

#if defined(_WIN32) && \
    defined(_AFXDLL)
# include <mfcstl/mfcstl.hpp>
#endif


/* FastFormat Header Files */
#include <fastformat/internal/stlsoft.h>
#if defined(STLSOFT_COMPILER_IS_MSVC) && \
    _MSC_VER >= 1400
# define _CRT_SECURE_NO_DEPRECATE
# pragma warning(disable : 4996)
# pragma warning(disable : 4505)
#endif
#if defined(STLSOFT_COMPILER_IS_MSVC) && \
    _MSC_VER == 1310
 /* These warnings only for Boost. Ho hum. */
# pragma warning(disable : 4511)
# pragma warning(disable : 4512)
# pragma warning(disable : 4671)
# pragma warning(disable : 4673)
# pragma warning(disable : 4702)
#endif
#if defined(__BORLANDC__) && \
    __BORLANDC__ < 0x0610
 /* Borland is really messed up, so we have to skip around the filter_type
  * mechanism, and instead define string access shims
  *
  * WARNING: The following implementation is hack that is good enough only
  * to make this compilation unit run correctly. Do not take this code and
  * put it into production
  */
# include <stdio.h>
# include <string.h>

    namespace
    {
        char    s_realBuffer[1001];
    }

    namespace stlsoft
    {
        char const* c_str_data_a(double d)
        {
            int n = ::snprintf(&s_realBuffer[0], STLSOFT_NUM_ELEMENTS(s_realBuffer) - 1, "%G", d);

            if (n < 0)
            {
                n = STLSOFT_NUM_ELEMENTS(s_realBuffer) - 1;
            }

            s_realBuffer[n] = '\0';

            return s_realBuffer;
        }
        size_t c_str_len_a(double d)
        {
            return strlen(c_str_data_a(d));
        }
    }

#else /* ? compiler */
# include <fastformat/shims/conversion/filter_type/reals.hpp>
#endif /* compiler */
#include <fastformat/format/specification_defect_handling/ignore_unreferenced_arguments_scope.hpp>

#if defined(_WIN32) && \
    defined(UNIX)
# include <winsock2.h>
# include <sys/time.h>
# include <platformstl/performance/performance_counter.hpp>
#endif

/* STLSoft Header Files */
#if defined(_WIN32) && \
    defined(_AFXDLL)
# include <mfcstl/mfcstl.hpp>
# include <mfcstl/string/grab_cstring_buffer.hpp>
# include <fastformat/sinks/CString.hpp>
#endif /* OS */
#include <stlsoft/stlsoft.h>
#include <stlsoft/shims/access/string/std/time.hpp>
#include <stlsoft/string/simple_string.hpp>
#include <platformstl/platformstl.h>
#if defined(PLATFORMSTL_OS_IS_WINDOWS)
# include <comstl/shims/access/string.hpp>
#endif /* OS */
#include <platformstl/performance/performance_counter.hpp>

#include <fastformat/sinks/ostream.hpp>
#include <fastformat/fastformat.hpp>

/* Boost Header Files */
#ifdef FASTFORMAT_PERFTEST_USE_BOOST
# include <boost/format.hpp>
#endif /* FASTFORMAT_PERFTEST_USE_BOOST */

/* Loki Header Files */
#ifdef FASTFORMAT_PERFTEST_USE_LOKI
# include <loki/SafeFormat.h>
#endif /* FASTFORMAT_PERFTEST_USE_LOKI */

/* xTests Header Files */
#include <xtests/xtests.h>

/* Standard C++ Header Files */
#include <exception>
#include <iostream>
#include <string>
#include <sstream>

/* Standard C Header Files */
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#if defined(_MSC_VER) && \
    defined(_DEBUG)
# include <crtdbg.h>
#endif /* _MSC_VER) && _DEBUG */


/* /////////////////////////////////////////////////////////////////////////
 * macros
 */

#define TX(x)       FASTFORMAT_LITERAL_STRING(x)


/* /////////////////////////////////////////////////////////////////////////
 * globals
 */

extern "C" const char PANTHEIOS_FE_PROCESS_IDENTITY[] = "test.performance.overload.ex.1";


/* ////////////////////////////////////////////////////////////////////// */

static int main_(int argc, char** argv)
{
    // 0 - nothing
    // 1 - ratios only, in the form of "t:v; t:v; ..."
    // 2 - ratios only, one-per-line
    // 3 - as is

    int verbosity;

    XTESTS_COMMANDLINE_PARSEVERBOSITY(argc, argv, &verbosity);


#ifndef NDEBUG
    unsigned ITERATIONS =   3;
    unsigned WARMUPS    =   1;
#else /* ? !NDEBUG */
    unsigned ITERATIONS =   100000;
    unsigned WARMUPS    =   2;
#endif /* !NDEBUG */
    size_t   length     =   0;

    platformstl::performance_counter                counter;
    platformstl::performance_counter::interval_type tm_Streams          =   1;
    platformstl::performance_counter::interval_type tm_IOStreams        =   1;
    platformstl::performance_counter::interval_type tm_CString_Format   =   1;
    platformstl::performance_counter::interval_type tm_Boost            =   1;
    platformstl::performance_counter::interval_type tm_Loki             =   1;
    platformstl::performance_counter::interval_type tm_FF_Format        =   1;
    platformstl::performance_counter::interval_type tm_FF_Write         =   1;

#ifdef FASTFORMAT_USE_WIDE_STRINGS
    std::wstring forename  = L"Professor";
    wchar_t      surname[] = L"Yaffle";
#else /* ? FASTFORMAT_USE_WIDE_STRINGS */
    std::string  forename  = "Professor";
    char         surname[] = "Yaffle";
#endif /* FASTFORMAT_USE_WIDE_STRINGS */
    int          age       = 134;

    // Test Identifier

    std::string TestId = PANTHEIOS_FE_PROCESS_IDENTITY;

    // IOStreams

    { for (unsigned j = 0; j < WARMUPS; ++j)
    {
        length = 0;
        counter.start();
        { for (unsigned i = 0; i < ITERATIONS; ++i)
        {
#ifdef FASTFORMAT_USE_WIDE_STRINGS
            std::wstringstream   ss;
#else /* ? FASTFORMAT_USE_WIDE_STRINGS */
            std::stringstream   ss;
#endif /* FASTFORMAT_USE_WIDE_STRINGS */

            ss << TX("My name is ") << forename << TX(" ") << surname << TX("; I am ") << age << TX(" years old; call me ") << forename;

#ifdef FASTFORMAT_USE_WIDE_STRINGS
            std::wstring        s   =   ss.str();
#else /* ? FASTFORMAT_USE_WIDE_STRINGS */
            std::string         s   =   ss.str();
#endif /* FASTFORMAT_USE_WIDE_STRINGS */

#ifdef SHOW_FIRST_RESULT
(0 == i) && fprintf(stderr, "%.*s\n", int(s.size()), s.c_str());
#endif

            length += s.size();
        }}
        counter.stop();

        tm_IOStreams = counter.get_microseconds();

        if (verbosity >= 3 &&
            j == WARMUPS - 1)
        {
            ::fprintf(stdout, "IOStreams:  %lu\t(%lu)\n", (unsigned long)tm_IOStreams, (unsigned long)length);
        }
    }}


#ifdef FASTFORMAT_PERFTEST_USE_BOOST
    // Boost.Format

    { for (unsigned j = 0; j < WARMUPS; ++j)
    {
        length = 0;
        counter.start();
        { for (unsigned i = 0; i < ITERATIONS; ++i)
        {
            std::string s = boost::str(boost::format(TX("My name is %1% %2%; I am %3% years old; call me %1%")) % forename % surname % age);

#ifdef SHOW_FIRST_RESULT
(0 == i) && fprintf(stderr, "%.*s\n", int(s.size()), s.c_str());
#endif

            length += s.size();
        }}
        counter.stop();

        tm_Boost = counter.get_microseconds();

        if (verbosity >= 3 &&
            j == WARMUPS - 1)
        {
            ::fprintf(stdout, "Boost.Format: %lu\t(%lu)\n", (unsigned long)tm_Boost, (unsigned long)length);
        }
    }}
#endif /* FASTFORMAT_PERFTEST_USE_BOOST */


#ifdef FASTFORMAT_PERFTEST_USE_LOKI
    // Loki.SafeFormat

    { for (unsigned j = 0; j < WARMUPS; ++j)
    {
        length = 0;
        counter.start();
        { for (unsigned i = 0; i < ITERATIONS; ++i)
        {
            std::string s;

            Loki::SPrintf(s, TX("My name is %s %s; I am %d years old; call me %s"))(forename)(surname)(age)(forename);

#ifdef SHOW_FIRST_RESULT
(0 == i) && fprintf(stderr, "%.*s\n", int(s.size()), s.c_str());
#endif

            length += s.size();
        }}
        counter.stop();

        tm_Loki = counter.get_microseconds();

        if (verbosity >= 3 &&
            j == WARMUPS - 1)
        {
            ::fprintf(stdout, "Loki.SafeFormat: %lu\t(%lu)\n", (unsigned long)tm_Loki, (unsigned long)length);
        }
    }}
#endif /* FASTFORMAT_PERFTEST_USE_LOKI */


#ifdef FASTFORMAT_INCL_FASTFORMAT_SINK_HPP_CSTRING
    // CString::Format()

    { for (unsigned j = 0; j < WARMUPS; ++j)
    {
        length = 0;
        counter.start();
        { for (unsigned i = 0; i < ITERATIONS; ++i)
        {
            CString s;

            s.Format(   TX("My name is %s %s; I am %d years old; call me %s")
                    ,   forename.c_str(), surname, age, forename.c_str());

#ifdef SHOW_FIRST_RESULT
(0 == i) && fprintf(stderr, "%.*s\n", int(s.GetLength()), static_cast<char const*>(s));
#endif

            length += size_t(s.GetLength());
        }}
        counter.stop();

        tm_CString_Format = counter.get_microseconds();

        if (verbosity >= 3 &&
            j == WARMUPS - 1)
        {
            ::fprintf(stdout, "CString::Format(): %lu\t(%lu)\n", (unsigned long)tm_CString_Format, (unsigned long)length);
        }
    }}


#endif /* FASTFORMAT_INCL_FASTFORMAT_SINK_HPP_CSTRING */
    // sprintf()

    { for (unsigned j = 0; j < WARMUPS; ++j)
    {
        length = 0;
        counter.start();
        { for (unsigned i = 0; i < ITERATIONS; ++i)
        {
            size_t                      total   = 39 // the literal part(s)
                                                + 2 * forename.size()
#ifdef FASTFORMAT_USE_WIDE_STRINGS
                                                + ::wcslen(surname)
#else /* ? FASTFORMAT_USE_WIDE_STRINGS */
                                                + ::strlen(surname)
#endif /* FASTFORMAT_USE_WIDE_STRINGS */
                                                + 21 // enough for any number
                                                + 1; // for the nul-terminator
            stlsoft::auto_buffer<fastformat::ff_char_t, 8>  buff(total);

#ifdef FASTFORMAT_USE_WIDE_STRINGS
            int r = ::wsprintf(&buff[0], TX("My name is %s %s; I am %d years old; call me %s")
#else /* ? FASTFORMAT_USE_WIDE_STRINGS */
            int r = ::sprintf(&buff[0], "My name is %s %s; I am %d years old; call me %s"
#endif /* FASTFORMAT_USE_WIDE_STRINGS */
                            , forename.c_str(), surname, age, forename.c_str());

            // TODO: handle r < 0

#ifdef FASTFORMAT_USE_WIDE_STRINGS
            std::wstring    s(buff.data(), size_t(r));
#else /* ? FASTFORMAT_USE_WIDE_STRINGS */
            std::string     s(buff.data(), size_t(r));
#endif /* FASTFORMAT_USE_WIDE_STRINGS */

#ifdef SHOW_FIRST_RESULT
(0 == i) && fprintf(stderr, "%.*s\n", int(s.size()), s.c_str());
#endif

            length += s.size();
        }}
        counter.stop();

        tm_Streams = counter.get_microseconds();

        if (verbosity >= 3 &&
            j == WARMUPS - 1)
        {
            ::fprintf(stdout, "sprintf():  %lu\t(%lu)\n", (unsigned long)tm_Streams, (unsigned long)length);
        }
    }}


    // FastFormat.Format

    { for (unsigned j = 0; j < WARMUPS; ++j)
    {
        length = 0;
        counter.start();
        { for (unsigned i = 0; i < ITERATIONS; ++i)
        {
#ifdef FASTFORMAT_USE_WIDE_STRINGS
            std::wstring    s;
#else /* ? FASTFORMAT_USE_WIDE_STRINGS */
            std::string     s;
#endif /* FASTFORMAT_USE_WIDE_STRINGS */

            fastformat::fmt(s, TX("My name is {0} {1}; I am {2} years old; call me {0}")
                          , forename, surname, age);

#ifdef SHOW_FIRST_RESULT
(0 == i) && fprintf(stderr, "%.*s\n", int(s.size()), s.c_str());
#endif

            length += s.size();
        }}
        counter.stop();

        tm_FF_Format = counter.get_microseconds();

        if (verbosity >= 3 &&
            j == WARMUPS - 1)
        {
            ::fprintf(stdout, "FastFormat.Format: %lu\t(%lu)\n", (unsigned long)tm_FF_Format, (unsigned long)length);
        }
    }}


    // FastFormat.Write

    { for (unsigned j = 0; j < WARMUPS; ++j)
    {
        length = 0;
        counter.start();
        { for (unsigned i = 0; i < ITERATIONS; ++i)
        {
#ifdef FASTFORMAT_USE_WIDE_STRINGS
            std::wstring    s;
#else /* ? FASTFORMAT_USE_WIDE_STRINGS */
            std::string     s;
#endif /* FASTFORMAT_USE_WIDE_STRINGS */

        fastformat::write(s, TX("My name is "), forename, TX(" "), surname, TX("; I am "), age, TX(" years old; call me "), forename);

#ifdef SHOW_FIRST_RESULT
(0 == i) && fprintf(stderr, "%.*s\n", int(s.size()), s.c_str());
#endif

            length += s.size();
        }}
        counter.stop();

        tm_FF_Write = counter.get_microseconds();

        if (verbosity >= 3 &&
            j == WARMUPS - 1)
        {
            ::fprintf(stdout, "FastFormat.Write: %lu\t(%lu)\n", (unsigned long)tm_FF_Write, (unsigned long)length);
        }
    }}

    STLSOFT_SUPPRESS_UNUSED(length);

    std::string     fmt1;
    std::string     fmt2;

    fastformat::ignore_unreferenced_arguments_scope scoper;

    switch (verbosity)
    {
    case 0:

        // no output
        break;
    case 1:

        fmt1 = "";
        fmt1 += "S:FF.F:\t{0}";
        fmt1 += "\tIOS:FF.F:\t{1}";
        fmt1 += "\tFF.W:FF.F:\t{3}";
#ifdef FASTFORMAT_PERFTEST_USE_BOOST
        fmt1 += "\tB.F:FF.F:\t{4}";
#endif /* FASTFORMAT_PERFTEST_USE_BOOST */
#ifdef FASTFORMAT_PERFTEST_USE_LOKI
        fmt1 += "\tL.SF:FF.F:\t{5}";
#endif /* FASTFORMAT_PERFTEST_USE_LOKI */
#ifdef FASTFORMAT_INCL_FASTFORMAT_SINK_HPP_CSTRING
        fmt1 += "\tMFC.F:FF.F:\t{2}";
#endif /* FASTFORMAT_INCL_FASTFORMAT_SINK_HPP_CSTRING */
        fastformat::fmtln(  std::cout, fmt1
                        ,   double(tm_Streams) / double(tm_FF_Format)
                        ,   double(tm_IOStreams) / double(tm_FF_Format)
                        ,   double(tm_CString_Format) / double(tm_FF_Format)
                        ,   double(tm_FF_Write) / double(tm_FF_Format)
                        ,   double(tm_Boost) / double(tm_FF_Format)
                        ,   double(tm_Loki) / double(tm_FF_Format));
        fmt1 = "";
        fmt1 += "S:FF.W:\t{0}";
        fmt1 += "\tIOS:FF.W:\t{1}";
        fmt1 += "\tFF.F:FF.W:\t{2}";
#ifdef FASTFORMAT_PERFTEST_USE_BOOST
        fmt1 += "\tB.F:FF.W:\t{3}";
#endif /* FASTFORMAT_PERFTEST_USE_BOOST */
#ifdef FASTFORMAT_PERFTEST_USE_LOKI
        fmt1 += "\tL.SF:FF.W:\t{3}";
#endif /* FASTFORMAT_PERFTEST_USE_LOKI */
#ifdef FASTFORMAT_INCL_FASTFORMAT_SINK_HPP_CSTRING
        fmt1 += "\tMFC.F:FF.W:\t{4}";
#endif /* FASTFORMAT_INCL_FASTFORMAT_SINK_HPP_CSTRING */
        fastformat::fmtln(  std::cout, fmt1
                        ,   double(tm_Streams) / double(tm_FF_Write)
                        ,   double(tm_IOStreams) / double(tm_FF_Write)
                        ,   double(tm_CString_Format) / double(tm_FF_Write)
                        ,   double(tm_FF_Format) / double(tm_FF_Write)
                        ,   double(tm_Boost) / double(tm_FF_Write)
                        ,   double(tm_Loki) / double(tm_FF_Write));
        break;
    case 2:

        fastformat::fmtln(std::cout, "{0}\tFastFormat.Format\tFastFormat.Write", TestId);
        fastformat::fmtln(std::cout, "Streams\t{0}\t{1}", double(tm_Streams) / double(tm_FF_Format), double(tm_Streams) / double(tm_FF_Write));
        fastformat::fmtln(std::cout, "IOStreams\t{0}\t{1}", double(tm_IOStreams) / double(tm_FF_Format), double(tm_IOStreams) / double(tm_FF_Write));
#ifdef FASTFORMAT_INCL_FASTFORMAT_SINK_HPP_CSTRING
        fastformat::fmtln(std::cout, "CString::Format\t{0}\t{1}", double(tm_CString_Format) / double(tm_FF_Format), double(tm_CString_Format) / double(tm_FF_Write));
#else /* ? FASTFORMAT_INCL_FASTFORMAT_SINK_HPP_CSTRING */
        fastformat::writeln(std::cout, "");
#endif /* FASTFORMAT_INCL_FASTFORMAT_SINK_HPP_CSTRING */
#ifdef FASTFORMAT_PERFTEST_USE_BOOST
        fastformat::fmtln(std::cout, "Boost.Format\t{0}\t{1}", double(tm_Boost) / double(tm_FF_Format), double(tm_Boost) / double(tm_FF_Write));
#else /* ? FASTFORMAT_PERFTEST_USE_BOOST */
        fastformat::writeln(std::cout, "");
#endif /* FASTFORMAT_PERFTEST_USE_BOOST */
#ifdef FASTFORMAT_PERFTEST_USE_LOKI
        fastformat::fmtln(std::cout, "Loki.SafeFormat\t{0}\t{1}", double(tm_Loki) / double(tm_FF_Format), double(tm_Loki) / double(tm_FF_Write));
#else /* ? FASTFORMAT_PERFTEST_USE_LOKI */
        fastformat::writeln(std::cout, "");
#endif /* FASTFORMAT_PERFTEST_USE_LOKI */
        fastformat::fmtln(std::cout, "FastFormat.Format\t{0}\t{1}", "", double(tm_FF_Format) / double(tm_FF_Write));
        fastformat::fmtln(std::cout, "FastFormat.Write\t{0}\t{1}", double(tm_FF_Write) / double(tm_FF_Format), "");
        break;
    case 3:

        ::puts("");
        ::fprintf(stdout, "sprintf():FastFormat.Format:         \t%2.04g\n", double(tm_Streams) / double(tm_FF_Format));
        ::fprintf(stdout, "IOStreams:FastFormat.Format:         \t%2.04g\n", double(tm_IOStreams) / double(tm_FF_Format));
#ifdef FASTFORMAT_INCL_FASTFORMAT_SINK_HPP_CSTRING
        ::fprintf(stdout, "CString::Format():FastFormat.Format: \t%2.04g\n", double(tm_CString_Format) / double(tm_FF_Format));
#endif /* FASTFORMAT_INCL_FASTFORMAT_SINK_HPP_CSTRING */
#ifdef FASTFORMAT_PERFTEST_USE_BOOST
        ::fprintf(stdout, "Boost.Format:FastFormat.Format:      \t%2.04g\n", double(tm_Boost) / double(tm_FF_Format));
#endif /* FASTFORMAT_PERFTEST_USE_BOOST */
#ifdef FASTFORMAT_PERFTEST_USE_LOKI
        ::fprintf(stdout, "Loki.SafeFormat:FastFormat.Format:   \t%2.04g\n", double(tm_Loki) / double(tm_FF_Format));
#endif /* FASTFORMAT_PERFTEST_USE_LOKI */
        ::puts("");
        ::fprintf(stdout, "sprintf():FastFormat.Write:          \t%2.04g\n", double(tm_Streams) / double(tm_FF_Write));
        ::fprintf(stdout, "IOStreams:FastFormat.Write:          \t%2.04g\n", double(tm_IOStreams) / double(tm_FF_Write));
#ifdef FASTFORMAT_INCL_FASTFORMAT_SINK_HPP_CSTRING
        ::fprintf(stdout, "CString::Format():FastFormat.Write:  \t%2.04g\n", double(tm_CString_Format) / double(tm_FF_Write));
#endif /* FASTFORMAT_INCL_FASTFORMAT_SINK_HPP_CSTRING */
#ifdef FASTFORMAT_PERFTEST_USE_BOOST
        ::fprintf(stdout, "Boost.Format:FastFormat.Write:       \t%2.04g\n", double(tm_Boost) / double(tm_FF_Write));
#endif /* FASTFORMAT_PERFTEST_USE_BOOST */
#ifdef FASTFORMAT_PERFTEST_USE_LOKI
        ::fprintf(stdout, "Loki.SafeFormat:FastFormat.Write:    \t%2.04g\n", double(tm_Loki) / double(tm_FF_Write));
#endif /* FASTFORMAT_PERFTEST_USE_LOKI */
        ::fprintf(stdout, "\n");
        ::fprintf(stdout, "FastFormat.Format:FastFormat.Write:  \t%2.04g\n", double(tm_FF_Format) / double(tm_FF_Write));
        break;
    }

    return EXIT_SUCCESS;
}

int main(int argc, char *argv[])
{
    int             res;

#if defined(_MSC_VER) && \
    defined(_DEBUG)
    _CrtMemState    memState;
#endif /* _MSC_VER && _MSC_VER */

#if defined(_MSC_VER) && \
    defined(_DEBUG)
    _CrtMemCheckpoint(&memState);
#endif /* _MSC_VER && _MSC_VER */

#if 0
    { for (size_t i = 0; i < 0xffffffff; ++i){} }
#endif /* 0 */

    try
    {
#if defined(_DEBUG) || \
    defined(__SYNSOFT_DBS_DEBUG)
        puts("test.performance.overload.ex.1: " STLSOFT_COMPILER_LABEL_STRING);
#endif /* debug */

        if (fastformat::init() < 0)
        {
            fprintf(stderr, "Failed to initialise FastFormat\n");

            res = EXIT_FAILURE;
        }
        else
        {
            res = main_(argc, argv);

            fastformat::uninit();
        }
    }
    catch (std::exception& x)
    {
        fprintf(stderr, "Unhandled error: %s\n", x.what());

        res = EXIT_FAILURE;
    }
    catch (...)
    {
        fprintf(stderr, "Unhandled unknown error\n");

        res = EXIT_FAILURE;
    }

#if defined(_MSC_VER) && \
    defined(_DEBUG)
    _CrtMemDumpAllObjectsSince(&memState);
#endif /* _MSC_VER) && _DEBUG */

    return res;
}


/* ///////////////////////////// end of file //////////////////////////// */

