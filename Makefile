.PHONY: all build rebuild check test testextra memtest memtestextra clean coverage

all: clean check build test coverage

clean:
	rm -rf build

check:
	cd scripts && chmod +x run_linters.sh && ./run_linters.sh

build:
	cd scripts && chmod +x build.sh && ./build.sh

test: build
	cd scripts && chmod +x run_tests.sh && ./run_tests.sh

coverage:
	cd scripts && chmod +x coverage.sh && ./coverage.sh
