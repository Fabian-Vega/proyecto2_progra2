CXX=g++
CXXFLAGS=-Wall -Wextra -std=c++17 -fno-elide-constructors
DEFS=#-DVERBOSE

.PHONY: all
all:  bin/blackBoxTestingApp bin/appGraph bin/test

.PHONY: asan
asan: CXXFLAGS += -fsanitize=address -fno-omit-frame-pointer
asan: all

# Link appGraph
bin/appGraph: build/app.o bin/graph.a | bin/.
	$(CXX) -g $(CXXFLAGS) $(DEFS) $^ -o $@

# Compile app
build/app.o: src/app.cpp | build/.
	$(CXX) -c -g $(CXXFLAGS) $(DEFS) -Isrc $< -o $@

# Link blackBoxTestingApp
bin/blackBoxTestingApp: build/blackBoxTesting.o bin/graph.a | bin/.
	$(CXX) -g $(CXXFLAGS) $(DEFS) $^ -o $@

# Compile app
build/blackBoxTesting.o: test/blackBoxTesting.cpp | build/.
	$(CXX) -c -g $(CXXFLAGS) $(DEFS) -Isrc $< -o $@

# Link catchApp
bin/test: test/testGraph.o bin/graph.a | bin/.
	$(CXX) -g $(CXXFLAGS) $(DEFS) $^ -o $@

# Compile app
build/test/%.o: test/test/%.cpp | build/test/.
	$(CXX) -c -g $(CXXFLAGS) $(DEFS) -Isrc $< -o $@

# graph library
#Lo que cambie probablemente es la linea 2309
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