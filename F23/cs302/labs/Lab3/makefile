ALL = midi_tester mconvert 

all: $(ALL)

midi_tester: midi_tester.o cs302-midi-base.o cs302-midi.o 
	g++ -o midi_tester midi_tester.o cs302-midi-base.o cs302-midi.o

mconvert: mconvert.o cs302-midi-base.o cs302-midi.o 
	g++ -o mconvert mconvert.o cs302-midi-base.o cs302-midi.o

midi_tester.o: cs302-midi.h
cs302-midi-base.o: cs302-midi.h
cs302-midi.o: cs302-midi.h
mconvert.o: cs302-midi.h

clean:
	rm -f *.o $(ALL) core

.SUFFIXES: .cpp .o

.cpp.o:
	g++ -c $*.cpp
