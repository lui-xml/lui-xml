/**
 * @file lui_xml_dropdown_parser.h
 *
 */

#ifndef LUI_XML_DROPDOWN_PARSER_H
#define LUI_XML_DROPDOWN_PARSER_H

#ifdef __cplusplus
extern "C" {
#endif

/*********************
 *      INCLUDES
 *********************/
#include "../lv_xml.h"
#if LV_USE_XML && LV_USE_DROPDOWN

/**********************
 *      TYPEDEFS
 **********************/

/**********************
 * GLOBAL PROTOTYPES
 **********************/

void * lui_xml_dropdown_create(lui_xml_parser_state_t * state, const char ** attrs);
void lui_xml_dropdown_apply(lui_xml_parser_state_t * state, const char ** attrs);
void * lui_xml_dropdown_list_create(lui_xml_parser_state_t * state, const char ** attrs);
void lui_xml_dropdown_list_apply(lui_xml_parser_state_t * state, const char ** attrs);

/**********************
 *      MACROS
 **********************/
#endif /* LV_USE_XML */

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif /*LUI_XML_DROPDOWN_PARSER_H*/
