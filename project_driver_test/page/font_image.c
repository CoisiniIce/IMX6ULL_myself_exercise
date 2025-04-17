/*******************************************************************************
 * Size: 32 px
 * Bpp: 1
 * Opts: --bpp 1 --size 32 --no-compress --font font_image.woff --range 58953 --format lvgl -o font_image.c
 ******************************************************************************/

#ifdef LV_LVGL_H_INCLUDE_SIMPLE
#include "lvgl.h"
#else
#include "lvgl/lvgl.h"
#endif

#ifndef FONT_IMAGE
#define FONT_IMAGE 1
#endif

#if FONT_IMAGE

/*-----------------
 *    BITMAPS
 *----------------*/

/*Store the image of the glyphs*/
static LV_ATTRIBUTE_LARGE_CONST const uint8_t glyph_bitmap[] = {
    /* U+E649 "" */
    0xf, 0xff, 0xff, 0xf0, 0x3f, 0xff, 0xff, 0xfc,
    0x7f, 0xff, 0xff, 0xfe, 0x7f, 0xff, 0xff, 0xfe,
    0xf8, 0x0, 0x0, 0x1f, 0xf0, 0x0, 0x0, 0xf,
    0xf1, 0xe0, 0x0, 0xf, 0xf3, 0xf0, 0x0, 0xf,
    0xf3, 0xf0, 0x0, 0xf, 0xf3, 0xf0, 0x0, 0xf,
    0xf3, 0xf0, 0x0, 0xf, 0xf1, 0xe0, 0x0, 0xf,
    0xf0, 0x0, 0x0, 0xf, 0xf0, 0x0, 0x0, 0xf,
    0xf0, 0x0, 0xc, 0xf, 0xf0, 0x0, 0x1e, 0xf,
    0xf0, 0x0, 0x3e, 0xf, 0xf0, 0x0, 0x7f, 0xf,
    0xf0, 0xc0, 0xff, 0xf, 0xf0, 0xc0, 0xff, 0x8f,
    0xf1, 0xe1, 0xff, 0x8f, 0xf1, 0xf3, 0xff, 0x8f,
    0xf3, 0xff, 0xff, 0xcf, 0xf3, 0xff, 0xff, 0xcf,
    0xf3, 0xff, 0xff, 0xcf, 0xf1, 0xff, 0xff, 0x8f,
    0xf0, 0x0, 0x0, 0xf, 0xf8, 0x0, 0x0, 0x1f,
    0x7f, 0xff, 0xff, 0xfe, 0x7f, 0xff, 0xff, 0xfe,
    0x3f, 0xff, 0xff, 0xfc, 0xf, 0xff, 0xff, 0xf0
};


/*---------------------
 *  GLYPH DESCRIPTION
 *--------------------*/

static const lv_font_fmt_txt_glyph_dsc_t glyph_dsc[] = {
    {.bitmap_index = 0, .adv_w = 0, .box_w = 0, .box_h = 0, .ofs_x = 0, .ofs_y = 0} /* id = 0 reserved */,
    {.bitmap_index = 0, .adv_w = 512, .box_w = 32, .box_h = 32, .ofs_x = 0, .ofs_y = -4}
};

/*---------------------
 *  CHARACTER MAPPING
 *--------------------*/



/*Collect the unicode lists and glyph_id offsets*/
static const lv_font_fmt_txt_cmap_t cmaps[] =
{
    {
        .range_start = 58953, .range_length = 1, .glyph_id_start = 1,
        .unicode_list = NULL, .glyph_id_ofs_list = NULL, .list_length = 0, .type = LV_FONT_FMT_TXT_CMAP_FORMAT0_TINY
    }
};



/*--------------------
 *  ALL CUSTOM DATA
 *--------------------*/

#if LVGL_VERSION_MAJOR == 8
/*Store all the custom data of the font*/
static  lv_font_fmt_txt_glyph_cache_t cache;
#endif

#if LVGL_VERSION_MAJOR >= 8
static const lv_font_fmt_txt_dsc_t font_dsc = {
#else
static lv_font_fmt_txt_dsc_t font_dsc = {
#endif
    .glyph_bitmap = glyph_bitmap,
    .glyph_dsc = glyph_dsc,
    .cmaps = cmaps,
    .kern_dsc = NULL,
    .kern_scale = 0,
    .cmap_num = 1,
    .bpp = 1,
    .kern_classes = 0,
    .bitmap_format = 0,
#if LVGL_VERSION_MAJOR == 8
    .cache = &cache
#endif
};



/*-----------------
 *  PUBLIC FONT
 *----------------*/

/*Initialize a public general font descriptor*/
#if LVGL_VERSION_MAJOR >= 8
const lv_font_t font_image = {
#else
lv_font_t font_image = {
#endif
    .get_glyph_dsc = lv_font_get_glyph_dsc_fmt_txt,    /*Function pointer to get glyph's data*/
    .get_glyph_bitmap = lv_font_get_bitmap_fmt_txt,    /*Function pointer to get glyph's bitmap*/
    .line_height = 32,          /*The maximum line height required by the font*/
    .base_line = 4,             /*Baseline measured from the bottom of the line*/
#if !(LVGL_VERSION_MAJOR == 6 && LVGL_VERSION_MINOR == 0)
    .subpx = LV_FONT_SUBPX_NONE,
#endif
#if LV_VERSION_CHECK(7, 4, 0) || LVGL_VERSION_MAJOR >= 8
    .underline_position = 0,
    .underline_thickness = 0,
#endif
    .dsc = &font_dsc,          /*The custom font data. Will be accessed by `get_glyph_bitmap/dsc` */
#if LV_VERSION_CHECK(8, 2, 0) || LVGL_VERSION_MAJOR >= 9
    .fallback = NULL,
#endif
    .user_data = NULL,
};



#endif /*#if FONT_IMAGE*/

