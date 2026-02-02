/**
 * @file lui_xml_table_parser.c
 *
 */

/*********************
 *      INCLUDES
 *********************/
#include "lui_xml_table_parser.h"
#if LV_USE_XML && LV_USE_TABLE

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
static lv_table_cell_ctrl_t table_ctrl_to_enum(const char * txt);

/**********************
 *  STATIC VARIABLES
 **********************/

/**********************
 *      MACROS
 **********************/

/**********************
 *   GLOBAL FUNCTIONS
 **********************/

void * lui_xml_table_create(lui_xml_parser_state_t * state, const char ** attrs)
{
    LV_UNUSED(attrs);
    void * item = lv_table_create(lui_xml_state_get_parent(state));

    return item;
}


void lui_xml_table_apply(lui_xml_parser_state_t * state, const char ** attrs)
{
    void * item = lui_xml_state_get_item(state);

    lui_xml_obj_apply(state, attrs); /*Apply the common properties, e.g. width, height, styles flags etc*/

    for(int i = 0; attrs[i]; i += 2) {
        const char * name = attrs[i];
        const char * value = attrs[i + 1];

        if(lv_streq("column_count", name)) lv_table_set_column_count(item, lui_xml_atoi(value));
        else if(lv_streq("row_count", name)) lv_table_set_row_count(item, lui_xml_atoi(value));
    }
}

void * lui_xml_table_column_create(lui_xml_parser_state_t * state, const char ** attrs)
{
    LV_UNUSED(attrs);

    /*Nothing to create*/
    return lui_xml_state_get_parent(state);
}

void lui_xml_table_column_apply(lui_xml_parser_state_t * state, const char ** attrs)
{
    LV_UNUSED(state);
    LV_UNUSED(attrs);

    lv_obj_t * table = lui_xml_state_get_parent(state);
    int32_t column = lui_xml_atoi(lui_xml_get_value_of(attrs, "column"));

    for(int i = 0; attrs[i]; i += 2) {
        const char * name = attrs[i];
        const char * value = attrs[i + 1];

        if(lv_streq("width", name))  lv_table_set_column_width(table, column, lui_xml_atoi(value));
    }
}

void * lui_xml_table_cell_create(lui_xml_parser_state_t * state, const char ** attrs)
{
    LV_UNUSED(attrs);

    /*Nothing to create*/
    return lui_xml_state_get_parent(state);
}

void lui_xml_table_cell_apply(lui_xml_parser_state_t * state, const char ** attrs)
{
    LV_UNUSED(state);
    LV_UNUSED(attrs);

    lv_obj_t * table = lui_xml_state_get_parent(state);
    int32_t row = lui_xml_atoi(lui_xml_get_value_of(attrs, "row"));
    int32_t column = lui_xml_atoi(lui_xml_get_value_of(attrs, "column"));

    for(int i = 0; attrs[i]; i += 2) {
        const char * name = attrs[i];
        const char * value = attrs[i + 1];

        if(lv_streq("value", name))  lv_table_set_cell_value(table, row, column, value);
        if(lv_streq("ctrl", name)) {
            lv_table_cell_ctrl_t ctrl = 0;
            char buf[256];
            lv_strncpy(buf, value, sizeof(buf));
            char * buf_p = buf;
            const char * str;
            while((str = lui_xml_split_str(&buf_p, '|')) != NULL) {
                ctrl |= table_ctrl_to_enum(str);
            }

            lv_table_set_cell_ctrl(table, row, column, ctrl);
        }
    }
}

/**********************
 *   STATIC FUNCTIONS
 **********************/

static lv_table_cell_ctrl_t table_ctrl_to_enum(const char * txt)
{
    if(lv_streq("none", txt)) return LV_TABLE_CELL_CTRL_NONE;
    if(lv_streq("merge_right", txt)) return LV_TABLE_CELL_CTRL_MERGE_RIGHT;
    if(lv_streq("text_crop", txt)) return LV_TABLE_CELL_CTRL_TEXT_CROP;
    if(lv_streq("custom_1", txt)) return LV_TABLE_CELL_CTRL_CUSTOM_1;
    if(lv_streq("custom_2", txt)) return LV_TABLE_CELL_CTRL_CUSTOM_2;
    if(lv_streq("custom_3", txt)) return LV_TABLE_CELL_CTRL_CUSTOM_3;
    if(lv_streq("custom_4", txt)) return LV_TABLE_CELL_CTRL_CUSTOM_4;

    LV_LOG_WARN("%s is an unknown value for table's ctrl", txt);
    return 0; /*Return 0 in lack of a better option. */
}

#endif /* LV_USE_XML */
