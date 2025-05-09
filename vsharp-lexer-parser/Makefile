# ---------- Variáveis ----------
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
MAIN_SRC  := $(SRC_DIR)/main.c
MAIN_OBJ  := $(BUILD_DIR)/main.o

# ---------- Alvo principal ----------
all: $(BUILD_DIR)/$(TARGET).exe

# ---------- Diretório build ----------
$(BUILD_DIR):
	if not exist "$(BUILD_DIR)" mkdir "$(BUILD_DIR)"

# ---------- Gerar parser ----------
$(Y_TAB_SRC) $(Y_TAB_HDR): $(SRC_DIR)/vsharp.y | $(BUILD_DIR)
	$(BISON) -d -o $(Y_TAB_SRC) $(SRC_DIR)/vsharp.y
	@echo "Bison gerou: $(Y_TAB_SRC) e $(Y_TAB_HDR)"

# ---------- Gerar scanner ----------
$(LEX_SRC): $(SRC_DIR)/vsharp.l $(Y_TAB_HDR) | $(BUILD_DIR)
	$(FLEX) -o $(LEX_SRC) $(SRC_DIR)/vsharp.l
	@echo "Flex gerou: $(LEX_SRC)"

# ---------- Compilar objetos ----------
$(Y_TAB_OBJ): $(Y_TAB_SRC)
	$(CC) -std=c99 -c $< -o $@

$(LEX_OBJ): $(LEX_SRC)
	$(CC) -std=c99 -c $< -o $@

$(MAIN_OBJ): $(MAIN_SRC) | $(BUILD_DIR)
	$(CC) -std=c99 -c $< -o $@

# ---------- Link final ----------
$(BUILD_DIR)/$(TARGET).exe: $(Y_TAB_OBJ) $(LEX_OBJ) $(MAIN_OBJ)
	$(CC) $^ -o $@
	@echo "Executável criado: $@"

# ---------- Limpar ----------
clean:
	if exist "$(BUILD_DIR)" rmdir /s /q "$(BUILD_DIR)"

.PHONY: all clean
