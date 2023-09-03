# Image Manipulation

This is a simple image manipulation project built on top of ImageMagick.
The project specifically uses MagickWand API. The MagickWand API is provided by ImageMagick 
as it's C language binding. The project can be compiled locally on the user's machine
by first compiling ImageMagick from source and then compiling the header files.

This is the first _version(1.0.0)_ of the project and demostrates simple features like converting the
image from one extension to other, cropping it and rotating the image to multiples of 90 degree.
The future version of this project will feature a gui to let the user __interact more__ easily.


### Configure the dynamic-linker runtime bindings
```
sudo ldconfig /usr/local/lib
```

### Steps to install the ImageMagick binaries in Linux(Debian)
```
$ git clone https://github.com/ImageMagick/ImageMagick.git ImageMagick-7.1
$ cd ImageMagick-7.1.1
$ ./configure
$ make

$ sudo make install
```

### Steps to compile the source code
```
$ cc -o [output_file_name] img_manipulation.c `pkg-config --cflags --libs MagickWand`
```

### Command line arguments manual

The script allows user to change extesion, rotate and crop the image. The cmdline arguments for the same are

```
-c, -convert : Convert image to desired extension
-r, -rotate  : Rotate the image to desired degrees(multiple of 90)
-cr, -crop   : Crop the image to desired height and width using x and y offset
```
### Demonstration

```
$./wand img.jpg -c -rotate
```
Everytime the program runs the first argument passed must be the location of the image file the user wants to manipulate.

