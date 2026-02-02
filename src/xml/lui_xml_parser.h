/**
 * @file lui_xml_parser.h
 *
 */

#ifndef LUI_XML_PARSER_H
#define LUI_XML_PARSER_H

#ifdef __cplusplus
extern "C" {
#endif

/*********************
 *      INCLUDES
 *********************/
#include "../misc/lv_types.h"
#include "../misc/lv_style.h"
#if LV_USE_XML

#include "lui_xml_component.h"
#include "lui_xml_component_private.h"

/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/

typedef enum {
    LUI_XML_PARSER_SECTION_NONE,
    LUI_XML_PARSER_SECTION_API,
    LUI_XML_PARSER_SECTION_CONSTS,
    LUI_XML_PARSER_SECTION_GRAD,
    LUI_XML_PARSER_SECTION_GRAD_STOP,
    LUI_XML_PARSER_SECTION_STYLES,
    LUI_XML_PARSER_SECTION_FONTS,
    LUI_XML_PARSER_SECTION_IMAGES,
    LUI_XML_PARSER_SECTION_SUBJECTS,
    LUI_XML_PARSER_SECTION_ANIMATION,
    LUI_XML_PARSER_SECTION_INCLUDE_TIMELINE,
    LUI_XML_PARSER_SECTION_TIMELINE,
    LUI_XML_PARSER_SECTION_VIEW
} lui_xml_parser_section_t;

struct _lui_xml_parser_state_t {
    const char * tag_name;
    lui_xml_component_scope_t scope;
    lv_ll_t parent_ll;
    lv_obj_t * parent;
    lv_obj_t * item;
    lv_obj_t * view;    /*Pointer to the created view during component creation*/
    void * context;     /*Custom data that can be stored during parsing*/
    const char ** parent_attrs;
    lui_xml_component_scope_t * parent_scope;
    lui_xml_parser_section_t section;
};

/**********************
 * GLOBAL PROTOTYPES
 **********************/

void lui_xml_parser_state_init(lui_xml_parser_state_t * state);

void lui_xml_parser_start_section(lui_xml_parser_state_t * state, const char * name);

void lui_xml_parser_end_section(lui_xml_parser_state_t * state, const char * name);

void * lui_xml_state_get_parent(lui_xml_parser_state_t * state);

void * lui_xml_state_get_item(lui_xml_parser_state_t * state);

/**********************
 *      MACROS
 **********************/

#endif /* LV_USE_XML */

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif /*LUI_XML_PARSER_H*/
