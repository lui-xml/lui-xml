/**
 * @file lui_xml_private.h
 *
 */

#ifndef LUI_XML_PRIVATE_H
#define LUI_XML_PRIVATE_H

#ifdef __cplusplus
extern "C" {
#endif

/*********************
 *      INCLUDES
 *********************/
#include "lv_xml.h"
#if LV_USE_XML

#include "parsers/lui_xml_obj_parser.h"
#include "lui_xml_parser.h"
#include "lui_xml_base_types.h"
#include "lui_xml_utils.h"
#include "lui_xml_style.h"

/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/

typedef struct {
    const char * name;
    const lv_font_t * font;
    void (*font_destroy_cb)(lv_font_t *);
} lui_xml_font_t;

typedef struct {
    const char * name;
    const void * src;
} lui_xml_image_t;

typedef struct {
    const char * name;
    lv_event_cb_t cb;
} lui_xml_event_cb_t;

/**
 * Store the data of <include_timeline>
 */
typedef struct {
    const char * target_name;  /**< Include the timeline of this widget*/
    const char * timeline_name;   /**< Include this timeline */
    int32_t delay;
} lui_xml_anim_timeline_include_t;

typedef struct {
    bool is_anim;
    union {
        lv_anim_t anim;
        lui_xml_anim_timeline_include_t incl;
    } data;
} lui_xml_anim_timeline_child_t;

/**********************
 * GLOBAL PROTOTYPES
 **********************/

/**********************
 *      MACROS
 **********************/

#endif /* LV_USE_XML */

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif /*LUI_XML_PRIVATE_H*/
