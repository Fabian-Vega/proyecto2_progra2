CXX=g++
CXXFLAGS=-Wall -Wextra -std=c++17 -fno-elide-constructors
DEFS=#-DVERBOSE

.PHONY: all
all: bin/mainApp bin/appGraph

.PHONY: asan
asan: CXXFLAGS += -fsanitize=address -fno-omit-frame-pointer
asan: all

# Link appGraph
bin/appGraph: build/LinkedUp.o bin/graph.a | bin/.
	$(CXX) -g $(CXXFLAGS) $(DEFS) $^ -o $@

# Compile app
build/LinkedUp.o: src/LinkedUp.cpp | build/.
	$(CXX) -c -g $(CXXFLAGS) $(DEFS) -Isrc $< -o $@

# Link mainApp
bin/mainApp: build/main.o bin/graph.a | bin/.
	$(CXX) -g $(CXXFLAGS) $(DEFS) $^ -o $@

# Compile app
build/main.o: src/main.cpp | build/.
	$(CXX) -c -g $(CXXFLAGS) $(DEFS) -Isrc $< -o $@

# graph library
#Lo que cambie probablemente es la linea 23
bin/graph.a: build/graph.o build/vertex.o | bin/.
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