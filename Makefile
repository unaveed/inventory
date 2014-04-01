all: cpp

cpp: 
	g++ *.cpp

clean:
	rm -rf *.o a.out
