/**
 * @file lui_xml_dropdown_parser.c
 *
 */

/*********************
 *      INCLUDES
 *********************/
#include "lui_xml_dropdown_parser.h"
#if LV_USE_XML && LV_USE_DROPDOWN

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

void * lui_xml_dropdown_create(lui_xml_parser_state_t * state, const char ** attrs)
{
    LV_UNUSED(attrs);
    void * item = lv_dropdown_create(lui_xml_state_get_parent(state));

    return item;
}


void lui_xml_dropdown_apply(lui_xml_parser_state_t * state, const char ** attrs)
{
    void * item = lui_xml_state_get_item(state);

    lui_xml_obj_apply(state, attrs); /*Apply the common properties, e.g. width, height, styles flags etc*/

    for(int i = 0; attrs[i]; i += 2) {
        const char * name = attrs[i];
        const char * value = attrs[i + 1];

        if(lv_streq("options", name)) lv_dropdown_set_options(item, value);
        else if(lv_streq("text", name)) lv_dropdown_set_text(item, value);
        else if(lv_streq("selected", name)) lv_dropdown_set_selected(item, lui_xml_atoi(value));
        else if(lv_streq("symbol", name)) lv_dropdown_set_symbol(item, lui_xml_get_image(&state->scope, value));
        else if(lv_streq("bind_value", name)) {
            lv_subject_t * subject = lui_xml_get_subject(&state->scope, value);
            if(subject) {
                lv_dropdown_bind_value(item, subject);
            }
            else {
                LV_LOG_WARN("Subject \"%s\" doesn't exist in dropdown bind_value", value);
            }
        }
    }
}

void * lui_xml_dropdown_list_create(lui_xml_parser_state_t * state, const char ** attrs)
{
    LV_UNUSED(attrs);

    return lv_dropdown_get_list(lui_xml_state_get_parent(state));
}

void lui_xml_dropdown_list_apply(lui_xml_parser_state_t * state, const char ** attrs)
{
    LV_UNUSED(state);
    LV_UNUSED(attrs);

    lui_xml_obj_apply(state, attrs);
}

/**********************
 *   STATIC FUNCTIONS
 **********************/

#endif /* LV_USE_XML */
