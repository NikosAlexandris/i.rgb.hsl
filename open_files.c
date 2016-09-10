#include <stdio.h>
#include <grass/gis.h>
#include <grass/raster.h>
#include <grass/glocale.h>
#include "globals.h"

/*
 * red, green, blue
 * hue, saturation, lightness,
 * input file descriptors, output file descriptors
 * (input/output?) rowbuffers
 */

void open_files(char *red, char *green, char *blue,
                char *hue, char *saturation, char *lightness,
                int fd_input[3], int fd_output[3],
                DCELL *rowbuffer[3])
{
    /* declarations */
    /* const char *mapset;              // pointer for mapset

    /* RASTER_MAP_TYPE red_data_type; */
    /* RASTER_MAP_TYPE green_data_type; */
    /* RASTER_MAP_TYPE blue_data_type; */

    /* open input files */
    fd_input[0] = Rast_open_old(red, "");
    fd_input[1] = Rast_open_old(green, "");
    fd_input[2] = Rast_open_old(blue, "");

    /* open output files */
    fd_output[0] = Rast_open_fp_new(hue);
    fd_output[1] = Rast_open_fp_new(saturation);
    fd_output[2] = Rast_open_fp_new(lightness);

    /* allocate row buffers */
    rowbuffer[0] = Rast_allocate_d_buf();
    rowbuffer[1] = Rast_allocate_d_buf();
    rowbuffer[2] = Rast_allocate_d_buf();

    /* how to dynamically set the map type? */

    /*
     * To Do: replicate an `any` function?
     */

    /* get mapset (NULL if map not found in any mapset) */
    /* mapset = (char *) G_find_raster2(red, ""); */
    /* if (mapset == NULL) */
    /*     G_fatal_error(_("Raster map <%s> not found"), red); */
    /* G_debug(1, "Working in current Mapset which is: %s", mapset); */

    /* determine input raster map type */
    /* red_data_type = Rast_map_type(red, mapset); */
    /* G_debug(1, "Red input raster map is of type: %RASTER_MAP_TYPE", red_data_type); */

    /* repeat for green and blue ------------------------------------------ */

    /* allocate the cell row buffer */
    /* rowbuffer[0] = Rast_allocate_buf(red_data_type); */
    /* rowbuffer[1] = Rast_allocate_buf(green_data_type); */
    /* rowbuffer[2] = Rast_allocate_buf(blue_data_type); */

}
