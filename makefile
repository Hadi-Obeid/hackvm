# tool macros
CC ?= gcc

# --- FIX: Fetch BOTH compilation flags (-I) and linker flags (-L / -lunity) ---
UNITY_CFLAGS := $(shell pkg-config --cflags unity 2>/dev/null)
UNITY_LIBS   := $(shell pkg-config --libs unity 2>/dev/null)

# Fallback defaults if pkg-config flags are blank outside Nix
CFLAGS := -Wall -O1 -Wpedantic $(if $(UNITY_CFLAGS),$(UNITY_CFLAGS),-I$(UNITY_INCLUDE_DIR)) -Isrc/ -Itest/
LDFLAGS := $(if $(UNITY_LIBS),$(UNITY_LIBS),-lunity)

DBGFLAGS := -g
COBJFLAGS := $(CFLAGS) -c

# path macros
BIN_PATH := bin
OBJ_PATH := obj
SRC_PATH := src
DBG_PATH := debug
TEST_PATH := test

# compile macros
TARGET_NAME := vm
TARGET := $(BIN_PATH)/$(TARGET_NAME)
TARGET_DEBUG := $(DBG_PATH)/$(TARGET_NAME)
TARGET_TEST := $(BIN_PATH)/test_runner

# src files & obj files
SRC := $(foreach x, $(SRC_PATH), $(wildcard $(addprefix $(x)/*,.c*)))
TEST_SRC := $(wildcard $(TEST_PATH)/*.c)

OBJ := $(addprefix $(OBJ_PATH)/, $(addsuffix .o, $(notdir $(basename $(SRC)))))
OBJ_DEBUG := $(addprefix $(DBG_PATH)/, $(addsuffix .o, $(notdir $(basename $(SRC)))))

# Separate source file configurations
SRC_NO_MAIN := $(filter-out $(SRC_PATH)/main.c, $(SRC))
OBJ_SRC_FOR_TEST := $(addprefix $(TEST_PATH)/, $(addsuffix .o, $(notdir $(basename $(SRC_NO_MAIN)))))
OBJ_TEST_FILES := $(addprefix $(TEST_PATH)/, $(addsuffix .o, $(notdir $(basename $(TEST_SRC)))))

# Notice: We removed $(TEST_PATH)/unity.o entirely because we are linking the archive file!
OBJ_TEST := $(OBJ_TEST_FILES) $(OBJ_SRC_FOR_TEST)

DISTCLEAN_LIST := $(OBJ) $(OBJ_DEBUG) $(OBJ_TEST)
CLEAN_LIST := $(TARGET) $(TARGET_DEBUG) $(TARGET_TEST) $(DISTCLEAN_LIST)

default: makedir all

$(TARGET): $(OBJ)
	$(CC) -o $@ $(OBJ) $(CFLAGS)

$(OBJ_PATH)/%.o: $(SRC_PATH)/%.c*
	$(CC) $(COBJFLAGS) -o $@ $<

$(DBG_PATH)/%.o: $(SRC_PATH)/%.c*
	$(CC) $(COBJFLAGS) $(DBGFLAGS) -o $@ $<

# Test directory compilation targets
$(TEST_PATH)/%.o: $(TEST_PATH)/%.c*
	$(CC) $(COBJFLAGS) $(DBGFLAGS) -o $@ $<

$(TEST_PATH)/%.o: $(SRC_PATH)/%.c*
	$(CC) $(COBJFLAGS) $(DBGFLAGS) -o $@ $<

$(TARGET_DEBUG): $(OBJ_DEBUG)
	$(CC) $(CFLAGS) $(DBGFLAGS) $(OBJ_DEBUG) -o $@

# --- FIX: Append LDFLAGS to link libunity.a cleanly ---
$(TARGET_TEST): $(OBJ_TEST)
	$(CC) $(CFLAGS) $(DBGFLAGS) $(OBJ_TEST) -o $@ $(LDFLAGS)

.PHONY: makedir
makedir:
	@mkdir -p $(BIN_PATH) $(OBJ_PATH) $(DBG_PATH) $(TEST_PATH)

.PHONY: all
all: $(TARGET)

.PHONY: debug
debug: $(TARGET_DEBUG)

.PHONY: test
test: makedir $(TARGET_TEST)
	@echo "🏃 Running Tests..."
	@./$(TARGET_TEST)

VMFILE := SimpleAdd.vm

.PHONY: run
run: $(TARGET)
	@./run.sh data/$(VMFILE) && cat out.asm # run file and observe result
.PHONY: clean
clean:
	@echo CLEAN $(CLEAN_LIST)
	@rm -f $(CLEAN_LIST)

.PHONY: distclean
distclean:
	@echo CLEAN $(DISTCLEAN_LIST)
	@rm -rf $(BIN_PATH) $(OBJ_PATH) $(DBG_PATH) $(TEST_PATH)
