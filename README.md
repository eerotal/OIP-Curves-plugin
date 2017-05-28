## An Open Image Pipeline curves plugin

An Open Image Pipeline plugin used for manipulating the different color
channels of an image by using a curve to set colors whose intensity is
to be changed. This plugin is a very powerful tool in image processing
since it makes it possible to make many kinds of modifications to the
individual color channels of and image.

## Plugin arguments

#### ctrl_points

This argument specifies the control points of the curve used for
processing the image. The value should be a string of the following
form  

`(x1, y1),(x2,y2),(x3,y3), ... ,(xn,yn)`

#### channels
This argument specifies the channels that will be affected by the
processing. The value of this argument should be a combination of
the letters R, G, B, A and L where  

`R = Red channel`  
`G = Green channel`  
`B = Blue channel`  
`A = Alpha channel`  
`L = Luminosity`  

For example, the value RB would enable the red and blue channels.  

## Compiling

To configure the local build environment, first execute the file named
`config-build-env.sh`. The shell script will prompt you for some information
that's needed by the makefile. After this script has finished, you can run `make`
and then `make install`, which will copy the created shared library file to
the `plugins` directory in the main OIP directory. The makefile also has the
following targets  

#### clean

Clean all the files created by the compilation.  

#### clean-hard

Clean all the files created by the compilation and also delete the build environment
configuration file.  

#### LOC

Count the total lines of code for this plugin.  

##### Copyright Eero Talus 2017
