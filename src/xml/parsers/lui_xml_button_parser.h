/**
 * @file lui_xml_button_parser.h
 *
 */

#ifndef LUI_XML_BUTTON_PARSER_H
#define LUI_XML_BUTTON_PARSER_H

#ifdef __cplusplus
extern "C" {
#endif

/*********************
 *      INCLUDES
 *********************/
#include "../lv_xml.h"
#if LV_USE_XML && LV_USE_BUTTON

/**********************
 *      TYPEDEFS
 **********************/

/**********************
 * GLOBAL PROTOTYPES
 **********************/

void * lui_xml_button_create(lui_xml_parser_state_t * state, const char ** attrs);
void lui_xml_button_apply(lui_xml_parser_state_t * state, const char ** attrs);


/**********************
 *      MACROS
 **********************/

#endif /* LV_USE_XML */

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif /*LUI_XML_BUTTON_PARSER_H*/
