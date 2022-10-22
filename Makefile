.PHONY: all build rebuild check test testextra memtest memtestextra clean

all: clean check build test

clean:
	rm -rf build

check:
	cd scripts && ./run_linters.sh

build:
	cd scripts && ./build.sh

test:
	cd scripts && ./run_tests.sh
