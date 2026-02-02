/**
 * @file lui_xml_style.c
 *
 */

/*********************
 *      INCLUDES
 *********************/
#include "../../lvgl.h"
#if LV_USE_XML

#include "lui_xml_base_types.h"
#include "lui_xml_parser.h"
#include "lui_xml_style.h"
#include "lui_xml_utils.h"
#include "lui_xml_component_private.h"
#include <string.h>

/*********************
 *      DEFINES
 *********************/
#ifdef _MSC_VER
    #define strtok_r strtok_s  // Use strtok_s as an equivalent to strtok_r in Visual Studio
#endif

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

/*Expands to e.g.
  if(lv_streq(name, "height")) lv_style_set_height(style, lui_xml_to_size(value));
 */
#define SET_STYLE_IF(prop, value) if(lv_streq(name, #prop)) lv_style_set_##prop(style, value)

/**********************
 *   GLOBAL FUNCTIONS
 **********************/

lv_result_t lui_xml_register_style(lui_xml_component_scope_t * scope, const char ** attrs)
{
    const char * style_name =  lui_xml_get_value_of(attrs, "name");
    if(style_name == NULL) {
        LV_LOG_WARN("'name' is missing from a style");
        return LV_RESULT_INVALID;
    }

    if(scope == NULL) scope = lui_xml_component_get_scope("globals");
    if(scope == NULL) return LV_RESULT_INVALID;


    lui_xml_style_t * xml_style;
    /*If a style with the same name is already created, use it */
    bool found = false;
    LV_LL_READ(&scope->style_ll, xml_style) {
        if(lv_streq(xml_style->name, style_name)) {
            found = true;
            LV_LOG_INFO("Style %s is already registered. Extending it with new properties.", style_name);
            break;
        }
    }

    if(!found) {
        xml_style = lv_ll_ins_tail(&scope->style_ll);
        xml_style->name = lv_strdup(style_name);
        lv_style_init(&xml_style->style);
        size_t long_name_len = lv_strlen(scope->name) + 1 + lv_strlen(style_name) + 1;
        xml_style->long_name = lv_malloc(long_name_len);
        lv_snprintf((char *)xml_style->long_name, long_name_len, "%s.%s", scope->name, style_name); /*E.g. my_button.style1*/
    }

    lv_style_t * style = &xml_style->style;

    int32_t i;
    for(i = 0; attrs[i]; i += 2) {
        const char * name = attrs[i];
        const char * value = attrs[i + 1];
        if(lv_streq(name, "name")) continue;
        if(lv_streq(name, "help")) continue;
        if(lv_streq(name, "figma_node_id")) continue;

        if(value[0] == '#') {
            const char * value_clean = &value[1];
            bool const_found = false;
            lui_xml_const_t * c;
            LV_LL_READ(&scope->const_ll, c) {
                if(lv_streq(c->name, value_clean)) {
                    value = c->value;
                    const_found = true;
                    break;
                }
            }
            if(!const_found) {
                lui_xml_component_scope_t * global_scope = lui_xml_component_get_scope("globals");
                if(global_scope) {
                    LV_LL_READ(&global_scope->const_ll, c) {
                        if(lv_streq(c->name, value_clean)) {
                            value = c->value;
                            const_found = true;
                            break;
                        }
                    }
                }
            }
            if(!const_found) {
                LV_LOG_WARN("Constant `%s` is not found", value_clean);
                continue;
            }
        }

        if(lv_streq(value, "remove")) {
            lv_style_prop_t prop = lui_xml_style_prop_to_enum(name);
            if(prop != LV_STYLE_PROP_INV) lv_style_remove_prop(style, prop);
            else if(lv_streq(name, "pad_all")) {
                lv_style_remove_prop(style, LV_STYLE_PAD_TOP);
                lv_style_remove_prop(style, LV_STYLE_PAD_BOTTOM);
                lv_style_remove_prop(style, LV_STYLE_PAD_LEFT);
                lv_style_remove_prop(style, LV_STYLE_PAD_RIGHT);
            }
            else if(lv_streq(name, "pad_hor")) {
                lv_style_remove_prop(style, LV_STYLE_PAD_LEFT);
                lv_style_remove_prop(style, LV_STYLE_PAD_RIGHT);
            }
            else if(lv_streq(name, "pad_ver")) {
                lv_style_remove_prop(style, LV_STYLE_PAD_TOP);
                lv_style_remove_prop(style, LV_STYLE_PAD_BOTTOM);
            }
            else if(lv_streq(name, "pad_gap")) {
                lv_style_remove_prop(style, LV_STYLE_PAD_COLUMN);
                lv_style_remove_prop(style, LV_STYLE_PAD_ROW);
            }
            else if(lv_streq(name, "margin_all")) {
                lv_style_remove_prop(style, LV_STYLE_MARGIN_TOP);
                lv_style_remove_prop(style, LV_STYLE_MARGIN_BOTTOM);
                lv_style_remove_prop(style, LV_STYLE_MARGIN_LEFT);
                lv_style_remove_prop(style, LV_STYLE_MARGIN_RIGHT);
            }
            else if(lv_streq(name, "margin_hor")) {
                lv_style_remove_prop(style, LV_STYLE_MARGIN_LEFT);
                lv_style_remove_prop(style, LV_STYLE_MARGIN_RIGHT);
            }
            else if(lv_streq(name, "margin_ver")) {
                lv_style_remove_prop(style, LV_STYLE_MARGIN_TOP);
                lv_style_remove_prop(style, LV_STYLE_MARGIN_BOTTOM);
            }
        }
        else SET_STYLE_IF(width, lui_xml_to_size(value));
        else SET_STYLE_IF(min_width, lui_xml_to_size(value));
        else SET_STYLE_IF(max_width, lui_xml_to_size(value));
        else SET_STYLE_IF(height, lui_xml_to_size(value));
        else SET_STYLE_IF(min_height, lui_xml_to_size(value));
        else SET_STYLE_IF(max_height, lui_xml_to_size(value));
        else SET_STYLE_IF(length, lui_xml_to_size(value));
        else SET_STYLE_IF(radius, lui_xml_to_size(value));
        else SET_STYLE_IF(radial_offset, lui_xml_atoi(value));
        else SET_STYLE_IF(align, lui_xml_align_to_enum(value));

        else SET_STYLE_IF(pad_left, lui_xml_atoi(value));
        else SET_STYLE_IF(pad_right, lui_xml_atoi(value));
        else SET_STYLE_IF(pad_top, lui_xml_atoi(value));
        else SET_STYLE_IF(pad_bottom, lui_xml_atoi(value));
        else SET_STYLE_IF(pad_hor, lui_xml_atoi(value));
        else SET_STYLE_IF(pad_ver, lui_xml_atoi(value));
        else SET_STYLE_IF(pad_all, lui_xml_atoi(value));
        else SET_STYLE_IF(pad_row, lui_xml_atoi(value));
        else SET_STYLE_IF(pad_column, lui_xml_atoi(value));
        else SET_STYLE_IF(pad_gap, lui_xml_atoi(value));
        else SET_STYLE_IF(pad_radial, lui_xml_atoi(value));

        else SET_STYLE_IF(margin_left, lui_xml_atoi(value));
        else SET_STYLE_IF(margin_right, lui_xml_atoi(value));
        else SET_STYLE_IF(margin_top, lui_xml_atoi(value));
        else SET_STYLE_IF(margin_bottom, lui_xml_atoi(value));
        else SET_STYLE_IF(margin_hor, lui_xml_atoi(value));
        else SET_STYLE_IF(margin_ver, lui_xml_atoi(value));
        else SET_STYLE_IF(margin_all, lui_xml_atoi(value));

        else SET_STYLE_IF(base_dir, lui_xml_base_dir_to_enum(value));
        else SET_STYLE_IF(clip_corner, lui_xml_to_bool(value));

        else SET_STYLE_IF(bg_opa, lui_xml_to_opa(value));
        else SET_STYLE_IF(bg_color, lui_xml_to_color(value));
        else SET_STYLE_IF(bg_grad_dir, lui_xml_grad_dir_to_enum(value));
        else SET_STYLE_IF(bg_grad_color, lui_xml_to_color(value));
        else SET_STYLE_IF(bg_main_stop, lui_xml_atoi(value));
        else SET_STYLE_IF(bg_grad_stop, lui_xml_atoi(value));
        else SET_STYLE_IF(bg_grad, lui_xml_component_get_grad(scope, value));

        else SET_STYLE_IF(bg_image_src, lui_xml_get_image(scope, value));
        else SET_STYLE_IF(bg_image_tiled, lui_xml_to_bool(value));
        else SET_STYLE_IF(bg_image_recolor, lui_xml_to_color(value));
        else SET_STYLE_IF(bg_image_recolor_opa, lui_xml_to_opa(value));

        else SET_STYLE_IF(border_color, lui_xml_to_color(value));
        else SET_STYLE_IF(border_width, lui_xml_atoi(value));
        else SET_STYLE_IF(border_opa, lui_xml_to_opa(value));
        else SET_STYLE_IF(border_side, lui_xml_border_side_to_enum(value));
        else SET_STYLE_IF(border_post, lui_xml_to_bool(value));

        else SET_STYLE_IF(outline_color, lui_xml_to_color(value));
        else SET_STYLE_IF(outline_width, lui_xml_atoi(value));
        else SET_STYLE_IF(outline_opa, lui_xml_to_opa(value));
        else SET_STYLE_IF(outline_pad, lui_xml_atoi(value));

        else SET_STYLE_IF(shadow_width, lui_xml_atoi(value));
        else SET_STYLE_IF(shadow_color, lui_xml_to_color(value));
        else SET_STYLE_IF(shadow_offset_x, lui_xml_atoi(value));
        else SET_STYLE_IF(shadow_offset_y, lui_xml_atoi(value));
        else SET_STYLE_IF(shadow_spread, lui_xml_atoi(value));
        else SET_STYLE_IF(shadow_opa, lui_xml_to_opa(value));

        else SET_STYLE_IF(text_color, lui_xml_to_color(value));
        else SET_STYLE_IF(text_font, lui_xml_get_font(scope, value));
        else SET_STYLE_IF(text_opa, lui_xml_to_opa(value));
        else SET_STYLE_IF(text_align, lui_xml_text_align_to_enum(value));
        else SET_STYLE_IF(text_letter_space, lui_xml_atoi(value));
        else SET_STYLE_IF(text_line_space, lui_xml_atoi(value));
        else SET_STYLE_IF(text_decor, lui_xml_text_decor_to_enum(value));

        else SET_STYLE_IF(image_opa, lui_xml_to_opa(value));
        else SET_STYLE_IF(image_recolor, lui_xml_to_color(value));
        else SET_STYLE_IF(image_recolor_opa, lui_xml_to_opa(value));

        else SET_STYLE_IF(line_color, lui_xml_to_color(value));
        else SET_STYLE_IF(line_opa, lui_xml_to_opa(value));
        else SET_STYLE_IF(line_width, lui_xml_atoi(value));
        else SET_STYLE_IF(line_dash_width, lui_xml_atoi(value));
        else SET_STYLE_IF(line_dash_gap, lui_xml_atoi(value));
        else SET_STYLE_IF(line_rounded, lui_xml_to_bool(value));

        else SET_STYLE_IF(arc_color, lui_xml_to_color(value));
        else SET_STYLE_IF(arc_opa, lui_xml_to_opa(value));
        else SET_STYLE_IF(arc_width, lui_xml_atoi(value));
        else SET_STYLE_IF(arc_rounded, lui_xml_to_bool(value));
        else SET_STYLE_IF(arc_image_src, lui_xml_get_image(scope, value));

        else SET_STYLE_IF(opa, lui_xml_to_opa(value));
        else SET_STYLE_IF(opa_layered, lui_xml_to_opa(value));
        else SET_STYLE_IF(color_filter_opa, lui_xml_to_opa(value));
        else SET_STYLE_IF(anim_duration, lui_xml_atoi(value));
        else SET_STYLE_IF(blend_mode, lui_xml_blend_mode_to_enum(value));
        else SET_STYLE_IF(transform_width, lui_xml_atoi(value));
        else SET_STYLE_IF(transform_height, lui_xml_atoi(value));
        else SET_STYLE_IF(translate_x, lui_xml_atoi(value));
        else SET_STYLE_IF(translate_y, lui_xml_atoi(value));
        else SET_STYLE_IF(translate_radial, lui_xml_atoi(value));
        else SET_STYLE_IF(transform_scale_x, lui_xml_atoi(value));
        else SET_STYLE_IF(transform_scale_y, lui_xml_atoi(value));
        else SET_STYLE_IF(transform_rotation, lui_xml_atoi(value));
        else SET_STYLE_IF(transform_pivot_x, lui_xml_atoi(value));
        else SET_STYLE_IF(transform_pivot_y, lui_xml_atoi(value));
        else SET_STYLE_IF(transform_skew_x, lui_xml_atoi(value));
        else SET_STYLE_IF(transform_skew_y, lui_xml_atoi(value));
        else SET_STYLE_IF(bitmap_mask_src, lui_xml_get_image(scope, value));
        else SET_STYLE_IF(rotary_sensitivity, lui_xml_atoi(value));
        else SET_STYLE_IF(recolor, lui_xml_to_color(value));
        else SET_STYLE_IF(recolor_opa, lui_xml_to_opa(value));

        else SET_STYLE_IF(blur_radius, lui_xml_atoi(value));
        else SET_STYLE_IF(blur_backdrop, lui_xml_to_bool(value));
        else SET_STYLE_IF(blur_quality, lui_xml_blur_quality_to_enum(value));

        else SET_STYLE_IF(layout, lui_xml_layout_to_enum(value));

        else SET_STYLE_IF(flex_flow, lui_xml_flex_flow_to_enum(value));
        else SET_STYLE_IF(flex_grow, lui_xml_atoi(value));
        else SET_STYLE_IF(flex_main_place, lui_xml_flex_align_to_enum(value));
        else SET_STYLE_IF(flex_cross_place, lui_xml_flex_align_to_enum(value));
        else SET_STYLE_IF(flex_track_place, lui_xml_flex_align_to_enum(value));

        else SET_STYLE_IF(grid_column_align, lui_xml_grid_align_to_enum(value));
        else SET_STYLE_IF(grid_row_align, lui_xml_grid_align_to_enum(value));
        else SET_STYLE_IF(grid_cell_column_pos, lui_xml_atoi(value));
        else SET_STYLE_IF(grid_cell_column_span, lui_xml_atoi(value));
        else SET_STYLE_IF(grid_cell_x_align, lui_xml_grid_align_to_enum(value));
        else SET_STYLE_IF(grid_cell_row_pos, lui_xml_atoi(value));
        else SET_STYLE_IF(grid_cell_row_span, lui_xml_atoi(value));
        else SET_STYLE_IF(grid_cell_y_align, lui_xml_grid_align_to_enum(value));
        else if(lv_streq(name, "grid_column_dsc_array") ||
                lv_streq(name, "grid_row_dsc_array")) {

            uint32_t item_cnt = 0;
            uint32_t c;
            for(c = 0; value[c] != '\0'; c++) {
                if(value[c] == ' ') item_cnt++;
            }

            /*This not freed automatically as the styles doesn't have any mechanisms to detect
             * removal of properties. It's assumed that the styles are created once and never freed. */
            int32_t * dsc_array = lv_malloc((item_cnt + 2) * sizeof(int32_t)); /*+2 for LV_GRID_TEMPLATE_LAST*/

            char * value_buf = (char *)value;
            item_cnt = 0;
            const char * sub_value = lui_xml_split_str(&value_buf, ' ');
            while(sub_value) {
                if(sub_value[0] == 'f' && sub_value[1] == 'r') {
                    dsc_array[item_cnt] = LV_GRID_FR(lui_xml_atoi(sub_value + 3)); /*+3 to skip "fr("*/
                }
                else {
                    dsc_array[item_cnt] = lui_xml_atoi(sub_value);
                }

                item_cnt++;
                sub_value = lui_xml_split_str(&value_buf, ' ');
            }
            dsc_array[item_cnt] = LV_GRID_TEMPLATE_LAST;

            if(lv_streq(name, "grid_column_dsc_array")) {
                lv_style_set_grid_column_dsc_array(style, dsc_array);
            }
            else {
                lv_style_set_grid_row_dsc_array(style, dsc_array);
            }
        }

        else {
            LV_LOG_WARN("%s style property is not supported", name);
        }
    }

    return LV_RESULT_OK;
}

const char * lui_xml_style_string_process(char * txt, lv_style_selector_t * selector)
{
    *selector = 0;

    char * style_name = lui_xml_split_str(&txt, '-');
    char * selector_str = lui_xml_split_str(&txt, '-');
    while(selector_str != NULL) {
        /* Handle different states and parts */
        *selector |= lui_xml_style_state_to_enum(selector_str);
        *selector |= lui_xml_style_part_to_enum(selector_str);

        /* Move to the next token */
        selector_str = lui_xml_split_str(&txt, '-');
    }

    return style_name;
}

lui_xml_style_t * lui_xml_get_style_by_name(lui_xml_component_scope_t * scope, const char * style_name_raw)
{
    const char * style_name = strrchr(style_name_raw, '.');

    if(style_name) {
        char component_name[256];
        size_t len = (size_t)(style_name - style_name_raw);
        lv_memcpy(component_name, style_name_raw, len);
        component_name[len] = '\0';
        scope = lui_xml_component_get_scope(component_name);
        if(scope == NULL) {
            LV_LOG_WARN("'%s' component or widget is not found", component_name);
        }
        style_name++; /*Skip the dot*/
    }
    else {
        style_name = style_name_raw;
    }

    /*Use the global scope is not specified*/
    if(scope == NULL) scope = lui_xml_component_get_scope("globals");
    if(scope == NULL) return NULL;

    lui_xml_style_t * xml_style;
    LV_LL_READ(&scope->style_ll, xml_style) {
        if(lv_streq(xml_style->name, style_name)) return xml_style;
    }

    /*If not found in the component check the global space*/
    if(!lv_streq(scope->name, "globals")) {
        scope = lui_xml_component_get_scope("globals");
        if(scope) {
            LV_LL_READ(&scope->style_ll, xml_style) {
                if(lv_streq(xml_style->name, style_name)) return xml_style;
            }
        }
    }

    LV_LOG_WARN("No style found with %s name", style_name_raw);

    return NULL;
}

lv_grad_dsc_t * lui_xml_component_get_grad(lui_xml_component_scope_t * scope, const char * name)
{
    lui_xml_grad_t * d;
    LV_LL_READ(&scope->gradient_ll, d) {
        if(lv_streq(d->name, name)) return &d->grad_dsc;
    }

    return NULL;
}

/**********************
 *   STATIC FUNCTIONS
 **********************/

#endif /* LV_USE_XML */
