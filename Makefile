# Bamphiane Annie Phongphouthai
# bp8qg
# October 13, 2017
# Makefile
CXX = clang++ -O2 
CXXFLAGS = -Wall -O2

OFILES = wordPuzzle.o hashTable.o timer.o 

main: $(OFILES)
	$(CXX) $(OFILES)

clean:
	-rm -f *.o *~ outputfile

wordPuzzle.o: wordPuzzle.cpp
hashTable.o: hashTable.cpp hashTable.h
timer.o: timer.cpp timer.h
