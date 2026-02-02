/**
 * @file luixml_compat.c
 * @brief Lui-XML Compatibility Layer Implementation
 *
 * Implementation of compatibility shims for LVGL v9.x
 */

#include "luixml_compat.h"

/*
 * Button Helper Functions
 * =======================
 */

/**
 * Set button text
 *
 * In LVGL 9.x, buttons don't have a direct set_text function.
 * We need to find or create a label child and set its text.
 *
 * @param btn Button object
 * @param text Text to set
 */
void luixml_btn_set_text(lv_obj_t *btn, const char *text)
{
    if (btn == NULL || text == NULL) {
        return;
    }

    /* Try to find existing label child */
    lv_obj_t *label = lv_obj_get_child(btn, 0);
    if (label == NULL || !lv_obj_check_type(label, &lv_label_class)) {
        /* No label found, create one */
        label = lv_label_create(btn);
        if (label == NULL) {
            return; /* Failed to create label */
        }
        lv_obj_center(label);
    }

    lv_label_set_text(label, text);
}

/**
 * Get button text
 *
 * @param btn Button object
 * @return Button text, or NULL if not found
 */
const char *luixml_btn_get_text(lv_obj_t *btn)
{
    if (btn == NULL) {
        return NULL;
    }

    /* Try to find label child */
    lv_obj_t *label = lv_obj_get_child(btn, 0);
    if (label != NULL && lv_obj_check_type(label, &lv_label_class)) {
        return lv_label_get_text(label);
    }

    return NULL;
}
