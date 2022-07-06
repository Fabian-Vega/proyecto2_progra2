CXX=g++
CXXFLAGS=-Wall -Wextra -std=c++17 -fno-elide-constructors
DEFS=#-DVERBOSE

.PHONY: all
all:  bin/appGraph

.PHONY: asan
asan: CXXFLAGS += -fsanitize=address -fno-omit-frame-pointer
asan: all
asan: test

.PHONY: test
test: bin/test bin/blackBoxTestingApp

.PHONY: val
val: 
	valgrind --leak-check=full -v  bin/appGraph

# Link appGraph
bin/appGraph: build/app.o bin/graph.a | bin/.
	$(CXX) -g $(CXXFLAGS) $(DEFS) $^ -o $@

# Compile app
build/app.o: src/app.cpp | build/.
	$(CXX) -c -g $(CXXFLAGS) $(DEFS) -Isrc $< -o $@


# Link blackBoxTestingApp
bin/blackBoxTestingApp: build/blackBoxTesting.o bin/graph.a | bin/.
	$(CXX) -g $(CXXFLAGS) $(DEFS) $^ -o $@

# Compile blackBoxTestingApp
build/blackBoxTesting.o: test/blackBoxTesting.cpp | build/.
	$(CXX) -c -g $(CXXFLAGS) $(DEFS) -Isrc $< -o $@



# Link catchApp
bin/test: build/testGraph.o bin/graph.a | bin/.
	$(CXX) -g $(CXXFLAGS) $(DEFS) $^ -o $@

# Compile catchApp
build/%.o: test/%.cpp | build/.
	$(CXX) -c -g $(CXXFLAGS) $(DEFS) -Isrc $< -o $@


# graph library
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