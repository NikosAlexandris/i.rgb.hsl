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

The digital numbers for the 8-bit Landsat 7 bands red, green and blue, range between 0 and 255:

`for BAND in 10 20 30 ;do echo `echo -e "Band ${BAND}: " && r.info -r lsat7_2002_$BAND` ;done`

```
Band 10: min=42 max=255
Band 20: min=28 max=255
Band 30: min=1 max=255
```

Coverting these to hue, saturation and lightness:

`i.rgb.hsl r=lsat7_2002_30 g=lsat7_2002_20 bl=lsat7_2002_10 hue=h lightness=l saturation=s`


The output images range within:

`for DIMENSION in h s l; do echo `echo "${DIMENSION}:" && r.info -r ${DIMENSION}` ;done

```
h: min=0 max=359.434
s: min=0 max=1
l: min=0.08431373 max=1
```

Note, the <em>bits</em> option is set to 8 by default. Since the input images,
in this examele, are 8-bit, there is no need to modify it.

Converting back to the original RGB color space using [i.hsl.rgb](i.hsl.rgb):

`i.hsl.rgb hue=h saturation=s lightness=l r=red g=green bl=blue`

Confirming that the range of the values of the output images red, green and
blue, is identical to the range of the input Landsat 7 bands:

`for IMAGE in red green blue ;do echo \`echo -e "${IMAGE}: " && r.info -r $IMAGE\` ;done`

```
red: min=0 max=255
green: min=28 max=255
blue: min=42 max=255
```


## 16-bit


SEE ALSO
--------

*[i.hsl.rgb](i.hsl.rgb.html), [i.rgb.his](i.rgb.his.html), [i.his.rgb](i.his.rgb.html),
[r.colors](r.colors.html)*


AUTHOR
------

Nikos Alexandris

*Last changed: \$Date: 2016-01-28 12:21:34 +0100 (Thu, 28 Jan 2016) \$*
