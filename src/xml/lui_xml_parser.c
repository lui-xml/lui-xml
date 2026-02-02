/**
 * @file lui_xml_parser.c
 *
 */

/*********************
 *      INCLUDES
 *********************/
#include "lv_xml.h"
#if LV_USE_XML

#include "lui_xml_private.h"
#include "lui_xml_parser.h"
#include "lui_xml_style.h"
#include "lui_xml_component_private.h"
#include "lui_xml_base_types.h"

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

void lui_xml_parser_state_init(lui_xml_parser_state_t * state)
{
    lv_memzero(state, sizeof(lui_xml_parser_state_t));
    lv_ll_init(&state->parent_ll, sizeof(lv_obj_t *));
    lui_xml_component_scope_init(&state->scope);
}

void lui_xml_parser_start_section(lui_xml_parser_state_t * state, const char * name)
{
    /* Check for context changes */
    if(lv_streq(name, "api")) {
        state->section = LUI_XML_PARSER_SECTION_API;
        return;
    }
    if(lv_streq(name, "gradients")) {
        state->section = LUI_XML_PARSER_SECTION_GRAD;
        return;
    }
    if(state->section == LUI_XML_PARSER_SECTION_GRAD && lv_streq(name, "stop")) {
        state->section = LUI_XML_PARSER_SECTION_GRAD_STOP;
        return;
    }
    else if(lv_streq(name, "consts")) {
        state->section = LUI_XML_PARSER_SECTION_CONSTS;
        return;
    }
    else if(lv_streq(name, "styles")) {
        state->section = LUI_XML_PARSER_SECTION_STYLES;
        return;
    }
    else if(lv_streq(name, "images")) {
        state->section = LUI_XML_PARSER_SECTION_IMAGES;
        return;
    }
    else if(lv_streq(name, "fonts")) {
        state->section = LUI_XML_PARSER_SECTION_FONTS;
        return;
    }
    else if(lv_streq(name, "subjects")) {
        state->section = LUI_XML_PARSER_SECTION_SUBJECTS;
        return;
    }
    else if(lv_streq(name, "animation")) {
        state->section = LUI_XML_PARSER_SECTION_ANIMATION;
        return;
    }
    else if(lv_streq(name, "include_timeline")) {
        state->section = LUI_XML_PARSER_SECTION_INCLUDE_TIMELINE;
        return;
    }
    else if(lv_streq(name, "timeline")) {
        state->section = LUI_XML_PARSER_SECTION_TIMELINE;
        return;
    }
    else if(lv_streq(name, "view")) {
        state->section = LUI_XML_PARSER_SECTION_VIEW;
        return;
    }
}

void lui_xml_parser_end_section(lui_xml_parser_state_t * state, const char * name)
{

    /* Reset context when leaving a block */
    if(lv_streq(name, "params") ||
       lv_streq(name, "consts") ||
       lv_streq(name, "gradients") ||
       lv_streq(name, "styles") ||
       lv_streq(name, "view")) {
        state->section = LUI_XML_PARSER_SECTION_NONE;
    }

    /*When processing gradient stops, but not a stop was closed got bacg to gradient processing
     * E.g. </linear_gradient>*/
    if(state->section == LUI_XML_PARSER_SECTION_GRAD_STOP && !lv_streq(name, "stop")) {
        state->section = LUI_XML_PARSER_SECTION_GRAD;
    }
}

void * lui_xml_state_get_parent(lui_xml_parser_state_t * state)
{
    return state->parent;
}

void * lui_xml_state_get_item(lui_xml_parser_state_t * state)
{
    return state->item;
}

/**********************
 *   STATIC FUNCTIONS
 **********************/

#endif /* LV_USE_XML */
