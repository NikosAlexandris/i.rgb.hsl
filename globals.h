#ifndef __GLOBALS_H__
#define __GLOBALS_H__

#include <grass/raster.h>

/*
 * open_files.c
 * red, green, blue
 * hue, saturation, lightness,
 * input file descriptors, output file descriptors
 * input rowbuffer
 */
void open_files(char *, char *, char *,
               char *, char *, char *,
               int[3], int[3],
               DCELL *[3]);

/*
 * rgb_to_hsl.c
 * input rowbuffer, columns, maximum range value
 */
void rgb_to_hsl(DCELL *[3], int, double);

/*
 * close_files.c
 * hue, saturation, intensity (lightness)
 * output file descriptors
 * output rowbuffers
 */
int close_files(char *, char *, char *,
               int[3],
               DCELL *[3]);

#endif /* __GLOBALS_H__ */
