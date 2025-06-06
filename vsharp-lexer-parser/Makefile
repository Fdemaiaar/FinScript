CC      = gcc
FLEX    = flex
BISON   = bison
BUILD   = build
SRC     = src

OBJS = $(BUILD)/ast.o $(BUILD)/vsharp.tab.o $(BUILD)/lex.yy.o $(BUILD)/main.o
BIN  = $(BUILD)/vsharp.exe

default: all

all: $(BIN)

$(BUILD):
	mkdir -p $(BUILD)

$(BUILD)/ast.o: $(SRC)/ast.c $(SRC)/ast.h | $(BUILD)
	$(CC) -c $< -o $@

$(BUILD)/vsharp.tab.c $(BUILD)/vsharp.tab.h: $(SRC)/vsharp.y | $(BUILD)
	$(BISON) -d -o $(BUILD)/vsharp.tab.c $<

$(BUILD)/vsharp.tab.o: $(BUILD)/vsharp.tab.c | $(BUILD)
	$(CC) -c $< -o $@

$(BUILD)/lex.yy.c: $(SRC)/vsharp.l $(BUILD)/vsharp.tab.h | $(BUILD)
	$(FLEX) -o $(BUILD)/lex.yy.c $<

$(BUILD)/lex.yy.o: $(BUILD)/lex.yy.c | $(BUILD)
	$(CC) -c $< -o $@

$(BUILD)/main.o: $(SRC)/main.c $(SRC)/ast.h | $(BUILD)
	$(CC) -c $< -o $@

$(BIN): $(OBJS)
	$(CC) -o $@ $(OBJS)

clean:
	rm -rf $(BUILD)
