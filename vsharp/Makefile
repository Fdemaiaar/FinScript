.DEFAULT_GOAL := test
BUILD = build
SRC = src
ifeq ($(OS),Windows_NT)
FLEX ?= win_flex
BISON ?= win_bison
CLANG ?= clang
CC = gcc
RM = del /Q
RMDIR = if exist "$(1)" rmdir /S /Q "$(1)"
MKDIR = if not exist "$(1)" mkdir "$(1)"
CAT = type
NULL = >nul 2>&1
PATH_SEP = \\
RUN = build\\vsharp.exe
BIN = $(RUN)
else
FLEX ?= flex
BISON ?= bison
CLANG ?= clang
CC = gcc
RM = rm -f
RMDIR = rm -rf "$(1)"
MKDIR = mkdir -p "$(1)"
CAT = cat
NULL = >/dev/null 2>&1
PATH_SEP = /
CFLAGS += -D_strdup=strdup
RUN = build/vsharp
BIN = $(RUN)
endif
CFLAGS += -Isrc -I$(BUILD) -Wall -Wextra
LDFLAGS = -lm
$(BUILD):
	@$(call MKDIR,$(BUILD))
OBJ = $(BUILD)/ast.o $(BUILD)/sem.o $(BUILD)/irgen.o $(BUILD)/runtime.o $(BUILD)/vsharp.tab.o $(BUILD)/lex.yy.o $(BUILD)/main.o
.PHONY: all clean test
all: | $(BUILD) $(BIN) $(BUILD)/runtime.bc
$(BUILD)/vsharp.tab.c $(BUILD)/vsharp.tab.h: $(SRC)/vsharp.y | $(BUILD)
	$(BISON) -d -o $(@D)/vsharp.tab.c $<
$(BUILD)/vsharp.tab.o: $(BUILD)/vsharp.tab.c
	$(CC) $(CFLAGS) -c $< -o $@
$(BUILD)/lex.yy.c: $(SRC)/vsharp.l $(BUILD)/vsharp.tab.h | $(BUILD)
	$(FLEX) -o $@ $<
$(BUILD)/lex.yy.o: $(BUILD)/lex.yy.c
	$(CC) $(CFLAGS) -c $< -o $@
$(BUILD)/%.o: $(SRC)/%.c | $(BUILD)
	$(CC) $(CFLAGS) -c $< -o $@
$(BUILD)/irgen.o: $(SRC)/irgen.c $(BUILD)/vsharp.tab.h
	$(CC) $(CFLAGS) -c $< -o $@
$(BIN): $(OBJ)
	$(CC) -o $@ $(OBJ) $(LDFLAGS)
$(BUILD)/runtime.bc: $(SRC)/runtime.c | $(BUILD)
	$(CLANG) -emit-llvm -c -o $@ $<
SCRATCH = $(BUILD)$(PATH_SEP)scratch
$(SCRATCH):
	@$(call MKDIR,$(SCRATCH))
test: all | $(SCRATCH)
ifeq ($(OS),Windows_NT)
	@for %%f in (examples\*.vs) do ( $(CAT) "%%f" | $(RUN) | findstr /V /R /C:"^IR gerado" /C:"^Executando JIT" > "$(SCRATCH)\out.tmp" && ( fc /N "%%~dpnf.expected" "$(SCRATCH)\out.tmp" >nul 2>&1 && $(RM) "$(SCRATCH)\out.tmp" ) || ( echo Falha em %%f & echo ----- ESPERADO ----- & $(CAT) "%%~dpnf.expected" & echo ----- OBTIDO ------ & $(CAT) "$(SCRATCH)\out.tmp" & exit /b 1 ) )
	@for %%f in (examples\error\*.vs) do ( $(CAT) "%%f" | $(RUN) $(NULL) && ( echo Nenhum erro em %%f & exit /b 1 ) || echo Erro detectado )
else
	@echo Testes automatizados não implementados neste SO
endif
clean:
	@$(call RMDIR,$(BUILD))
