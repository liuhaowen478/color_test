CXX=g++
CXX_FLAGS=-g -Wall -std=c++11

all: test

test: 
	-@echo "Compiling map generator"
	$(CXX) $(CXX_FLAGS) map_gen.cpp -o gen
	-@echo "Running coloring on generated maps"
	./gen
	./../color gmap0.in gmap0.out
	./../color gmap1.in gmap1.out
	./../color gmap2.in gmap2.out
	./../color gmap3.in gmap3.out
	./../color gmap4.in gmap4.out
	./../color gmap5.in gmap5.out
	./../color gmap6.in gmap6.out
	./../color gmap7.in gmap7.out
	./../color gmap8.in gmap8.out
	./../color gmap9.in gmap9.out
	$(CXX) $(CXX_FLAGS) checker.cpp -o checker
	-@echo "Checking result"
	./checker
