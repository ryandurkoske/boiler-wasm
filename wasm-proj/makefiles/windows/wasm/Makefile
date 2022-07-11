TARGET_EXEC ?= verm.wasm

BIN_DIR ?= ../verm-client-pwa/public
BUILD_DIR ?= ./build
SRC_DIRS ?= src

C_FILES := $(shell find $(SRC_DIRS) -name *.c)
CPP_FILES := #$(shell find $(SRC_DIRS) -name *.cpp)
ALL_SRCS := $(C_FILES) $(CPP_FILES)
SRCS = $(filter-out $(SRC_DIRS)/main/server_main.c, $(ALL_SRCS))

OBJS := $(SRCS:%=$(BUILD_DIR)/%.o)
DEPS := $(OBJS:.o=.d)

INC_DIRS := $(shell find $(SRC_DIRS) -type d)
INC_FLAGS := $(addprefix -I,$(INC_DIRS))

D_FLAGS = -D CXX_WASMCLIENT

COMPILE_FLAGS = -Wall \
		--target=wasm32 \
		-Os \
		-nostdlib \
		-fvisibility=hidden \
		-ffunction-sections \
		-fdata-sections \
		-DPRINTF_DISABLE_SUPPORT_FLOAT=1 \
		-DPRINTF_DISABLE_SUPPORT_LONG_LONG=1 \
		-DPRINTF_DISABLE_SUPPORT_PTRDIFF_T=1 \
		$(D_FLAGS)



#link
$(BIN_DIR)/$(TARGET_EXEC): $(OBJS)
	wasm-ld \
		-o $(BIN_DIR)/$(TARGET_EXEC) \
		--no-entry \
		--strip-all \
		--export-dynamic \
		--allow-undefined \
		--initial-memory=131072 \
		-error-limit=0 \
		--lto-O3 \
		-O3 \
		--gc-sections \
		$(OBJS)

#build object files into build folder
$(BUILD_DIR)/%.c.o: %.c
	mkdir -p $(dir $@)
	clang \
		-std=c17 \
		$(COMPILE_FLAGS) \
		$(INC_FLAGS) \
		-c $< \
		-o $@
		
-include $(DEPS)

