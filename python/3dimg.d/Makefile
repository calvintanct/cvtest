
# Created: Feb 14 2018
# Author: Kris Gunnarsson
# Purpose: Extend Tcl with calls to OpenCV. Useful in 3D camera osftware development

# COLOR we must have colored output
RED   = \033[0;31m
GREEN =\033[0;32m
BLUE  =\033[0;34m
BOLD  =\033[1m
NC    =\033[0m # No Color

CC := g++
DEFINES := -g -fPIC

INCLUDE = -I /usr/local/include -I /usr/local/tara-opencv/include

PCL_INCLUDE = -I/usr/include/pcl-1.7 -I/usr/include/eigen3 -I/usr/include/vtk-5.8
PCL_LIBS = -lpcl_visualization -lpcl_common -lpcl_io -lboost_system -lvtkGraphics -lvtkFiltering -lvtkCommon -lvtkRendering 

OPENCV_LIBS := -L/usr/local/tara-opencv/lib -lopencv_core -lopencv_imgproc -lopencv_highgui -lopencv_imgcodecs
OPENCV_CALIB := -lopencv_ximgproc -lopencv_calib3d

LIBS := $(OPENCV_LIBS) $(OPENCV_CALIB) $(PCL_LIBS)

INCLUDES = $(INCLUDE) $(OPENCV_INCLUDE) $(PCL_INCLUDE) `pkg-config --cflags glib-2.0`

SOURCE = main.cpp disp.cpp pcloud.cpp 
OUTPUT = Disp

DISP = readisp.cpp

$(OUTPUT): $(SOURCE:%.cpp=%.o)
	$(CC) $(DEFINES) -o $(OUTPUT) $(SOURCE:%.cpp=%.o) $(LIBS) 

RD: readisp.o
	$(CC) $(DEFINES) -o RD readisp.o $(LIBS) 

%.o: %.cpp  header.h
	$(CC) $(DEFINES) -c $< $(INCLUDES)

.PHONY: clean
clean:
	rm *o
	rm Disp
