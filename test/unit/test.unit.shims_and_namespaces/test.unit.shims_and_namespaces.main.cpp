/* /////////////////////////////////////////////////////////////////////////
 * File:    test.unit.shims_and_namespaces.main.cpp
 *
 * Purpose: Main implementation file for the test.unit.shims_and_namespaces project.
 *
 * Created: 11th November 2013
 * Updated: 11th August 2024
 *
 * ////////////////////////////////////////////////////////////////////// */



/* /////////////////////////////////////////////////////////////////////////
 * includes
 */

/* xTests Header Files */
#include <xtests/xtests.h>

/* FastFormat header files */
#include <fastformat/fastformat.h>

/* STLSoft Header Files */
#include <stlsoft/stlsoft.h>

/* Standard C Header Files */
#include <stdlib.h>

/* /////////////////////////////////////////////////////////////////////////
 * forward declarations
 */

extern "C++"
{

    namespace with_fastformat_namespace
    {
        void test_slice_empty_and_null(void);
        void test_slice_empty_and_non_null(void);
        void test_slice_short_full_string(void);
        void test_slice_short_partial_string(void);

        void test_parse_code_1(void);
        void test_parse_code_2(void);
        void test_parse_code_3(void);
        void test_replacement_code_1(void);
        void test_replacement_code_2(void);
        void test_replacement_code_3(void);

    } /* namespace with_fastformat_namespace */

    namespace without_fastformat_namespace
    {
        void test_slice_empty_and_null(void);
        void test_slice_empty_and_non_null(void);
        void test_slice_short_full_string(void);
        void test_slice_short_partial_string(void);

        void test_parse_code_1(void);
        void test_parse_code_2(void);
        void test_parse_code_3(void);
        void test_replacement_code_1(void);
        void test_replacement_code_2(void);
        void test_replacement_code_3(void);

    } /* namespace without_fastformat_namespace */

    namespace without_stlsoft_namespace
    {
        void test_slice_empty_and_null(void);
        void test_slice_empty_and_non_null(void);
        void test_slice_short_full_string(void);
        void test_slice_short_partial_string(void);

        void test_parse_code_1(void);
        void test_parse_code_2(void);
        void test_parse_code_3(void);
        void test_replacement_code_1(void);
        void test_replacement_code_2(void);
        void test_replacement_code_3(void);

    } /* namespace without_stlsoft_namespace */

    namespace without_either_namespace
    {
        void test_slice_empty_and_null(void);
        void test_slice_empty_and_non_null(void);
        void test_slice_short_full_string(void);
        void test_slice_short_partial_string(void);

        void test_parse_code_1(void);
        void test_parse_code_2(void);
        void test_parse_code_3(void);
        void test_replacement_code_1(void);
        void test_replacement_code_2(void);
        void test_replacement_code_3(void);

    } /* namespace without_either_namespace */


} // extern "C++"

/* /////////////////////////////////////////////////////////////////////////
 * main()
 */

int main(int argc, char **argv)
{
    int retCode = EXIT_SUCCESS;
    int verbosity = 2;

    XTESTS_COMMANDLINE_PARSEVERBOSITY(argc, argv, &verbosity);

    int const executionFlags    =   0
                                |   xtests::c::xtestsReportOnlyNonEmptyCases
                                ;

    if (XTESTS_START_RUNNER_WITH_FLAGS("test.unit.shims_and_namespaces", verbosity, executionFlags))
    {
        // with_fastformat_namespace

        XTESTS_RUN_CASE(with_fastformat_namespace::test_slice_empty_and_null);
        XTESTS_RUN_CASE(with_fastformat_namespace::test_slice_empty_and_non_null);
        XTESTS_RUN_CASE(with_fastformat_namespace::test_slice_short_full_string);
        XTESTS_RUN_CASE(with_fastformat_namespace::test_slice_short_partial_string);

        XTESTS_RUN_CASE(with_fastformat_namespace::test_parse_code_1);
        XTESTS_RUN_CASE(with_fastformat_namespace::test_parse_code_2);
        XTESTS_RUN_CASE(with_fastformat_namespace::test_parse_code_3);
        XTESTS_RUN_CASE(with_fastformat_namespace::test_replacement_code_1);
        XTESTS_RUN_CASE(with_fastformat_namespace::test_replacement_code_2);
        XTESTS_RUN_CASE(with_fastformat_namespace::test_replacement_code_3);

        // without_fastformat_namespace

        XTESTS_RUN_CASE(without_fastformat_namespace::test_slice_empty_and_null);
        XTESTS_RUN_CASE(without_fastformat_namespace::test_slice_empty_and_non_null);
        XTESTS_RUN_CASE(without_fastformat_namespace::test_slice_short_full_string);
        XTESTS_RUN_CASE(without_fastformat_namespace::test_slice_short_partial_string);

        XTESTS_RUN_CASE(without_fastformat_namespace::test_parse_code_1);
        XTESTS_RUN_CASE(without_fastformat_namespace::test_parse_code_2);
        XTESTS_RUN_CASE(without_fastformat_namespace::test_parse_code_3);
        XTESTS_RUN_CASE(without_fastformat_namespace::test_replacement_code_1);
        XTESTS_RUN_CASE(without_fastformat_namespace::test_replacement_code_2);
        XTESTS_RUN_CASE(without_fastformat_namespace::test_replacement_code_3);

        // without_stlsoft_namespace

        XTESTS_RUN_CASE(without_stlsoft_namespace::test_slice_empty_and_null);
        XTESTS_RUN_CASE(without_stlsoft_namespace::test_slice_empty_and_non_null);
        XTESTS_RUN_CASE(without_stlsoft_namespace::test_slice_short_full_string);
        XTESTS_RUN_CASE(without_stlsoft_namespace::test_slice_short_partial_string);

        XTESTS_RUN_CASE(without_stlsoft_namespace::test_parse_code_1);
        XTESTS_RUN_CASE(without_stlsoft_namespace::test_parse_code_2);
        XTESTS_RUN_CASE(without_stlsoft_namespace::test_parse_code_3);
        XTESTS_RUN_CASE(without_stlsoft_namespace::test_replacement_code_1);
        XTESTS_RUN_CASE(without_stlsoft_namespace::test_replacement_code_2);
        XTESTS_RUN_CASE(without_stlsoft_namespace::test_replacement_code_3);

        // without_either_namespace

        XTESTS_RUN_CASE(without_either_namespace::test_slice_empty_and_null);
        XTESTS_RUN_CASE(without_either_namespace::test_slice_empty_and_non_null);
        XTESTS_RUN_CASE(without_either_namespace::test_slice_short_full_string);
        XTESTS_RUN_CASE(without_either_namespace::test_slice_short_partial_string);

        XTESTS_RUN_CASE(without_either_namespace::test_parse_code_1);
        XTESTS_RUN_CASE(without_either_namespace::test_parse_code_2);
        XTESTS_RUN_CASE(without_either_namespace::test_parse_code_3);
        XTESTS_RUN_CASE(without_either_namespace::test_replacement_code_1);
        XTESTS_RUN_CASE(without_either_namespace::test_replacement_code_2);
        XTESTS_RUN_CASE(without_either_namespace::test_replacement_code_3);


        XTESTS_PRINT_RESULTS();

        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }

    return retCode;
}

/* ///////////////////////////// end of file //////////////////////////// */

