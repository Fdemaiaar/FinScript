###############################################################################
# ValuationSharp – build (Windows-first, filtro de logs restaurado)
###############################################################################

BUILD = build
SRC   = src

# ---------------------------------------------------------------------------
# cria build/ se faltar
# ---------------------------------------------------------------------------
$(BUILD):
	@if not exist "$(BUILD)" mkdir "$(BUILD)"

# ---------------------------------------------------------------------------
# ferramentas
# ---------------------------------------------------------------------------
ifeq ($(OS),Windows_NT)
FLEX  ?= win_flex
BISON ?= win_bison
CLANG ?= clang
CC    = gcc
RM    = del /Q
RMDIR = if exist "$(1)" rmdir /S /Q "$(1)"
CAT   = type
NULL  = >nul 2>&1
RUN   = build\\vsharp.exe
else
FLEX  ?= flex
BISON ?= bison
CLANG ?= clang
CC    = gcc
RM    = rm -f
RMDIR = rm -rf "$(1)"
CAT   = cat
NULL  = >/dev/null 2>&1
RUN   = build/vsharp.exe
endif

CFLAGS += -Isrc -I$(BUILD) -Wall -Wextra
LDFLAGS = -lm

# ---------------------------------------------------------------------------
# objetos
# ---------------------------------------------------------------------------
OBJ = \
 $(BUILD)/ast.o $(BUILD)/sem.o $(BUILD)/irgen.o $(BUILD)/runtime.o \
 $(BUILD)/vsharp.tab.o $(BUILD)/lex.yy.o $(BUILD)/main.o

BIN = $(BUILD)/vsharp.exe

# ---------------------------------------------------------------------------
# alvos principais
# ---------------------------------------------------------------------------
.PHONY: all clean test
all: | $(BUILD) $(BIN) $(BUILD)/runtime.bc

# ---------------------------------------------------------------------------
# bison
# ---------------------------------------------------------------------------
$(BUILD)/vsharp.tab.c $(BUILD)/vsharp.tab.h: $(SRC)/vsharp.y | $(BUILD)
	$(BISON) -d -o $(@D)/vsharp.tab.c $<

$(BUILD)/vsharp.tab.o: $(BUILD)/vsharp.tab.c
	$(CC) $(CFLAGS) -c $< -o $@

# ---------------------------------------------------------------------------
# flex
# ---------------------------------------------------------------------------
$(BUILD)/lex.yy.c: $(SRC)/vsharp.l $(BUILD)/vsharp.tab.h | $(BUILD)
	$(FLEX) -o $@ $<

$(BUILD)/lex.yy.o: $(BUILD)/lex.yy.c
	$(CC) $(CFLAGS) -c $< -o $@

# ---------------------------------------------------------------------------
# fontes C
# ---------------------------------------------------------------------------
$(BUILD)/%.o: $(SRC)/%.c | $(BUILD)
	$(CC) $(CFLAGS) -c $< -o $@

# irgen precisa do header dos tokens
$(BUILD)/irgen.o: $(SRC)/irgen.c $(BUILD)/vsharp.tab.h
	$(CC) $(CFLAGS) -c $< -o $@

# ---------------------------------------------------------------------------
# link
# ---------------------------------------------------------------------------
$(BIN): $(OBJ)
	$(CC) -o $@ $(OBJ) $(LDFLAGS)
	@echo ">> Executavel gerado: $@"

# ---------------------------------------------------------------------------
# runtime.bc
# ---------------------------------------------------------------------------
$(BUILD)/runtime.bc: $(SRC)/runtime.c | $(BUILD)
	$(CLANG) -emit-llvm -c -o $@ $<
	@echo ">> Bitcode gerado: $@"

# ---------------------------------------------------------------------------
# testes
# ---------------------------------------------------------------------------
SCRATCH = $(BUILD)\scratch
$(SCRATCH):
	@if not exist "$(SCRATCH)" mkdir "$(SCRATCH)"

test: all | $(SCRATCH)
ifeq ($(OS),Windows_NT)
	@echo === Testes de sucesso ===
	@for %%f in (examples\*.vs) do ( \
		$(CAT) "%%f" | $(RUN) | \
		findstr /V /R /C:"^IR gerado" /C:"^Executando JIT" \
		> "$(SCRATCH)\out.tmp" && ( \
			fc /N "%%~dpnf.expected" "$(SCRATCH)\out.tmp" >nul 2>&1 \
			&& $(RM) "$(SCRATCH)\out.tmp" \
		) || ( \
			echo ❌ Falha em %%f & \
			echo ----- ESPERADO ----- & $(CAT) "%%~dpnf.expected" & \
			echo ----- OBTIDO  ------ & $(CAT) "$(SCRATCH)\out.tmp" & \
			exit /b 1 \
		) \
	)
	@echo === Testes que DEVEM falhar ===
	@for %%f in (examples\error\*.vs) do ( \
		$(CAT) "%%f" | $(RUN) $(NULL) && ( \
			echo ❌ Nenhum erro em %%f & exit /b 1 \
		) || echo ✓ Erro detectado \
	)
	@echo ✔ Todos os testes passaram
else
	@echo "Este Makefile está configurado apenas para Windows."
endif

clean:
	@$(call RMDIR,$(BUILD))
