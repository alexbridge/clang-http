.SHELL := /bin/bash

CCC := clang++
CCC_OPTS := -std=c++17
CCC_OPTS_COMPILE := $(CCC_OPTS) -c

IMAGE_BUILDER := clang/clang16:builder
IMAGE_RUNNER := clang/clang16:runner
DOCKER_USER := --user "$$(id -u):$$(id -g)"
BUILDER := docker run -it -v .:/app -w /app --rm $(IMAGE_BUILDER)
RUNNER := docker run -it $(DOCKER_USER) -v .:/app -w /app -p 8080:8080 --rm $(IMAGE_RUNNER)

tag-builder:
	docker build -f ./docker/Builder -t $(IMAGE_BUILDER) .
tag-runner:
	docker build -f ./docker/Runner -t $(IMAGE_RUNNER) .
tag: tag-builder tag-runner
exec-builder:
	$(BUILDER) sh
exec-runner:
	$(RUNNER) sh

NON_APPS_CPP := $(shell find src -name "*.cpp" ! -wholename "src/apps/*")
# src/utils/string.cpp -> utils/string.cpp
NON_APPS_CPP_RELATIVE := $(shell find src -name "*.cpp" ! -wholename "src/apps/*" | cut -c5-)
NON_APPS_CPP_O := $(patsubst %.cpp,build/%.o,$(NON_APPS_CPP_RELATIVE))

echo:
	@echo $(NON_APPS_CPP_RELATIVE)
	@echo $(NON_APPS_CPP_O)
	@echo $(ALL_CPP)
	@echo $(ALL_CPP_O)

# build-socket-server:
# 	@$(BUILDER) $(CCC) $(CCC_OPTS) $(NON_APPS_CPP) src/apps/socket-server.cpp -o bin/socket-server
# run-socket-server:
# 	$(RUNNER) ./bin/socket-server

# ===== COMPILE AND LINK SEPARATELY
ALL_CPP := $(shell find src -name "*.cpp")
ALL_CPP_RELATIVE := $(shell find src -name "*.cpp")
ALL_CPP_O := $(patsubst src/%.cpp,build/%.o,$(ALL_CPP_RELATIVE))

clean-bin:
	rm -fr bin/*
clean-build:
	rm -fr build/*

build/%.o: src/%.cpp
	@[ -d "$(@D)" ] || mkdir -p "$(@D)"
	@$(BUILDER) $(CCC) $(CCC_OPTS_COMPILE) $< -o $(@)
	@echo "$@ compiled"

build-all: $(ALL_CPP_O)

build-socket-server: clean-build build-all
	@$(BUILDER) $(CCC) $(CCC_OPTS) $(NON_APPS_CPP_O) build/apps/socket-server.o -o bin/socket-server

run-socket-server: clean-bin build-all
	@$(BUILDER) $(CCC) $(CCC_OPTS) $(NON_APPS_CPP_O) build/apps/socket-server.o -o bin/socket-server
	@$(RUNNER) ./bin/socket-server
run-http-server: clean-bin build-all
	@$(BUILDER) $(CCC) $(CCC_OPTS) $(NON_APPS_CPP_O) build/apps/http-server.o -o bin/http-server
	@$(RUNNER) ./bin/http-server

run-cli-algs: clean-bin build-all
	@$(BUILDER) $(CCC) $(CCC_OPTS) $(NON_APPS_CPP_O) build/apps/cli-algs.o -o bin/cli-algs
	@$(RUNNER) ./bin/cli-algs
run-raw-socket: clean-bin build-all
	@$(BUILDER) $(CCC) $(CCC_OPTS) $(NON_APPS_CPP_O) build/apps/raw-socket.o -o bin/raw-socket
	@$(RUNNER) ./bin/raw-socket
run-cli-io: clean-bin build-all
	@$(BUILDER) $(CCC) $(CCC_OPTS) src/apps/cli-io.cpp -o bin/cli_io
	@$(RUNNER) ./bin/cli_io

snippet-class:
	@$(BUILDER) $(CCC) $(CCC_OPTS) snippets/class.cpp -o bin/snippet_class
	@$(RUNNER) ./bin/snippet_class


.PHONY: build-all