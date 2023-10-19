all: bin/null_sort \
     bin/set_sort \
     bin/bubble_sort \
     bin/selection_sort \
     bin/insertion_1_sort \
     bin/insertion_2_sort \
     bin/insertion_3_sort \
     bin/insertion_1_sorted \
     bin/heap_sort \
     bin/heap_fast_sort \
     bin/stl_sort \
     bin/qsort_sort \
     bin/bucket_1_sort \
     bin/bucket_2_sort 

lab: bin/merge_1_lab_sort bin/quick_2_lab_sort

private: bin/merge_1_sort \
         bin/merge_2_sort \
         bin/quick_1_sort \
         bin/quick_1_sorted \
         bin/quick_2_sort \
         bin/quick_2_sorted \
         bin/quick_3_sort
         

clean: 
	rm -f a.out bin/* obj/*

CFLAGS = -O3 -Iinclude -Wall -Wextra

# ----------------------------------------
# Object files

obj/bubble_sort.o: include/sorting.hpp src/bubble_sort.cpp
	g++ $(CFLAGS) -c -o obj/bubble_sort.o src/bubble_sort.cpp

obj/bucket_1_sort.o: include/sorting.hpp src/bucket_1_sort.cpp
	g++ $(CFLAGS) -c -o obj/bucket_1_sort.o src/bucket_1_sort.cpp

obj/bucket_2_sort.o: include/sorting.hpp src/bucket_2_sort.cpp
	g++ $(CFLAGS) -c -o obj/bucket_2_sort.o src/bucket_2_sort.cpp

obj/heap_fast_sort.o: include/sorting.hpp src/heap_fast_sort.cpp
	g++ $(CFLAGS) -c -o obj/heap_fast_sort.o src/heap_fast_sort.cpp

obj/heap_sort.o: include/sorting.hpp src/heap_sort.cpp
	g++ $(CFLAGS) -c -o obj/heap_sort.o src/heap_sort.cpp

obj/insertion_1_sort.o: include/sorting.hpp src/insertion_1_sort.cpp
	g++ $(CFLAGS) -c -o obj/insertion_1_sort.o src/insertion_1_sort.cpp

obj/insertion_2_sort.o: include/sorting.hpp src/insertion_2_sort.cpp
	g++ $(CFLAGS) -c -o obj/insertion_2_sort.o src/insertion_2_sort.cpp

obj/insertion_3_sort.o: include/sorting.hpp src/insertion_3_sort.cpp
	g++ $(CFLAGS) -c -o obj/insertion_3_sort.o src/insertion_3_sort.cpp

obj/null_sort.o: include/sorting.hpp src/null_sort.cpp
	g++ $(CFLAGS) -c -o obj/null_sort.o src/null_sort.cpp

obj/pqueue_heap.o: include/sorting.hpp src/pqueue_heap.cpp
	g++ $(CFLAGS) -c -o obj/pqueue_heap.o src/pqueue_heap.cpp

obj/qsort_sort.o: include/sorting.hpp src/qsort_sort.cpp
	g++ $(CFLAGS) -c -o obj/qsort_sort.o src/qsort_sort.cpp

obj/selection_sort.o: include/sorting.hpp src/selection_sort.cpp
	g++ $(CFLAGS) -c -o obj/selection_sort.o src/selection_sort.cpp

obj/set_sort.o: include/sorting.hpp src/set_sort.cpp
	g++ $(CFLAGS) -c -o obj/set_sort.o src/set_sort.cpp

obj/sort_driver.o: include/sorting.hpp src/sort_driver.cpp
	g++ $(CFLAGS) -c -o obj/sort_driver.o src/sort_driver.cpp

obj/sort_driver_lab.o: include/sorting.hpp src/sort_driver_lab.cpp
	g++ $(CFLAGS) -c -o obj/sort_driver_lab.o src/sort_driver_lab.cpp

obj/sort_sorted.o: include/sorting.hpp src/sort_sorted.cpp
	g++ $(CFLAGS) -c -o obj/sort_sorted.o src/sort_sorted.cpp

obj/sort_stdin.o: include/sorting.hpp src/sort_stdin.cpp
	g++ $(CFLAGS) -c -o obj/sort_stdin.o src/sort_stdin.cpp

obj/stl_sort.o: include/sorting.hpp src/stl_sort.cpp
	g++ $(CFLAGS) -c -o obj/stl_sort.o src/stl_sort.cpp

obj/merge_1_sort.o: include/sorting.hpp src/merge_1_sort.cpp
	g++ $(CFLAGS) -c -o obj/merge_1_sort.o src/merge_1_sort.cpp

obj/merge_2_sort.o: include/sorting.hpp src/merge_2_sort.cpp
	g++ $(CFLAGS) -c -o obj/merge_2_sort.o src/merge_2_sort.cpp

obj/quick_1_sort.o: include/sorting.hpp src/quick_1_sort.cpp
	g++ $(CFLAGS) -c -o obj/quick_1_sort.o src/quick_1_sort.cpp

obj/quick_2_sort.o: include/sorting.hpp src/quick_2_sort.cpp
	g++ $(CFLAGS) -c -o obj/quick_2_sort.o src/quick_2_sort.cpp

obj/quick_3_sort.o: include/sorting.hpp src/quick_3_sort.cpp
	g++ $(CFLAGS) -c -o obj/quick_3_sort.o src/quick_3_sort.cpp

# ----------------------------------------
# Binaries

bin/null_sort: obj/null_sort.o obj/sort_driver.o
	g++ $(CFLAGS) -o bin/null_sort obj/null_sort.o obj/sort_driver.o

bin/set_sort: obj/set_sort.o obj/sort_driver.o
	g++ $(CFLAGS) -o bin/set_sort obj/set_sort.o obj/sort_driver.o

bin/bubble_sort: obj/bubble_sort.o obj/sort_driver.o
	g++ $(CFLAGS) -o bin/bubble_sort obj/bubble_sort.o obj/sort_driver.o

bin/selection_sort: obj/selection_sort.o obj/sort_driver.o
	g++ $(CFLAGS) -o bin/selection_sort obj/selection_sort.o obj/sort_driver.o

bin/insertion_1_sort: obj/insertion_1_sort.o obj/sort_driver.o
	g++ $(CFLAGS) -o bin/insertion_1_sort obj/insertion_1_sort.o obj/sort_driver.o

bin/insertion_2_sort: obj/insertion_2_sort.o obj/sort_driver.o
	g++ $(CFLAGS) -o bin/insertion_2_sort obj/insertion_2_sort.o obj/sort_driver.o

bin/insertion_3_sort: obj/insertion_3_sort.o obj/sort_driver.o
	g++ $(CFLAGS) -o bin/insertion_3_sort obj/insertion_3_sort.o obj/sort_driver.o

bin/insertion_1_sorted: obj/insertion_1_sort.o obj/sort_sorted.o
	g++ $(CFLAGS) -o bin/insertion_1_sorted obj/insertion_1_sort.o obj/sort_sorted.o

bin/heap_sort: obj/heap_sort.o obj/sort_driver.o obj/pqueue_heap.o
	g++ $(CFLAGS) -o bin/heap_sort obj/heap_sort.o obj/sort_driver.o obj/pqueue_heap.o

bin/heap_fast_sort: obj/heap_fast_sort.o obj/sort_driver.o
	g++ $(CFLAGS) -o bin/heap_fast_sort obj/heap_fast_sort.o obj/sort_driver.o

bin/stl_sort: obj/stl_sort.o obj/sort_driver.o
	g++ $(CFLAGS) -o bin/stl_sort obj/stl_sort.o obj/sort_driver.o

bin/qsort_sort: obj/qsort_sort.o obj/sort_driver.o
	g++ $(CFLAGS) -o bin/qsort_sort obj/qsort_sort.o obj/sort_driver.o

bin/bucket_1_sort: obj/bucket_1_sort.o obj/sort_driver.o
	g++ $(CFLAGS) -o bin/bucket_1_sort obj/bucket_1_sort.o obj/sort_driver.o

bin/bucket_2_sort: obj/bucket_2_sort.o obj/sort_driver.o
	g++ $(CFLAGS) -o bin/bucket_2_sort obj/bucket_2_sort.o obj/sort_driver.o

bin/merge_1_lab_sort: obj/merge_1_sort.o obj/sort_driver_lab.o
	g++ $(CFLAGS) -o bin/merge_1_lab_sort obj/merge_1_sort.o obj/sort_driver_lab.o

bin/quick_2_lab_sort: obj/quick_2_sort.o obj/sort_driver_lab.o
	g++ $(CFLAGS) -o bin/quick_2_lab_sort obj/quick_2_sort.o obj/sort_driver_lab.o

bin/merge_1_sort: obj/merge_1_sort.o obj/sort_driver.o
	g++ $(CFLAGS) -o bin/merge_1_sort obj/merge_1_sort.o obj/sort_driver.o

bin/merge_2_sort: obj/merge_2_sort.o obj/sort_driver.o
	g++ $(CFLAGS) -o bin/merge_2_sort obj/merge_2_sort.o obj/sort_driver.o

bin/quick_1_sort: obj/quick_1_sort.o obj/sort_driver.o
	g++ $(CFLAGS) -o bin/quick_1_sort obj/quick_1_sort.o obj/sort_driver.o

bin/quick_1_sorted: obj/quick_1_sort.o obj/sort_sorted.o
	g++ $(CFLAGS) -o bin/quick_1_sorted obj/quick_1_sort.o obj/sort_sorted.o

bin/quick_2_sort: obj/quick_2_sort.o obj/sort_driver.o
	g++ $(CFLAGS) -o bin/quick_2_sort obj/quick_2_sort.o obj/sort_driver.o

bin/quick_2_sorted: obj/quick_2_sort.o obj/sort_sorted.o
	g++ $(CFLAGS) -o bin/quick_2_sorted obj/quick_2_sort.o obj/sort_sorted.o

bin/quick_1_lab_sort: obj/quick_1_sort.o obj/sort_driver_lab.o
	g++ $(CFLAGS) -o bin/quick_1_lab_sort obj/quick_1_sort.o obj/sort_driver_lab.o

bin/quick_3_sort: obj/quick_3_sort.o obj/sort_driver.o
	g++ $(CFLAGS) -o bin/quick_3_sort obj/quick_3_sort.o obj/sort_driver.o

