# PPM Image Manipulation Project

## Detailed Description
In the previous project, I developed classes to represent a Color, a ColorImage, and a Row/Column Location. For this project, I’ve built upon those concepts, with a focus on more advanced features such as dynamic memory allocation for arrays, file input/output operations, and splitting the implementation across multiple files for better organization.

In addition to expanding the structure of the program, this project also introduced the challenge of handling potential stream issues. As part of the process, I’ve learned how to detect and manage these issues effectively, ensuring that the program can handle file reading and writing smoothly without crashing or encountering errors.

## Background: .ppm Imagery
<p float="left">
<img src="Images/deer.jpg" width="200" height="150"/>
<img src="Images/new1.jpg" width="200" height="150"/>
<img src="Images/new2.jpg" width="200" height="150"/>
<img src="Images/new3.jpg" width="200" height="150"/>
<img src="Images/new4.jpg" width="200" height="150"/>
<img src="Images/new5.jpg" width="200" height="150"/>
</p>

For this project, I worked with the PPM (Portable Pixmap) image format. Unlike compressed formats like .gif or .jpg, PPM images are stored as ASCII text files. While this makes them larger in file size, it also simplifies reading and writing since I’m already familiar with text files. The main focus was understanding the .ppm format to properly handle the image data.

In this project, I learned that most image formats start with a "magic number," which helps programs identify the file type. For PPM images, the magic number is "P3." This signals to the program that the file follows the PPM format and should be processed accordingly. If the file doesn’t begin with "P3," it’s flagged as an invalid PPM file, which is something I need to handle in my implementation.

In this project, I had to account for the specific size of an image, since the number of pixels could be arranged in many ways. For example, a 100-pixel image could be 25 rows by 4 columns, or 10 rows by 10 columns, or any other combination. After the "magic number," the next two pieces of data in a PPM file are the image's width and height. These are both integers that represent the number of pixels. It's important to remember that the width comes first, followed by the height — a common mix-up that I had to be careful of when handling the data.

The next value is also an integer, and is simply the maximum value in the color descriptions. For this project, I will use 255 as the maximum number. With a maximum of 10, you are only allowed 10 shades of gray, and 10^3 unique colors which would not allow you to generate a very photographic-looking image. But if the maximum value is 255, you could get a much wider range of colors (255^3). For this project, a value of 255 is the only valid “maximum color value” allowed, and any value that is NOT 255 will be considered an “invalid PPM image” and should be reported as an error.

The remaining part of the PPM file contains a description of each pixel. Starting from the upper-left corner, the pixels are listed row by row. After all the pixels in the first row are described, the next row starts. This pattern continues until all pixels are described. For example, a 4x4 image requires 4 rows and 4 columns, so it will have 4 * 4 * 3 = 48 integers in total, with each pixel represented by three integers for its red, green, and blue values.

A very small image of a red square on a blue background would be stored in a PPM file as follows:<br />
P3 <br />
4 4 <br />
255 <br />
0 0 255   0 0 255   0 0 255   0 0 255 <br />
0 0 255   255 0 0   255 0 0   0 0 255 <br />
0 0 255   255 0 0   255 0 0   0 0 255 <br />
0 0 255   0 0 255   0 0 255   0 0 255 <br />

Please note that I have provided this example in a nicely formatted way for ease of understanding, but a PPM file is not required to be “line-based”. In other words, there is nothing in the PPM format that requires one row of pixels to be contained on a single line, or that pixel values are separated with more spaces than the RGB values, etc.

### File Naming For PPM Images
Most often, PPM files will end with a “.ppm” extension. However, this is not a requirement, and the program should not perform any checking for a specific filename extension. While it might be very confusing, there could be a file named “definitelyNotAPPM.exe” with contents that were a valid PPM – if we were to provide such a file to your implementation, you should read the contents of the file just as if it were named “myPPM.ppm”. Typically, file extensions are used as a convention for general understanding of what a file contains, but (especially in Linux) this is strictly a convention as opposed to a requirement.

## Required Functionality
For this project, only requires to implement a few algorithms to modify an image. However, you will be able to add any number of your own algorithms to modify imagery in any number of ways. Below are the descriptions of the algorithms you are required to implement:

### 1. Rectangle Drawing
In this project, I implemented the functionality to draw rectangles on an image. I allow users to place rectangle outlines or filled rectangles to either highlight or block out specific areas on an image. Both types of rectangle operations will be supported throughout the project.

### 2. Pattern Annotation
I also allow users to annotate images with patterns. Patterns consist of a rectangular grid of zeros and ones, where a '1' in the pattern indicates that the corresponding pixel in the image should be modified with a user-defined color, while a '0' means the pixel remains unchanged (effectively transparent). This allows for targeted image editing without affecting the entire image.

### 3. Image Insertion
Another feature I implemented is the ability to insert one image into another. This involves reading a smaller PPM image and inserting it at a specified location within the main image. The inserted image may have a transparency color (defined by the user), where any pixel in the inserted image that matches the transparency color will be ignored, and only the non-transparent pixels will replace those in the original image.

### 4. Output to PPM File
Throughout the editing process, I provide the option to output the current state of the image to a PPM file. This allows users to save their progress either after each modification or at the end of their edits.

## Out of Bounds Patterns and Inserted Images
When placing a pattern or inserting an image, it’s possible that part of the inserted content might extend beyond the boundaries of the image. I made sure that this isn’t treated as an error; the pixels within bounds will be correctly inserted, while those out of bounds will have no effect. This flexibility lets users intentionally place patterns or images in such a way that only part of it is included within the final image.

## Implementation and Design
For this project, all global constants are declared and initialized in a file named constants.h. Since this file only contains constant definitions and no functions or class definitions, it does not require a corresponding .cpp file. I made sure to avoid using "magic numbers" by placing all the constants in this header file. This ensures that any constants used throughout the project are easily managed and can be modified in a single location if needed.

In this project, the image pixels are dynamically allocated using the new operator. The memory is allocated based on the exact size of the image, which means the memory usage scales with the size of the image. Smaller images will consume less memory, and larger images will require more. This approach ensures that there’s no fixed limit on the size of the images that can be processed, allowing for greater flexibility in image manipulation.

Each individual class in this project is defined in two files: a header file (.h) and a source file (.cpp). The class names are used as the file names, making it easy to organize and navigate through the project. All class member variables are kept private to adhere to the principle of encapsulation, while the member functions are public, allowing for controlled access and manipulation of the class data.

## Files Included
- `constants.h` – Contains global constants.
- `ColorClass.h`, `ColorClass.cpp` – Represents color information for each pixel.
- `ColorImageClass.h`, `ColorImageClass.cpp` – Contains logic for managing an image.
- `RowColumnClass.h`, `RowColumnClass.cpp` – Manages row and column data.
- Additional utility and test files.

## Rectangle Input Methods

In this project, the user can specify a rectangle in three different ways. These methods allow flexibility in how rectangles are described but are internally stored in a consistent format. The three input methods are:

1. **Upper-left and Lower-right Corners**: 
   - The user specifies the upper-left corner and the lower-right corner directly by providing the coordinates of both points.
   
2. **Upper-left Corner, Width, and Height**: 
   - The user provides the coordinates of the upper-left corner and the dimensions (width and height) of the rectangle. The lower-right corner is computed internally by adding the width to the x-coordinate and the height to the y-coordinate.
   
3. **Center, Half-width, and Half-height**: 
   - The user specifies the center of the rectangle and its half-width and half-height (i.e., the extents from the center). The program internally calculates the upper-left and lower-right corners by using the center coordinates and the extents.

### Internal Representation of Rectangles

Regardless of the input method chosen by the user, **all rectangles are represented internally by two points: the upper-left corner and the lower-right corner**. This simplifies the design and ensures that all operations (such as drawing the rectangle) are performed in a consistent way.

The conversion logic for each input method is as follows:

- **Method 1 (Upper-left and Lower-right Corners)**: These values are used directly as the internal representation of the rectangle.
- **Method 2 (Upper-left Corner and Width/Height)**: The lower-right corner is calculated by adding the width to the x-coordinate and the height to the y-coordinate of the upper-left corner.
- **Method 3 (Center and Half-width/Height)**: The upper-left corner is calculated by subtracting half the width from the center's x-coordinate and half the height from the center's y-coordinate. The lower-right corner is calculated by adding these values.

### Design Philosophy

The design of the rectangle handling is focused on **simplicity and flexibility**. Instead of storing separate attributes for each method of input, the program stores only the upper-left and lower-right corners. This eliminates redundancy and ensures the code is easier to maintain and extend in the future.

### User Interface

The program uses a menu-driven interface where the user can choose from the following options:
- Insert a rectangle
- Insert a pattern
- Insert an image
- Save the image
- Exit the program

The program will guide the user through the necessary inputs for each action. 

**Important Note**: The program **must** follow the exact sequence of actions and user input prompts as specified in the sample output. Do not reorder menu options, add extra prompts, or change the required user inputs. The program must behave consistently with the expected flow and format.

---

## Example Usage

### Compilation
```bash
make
./proj3.exe
```

## Project Structure

```bash
.
├── src/
│   ├── checkOutOfBoundry.cpp
│   ├── checkOutOfBoundry.h
│   ├── ColorClass.cpp
│   ├── ColorClass.h
│   ├── ColorImageClass.cpp
│   ├── ColorImageClass.h
│   ├── constants.h
│   ├── RowColumnClass.cpp
│   ├── RowColumnClass.h
│   ├── mainMenu.cpp
│   ├── mainMenu.h
│   ├── setColorMenu.cpp
│   ├── setColorMenu.h
│   └── Makefile
├── Inputs/
│   ├── deer.ppm
│   ├── ohdeerPattern.txt
│   └── topHat.ppm
├── Outputs/
│   ├── new1.ppm
│   ├── new2.ppm
│   ├── new3.ppm
│   ├── new4.ppm
│   └── new5.ppm
└── README.md
