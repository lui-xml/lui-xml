/**
 * @file lui_xml_imagebutton_parser.h
 *
 */

#ifndef LUI_XML_IMAGEBUTTON_PARSER_H
#define LUI_XML_IMAGEBUTTON_PARSER_H

#ifdef __cplusplus
extern "C" {
#endif

/*********************
 *      INCLUDES
 *********************/
#include "../lv_xml.h"
#if LV_USE_XML && LV_USE_IMAGEBUTTON

/**********************
 *      TYPEDEFS
 **********************/

/**********************
 * GLOBAL PROTOTYPES
 **********************/

void * lui_xml_imagebutton_create(lui_xml_parser_state_t * state, const char ** attrs);
void lui_xml_imagebutton_apply(lui_xml_parser_state_t * state, const char ** attrs);
void * lui_xml_imagebutton_src_left_create(lui_xml_parser_state_t * state, const char ** attrs);
void lui_xml_imagebutton_src_left_apply(lui_xml_parser_state_t * state, const char ** attrs);
void * lui_xml_imagebutton_src_right_create(lui_xml_parser_state_t * state, const char ** attrs);
void lui_xml_imagebutton_src_right_apply(lui_xml_parser_state_t * state, const char ** attrs);
void * lui_xml_imagebutton_src_mid_create(lui_xml_parser_state_t * state, const char ** attrs);
void lui_xml_imagebutton_src_mid_apply(lui_xml_parser_state_t * state, const char ** attrs);

/**********************
 *      MACROS
 **********************/
#endif /* LV_USE_XML */

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif /*LUI_XML_IMAGEBUTTON_PARSER_H*/
