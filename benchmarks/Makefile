all: with_unlocks.bin without_unlocks.bin

# no dependencies here

with_unlocks.bin: with_unlocks.c
	gcc -pthread with_unlocks.c -o with_unlocks.bin

without_unlocks.bin: without_unlocks.c
	gcc -pthread without_unlocks.c -o without_unlocks.bin

# no need to run this, but it'll clear out your local directory of .bin files
clean:
	rm -rf *.o *.bin
