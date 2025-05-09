# Makefile para V# (Flex + Bison + GCC/MinGW)

CC        := gcc
FLEX      := win_flex
BISON     := win_bison
SRC_DIR   := src
BUILD_DIR := build
TARGET    := vsharp

LEX_SRC   := $(BUILD_DIR)/lex.yy.c
Y_TAB_SRC := $(BUILD_DIR)/vsharp.tab.c
Y_TAB_HDR := $(BUILD_DIR)/vsharp.tab.h

LEX_OBJ   := $(BUILD_DIR)/lex.yy.o
Y_TAB_OBJ := $(BUILD_DIR)/vsharp.tab.o

all: $(BUILD_DIR)/$(TARGET).exe

$(BUILD_DIR):
	if not exist "$(BUILD_DIR)" mkdir "$(BUILD_DIR)"

$(Y_TAB_SRC) $(Y_TAB_HDR): $(SRC_DIR)/vsharp.y | $(BUILD_DIR)
	$(BISON) -d -o $(Y_TAB_SRC) $(SRC_DIR)/vsharp.y
	@echo "Bison gerou: $(Y_TAB_SRC) e $(Y_TAB_HDR)"

$(LEX_SRC): $(SRC_DIR)/vsharp.l $(Y_TAB_HDR) | $(BUILD_DIR)
	$(FLEX) -o $(LEX_SRC) $(SRC_DIR)/vsharp.l
	@echo "Flex gerou: $(LEX_SRC)"

$(Y_TAB_OBJ): $(Y_TAB_SRC)
	$(CC) -c $< -o $@

$(LEX_OBJ): $(LEX_SRC)
	$(CC) -c $< -o $@

$(BUILD_DIR)/$(TARGET).exe: $(Y_TAB_OBJ) $(LEX_OBJ)
	$(CC) $^ -o $@
	@echo "Executável: $@ pronto para uso"

clean:
	if exist "$(BUILD_DIR)" rmdir /s /q "$(BUILD_DIR)"
	if exist "$(TARGET).exe" del "$(TARGET).exe"
	@echo "Limpo."

.PHONY: all clean
