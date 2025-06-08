###############################################################################
# ValuationSharp – build (Windows-first)
###############################################################################

# ---------------------------------------------------------------------------
# 0. Se build/ não existir, cria
# ---------------------------------------------------------------------------
BUILD = build
SRC   = src

$(BUILD):
	@if not exist "$(BUILD)" mkdir "$(BUILD)"

# ---------------------------------------------------------------------------
# 1. Ferramentas – Windows como padrão
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
RUN   = build\\vsharp.exe               # executável gerado
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
# 2. Objetos
# ---------------------------------------------------------------------------
OBJ = \
 $(BUILD)/ast.o        $(BUILD)/sem.o       $(BUILD)/irgen.o \
 $(BUILD)/runtime.o    \
 $(BUILD)/vsharp.tab.o $(BUILD)/lex.yy.o    $(BUILD)/main.o

BIN = $(BUILD)/vsharp.exe

# ---------------------------------------------------------------------------
# 3. Alvos principais
# ---------------------------------------------------------------------------
.PHONY: all clean test
all: $(BIN) $(BUILD)/runtime.bc

# ---------------------------------------------------------------------------
# 4. Bison
# ---------------------------------------------------------------------------
$(BUILD)/vsharp.tab.c $(BUILD)/vsharp.tab.h: $(SRC)/vsharp.y | $(BUILD)
	$(BISON) -d -o $(@D)/vsharp.tab.c $<

$(BUILD)/vsharp.tab.o: $(BUILD)/vsharp.tab.c
	$(CC) $(CFLAGS) -c $< -o $@

# ---------------------------------------------------------------------------
# 5. Flex
# ---------------------------------------------------------------------------
$(BUILD)/lex.yy.c: $(SRC)/vsharp.l $(BUILD)/vsharp.tab.h | $(BUILD)
	$(FLEX) -o $@ $<

$(BUILD)/lex.yy.o: $(BUILD)/lex.yy.c
	$(CC) $(CFLAGS) -c $< -o $@

# ---------------------------------------------------------------------------
# 6. Fontes C genéricos
# ---------------------------------------------------------------------------
$(BUILD)/%.o: $(SRC)/%.c | $(BUILD)
	$(CC) $(CFLAGS) -c $< -o $@

# irgen depende do header de tokens
$(BUILD)/irgen.o: $(SRC)/irgen.c $(BUILD)/vsharp.tab.h
	$(CC) $(CFLAGS) -c $< -o $@

# ---------------------------------------------------------------------------
# 7. Link
# ---------------------------------------------------------------------------
$(BIN): $(OBJ)
	$(CC) -o $@ $(OBJ) $(LDFLAGS)
	@echo ">> Executavel gerado: $@"

# ---------------------------------------------------------------------------
# 8. runtime.bc (LLVM)
# ---------------------------------------------------------------------------
$(BUILD)/runtime.bc: $(SRC)/runtime.c | $(BUILD)
	$(CLANG) -emit-llvm -c -o $@ $<
	@echo ">> Bitcode gerado: $@"

# ---------------------------------------------------------------------------
# 9. Testes automatizados  (versão original)
# ---------------------------------------------------------------------------
SCRATCH = $(BUILD)\scratch

$(SCRATCH):
	@if not exist "$(SCRATCH)" mkdir "$(SCRATCH)"

test: all | $(SCRATCH)
ifeq ($(OS),Windows_NT)
	@echo === Testes de sucesso ===
	@for %%f in (examples\*.vs) do ( \
		copy /Y "%%f" "$(SCRATCH)\test.vs" >nul & \
		$(CAT) "$(SCRATCH)\test.vs" | $(RUN) > "$(SCRATCH)\test.out" & \
		fc /N "%%~dpnf.expected" "$(SCRATCH)\test.out" >nul && ( \
			del "$(SCRATCH)\test.out" \
		) || ( \
			echo ❌ Falha em %%f & \
			echo ----- ESPERADO ----- & $(CAT) "%%~dpnf.expected" & \
			echo ----- OBTIDO  ------ & $(CAT) "$(SCRATCH)\test.out" & \
			exit /b 1 \
		) \
	)
	@echo === Testes que DEVEM falhar ===
	@for %%f in (examples\error\*.vs) do ( \
		copy /Y "%%f" "$(SCRATCH)\err.vs" >nul & \
		echo ==> %%f (erro esperado) & \
		$(CAT) "$(SCRATCH)\err.vs" | $(RUN) $(NULL) && ( \
			echo ❌ Nenhum erro em %%f & exit /b 1 \
		) || echo ✓ Erro detectado \
	)
	@echo ✔ Todos os testes passaram
else
	@echo "Este Makefile está configurado apenas para Windows."
endif

clean:
	@$(call RMDIR,$(BUILD))
