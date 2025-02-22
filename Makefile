.SHELL := /bin/bash

CCC := clang++
CCC_OPTS := -std=c++17 -c

BUILDER := docker run -it -v .:/app -w /app silkeh/clang:16
DOCKER_DEBIAN_12_IT := docker run -it -v .:/app -w /app debian:sid-slim
DOCKER_DEBIAN_12 := docker run -v .:/app -w /app -p 8090:8090 debian:12-slim

build-app:
	@clang++ -std=c++17 app.cpp -o app
	./app

build-sample:
	@clang++ -std=c++17 utils/string.cpp samples/sample.cpp -o sample
	./sample

HTTP_ALL_CPP := $$(find ./http-server -name '*.cpp')

build-app-server:
	clang++ -std=c++17 $(HTTP_ALL_CPP) -o app-server
run-app-server:
	$(DOCKER_DEBIAN_12) ./app-server 8090
exec-app-server:
	$(DOCKER_DEBIAN_12_IT) bash
exec-builder:
	$(BUILDER) bash

cpp_files := $(shell find . -name "*.cpp" | cut -c3-)
o_files := $(patsubst %.cpp,build/%.o,$(cpp_files))

build/%.o: %.cpp
	@[ -d "$(@D)" ] || mkdir -p "$(@D)"
	@$(CCC) $(CCC_OPTS) $< -o $(@)

build-all: $(o_files)

.PHONY: destination source