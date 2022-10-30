all: imageit
imageit: src/imageit.cpp
	g++ -std=c++17 `find . -type f -name *.cpp` `pkg-config --cflags --libs gtkmm-3.0 vips-cpp`

