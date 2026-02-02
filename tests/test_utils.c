/**
 * @file test_utils.c
 * @brief Test utilities implementation for Lui-XML test suite
 */

#include "test_utils.h"

#include <stdlib.h>
#include <stdio.h>

/* Static test display */
static lv_display_t *test_display = NULL;
static lv_display_draw_buf_t test_draw_buf;
static lv_color_t test_buf[LV_DISPLAY_RESOLUTION_X * 10];

/**
 * Flush callback for test display
 * This is a no-op since we don't have actual hardware
 */
static void test_display_flush_callback(lv_display_t *display, const lv_area_t *area, uint8_t *px_map)
{
    /* No-op - we don't have actual display hardware in tests */
    lv_display_flush_ready(display);
}

/**
 * Initialize LVGL display for testing
 */
int test_lvgl_init(void)
{
    if (test_display != NULL) {
        /* Already initialized */
        return 0;
    }

    /* Initialize LVGL if not already initialized */
    extern lv_display_t *lv_display_get_next(NULL);
    if (lv_display_get_next(NULL) == NULL) {
        lv_init();
    }

    /* Create a display */
    test_display = lv_display_create(LV_DISPLAY_RESOLUTION_X, LV_DISPLAY_RESOLUTION_Y);
    if (test_display == NULL) {
        fprintf(stderr, "Failed to create test display\n");
        return -1;
    }

    /* Initialize draw buffer */
    lv_display_draw_buf_init(&test_draw_buf, test_buf, NULL, LV_DISPLAY_RESOLUTION_X * 10);

    /* Set display buffer */
    lv_display_set_buffers(test_display, &test_draw_buf, NULL, LV_DISPLAY_RESOLUTION_X * 10, LV_DISPLAY_RENDER_MODE_DIRECT);

    /* Set flush callback */
    lv_display_set_flush_cb(test_display, test_display_flush_callback);

    /* Set default display */
    lv_display_set_default(test_display);

    printf("Test display initialized: %dx%d\n",
           LV_DISPLAY_RESOLUTION_X,
           LV_DISPLAY_RESOLUTION_Y);

    return 0;
}

/**
 * Cleanup LVGL display
 */
void test_lvgl_deinit(void)
{
    if (test_display != NULL) {
        lv_display_delete(test_display);
        test_display = NULL;
    }
}

/**
 * Get the test display
 */
lv_display_t* test_get_display(void)
{
    return test_display;
}

/**
 * Create a test screen
 */
lv_obj_t* test_create_screen(void)
{
    lv_obj_t *screen = lv_obj_create(NULL);
    if (screen == NULL) {
        fprintf(stderr, "Failed to create test screen\n");
        return NULL;
    }

    /* Load the screen */
    lv_screen_load(screen);

    return screen;
}

/**
 * Cleanup test screen
 */
void test_cleanup_screen(lv_obj_t *screen)
{
    if (screen != NULL) {
        lv_obj_delete(screen);
    }
}
