all: generate build test
	
generate:
	cmake -S . -B dist

build: generate
	cmake --build dist

test: build
	ctest --test-dir dist --output-on-failure

