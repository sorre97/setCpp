
#MODE = -DNDEBUG #per compilare in modalita' release

MODE =  # per compilare in modalita' debug

main.out: main.o
	g++ $(MODE) main.o -o main.out

main.o: main.cpp
	g++ $(MODE)  -c main.cpp -o main.o


.PHONY: clean

clean:
	rm *.out *.o
