#include <stdlib.h>
#include "globals.h"

/* 
 * free allocated memory (row buffers),
 * close raster maps
 * set color table for output maps to grey scale.
 */

int close_files(char *hue, char *saturation, char *lightness,
               int fd_output[3], DCELL * output_rowbuffer[3])
{
    int row;
    struct Colors colors;
    struct FPRange range;
    struct History history;
    double min;
    double max;
    const char *mapset;

    /* free allocated memory, close raster maps */
    for (row = 0; row < 3; row++) {
        G_free(output_rowbuffer[row]);
        Rast_close(fd_output[row]);
    }

    mapset = G_mapset();

    /* write colors */
    Rast_read_fp_range(hue, mapset, &range);
    Rast_get_fp_range_min_max(&range, &min, &max);
    Rast_make_grey_scale_fp_colors(&colors, min, max);
    Rast_write_colors(hue, mapset, &colors);

    Rast_read_fp_range(lightness, mapset, &range);
    Rast_get_fp_range_min_max(&range, &min, &max);
    Rast_make_grey_scale_fp_colors(&colors, min, max);
    Rast_write_colors(lightness, mapset, &colors);

    Rast_read_fp_range(saturation, mapset, &range);
    Rast_get_fp_range_min_max(&range, &min, &max);
    Rast_make_grey_scale_fp_colors(&colors, min, max);
    Rast_write_colors(saturation, mapset, &colors);

    /* write metadata */
    Rast_short_history(hue, "raster", &history);
    Rast_command_history(&history);
    Rast_write_history(hue, &history);
    Rast_put_cell_title(hue, "Image hue");
    Rast_write_units(hue, "degrees");

    Rast_short_history(lightness, "raster", &history);
    Rast_command_history(&history);
    Rast_write_history(lightness, &history);
    Rast_put_cell_title(lightness, "Image lightness");

    Rast_short_history(saturation, "raster", &history);
    Rast_command_history(&history);
    Rast_write_history(saturation, &history);
    Rast_put_cell_title(saturation, "Image saturation");

    return 0;
}
