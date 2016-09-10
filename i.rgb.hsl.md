DESCRIPTION
-----------

*i.rgb.his* is an image processing program that processes three input
raster map layers as red, green, and blue components and produces three
output raster map layers representing the hue, intensity, and saturation
of the data. The output raster map layers are created by a standard
red-green-blue (RGB) to hue-intensity-saturation (HIS) color
transformation. Each output raster map layer is given a linear gray
scale color table. The current geographic region definition and mask
settings are respected.

EXAMPLES
--------

## 8-bit

The digital numbers of the 8-bit Landsat 7 bands red, green and blue, range between 0 and 255:

```
for BAND in 10 20 30 ;do echo `echo -e "Band ${BAND}: " && r.info -r lsat7_2002_$BAND` ;done

Band 10: min=42 max=255
Band 20: min=28 max=255
Band 30: min=1 max=255
```

Coverting these bands to hue, saturation and lightness:

```
i.rgb.hsl r=lsat7_2002_30 g=lsat7_2002_20 bl=lsat7_2002_10 hue=h lightness=l saturation=s
```

The output images range within:

```
for DIMENSION in h s l; do echo `echo "${DIMENSION}:" && r.info -r ${DIMENSION}` ;done

h: min=0 max=359.434
s: min=0 max=1
l: min=0.08431373 max=1
```

Note, the <em>bits</em> option is set to 8 by default. Since the input images,
in this example, are 8-bit, there is no need to modify it.

Converting back to the original RGB color space using [i.hsl.rgb](i.hsl.rgb):

```
i.hsl.rgb hue=h saturation=s lightness=l r=red g=green bl=blue
```

Confirming that the range of the values of the output images red, green and
blue, is identical to the range of the input Landsat 7 bands:

```
for IMAGE in red green blue ;do echo `echo -e "${IMAGE}: " && r.info -r $IMAGE` ;done

red: min=0 max=255
green: min=28 max=255
blue: min=42 max=255
```

## 11-bit

For 11-bit sensors, like QuickBird2 [0], set `bits=11`. For example:

```
i.rgb.his r=Red g=Green bl=Blue h=h s=s l=l bit_depth=11 --o
```


## 16-bit

The Landsat 8 instruments OLI and TIRS are capable of 12-bit. Products are,
however, delivered as 16-bit images (scaled to 55,000 grey levels). [0]

Therefore, *bitness* needs to be set to 16, like:

```
i.rgb.his red=B4.hpf green=B3.hpf blue=B2.hpf h=h s=s l=l bit=16
```

## Arbitrary lower bit depths

The module allows for data of less than 8-bit. For example, data from the DMSP Operational
Linescan System (OLS) nighttime lights time series, which feature 6-bit sensors [2].

For example:

```
i.rgb.his r=F152007 g=F152005 bl=F152004 h=h s=s l=l bits=6
```

# References

[0]

[1] http://landsat.usgs.gov/landsat8.php

[2] http://ngdc.noaa.gov/eog/sensors/ols.html

SEE ALSO
--------

*[i.hsl.rgb](i.hsl.rgb.html), [i.rgb.his](i.rgb.his.html), [i.his.rgb](i.his.rgb.html),
[r.colors](r.colors.html)*


AUTHOR
------

Nikos Alexandris
