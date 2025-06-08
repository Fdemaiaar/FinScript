###############################################################################
# ValuationSharp – build
###############################################################################

# ---------------------------------------------------------------------------
# 1. Ferramentas / flags por plataforma
# ---------------------------------------------------------------------------
ifeq ($(OS),Windows_NT)                       # ---------- Windows ----------
FLEX   ?= win_flex
BISON  ?= win_bison
CLANG  ?= clang                               # do pacote LLVM instalado
RM      = del /Q
MKDIR   = if not exist "$(1)" mkdir "$(1)"
RMDIR   = if exist "$(1)" rmdir /S /Q "$(1)"
else                                          # ---------- Unix/macOS --------
FLEX   ?= flex
BISON  ?= bison
CLANG  ?= clang
RM      = rm -f
MKDIR   = mkdir -p "$(1)"
RMDIR   = rm -rf  "$(1)"
endif

CC      = gcc                                 # compilador C para o executável
BUILD   = build
SRC     = src

CFLAGS += -Isrc -I$(BUILD) -Wall -Wextra
LDFLAGS = -lm                                 # runtime usa <math.h>

# ---------------------------------------------------------------------------
# 2. Objetos do executável
# ---------------------------------------------------------------------------
OBJ = \
 $(BUILD)/ast.o        $(BUILD)/sem.o       $(BUILD)/irgen.o \
 $(BUILD)/runtime.o    \
 $(BUILD)/vsharp.tab.o $(BUILD)/lex.yy.o    $(BUILD)/main.o

BIN = $(BUILD)/vsharp.exe                   # extensão .exe no Windows ok no Unix

# ---------------------------------------------------------------------------
# 3. Alvos principais
# ---------------------------------------------------------------------------
.PHONY: all clean
all: $(BIN) $(BUILD)/runtime.bc             # ← runtime.bc sempre gerado

# ---------------------------------------------------------------------------
# 4. Diretório build
# ---------------------------------------------------------------------------
$(BUILD):
	@$(call MKDIR,$(BUILD))

# ---------------------------------------------------------------------------
# 5. Bison
# ---------------------------------------------------------------------------
$(BUILD)/vsharp.tab.c $(BUILD)/vsharp.tab.h: $(SRC)/vsharp.y | $(BUILD)
	$(BISON) -d -o $(@D)/vsharp.tab.c $<

$(BUILD)/vsharp.tab.o: $(BUILD)/vsharp.tab.c
	$(CC) $(CFLAGS) -c $< -o $@

# ---------------------------------------------------------------------------
# 6. Flex
# ---------------------------------------------------------------------------
$(BUILD)/lex.yy.c: $(SRC)/vsharp.l $(BUILD)/vsharp.tab.h | $(BUILD)
	$(FLEX) -o $@ $<

$(BUILD)/lex.yy.o: $(BUILD)/lex.yy.c
	$(CC) $(CFLAGS) -c $< -o $@

# ---------------------------------------------------------------------------
# 7. Fontes C genéricos
# ---------------------------------------------------------------------------
$(BUILD)/%.o: $(SRC)/%.c | $(BUILD)
	$(CC) $(CFLAGS) -c $< -o $@

# irgen precisa do header de tokens
$(BUILD)/irgen.o: $(SRC)/irgen.c $(BUILD)/vsharp.tab.h
	$(CC) $(CFLAGS) -c $< -o $@

# ---------------------------------------------------------------------------
# 8. Link do executável
# ---------------------------------------------------------------------------
$(BIN): $(OBJ) | $(BUILD)
	$(CC) -o $@ $(OBJ) $(LDFLAGS)
	@echo ">> Executável gerado: $@"

# ---------------------------------------------------------------------------
# 9. runtime.bc  (bitcode/IR usado pelo JIT)
# ---------------------------------------------------------------------------
$(BUILD)/runtime.bc: $(SRC)/runtime.c | $(BUILD)
	$(CLANG) -emit-llvm -c -o $@ $<
	@echo ">> Bitcode gerado: $@"

# ---------------------------------------------------------------------------
# 10. Limpeza
# ---------------------------------------------------------------------------
clean:
	@$(call RMDIR,$(BUILD))
	@echo ">> build/ removido"
