all: cpp

cpp: 
	g++ *.cpp

debug:
	g++ -g *.cpp

clean:
	rm -rf *.o a.out
