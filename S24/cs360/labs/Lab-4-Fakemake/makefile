include = /home/jplank/cs360/include
lib = /home/jplank/cs360/lib

all: fakemake

clean:
	rm -f fakemake

fakemake: fakemake.c
	gcc -g -o fakemake -I$(include) fakemake.c $(lib)/libfdr.a

