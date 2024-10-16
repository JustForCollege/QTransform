# QTransform

A Simple app written with C++ and QT6, with straighforward UI, Just Drag & Drop your image and choose your desired tranformation.

Supported Transformtions: 
	- Black & White Transformer 
	- Image Invert 
	- GrayScale Transformer 

Supported File Formats:
	- PNG,
	- JPEG
	- BMP

# Demo:

https://github.com/user-attachments/assets/1a28c3d4-fd48-4873-89f5-653f7357bb22

# How To Use ? 

1) Download "Windows.7z" from the Releases Sections.
2) Decompress it.
3) Run "QTransform.exe"
4) Drag and Drop your image and you are good to go. 

# How To Build ?

- Prequisties: QT6, CMake, MinGW-64. 

1) Download QT6: https://www.qt.io/download-dev
2) CMake: https://cmake.org/download/
3) MinGW-64: https://github.com/skeeto/w64devkit

After downloading all the requirements, open powershell and run 

```
git clone --depth=1 https://github.com/JustForCollege/QTransform.git
cd QTransform 
mkdir build 
cd build 
cmake .. -G"MinGW Makefiles" -DCMAKE_PREFIX_PATH="C:\Qt\<version>\mingw_64\lib\cmake" -DQT_DIR="C:\Qt\<version>\mingw_64\lib\cmake\Qt6"
``` 

# How It Works ?

Black & White Transformer:
---------------------------

I simply go through the image pixels, then apply a gray scale transformation on each pixel, then checking to see if the resulting 
gray value is larger than or equal a specific threshold (I picked 127), I then set that pixel to white, else set it to black. 
it can be described as follows: 

```
	Load(Image)

	For pixel in Image.Pixels:
		grayedPixel = GrayScale(pixel) 
		if grayedPixel >= 127:
			pixel = WHITE
		else:
			pixel = BLACK 
	
	Save(Image)
```

GrayScale Transformer: 
----------------------

I have used QT6 `QImage::convertToFormat(QImage::Format_Grayscale8)` function to do a GrayScale Transformation however the algorithm is quite simple 
and it can be described as follows: 

```	
	Load(Image)
	
	For pixel in Image.Pixels:
		grayedPixel = (pixel.red + pixel.green + pixel.blue) / 3 
		pixel = grayedPixel
	
	Save(Image)
```

Image Inverter:
---------------

I have used QT6 `QImage::invertPixels()` function to invert the image, however the algorithm for inverting an image is quite simple and it can be described as follows

```
 Load(Image) 
 
 For pixel in Image.Pixels:
   pixel.red = 255 - pixel.red
   pixel.green = 255 - pixel.green 
   pixel.blue = 255 - pixel.blue 

 Save(Image)
```