# Makefile for AMO Labs

CC = clang
CFLAGS = -g -Wall
LDFLAGS = -lm

# Lab 1
LAB1_SRC = lab-1/src/main.c
LAB1_BIN = lab-1/src/program

# Lab 2
LAB2_SRC = lab-2/src/main.c \
           lab-2/src/chords/chords.c \
           lab-2/src/f/f.c \
           lab-2/src/iteration/iteration.c \
           lab-2/src/log/log.c
LAB2_BIN = lab-2/src/program

# Lab 3
LAB3_SRC = lab-3/src/main.c \
           lab-3/src/gauss/gauss.c \
           lab-3/src/gauss-seidel/gauss-seidel.c \
           lab-3/src/matrix/matrix.c \
           lab-3/src/vector/vector.c
LAB3_BIN = lab-3/src/program

.PHONY: all lab-1 lab-2 lab-3 run-lab-1 run-lab-2 run-lab-3 clean

# Build all labs
all: lab-1 lab-2 lab-3

# Build individual labs
lab-1: $(LAB1_BIN)

lab-2: $(LAB2_BIN)

lab-3: $(LAB3_BIN)

# Build rules
$(LAB1_BIN): $(LAB1_SRC)
	$(CC) $(CFLAGS) $(LAB1_SRC) -o $(LAB1_BIN) $(LDFLAGS)

$(LAB2_BIN): $(LAB2_SRC)
	$(CC) $(CFLAGS) $(LAB2_SRC) -o $(LAB2_BIN) $(LDFLAGS)

$(LAB3_BIN): $(LAB3_SRC)
	$(CC) $(CFLAGS) $(LAB3_SRC) -o $(LAB3_BIN) $(LDFLAGS)

# Run individual labs
run-lab-1: lab-1
	@echo "Running Lab 1..."
	@cd lab-1/src && ./program

run-lab-2: lab-2
	@echo "Running Lab 2..."
	@cd lab-2/src && ./program

run-lab-3: lab-3
	@echo "Running Lab 3..."
	@cd lab-3/src && ./program

# Clean build artifacts
clean:
	rm -f $(LAB1_BIN) $(LAB2_BIN) $(LAB3_BIN)
	@echo "Build artifacts cleaned."
