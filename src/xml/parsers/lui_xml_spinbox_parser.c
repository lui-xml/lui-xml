/**
 * @file lui_xml_spinbox_parser.c
 *
 */

/*********************
 *      INCLUDES
 *********************/
#include "lui_xml_spinbox_parser.h"
#if LV_USE_XML && LV_USE_SPINBOX

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

void * lui_xml_spinbox_create(lui_xml_parser_state_t * state, const char ** attrs)
{
    LV_UNUSED(attrs);

    void * item = lv_spinbox_create(lui_xml_state_get_parent(state));
    return item;
}

void lui_xml_spinbox_apply(lui_xml_parser_state_t * state, const char ** attrs)
{
    void * item = lui_xml_state_get_item(state);
    lui_xml_obj_apply(state, attrs); /*Apply the common properties, e.g. width, height, styles flags etc*/

    for(int i = 0; attrs[i]; i += 2) {
        const char * name = attrs[i];
        const char * value = attrs[i + 1];

        if(lv_streq("value", name)) lv_spinbox_set_value(item, lui_xml_atoi(value));
        else if(lv_streq("rollover", name)) lv_spinbox_set_rollover(item, lui_xml_to_bool(value));
        else if(lv_streq("digit_count", name)) lv_spinbox_set_digit_count(item, lui_xml_atoi(value));
        else if(lv_streq("dec_point_pos", name)) lv_spinbox_set_dec_point_pos(item, lui_xml_atoi(value));
        else if(lv_streq("min_value", name)) lv_spinbox_set_min_value(item, lui_xml_atoi(value));
        else if(lv_streq("max_value", name)) lv_spinbox_set_max_value(item, lui_xml_atoi(value));
        else if(lv_streq("step", name)) lv_spinbox_set_step(item, lui_xml_atoi(value));
        else if(lv_streq("bind_value", name)) {
            lv_subject_t * subject = lui_xml_get_subject(&state->scope, value);
            if(subject) {
                lv_spinbox_bind_value(item, subject);
            }
            else {
                LV_LOG_WARN("Subject \"%s\" doesn't exist in spinbox bind_value", value);
            }
        }
    }
}

/**********************
 *   STATIC FUNCTIONS
 **********************/

#endif /* LV_USE_XML */
