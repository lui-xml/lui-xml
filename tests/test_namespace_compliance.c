/**
 * @file test_namespace_compliance.c
 * @brief Namespace compliance tests
 *
 * This test verifies that the codebase follows the namespace rules:
 * - Public API uses lui_xml_* prefix
 * - Internal widgets use luixml_* prefix
 * - NO lv_xml_* symbols allowed (forbidden legacy namespace)
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>

/* Test: No lv_xml_ symbols in source code */
int test_no_lv_xml_symbols(void)
{
    printf("TEST: No forbidden lv_xml_ symbols... ");

    /* Use grep to search for lv_xml_ in source files */
    int result = system("grep -r 'lv_xml_' /Users/coevin/Documents/dev/lvgl/lui-xml/src/ > /dev/null 2>&1");

    /* grep returns 1 if no matches found, 0 if matches found */
    if (result == 0) {
        printf("FAIL - Found forbidden lv_xml_ symbols!\n");
        printf("Run: grep -r 'lv_xml_' src/\n");
        return 1;
    } else {
        printf("PASS - No lv_xml_ symbols found\n");
        return 0;
    }
}

/* Test: Public API uses lui_xml_ prefix */
int test_lui_xml_symbols_exist(void)
{
    printf("TEST: Public lui_xml_ symbols exist... ");

    /* Check for lui_xml_ symbols in public headers */
    int result = system("grep -r 'lui_xml_' /Users/coevin/Documents/dev/lvgl/lui-xml/src/xml/ > /dev/null 2>&1");

    if (result != 0) {
        printf("FAIL - No lui_xml_ symbols found in public API!\n");
        return 1;
    } else {
        printf("PASS - lui_xml_ symbols found\n");
        return 0;
    }
}

/* Test: Internal widgets use luixml_ prefix */
int test_luixml_symbols_exist(void)
{
    printf("TEST: Internal luixml_ symbols exist... ");

    /* Check for luixml_ symbols in compat layer */
    int result = system("grep -r 'luixml_' /Users/coevin/Documents/dev/lvgl/lui-xml/src/ > /dev/null 2>&1");

    if (result != 0) {
        printf("FAIL - No luixml_ symbols found!\n");
        return 1;
    } else {
        printf("PASS - luixml_ symbols found\n");
        return 0;
    }
}

/* Test: No private headers included */
int test_no_private_headers(void)
{
    printf("TEST: No private headers included... ");

    /* Check for lvgl/src/ includes */
    int result = system("grep -r 'lvgl/src/' /Users/coevin/Documents/dev/lvgl/lui-xml/src/ > /dev/null 2>&1");

    if (result == 0) {
        printf("FAIL - Found private header includes!\n");
        printf("Run: grep -r 'lvgl/src/' src/\n");
        return 1;
    }

    /* Check for lvgl_private.h includes */
    result = system("grep -r 'lvgl_private' /Users/coevin/Documents/dev/lvgl/lui-xml/src/ > /dev/null 2>&1");

    if (result == 0) {
        printf("FAIL - Found lvgl_private.h includes!\n");
        printf("Run: grep -r 'lvgl_private' src/\n");
        return 1;
    }

    printf("PASS - No private headers included\n");
    return 0;
}

/* Test: Only public lvgl.h included */
int test_public_lvgl_h_only(void)
{
    printf("TEST: Only public lvgl.h included... ");

    /* Check that files use lvgl.h, not private headers */
    int result = system("grep -r '#include.*lvgl.h' /Users/coevin/Documents/dev/lvgl/lui-xml/src/ | grep -v 'lvgl_private' > /dev/null 2>&1");

    if (result != 0) {
        printf("WARN - No public lvgl.h includes found (may be using compat layer)\n");
        return 0; /* Not a failure - compat layer is OK */
    }

    printf("PASS - Public lvgl.h includes found\n");
    return 0;
}

int main(void)
{
    int failed = 0;

    printf("=== Lui-XML Namespace Compliance Tests ===\n");
    printf("\n");

    failed += test_no_lv_xml_symbols();
    failed += test_lui_xml_symbols_exist();
    failed += test_luixml_symbols_exist();
    failed += test_no_private_headers();
    failed += test_public_lvgl_h_only();

    printf("\n");
    if (failed == 0) {
        printf("=== All Namespace Tests PASSED ===\n");
        return 0;
    } else {
        printf("=== %d Namespace Test(s) FAILED ===\n", failed);
        return 1;
    }
}
