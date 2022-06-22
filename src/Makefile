CC=cc
CFLAGS=-g -Wall -Wextra

# Cryptoarithmetic app 
bin/cryptosolver:  bin/cryptoarithmetic.so bin/main.so | bin/.
	$(CC) $(CFLAGS) $^ -o $@

bin/main.so: build/main.o bin/cryptoarithmetic.so build/wordlist.o build/solutionbook.o| bin/.
	$(CC) $(CFLAGS) -shared $^ -o $@

build/main.o: src/main.c | build/.
	$(CC) -c -fPIC $(CFLAGS) $< -o $@

# Cryptoarithmetic Library
bin/cryptoarithmetic.so:  bin/solutionbook.so build/solutionkey.o build/wordlist.o build/cryptoarithmetic.o| build/. bin/.
	$(CC) $(CFLAGS) -shared $^ -o $@

bin/solutionbook.so: build/solutionkey.o build/solutionbook.o | bin/.
	$(CC) $(CFLAGS) -shared $^ -o $@

build/%.o: src/%.c src/%.h | build/.
	$(CC) -c -fPIC $(CFLAGS) $< -o $@

%/.:
	mkdir -p $@ 

.PHONY: clean
clean:
	rm -rf bin/ build/ doc/

.PHONY: lint
lint:
	cpplint --filter=-build/header_guard,-build/include_subdir,-readability,-casting,-runtime/int src/*.h src/*.c

