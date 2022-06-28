CXX=g++
CXXFLAGS=-Wall -Wextra -std=c++17 -fno-elide-constructors
DEFS=#-DVERBOSE

.PHONY: all
all: bin/appGraph

.PHONY: asan
asan: CXXFLAGS += -fsanitize=address -fno-omit-frame-pointer
asan: all

# Link appGraph
bin/appGraph: bin/main.a bin/graph.a bin/vertex.a | bin/.
	$(CXX) -g $(CXXFLAGS) $(DEFS) $^ -o $@

# Compile app
bin/main.a: build/main.o bin/vertex.a bin/graph.a | bin/.
	ar rs $@ $^

build/main.o: src/main.cpp | build/.
	$(CXX) -c -g $(CXXFLAGS) $(DEFS) -Isrc $< -o $@

# graph library
#Lo que cambie probablemente es la linea 23
bin/graph.a: build/graph.o bin/vertex.a | bin/.
	ar rs $@ $^

# vertex library
bin/vertex.a: build/vertex.o build/link.o | bin/.
	ar rs $@ $^

build/%.o: src/%.cpp src/%.hpp | build/.
	$(CXX) -c -g $(CXXFLAGS) $(DEFS) $< -o $@

.PRECIOUS: %/.
%/.:
	mkdir -p $@

.PHONY: clean
clean:
	rm -rf bin/ build/ doc/

.PHONY: lint
lint:
	cpplint --filter=-build/header_guard,-build/include_subdir,-build/c++11,-runtime/references src/*.?pp src/*.?pp