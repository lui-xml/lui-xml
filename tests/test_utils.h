/**
 * @file test_utils.h
 * @brief Test utilities for Lui-XML test suite
 */

#ifndef TEST_UTILS_H
#define TEST_UTILS_H

#include "lvgl.h"

/**
 * Initialize LVGL display for testing
 *
 * Creates a display with a driver that doesn't require actual hardware.
 * This is used for unit tests that need LVGL initialized.
 *
 * @return 0 on success, -1 on failure
 */
int test_lvgl_init(void);

/**
 * Cleanup LVGL display
 *
 * Destroys the display created by test_lvgl_init().
 */
void test_lvgl_deinit(void);

/**
 * Get the test display
 *
 * Returns the display handle created by test_lvgl_init().
 *
 * @return Display pointer, or NULL if not initialized
 */
lv_display_t* test_get_display(void);

/**
 * Create a test screen
 *
 * Creates a screen object for testing.
 *
 * @return Screen object, or NULL on failure
 */
lv_obj_t* test_create_screen(void);

/**
 * Cleanup test screen
 *
 * @param screen Screen object to destroy
 */
void test_cleanup_screen(lv_obj_t *screen);

#endif /* TEST_UTILS_H */
