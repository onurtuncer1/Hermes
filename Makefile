
# Default target
all: help

# Base directory for your project
ROOT_DIR := $(shell pwd)
BUILD_DIR := $(ROOT_DIR)/build

# Targets
.PHONY: all gcc-release  gcc-debug gcc-test clang-debug

all: gcc-release

# Default gcc-release build
gcc-release:
	cmake --preset=gcc-release
	cmake --build --preset=gcc-release

# Default gcc-debug build
gcc-debug:
	cmake --preset=gcc-debug
	cmake --build --preset=gcc-debug

# Default gcc-test build
gcc-test:
	cmake --preset=gcc-test
	cmake --build --preset=gcc-test

# Default clang-debug build
clang-debug:
	cmake --preset=clang-debug
	cmake --build --preset=clang-debug

# Style
# --------------------------------------------------------------------
.PHONY: check-format format check-newlines

check-format:
	$(call colorecho,'Checking formatting with astyle')
	@"$(ROOT_DIR)"/tools/astyle/check_code_style_all.sh
	@cd "$(ROOT_DIR)" && git diff --check

format:
	$(call colorecho,'Formatting with astyle')
	@"$(ROOT_DIR)"/tools/astyle/check_code_style_all.sh --fix

check-newlines:
	$(call colorecho,'Checking for missing or duplicate newlines at the end of files')
	@"$(ROOT_DIR)"/tools/astyle/check_newlines.sh

# Testing
# --------------------------------------------------------------------
.PHONY: tests test-coverage

tests: gcc-test
	cd $(BUILD_DIR)/gcc-test && ctest --output-on-failure


# Static analysis
# --------------------------------------------------------------------
.PHONY: static-analysis

STATIC_ANALYSIS_DIR := $(BUILD_DIR)/static_analysis

static-analysis:
	@echo "Running static analysis"
	@mkdir -p $(STATIC_ANALYSIS_DIR)
	@cd $(STATIC_ANALYSIS_DIR) && \
		cmake $(ROOT_DIR) \
			-G "Unix Makefiles" \
			-DCMAKE_BUILD_TYPE=Release \
			-DENABLE_STATIC_ANALYSIS=ON 
	@make -j$(shell nproc) -C $(STATIC_ANALYSIS_DIR) static_analysis

# Documentation
# --------------------------------------------------------------------
.PHONY: documents

DOC_SRC_DIR := $(ROOT_DIR)
DOC_BUILD_DIR := $(BUILD_DIR)

documents:
	@echo "Building documentation from $(DOC_SRC_DIR) into $(DOC_BUILD_DIR)"
	@mkdir -p "$(DOC_BUILD_DIR)"
	cd "$(DOC_BUILD_DIR)" && \
		cmake -S "$(DOC_SRC_DIR)" -B $(DOC_BUILD_DIR) \
		      -G"Unix Makefiles" \
			  -DCMAKE_CXX_STANDARD=23 \
			  -DBUILD_DOCS=ON && \
		$(MAKE)

# Cleanup
# --------------------------------------------------------------------
.PHONY: clean
clean:
	@echo "Cleaning up build artifacts"
	@rm -rf build/*

# Help 
# --------------------------------------------------------------------
%::
	@echo "Unknown target: $@"
	@echo "Use 'make help' to see available targets."
	@false

# Print a list of non-config targets (based on http://stackoverflow.com/a/26339924/1487069)
help:
	@echo "Usage: $(MAKE) <target>"
	@echo "Where <target> is one of:"
	@$(MAKE) -pRrq -f $(lastword $(MAKEFILE_LIST)) : 2>/dev/null | \
		awk -v RS= -F: '/(^|\n)# Files(\n|$$)/,/(^|\n)# Finished Make data base/ {if ($$1 !~ "^[#.]") {print $$1}}' | sort | \
		egrep -v -e '^[^[:alnum:]]' -e '^($(subst $(space),|,$(ALL_CONFIG_TARGETS)))$$' -e '_default$$' -e '^(Makefile)'
	@echo
	@echo "Or, $(MAKE) <config_target> [<make_target(s)>]"
	@echo "Use '$(MAKE) list_config_targets' for a list of configuration targets."
