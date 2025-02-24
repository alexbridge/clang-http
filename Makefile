.SHELL := /bin/bash

CCC := clang++
CCC_OPTS := -std=c++17
CCC_OPTS_COMPILE := $(CCC_OPTS) -c

BUILDER := docker run -it -v .:/app -w /app silkeh/clang:16
DOCKER_DEBIAN_12_IT := docker run -it -v .:/app -w /app debian:sid-slim
DOCKER_DEBIAN_12 := docker run -v .:/app -w /app -p 8090:8090 debian:12-slim

ALL_CPP := $$(find . -name "*.cpp" ! -name "main.cpp" ! -name "app.cpp" ! -name "sample.cpp")

build-app:
	@clang++ -std=c++17 app.cpp -o app
	./app

build-sample-alone:
	@echo $(ALL_CPP)
	@$(CCC) $(CCC_OPTS) $(ALL_CPP) samples/sample.cpp -o sample

HTTP_ALL_CPP := $$(find ./http-server -name '*.cpp')

build-app-server:
	clang++ -std=c++17 $(HTTP_ALL_CPP) -o app-server
run-app-server:
	$(DOCKER_DEBIAN_12) ./app-server 8090
exec-app-server:
	$(DOCKER_DEBIAN_12_IT) bash
exec-builder:
	$(BUILDER) bash

clean:
	rm -fr build

cpp_files := $(shell find . -name "*.cpp" | cut -c3-)
o_files := $(patsubst %.cpp,build/%.o,$(cpp_files))

build/%.o: %.cpp
	@[ -d "$(@D)" ] || mkdir -p "$(@D)"
	@$(CCC) $(CCC_OPTS_COMPILE) $< -o $(@)
	@echo "$@ compiled"

build-all: $(o_files)

build-sample: clean build-all
	@echo "Link sample"
	@$(CCC) $(CCC_OPTS) build/utils/string.o build/samples/sample.o -o sample


.PHONY: destination source