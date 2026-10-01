Image Processing application developed with C++, the application allow users to load an image, apply filters and save image

*Features*
#Image Management:
- Load image for processing
- Apply one or more filters
- save the processed image
- Exit the application

#Currently Implemented Filters:
-Grayscale -> Converts Image to grayscale.
-Black & White —> Converts the image into a black-and-white image.
-Horizontal Flip —> Flips the image horizontally.
-Vertical Flip —> Flips the image vertically.
-Rotate 90° —> Rotates the image by 90 degrees.
-Rotate 180° —> Rotates the image by 180 degrees.
-Rotate 270° —> Rotates the image by 270 degrees.
-Invert —> Inverts the colors of the image.
-Lighten —> Increases the brightness of the image.
-Darken —> Decreases the brightness of the image.
-Resize —> Changes the dimensions of the image.
-Frame —> Adds a frame around the image.
  *Normal frame
  *Fancy frame
  *Custom frame color

*Project Structure*
Image-Processing/
│
├── Image_Class.h ( The image class provided for the project, used to load, manipulate, and save images. )
├── TemplateCode.cpp ( Main C++ program containing the menu, image loading/saving, and filter implementations. )
├── stb_image.h ( Image loading library used by the project. Your provided header is an edited FCAI version. )
├── stb_image_write.h ( Image writing/saving library. The header identifies itself as an edited FCAI version. )
└── README.md    

*Technologies*
C++
Object-Oriented Programming
Git
GitHub
