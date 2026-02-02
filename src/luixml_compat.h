/**
 * @file luixml_compat.h
 * @brief Lui-XML Compatibility Layer for LVGL
 *
 * This header provides version detection and compatibility shims for LVGL.
 * It abstracts LVGL internal API differences to enable forward compatibility.
 *
 * Namespace: luixml_* (internal compatibility layer)
 * Required LVGL version: v9.1.0
 */

#ifndef LUIXML_COMPAT_H
#define LUIXML_COMPAT_H

#include "lvgl.h"

/*
 * Version Detection and Validation
 * =================================
 */

/* LVGL version macros from lvgl.h */
#ifndef LVGL_VERSION_MAJOR
    #error "LVGL version macros not found. Cannot determine LVGL version."
#endif

/* Compile-time version check for LVGL v9.0+ */
#if (LVGL_VERSION_MAJOR != 9)
    #error "Lui-XML requires LVGL v9.x. "\
           "Detected LVGL v" LVGL_VERSION_STRING ". "\
           "Please use LVGL v9.0 or later."
#endif

#if (LVGL_VERSION_MINOR < 0)
    #error "Lui-XML requires LVGL v9.0 or later. "\
           "Detected LVGL v" LVGL_VERSION_STRING "."
#endif

/* Tested versions warning */
#if (LVGL_VERSION_MINOR > 5)
    #warning "Lui-XML has been tested with LVGL v9.0-v9.5. "\
             "Detected LVGL v" LVGL_VERSION_STRING ". "\
             "Compatibility with newer versions is not guaranteed."
#endif

/*
 * Compatibility Shims - Object Creation
 * =====================================
 * These shims wrap LVGL object creation functions.
 * They provide a stable API for Lui-XML widget parsers.
 */

/**
 * Create an LVGL object
 * @param parent Parent object (NULL for screen)
 * @return Created object
 */
static inline lv_obj_t* luixml_obj_create(lv_obj_t *parent)
{
    return lv_obj_create(parent);
}

/**
 * Create an LVGL button
 * @param parent Parent object
 * @return Created button object
 */
static inline lv_obj_t* luixml_btn_create(lv_obj_t *parent)
{
    return lv_button_create(parent);
}

/**
 * Create an LVGL label
 * @param parent Parent object
 * @return Created label object
 */
static inline lv_obj_t* luixml_label_create(lv_obj_t *parent)
{
    return lv_label_create(parent);
}

/**
 * Create an LVGL image
 * @param parent Parent object
 * @return Created image object
 */
static inline lv_obj_t* luixml_image_create(lv_obj_t *parent)
{
    return lv_image_create(parent);
}

/**
 * Create an LVGL arc
 * @param parent Parent object
 * @return Created arc object
 */
static inline lv_obj_t* luixml_arc_create(lv_obj_t *parent)
{
    return lv_arc_create(parent);
}

/**
 * Create an LVGL bar
 * @param parent Parent object
 * @return Created bar object
 */
static inline lv_obj_t* luixml_bar_create(lv_obj_t *parent)
{
    return lv_bar_create(parent);
}

/**
 * Create an LVGL slider
 * @param parent Parent object
 * @return Created slider object
 */
static inline lv_obj_t* luixml_slider_create(lv_obj_t *parent)
{
    return lv_slider_create(parent);
}

/**
 * Create an LVGL checkbox
 * @param parent Parent object
 * @return Created checkbox object
 */
static inline lv_obj_t* luixml_checkbox_create(lv_obj_t *parent)
{
    return lv_checkbox_create(parent);
}

/**
 * Create an LVGL dropdown
 * @param parent Parent object
 * @return Created dropdown object
 */
static inline lv_obj_t* luixml_dropdown_create(lv_obj_t *parent)
{
    return lv_dropdown_create(parent);
}

/**
 * Create an LVGL roller
 * @param parent Parent object
 * @return Created roller object
 */
static inline lv_obj_t* luixml_roller_create(lv_obj_t *parent)
{
    return lv_roller_create(parent);
}

/**
 * Create an LVGL switch
 * @param parent Parent object
 * @return Created switch object
 */
static inline lv_obj_t* luixml_switch_create(lv_obj_t *parent)
{
    return lv_switch_create(parent);
}

/**
 * Create an LVGL textarea
 * @param parent Parent object
 * @return Created textarea object
 */
static inline lv_obj_t* luixml_textarea_create(lv_obj_t *parent)
{
    return lv_textarea_create(parent);
}

/**
 * Create an LVGL keyboard
 * @param parent Parent object
 * @return Created keyboard object
 */
static inline lv_obj_t* luixml_keyboard_create(lv_obj_t *parent)
{
    return lv_keyboard_create(parent);
}

/**
 * Create an LVGL button matrix
 * @param parent Parent object
 * @return Created button matrix object
 */
static inline lv_obj_t* luixml_buttonmatrix_create(lv_obj_t *parent)
{
    return lv_buttonmatrix_create(parent);
}

/**
 * Create an LVGL chart
 * @param parent Parent object
 * @return Created chart object
 */
static inline lv_obj_t* luixml_chart_create(lv_obj_t *parent)
{
    return lv_chart_create(parent);
}

/**
 * Create an LVGL calendar
 * @param parent Parent object
 * @return Created calendar object
 */
static inline lv_obj_t* luixml_calendar_create(lv_obj_t *parent)
{
    return lv_calendar_create(parent);
}

/**
 * Create an LVGL canvas
 * @param parent Parent object
 * @return Created canvas object
 */
static inline lv_obj_t* luixml_canvas_create(lv_obj_t *parent)
{
    return lv_canvas_create(parent);
}

/**
 * Create an LVGL tabview
 * @param parent Parent object
 * @return Created tabview object
 */
static inline lv_obj_t* luixml_tabview_create(lv_obj_t *parent)
{
    return lv_tabview_create(parent);
}

/**
 * Create an LVGL spinbox
 * @param parent Parent object
 * @return Created spinbox object
 */
static inline lv_obj_t* luixml_spinbox_create(lv_obj_t *parent)
{
    return lv_spinbox_create(parent);
}

/**
 * Create an LVGL spinner
 * @param parent Parent object
 * @return Created spinner object
 */
static inline lv_obj_t* luixml_spinner_create(lv_obj_t *parent)
{
    return lv_spinner_create(parent);
}

/**
 * Create an LVGL scale
 * @param parent Parent object
 * @return Created scale object
 */
static inline lv_obj_t* luixml_scale_create(lv_obj_t *parent)
{
    return lv_scale_create(parent);
}

/**
 * Create an LVGL table
 * @param parent Parent object
 * @return Created table object
 */
static inline lv_obj_t* luixml_table_create(lv_obj_t *parent)
{
    return lv_table_create(parent);
}

/**
 * Create an LVGL switch (for backward compatibility)
 * @param parent Parent object
 * @return Created switch object
 */
static inline lv_obj_t* luixml_switch_create_obj(lv_obj_t *parent)
{
    return lv_switch_create(parent);
}

/**
 * Create an LVGL image button
 * @param parent Parent object
 * @return Created image button object
 */
static inline lv_obj_t* luixml_imagebutton_create(lv_obj_t *parent)
{
    return lv_imagebutton_create(parent);
}

/**
 * Create an LVGL QR code
 * @param parent Parent object
 * @return Created QR code object
 */
static inline lv_obj_t* luixml_qrcode_create(lv_obj_t *parent)
{
    return lv_qrcode_create(parent);
}

/**
 * Create an LVGL span group
 * @param parent Parent object
 * @return Created span group object
 */
static inline lv_obj_t* luixml_spangroup_create(lv_obj_t *parent)
{
    return lv_spangroup_create(parent);
}

/*
 * Compatibility Shims - Property Setting
 * =====================================
 * These shims wrap LVGL property setting functions.
 */

/**
 * Set object position
 * @param obj Object to modify
 * @param x X coordinate
 * @param y Y coordinate
 */
static inline void luixml_obj_set_pos(lv_obj_t *obj, int32_t x, int32_t y)
{
    lv_obj_set_pos(obj, x, y);
}

/**
 * Set object size
 * @param obj Object to modify
 * @param w Width
 * @param h Height
 */
static inline void luixml_obj_set_size(lv_obj_t *obj, int32_t w, int32_t h)
{
    lv_obj_set_size(obj, w, h);
}

/**
 * Set object width
 * @param obj Object to modify
 * @param w Width
 */
static inline void luixml_obj_set_width(lv_obj_t *obj, int32_t w)
{
    lv_obj_set_width(obj, w);
}

/**
 * Set object height
 * @param obj Object to modify
 * @param h Height
 */
static inline void luixml_obj_set_height(lv_obj_t *obj, int32_t h)
{
    lv_obj_set_height(obj, h);
}

/**
 * Set object align
 * @param obj Object to modify
 * @param align Alignment type
 * @param x_ofs X offset
 * @param y_ofs Y offset
 */
static inline void luixml_obj_set_align(lv_obj_t *obj, lv_align_t align, int32_t x_ofs, int32_t y_ofs)
{
    lv_obj_set_align(obj, align);
    if (x_ofs != 0 || y_ofs != 0) {
        lv_obj_set_pos(obj, x_ofs, y_ofs);
    }
}

/**
 * Set object center alignment
 * @param obj Object to modify
 */
static inline void luixml_obj_center(lv_obj_t *obj)
{
    lv_obj_center(obj);
}

/*
 * Button Helper Functions
 * =======================
 * Helper functions for button label manipulation.
 */

/**
 * Set button text
 * @param btn Button object
 * @param text Text to set
 */
void luixml_btn_set_text(lv_obj_t *btn, const char *text);

/**
 * Get button text
 * @param btn Button object
 * @return Button text
 */
const char *luixml_btn_get_text(lv_obj_t *btn);

/*
 * Compatibility Constants
 * =======================
 */

/* Default display and layer access */
#define LUIXML_DISPLAY_GET_DEFAULT() lv_display_get_default()
#define LUIXML_DISPLAY_GET_LAYER_SYS(disp) lv_display_get_layer_sys(disp)

#endif /* LUIXML_COMPAT_H */
