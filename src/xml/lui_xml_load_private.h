/**
 * @file lui_xml_load_private.h
 *
 */

#ifndef LUI_XML_LOAD_PRIVATE_H
#define LUI_XML_LOAD_PRIVATE_H

#ifdef __cplusplus
extern "C" {
#endif

/*********************
 *      INCLUDES
 *********************/

#include "lui_xml_load.h"
#if LV_USE_XML

/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/

/**********************
 * GLOBAL PROTOTYPES
 **********************/

void lui_xml_load_init(void);

void lui_xml_load_deinit(void);

/**********************
 *      MACROS
 **********************/

#endif /*LV_USE_XML*/

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif /*LUI_XML_LOAD_PRIVATE_H*/
