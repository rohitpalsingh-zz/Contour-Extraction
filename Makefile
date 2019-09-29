CC = g++ -O2 -Wno-deprecated 

tag = -i

ifdef linux
tag = -n
endif

test.out: contour.o test.o
	$(CC) -o test.out contour.o test.o -lfl
	
test.o: test.cc
	$(CC) -g -c test.cc

contour.o: contour.cc
	$(CC) -g -c contour.cc
clean: 
	rm -f *.o
	rm -f *.out
