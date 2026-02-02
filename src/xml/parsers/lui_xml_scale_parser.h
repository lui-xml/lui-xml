/**
 * @file lui_xml_scale_parser.h
 *
 */

#ifndef LUI_XML_SCALE_PARSER_H
#define LUI_XML_SCALE_PARSER_H

#ifdef __cplusplus
extern "C" {
#endif

/*********************
 *      INCLUDES
 *********************/
#include "../lv_xml.h"
#if LV_USE_XML && LV_USE_SCALE

/**********************
 *      TYPEDEFS
 **********************/

/**********************
 * GLOBAL PROTOTYPES
 **********************/

void * lui_xml_scale_create(lui_xml_parser_state_t * state, const char ** attrs);
void lui_xml_scale_apply(lui_xml_parser_state_t * state, const char ** attrs);
void * lui_xml_scale_section_create(lui_xml_parser_state_t * state, const char ** attrs);
void lui_xml_scale_section_apply(lui_xml_parser_state_t * state, const char ** attrs);

/**********************
 *      MACROS
 **********************/
#endif /* LV_USE_XML */

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif /*LUI_XML_SCALE_PARSER_H*/
