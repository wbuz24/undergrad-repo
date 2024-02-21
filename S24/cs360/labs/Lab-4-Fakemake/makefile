include = /home/shartreuce/repos/undergrad-repo/S24/cs360/notes/Libfdr/include
lib = /home/shartreuce/repos/undergrad-repo/S24/cs360/notes/Libfdr/lib

all: fakemake

clean:
	rm -f fakemake

fakemake: fakemake.c
	gcc -g -o fakemake -I$(include) fakemake.c $(lib)/libfdr.a

