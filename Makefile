.SHELL := /bin/bash

CCC := clang++
CCC_OPTS := -std=c++17
CCC_OPTS_COMPILE := $(CCC_OPTS) -c

IMAGE_BUILDER := clang/clang16:builder
IMAGE_RUNNER := clang/clang16:runner
BUILDER := docker run -it -v .:/app -w /app $(IMAGE_BUILDER)
RUNNER := docker run -it -v .:/app -w /app -p 8080:8080 $(IMAGE_RUNNER)
DOCKER_DEBIAN_12_IT := docker run -it -v .:/app -w /app debian:12-slim
DOCKER_DEBIAN_12 := docker run -v .:/app -w /app -p 8090:8090 debian:12-slim

NON_APPS_CPP := $(shell find src -name "*.cpp" ! -wholename "src/apps/*")
# src/utils/string.cpp -> utils/string.cpp
NON_APPS_CPP_RELATIVE := $(shell find src -name "*.cpp" ! -wholename "src/apps/*" | cut -c5-)
NON_APPS_CPP_O := $(patsubst %.cpp,build/%.o,$(NON_APPS_CPP_RELATIVE))

tag-builder:
	docker build -f ./docker/Builder -t $(IMAGE_BUILDER) .
tag-runner:
	docker build -f ./docker/Runner -t $(IMAGE_RUNNER) .

echo:
	@echo $(NON_APPS_CPP_RELATIVE)
	@echo $(NON_APPS_CPP_O)
	@echo $(ALL_CPP)
	@echo $(ALL_CPP_O)

build-socket-server:
	@$(BUILDER) $(CCC) $(CCC_OPTS) $(NON_APPS_CPP) src/apps/socket-server.cpp -o socket-server
run-socket-server:
	$(DOCKER_DEBIAN_12) ./socket-server
exec-builder:
	$(BUILDER) sh
exec-runner:
	$(RUNNER) sh

# ===== COMPILE AND LINK SEPARATELY
ALL_CPP := $(shell find src -name "*.cpp")
ALL_CPP_RELATIVE := $(shell find src -name "*.cpp")
ALL_CPP_O := $(patsubst src/%.cpp,build/%.o,$(ALL_CPP_RELATIVE))

clean:
	rm -fr build

build/%.o: src/%.cpp
	@[ -d "$(@D)" ] || mkdir -p "$(@D)"
	@$(CCC) $(CCC_OPTS_COMPILE) $< -o $(@)
	@echo "$@ compiled"

build-all: $(ALL_CPP_O)

build-socket-server-slim: clean build-all
	@$(BUILDER) $(CCC) $(CCC_OPTS) $(NON_APPS_CPP_O) build/apps/socket-server.o -o socket-server-slim

run-socket-server-slim:
	$(RUNNER) ./socket-server-slim


.PHONY: destination source