/**
 * @file lui_xml_obj_parser.h
 *
 */

#ifndef LUI_XML_OBJ_PARSER_H
#define LUI_XML_OBJ_PARSER_H

#ifdef __cplusplus
extern "C" {
#endif

/*********************
 *      INCLUDES
 *********************/
#include "../lv_xml.h"
#if LV_USE_XML

/**********************
 *      TYPEDEFS
 **********************/

/**********************
 * GLOBAL PROTOTYPES
 **********************/

void * lui_xml_obj_create(lui_xml_parser_state_t * state, const char ** attrs);
void lui_xml_obj_apply(lui_xml_parser_state_t * state, const char ** attrs);

void * lv_obj_xml_style_create(lui_xml_parser_state_t * state, const char ** attrs);
void lv_obj_xml_style_apply(lui_xml_parser_state_t * state, const char ** attrs);

void * lv_obj_xml_remove_style_create(lui_xml_parser_state_t * state, const char ** attrs);
void lv_obj_xml_remove_style_apply(lui_xml_parser_state_t * state, const char ** attrs);

void * lv_obj_xml_remove_style_all_create(lui_xml_parser_state_t * state, const char ** attrs);
void lv_obj_xml_remove_style_all_apply(lui_xml_parser_state_t * state, const char ** attrs);

void * lv_obj_xml_event_cb_create(lui_xml_parser_state_t * state, const char ** attrs);
void lv_obj_xml_event_cb_apply(lui_xml_parser_state_t * state, const char ** attrs);

void * lv_obj_xml_subject_toggle_create(lui_xml_parser_state_t * state, const char ** attrs);
void lv_obj_xml_subject_toggle_apply(lui_xml_parser_state_t * state, const char ** attrs);

void * lv_obj_xml_subject_set_create(lui_xml_parser_state_t * state, const char ** attrs);
void lv_obj_xml_subject_set_apply(lui_xml_parser_state_t * state, const char ** attrs);

void * lv_obj_xml_subject_increment_create(lui_xml_parser_state_t * state, const char ** attrs);
void lv_obj_xml_subject_increment_apply(lui_xml_parser_state_t * state, const char ** attrs);

void * lv_obj_xml_bind_style_create(lui_xml_parser_state_t * state, const char ** attrs);
void lv_obj_xml_bind_style_apply(lui_xml_parser_state_t * state, const char ** attrs);

void * lv_obj_xml_bind_style_prop_create(lui_xml_parser_state_t * state, const char ** attrs);
void lv_obj_xml_bind_style_prop_apply(lui_xml_parser_state_t * state, const char ** attrs);

void * lv_obj_xml_bind_flag_create(lui_xml_parser_state_t * state, const char ** attrs);
void lv_obj_xml_bind_flag_apply(lui_xml_parser_state_t * state, const char ** attrs);

void * lv_obj_xml_bind_state_create(lui_xml_parser_state_t * state, const char ** attrs);
void lv_obj_xml_bind_state_apply(lui_xml_parser_state_t * state, const char ** attrs);

void * lv_obj_xml_screen_load_event_create(lui_xml_parser_state_t * state, const char ** attrs);
void lv_obj_xml_screen_load_event_apply(lui_xml_parser_state_t * state, const char ** attrs);

void * lv_obj_xml_screen_create_event_create(lui_xml_parser_state_t * state, const char ** attrs);
void lv_obj_xml_screen_create_event_apply(lui_xml_parser_state_t * state, const char ** attrs);

void * lv_obj_xml_play_timeline_event_create(lui_xml_parser_state_t * state, const char ** attrs);
void lv_obj_xml_play_timeline_event_apply(lui_xml_parser_state_t * state, const char ** attrs);

/**********************
 *      MACROS
 **********************/

#endif /* LV_USE_XML */

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif /*LUI_XML_OBJ_PARSER_H*/
