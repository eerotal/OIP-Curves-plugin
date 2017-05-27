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

  
  `R = Red channel  
  G = Green channel  
  B = Blue channel  
  A = Alpha channel  
  L = Luminosity`
  

  For example, the value RB would enable the red and blue channels. 

##### Copyright Eero Talus 2017
