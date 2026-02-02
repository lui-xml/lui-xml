/**
 * @file lv_xml.h
 *
 */

#ifndef LUI_XML_H
#define LUI_XML_H

#ifdef __cplusplus
extern "C" {
#endif

/*********************
 *      INCLUDES
 *********************/
#include "../misc/lv_types.h"

#if LV_USE_XML
#include "../misc/lv_event.h"
#include "../core/lv_observer.h"
#include "lui_xml_test.h"
#include "lui_xml_translation.h"
#include "lui_xml_component.h"
#include "lui_xml_widget.h"
#include "lui_xml_load.h"

/*********************
 *      DEFINES
 *********************/

#define LUI_XML_MAX_PATH_LENGTH 256

/**********************
 *      TYPEDEFS
 **********************/

/**********************
 * GLOBAL PROTOTYPES
 **********************/

void lui_xml_init(void);

void lui_xml_deinit(void);

/**
 * Create a UI element from XML.
 * @param parent    Pointer to the parent
 * @param name      The name of an already-registered Component or Widget
 * @param attrs     Pointer to a list of attribute/value pairs to pass.
 *                  The last two items should be `NULL`.
 * @return          Pointer to the created UI element
 * @example         If `name` is "lv_slider" and
 *                  `attrs` is {"width", "100", "value", "30", NULL, NULL};
 *                  it's equivalent to `<lv_slider width="100" value="30"/>`
 * @example         not only components can be created this way but e.g
 *                  - `name`="lv_chart-series", `attrs`={"color", "0xf00", "axis", "primary_y", NULL, NULL}
 *                  - `name`="style", `attrs`={"name", "style1", "selector", "pressed|knob", NULL, NULL}
 *                  - `name`="bind_flag_if_eq",
 *                    `attrs`={"subject", "subject1", "flag", "hidden", "ref_value", "1", NULL, NULL}
 */
void * lui_xml_create(lv_obj_t * parent, const char * name, const char ** attrs);

/**
 * Create a Screen from XML.
 * @param name  The name of an already-registered Screen
 * @return      Pointer to the created Screen
 * @note        If required, can be loaded with `lv_screen_load()`.
 */
lv_obj_t * lui_xml_create_screen(const char * name);

void * lui_xml_create_in_scope(lv_obj_t * parent, lui_xml_component_scope_t * parent_ctx,
                              lui_xml_component_scope_t * scope,
                              const char ** attrs);

/**
 * Set a path to prefix the image and font file source paths.
 *
 * In globals.xml usually the source path is like "images/logo.png".
 * But on the actual device it can be located at e.g. "A:ui/assets/images/logo.png".
 * By setting "A:ui/assets/" the path set in the XML files will be prefixed accordingly.
 *
 * @param path_prefix   the path to be used as prefix
 */
void lui_xml_set_default_asset_path(const char * path_prefix);

lv_result_t lui_xml_register_font(lui_xml_component_scope_t * scope, const char * name, const lv_font_t * font);

const lv_font_t * lui_xml_get_font(lui_xml_component_scope_t * scope, const char * name);

lv_result_t lui_xml_register_image(lui_xml_component_scope_t * scope, const char * name, const void * src);

const void * lui_xml_get_image(lui_xml_component_scope_t * scope, const char * name);

/**
 * Map globally available subject name to an actual subject variable
 * @param name      name of the subject
 * @param subject   pointer to a subject
 * @return          `LV_RESULT_OK`: success
 */
lv_result_t lui_xml_register_subject(lui_xml_component_scope_t * scope, const char * name, lv_subject_t * subject);

/**
 * Get a subject by name.
 * @param scope     If specified start searching in that component's subject list,
 *                  and if not found search in the global space.
 *                  If `NULL` search in global space immediately.
 * @param name      Name of the subject to find.
 * @return          Pointer to the subject or NULL if not found.
 */
lv_subject_t * lui_xml_get_subject(lui_xml_component_scope_t * scope, const char * name);

lv_result_t lui_xml_register_const(lui_xml_component_scope_t * scope, const char * name, const char * value);

const char * lui_xml_get_const(lui_xml_component_scope_t * scope, const char * name);

lv_result_t lui_xml_register_event_cb(lui_xml_component_scope_t * scope, const char * name, lv_event_cb_t cb);

lv_event_cb_t lui_xml_get_event_cb(lui_xml_component_scope_t * scope, const char * name);

lv_result_t lui_xml_register_timeline(lui_xml_component_scope_t * scope, const char * name);

void * lui_xml_get_timeline(lui_xml_component_scope_t * scope, const char * name);

/**********************
 *      MACROS
 **********************/

#endif /* LV_USE_XML */

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif /*LUI_XML_H*/
