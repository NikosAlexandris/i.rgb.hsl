
/****************************************************************************
 *
 * MODULE:      i.rgb.hsl
 *
 * AUTHOR(S):   Nikos Alexandris
 *
 * PURPOSE:     Color space conversion, RGB to HSL
 *
 * COPYRIGHT:   (C) 2016 by the GRASS Development Team
 *
 *              This program is free software under the GNU General Public
 *              License (>=v2). Read the file COPYING that comes with GRASS
 *              for details.
 *
 * NOTES:       - Reused base code from i.rgb.his and parts from diff submitted
 *                in GRASS-GIS' trac ticket #774
 *              - Adapted from https://en.wikipedia.org/wiki/HSL_and_HSV#From_HSL
 *              - Also consulted http://dystopiancode.blogspot.ch/2012/06/hsl-rgb-conversion-algorithms-in-c.html
 *
 *****************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <grass/gis.h>
#include <grass/raster.h>
#include <grass/glocale.h>
#include "globals.h"

int main(int argc, char **argv)
{
    unsigned long row;      // long is 32-/64-bit, ~4 billion/~18 qunitillion
    unsigned int bands;     // input band counter
    unsigned int rows;      // input number of rows
    unsigned int cols;      // input columns
    DCELL *rowbuffer[3];
    struct Option *opt_red;
    struct Option *opt_green;
    struct Option *opt_blue;
    struct Option *opt_hue;
    struct Option *opt_saturation;
    struct Option *opt_lightness;
    struct Option *opt_bits;
    struct GModule *module; // GRASS module for parsing arguments
    int fd_input[3];        // input file descriptors
    int fd_output[3];       // output file descriptors
    int bits;               // bitness of input raster maps
    double max_colors;      // maximum level based on input bitness

    G_gisinit(argv[0]);     // initialize GIS engine

    /* Set description */
    module = G_define_module();
    G_add_keyword(_("imagery"));
    G_add_keyword(_("color transformation"));
    G_add_keyword("RGB");
    G_add_keyword("red");
    G_add_keyword("green");
    G_add_keyword("blue");
    G_add_keyword("HSL");   // Lightness, Luminosity or Luminance
    G_add_keyword("hue");
    G_add_keyword("saturation");
    G_add_keyword("lightness");
    module->description =
    ("Converts individual Red, Green and Blue (RGB) images to "
     "Hue, Saturation and Lightness dimensions in the HSL color space");

    /* Define the different options */
    opt_red = G_define_standard_option(G_OPT_R_INPUT);
    opt_red->key = "red";
    opt_red->description = _("Red input image");

    opt_green = G_define_standard_option(G_OPT_R_INPUT);
    opt_green->key = "green";
    opt_green->description = _("Green input image");

    opt_blue = G_define_standard_option(G_OPT_R_INPUT);
    opt_blue->key = "blue";
    opt_blue->description = _("Blue input image");

    opt_hue = G_define_standard_option(G_OPT_R_OUTPUT);
    opt_hue->key = "hue";
    opt_hue->description = _("Hue output image in degrees [0, 360]");

    opt_saturation = G_define_standard_option(G_OPT_R_OUTPUT);
    opt_saturation->key = "saturation";
    opt_saturation->description = _("Saturation output image ranging in [0, 1]");

    opt_lightness = G_define_standard_option(G_OPT_R_OUTPUT);
    opt_lightness->key = "lightness";
    opt_lightness->description = _("Lightness output image ranging in [0, 1]");

    opt_bits = G_define_option();
    opt_bits->key = "bits";
    opt_bits->type = TYPE_INTEGER;
    opt_bits->required = NO;
    opt_bits->answer = "8";
    opt_bits->options = "2-16";
    opt_bits->description = _("Bits per input image");

    if (G_parser(argc, argv))
        exit(EXIT_FAILURE);

    /* bit depth, should be > 0 */
    bits = atoi(opt_bits->answer);
    if (bits <= 0)
        G_fatal_error(_("Invalid bit depth definition!"));

    /* open half ended range for maximum level */
    max_colors = pow(2, bits) - 1.0;
    G_debug(1, "%d-bit data ranging in [0,%.0f)", bits, max_colors);

    /* get image dimensions */
    rows = Rast_window_rows();
    cols = Rast_window_cols();

    /* open files */
    open_files(opt_red->answer, opt_green->answer, opt_blue->answer,
               opt_hue->answer, opt_saturation->answer, opt_lightness->answer,
               fd_input, fd_output, rowbuffer);

    /* read in maps per row*/
    for (row = 0; row < rows; row++) {
        G_percent(row, rows, 2);

        /* loop over input ranster maps */
        for (band = 0; band < 3; band++)
            Rast_get_d_row(fd_input[band], rowbuffer[band], row);

            /* process row of image */
            rgb_to_hsl(rowbuffer, cols, max_colors);

        /* write new row for band */
        for (band = 0; band < 3; band++)
            Rast_put_row(fd_output[band], rowbuffer[band], DCELL_TYPE);
    }

    /* progress */
    G_percent(row, rows, 2);

    /* close files */
    close_files(opt_hue->answer, opt_saturation->answer, opt_lightness->answer,
                fd_output, rowbuffer);

    exit(EXIT_SUCCESS);
}
