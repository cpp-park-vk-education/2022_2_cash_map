.PHONY: all build rebuild check test testextra memtest memtestextra clean

all: clean check build test

clean:
	rm -rf build

check:
	cd scripts && chmod +x run_linters.sh && ./run_linters.sh

build:
	cd scripts && chmod +x build.sh && ./build.sh

test: build
	cd scripts && chmod +x run_tests.sh && ./run_tests.sh
