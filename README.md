## Bad-Apple-in-ASCII
A program which displays the video "Bad Apple" in ASCII. This program is written in C++, and was made by an amateur programmer trying to learn C++.

## REQUIREMENTS
- Windows x64
-  Cmake 3.22 or newer
-  C++17 compatible compiler
- OpenCV 5.0

## BUILD
Instruction in configurating the project. You must locate your own OpenCV build directory

```powershell
cmake -S .B -Dopen_DIR=C:/path/to/openCV/build
cmake --build build-new --config Release
```

##Executable location 
build-new/Release/BadApple.exe

## How to run 
1. Initialize a terminal or IDE.
2. Open folder and write in terminal the ff. "./build-new/Release/BadApple.exe
3. Select video
4. Open terminal to view display

## FAQ 
1. OpenCV won't read video, make sure these files are in BadApple/build-new/Release
   - /opencv_videoio_ffmpeg500_64.dll
   - /opencv_world500.dll
