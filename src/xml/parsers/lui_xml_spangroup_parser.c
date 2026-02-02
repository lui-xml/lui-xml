/**
 * @file lui_xml_spangroup_parser.c
 *
 */

/*********************
 *      INCLUDES
 *********************/
#include "lui_xml_spangroup_parser.h"
#if LV_USE_XML && LV_USE_SPAN

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

static lv_span_overflow_t spangroup_overflow_to_enum(const char * txt);

/**********************
 *  STATIC VARIABLES
 **********************/

/**********************
 *      MACROS
 **********************/

/**********************
 *   GLOBAL FUNCTIONS
 **********************/

void * lui_xml_spangroup_create(lui_xml_parser_state_t * state, const char ** attrs)
{
    LV_UNUSED(attrs);
    void * item = lv_spangroup_create(lui_xml_state_get_parent(state));

    return item;
}


void lui_xml_spangroup_apply(lui_xml_parser_state_t * state, const char ** attrs)
{
    void * item = lui_xml_state_get_item(state);

    lui_xml_obj_apply(state, attrs); /*Apply the common properties, e.g. width, height, styles flags etc*/

    for(int i = 0; attrs[i]; i += 2) {
        const char * name = attrs[i];
        const char * value = attrs[i + 1];

        if(lv_streq("overflow", name)) lv_spangroup_set_overflow(item, spangroup_overflow_to_enum(value));
        else if(lv_streq("max_lines", name)) lv_spangroup_set_max_lines(item, lui_xml_atoi(value));
        else if(lv_streq("indent", name)) lv_spangroup_set_indent(item, lui_xml_atoi(value));
    }
}

void * lui_xml_spangroup_span_create(lui_xml_parser_state_t * state, const char ** attrs)
{
    LV_UNUSED(attrs);
    void * item = lv_spangroup_add_span(lui_xml_state_get_parent(state));
    return item;
}

void lui_xml_spangroup_span_apply(lui_xml_parser_state_t * state, const char ** attrs)
{
    LV_UNUSED(state);
    LV_UNUSED(attrs);

    lv_obj_t * spangroup = lui_xml_state_get_parent(state);
    lv_span_t * span = lui_xml_state_get_item(state);

    for(int i = 0; attrs[i]; i += 2) {
        const char * name = attrs[i];
        const char * value = attrs[i + 1];

        if(lv_streq("text", name)) lv_spangroup_set_span_text(spangroup, span, value);
        else if(lv_streq("style", name)) {
            lui_xml_style_t * style_dsc = lui_xml_get_style_by_name(&state->scope, value);
            lv_spangroup_set_span_style(spangroup, span, &style_dsc->style);
        }
        else if(lv_streq("bind_text", name)) {
            lv_subject_t * subject = lui_xml_get_subject(&state->scope, value);
            if(subject == NULL) {
                LV_LOG_WARN("Subject \"%s\" doesn't exist in spangroup span bind_text", value);
                continue;
            }
            const char * fmt = lui_xml_get_value_of(attrs, "bind_text-fmt");
            if(fmt) {
                fmt = lv_strdup(fmt);
                lv_obj_add_event_cb(spangroup, lv_event_free_user_data_cb, LV_EVENT_DELETE, (void *) fmt);
            }
            lv_spangroup_bind_span_text(spangroup, span, subject, fmt);
        }
    }
}

/**********************
 *   STATIC FUNCTIONS
 **********************/

static lv_span_overflow_t spangroup_overflow_to_enum(const char * txt)
{
    if(lv_streq("clip", txt)) return LV_SPAN_OVERFLOW_CLIP;
    if(lv_streq("ellipsis", txt)) return LV_SPAN_OVERFLOW_ELLIPSIS;

    LV_LOG_WARN("%s is an unknown value for span's overflow", txt);
    return 0; /*Return 0 in lack of a better option. */
}

#endif /* LV_USE_XML */
