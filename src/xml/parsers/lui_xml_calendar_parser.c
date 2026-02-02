/**
 * @file lui_xml_calendar_parser.c
 *
 */

/*********************
 *      INCLUDES
 *********************/
#include "lui_xml_calendar_parser.h"
#if LV_USE_XML && LV_USE_CALENDAR

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

void * lui_xml_calendar_create(lui_xml_parser_state_t * state, const char ** attrs)
{
    LV_UNUSED(attrs);
    void * item = lv_calendar_create(lui_xml_state_get_parent(state));

    return item;
}


void lui_xml_calendar_apply(lui_xml_parser_state_t * state, const char ** attrs)
{
    void * item = lui_xml_state_get_item(state);

    lui_xml_obj_apply(state, attrs); /*Apply the common properties, e.g. width, height, styles flags etc*/

    for(int i = 0; attrs[i]; i += 2) {
        const char * name = attrs[i];
        const char * value = attrs[i + 1];

        if(lv_streq("today_year", name)) lv_calendar_set_today_year(item, lui_xml_atoi(value));
        else if(lv_streq("today_month", name)) lv_calendar_set_today_month(item, lui_xml_atoi(value));
        else if(lv_streq("today_day", name)) lv_calendar_set_today_day(item, lui_xml_atoi(value));
        else if(lv_streq("shown_year", name)) lv_calendar_set_shown_year(item, lui_xml_atoi(value));
        else if(lv_streq("shown_month", name)) lv_calendar_set_shown_month(item, lui_xml_atoi(value));
    }
}

#if  LV_USE_CALENDAR_HEADER_DROPDOWN
void * lui_xml_calendar_header_dropdown_create(lui_xml_parser_state_t * state, const char ** attrs)
{
    LV_UNUSED(attrs);
    void * item = lv_calendar_add_header_dropdown(lui_xml_state_get_parent(state));
    return item;
}

void lui_xml_calendar_header_dropdown_apply(lui_xml_parser_state_t * state, const char ** attrs)
{
    lui_xml_obj_apply(state, attrs); /*Apply the common properties, e.g. width, height, styles flags etc*/
}
#endif

#if  LV_USE_CALENDAR_HEADER_ARROW
void * lui_xml_calendar_header_arrow_create(lui_xml_parser_state_t * state, const char ** attrs)
{
    LV_UNUSED(attrs);
    void * item = lv_calendar_add_header_arrow(lui_xml_state_get_parent(state));

    return item;
}

void lui_xml_calendar_header_arrow_apply(lui_xml_parser_state_t * state, const char ** attrs)
{
    lui_xml_obj_apply(state, attrs); /*Apply the common properties, e.g. width, height, styles flags etc*/
}
#endif


/**********************
 *   STATIC FUNCTIONS
 **********************/

#endif /* LV_USE_XML */
