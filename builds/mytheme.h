#ifndef _my_theme_h
#define _my_theme_h

/*        ************************************************************************      */
/*        *        This file must be in the root folder of the sketch !!!        *      */
/*        ************************************************************************      */

/* Theming of color displays:                                                           */
/*         DSP_ST7735, DSP_ST7789, DSP_ILI9341, DSP_GC9106, DSP_ILI9225, DSP_ST7789_240 */
/* Uncomment (remove double slash //) from desired line to apply color                  */

/* This file contains the ehRadio theme colors (blue & red & more)                      */
/* These are the same colors applied by options.h when this file is not found.          */
/* You can use it as a template for your own theming!                                   */

#define ENABLE_THEME
#ifdef  ENABLE_THEME

/*-----------------------------------------------------------------------------------------------*/
/*       | COLORS               |   values (0-255)  |                                            */
/*       | color name           |    R    G    B    |                                            */
/*-----------------------------------------------------------------------------------------------*/

#define COLOR_BACKGROUND             0,   0,   0 // background
#define COLOR_STATION_NAME         247, 247, 247 // station text color
#define COLOR_STATION_BG             0,  63, 207 // current station background
#define COLOR_STATION_FILL           0,  55, 191 // fill color (outside bg)
#define COLOR_SNG_TITLE_1          239, 239, 239 // first title
#define COLOR_SNG_TITLE_2          207, 207, 207 // second title
#define COLOR_WEATHER              223, 223,   0 // weather string
#define COLOR_VU_MAX               175,  31,  31 // max of VU meter
#define COLOR_VU_MIN                15, 127,  15 // min of VU meter
#define COLOR_CLOCK                255,  31,   7 // clock color
#define COLOR_CLOCK_BG              31,   3,   0 // clock color background
#define COLOR_SECONDS              247,  27,   5 // seconds color (DSP_ST7789, DSP_ILI9341, DSP_ILI9225)
#define COLOR_DAY_OF_W             255, 192, 192 // day of week color (for DSP_ST7789, DSP_ILI9341, DSP_ILI9225)
#define COLOR_DATE                 192, 192, 255 // date color (DSP_ST7789, DSP_ILI9341, DSP_ILI9225)
#define COLOR_CLOCK_SS             153, 217, 234 // screensaver clock color
#define COLOR_CLOCK_BG_SS            8,  11,  12 // screensaver clock glow/background color
#define COLOR_SECONDS_SS           140, 200, 220 // screensaver seconds color
#define COLOR_DAY_OF_W_SS          110, 110, 150 // screensaver day of week color
#define COLOR_DATE_SS              150, 110, 110 // screensaver date color
#define COLOR_BUFFER               231,  47, 255 // buffer bar line
#define COLOR_IP                   153, 217, 234 // IP address
#define COLOR_VOLUME_VALUE         223, 223,   0 // volume number
#define COLOR_RSSI                 153, 217, 234 // rssi
#define COLOR_BATTERY              153, 217, 234 // battery
#define COLOR_VOLBAR_OUT           223, 223,   0 // border of volume bar
#define COLOR_VOLBAR_IN            207, 207,   0 // inside volume bar
#define COLOR_DIGITS               255,  31,   7 // number on the volume page
#define COLOR_DIVIDER               91,  91,  91 // lines around clock
#define COLOR_PL_CURRENT           255, 255, 255 // playlist current item
#define COLOR_PL_CURRENT_BG        255,  31,   7 // playlist current item background
#define COLOR_PL_CURRENT_FILL      231,  23,   7 // playlist current item fill outline
#define COLOR_PLAYLIST_0           231, 231, 231 // playlist string 0
#define COLOR_PLAYLIST_1           199, 199, 199 // playlist string 1
#define COLOR_PLAYLIST_2           167, 167, 167 // playlist string 2
#define COLOR_PLAYLIST_3           135, 135, 135 // playlist string 3
#define COLOR_PLAYLIST_4           103, 103, 103 // playlist string 4
#define COLOR_BITRATE              231,  47, 255 // stream bitrate

#endif  /* #ifdef ENABLE_THEME */
#endif  /* #define _my_theme_h  */
