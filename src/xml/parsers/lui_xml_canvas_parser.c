/**
 * @file lui_xml_canvas_parser.c
 *
 */

/*********************
 *      INCLUDES
 *********************/

#include "lui_xml_canvas_parser.h"
#if LV_USE_XML
#include <lvgl.h>
#include "luixml_compat.h"


/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/

/**********************
 *  STATIC PROTOTYPES
 **********************/

/**********************
 *  STATIC VARIABLES
 **********************/

/**********************
 *      MACROS
 **********************/

/**********************
 *   GLOBAL FUNCTIONS
 **********************/

void * lui_xml_canvas_create(lui_xml_parser_state_t * state, const char ** attrs)
{
    LV_UNUSED(attrs);

    void * item = lv_canvas_create(lui_xml_state_get_parent(state));

    return item;
}

void lui_xml_canvas_apply(lui_xml_parser_state_t * state, const char ** attrs)
{
    /*Apply the common properties, e.g. width, height, styles flags etc*/
    lui_xml_obj_apply(state, attrs);
}

/**********************
 *   STATIC FUNCTIONS
 **********************/

#endif /* LV_USE_XML */
