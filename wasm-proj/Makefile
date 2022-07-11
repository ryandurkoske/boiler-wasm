SRC_DIR := src
NATIVE_SRC_DIR := $(SRC_DIR)/native
SHARED_SRC_DIR := $(SRC_DIR)/shared
WASM_SRC_DIR := $(SRC_DIR)/wasm

#add more native folders here
NATIVE_SRC := $(wildcard $(NATIVE_SRC_DIR)/*.c)

#add more shared folders here
SHARED_SRC := $(wildcard $(SHARED_SRC_DIR)/*.c) \
	$(wildcard $(SHARED_SRC_DIR)/nested/*.c)

#add more wasm folders here
WASM_SRC := $(wildcard $(WASM_SRC)/*.c)

OBJ_DIR := builds
NATIVE_OBJ_DIR := $(OBJ_DIR)/native
WASM_OBJ_DIR := $(OBJ_DIR)/wasm

NATIVE_BIN_DIR := bin
NATIVE_TARGET := $(NATIVE_BIN_DIR)/program.exe

WASM_BIN_DIR := bin
WASM_TARGET := $(WASM_BIN_DIR)/program.wasm



.PHONY: all native wasm clean clean_native clean_wasm

all: $(NATIVE_TARGET) $(WASM_TARGET)


native: $(NATIVE_TARGET)

SRCS := $(NATIVE_SRC) $(SHARED_SRC)
OBJS := $(SRCS:%=$(NATIVE_OBJ_DIR)/%.o)

$(NATIVE_OBJ_DIR)/%.c.o: C_PREPROCESSOR_FLAGS := -Iinclude -MMD -MP
$(NATIVE_OBJ_DIR)/%.c.o: COMPILER_FLAGS   := -Wall
$(NATIVE_TARGET): LDFLAGS  := -Llib
$(NATIVE_TARGET): LDLIBS   :=

$(NATIVE_TARGET): LD := clang
$(NATIVE_OBJ_DIR)/%.c.o: CC := clang

$(NATIVE_TARGET): $(OBJS)
	$(LD) -o $@ $(LDFLAGS) $(LDLIBS) $^

$(NATIVE_OBJ_DIR)/%.c.o: %.c
	if not exist "$(dir $@)" mkdir "$(dir $@)"
	$(CC) $(C_PREPROCESSOR_FLAGS) $(COMPILER_FLAGS) -c $< -o $@


wasm: $(WASM_TARGET)

SRCS := $(WASM_SRC) $(SHARED_SRC)
OBJS := $(SRCS:%=$(WASM_OBJ_DIR)/%.o)

$(WASM_OBJ_DIR)/%.c.o: C_PREPROCESSOR_FLAGS := -Iinclude -MMD -MP
$(WASM_OBJ_DIR)/%.c.o: COMPILER_FLAGS := -Wall \
	-Os \
	-nostdlib \
	-fvisibility=hidden \
	-ffunction-sections \
	-fdata-sections \
	-DPRINTF_DISABLE_SUPPORT_FLOAT=1 \
	-DPRINTF_DISABLE_SUPPORT_LONG_LONG=1 \
	-DPRINTF_DISABLE_SUPPORT_PTRDIFF_T=1 \
	$(D_FLAGS)

$(WASM_TARGET): LDFLAGS  := -Llib \
	--no-entry \
	--strip-all \
	--export-dynamic \
	--allow-undefined \
	--initial-memory=131072 \
	--error-limit=0 \
	--lto-O3 \
	-O3 \
	--gc-sections
$(WASM_TARGET): LDLIBS := 

$(WASM_TARGET): LD := wasm-ld
$(WASM_OBJ_DIR)/%.c.o: CC := clang --target=wasm32

$(WASM_TARGET): $(OBJS)
	$(LD) -o $@ $(LDFLAGS) $(LDLIBS) $^

$(WASM_OBJ_DIR)/%.c.o: %.c
	if not exist "$(dir $@)" mkdir "$(dir $@)"
	$(CC) $(C_PREPROCESSOR_FLAGS) $(COMPILER_FLAGS) -c $< -o $@


clean:
	- rmdir "$(OBJ_DIR)" /s /q
	- del /f "$(NATIVE_TARGET)" /q
	- del /f "$(WASM_TARGET)" /q

clean_native:
	- rmdir "$(NATIVE_OBJ_DIR)" /s /q
	- del /f "$(NATIVE_TARGET)" /q

clean_wasm:
	- rmdir "$(WASM_OBJ_DIR)" /s /q
	- del /f "./$(WASM_TARGET)" /q

#-include $(NATIVE_DEPS)
#-include $(WASM_OBJ:.o=.d)