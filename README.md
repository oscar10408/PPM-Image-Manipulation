# PPM Image Manipulation Project

## Overview

This project involves reading, modifying, and saving PPM image files. The program allows users to perform a range of image manipulation tasks such as drawing rectangles, adding patterns, and inserting images. It utilizes dynamic memory allocation, file input/output, and structured error handling.

## Features

- **Draw Rectangles**: Insert filled or outlined rectangles on the image.
- **Pattern Annotation**: Place patterns defined in text files onto the image. The pattern affects pixels based on predefined shapes.
- **Image Insertion**: Insert smaller PPM images into a larger one at a specified location, with support for transparency.
- **File Handling**: Supports reading and writing PPM files with validation for the format and structure.

## Background

This project focuses on working with PPM images (Portable Pixel Map), a simple ASCII-based image format. Unlike binary formats like JPG or PNG, PPM files store image data in a text format, making them easier to work with for educational purposes. The format uses three main components:

1. **Magic Number**: `P3` signifies a PPM image.
2. **Image Dimensions**: Specifies the width and height of the image.
3. **Maximum Color Value**: Typically set to `255` for 8-bit colors (RGB).
4. **Pixel Data**: A sequence of RGB values for each pixel in the image.

## Project Structure

```bash
.
├── src/
│   ├── ColorClass.cpp
│   ├── ColorClass.h
│   ├── ColorImageClass.cpp
│   ├── ColorImageClass.h
│   ├── RowColumnClass.cpp
│   ├── RowColumnClass.h
│   ├── main.cpp
│   └── Makefile
├── input/
│   └── pattern.txt
├── output/
│   └── result.ppm
└── README.md
