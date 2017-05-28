## An Open Image Pipeline Curves plugin

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

## Open Source Libraries used

### Freeimage

This software uses the FreeImage open source image library.
See http://freeimage.sourceforge.net for details.
FreeImage is used under the GNU GPL, version 3.

You can find the full license in the file FreeImage-License-GNU-GPLv3.txt
in the source root of Open Image Pipeline Curves plugin.

## License

Copyright 2017 Eero Talus

This file is part of Open Image Pipeline Curves plugin.

Open Image Pipeline Curves plugin is free software: you can redistribute
it and/or modify it under the terms of the GNU General Public License
as published by the Free Software Foundation, either version 3 of the
License, or (at your option) any later version.

Open Image Pipeline Curves plugin is distributed in the hope that it
will be useful, but WITHOUT ANY WARRANTY; without even the implied
warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License along
with Open Image Pipeline Curves plugin.  If not, see <http://www.gnu.org/licenses/>.
