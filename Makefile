OUT_DIR = ./bin
OUT = $(OUT_DIR)/vuln.o

run:
	$(OUT)

.PHONY: compile
compile:
	mkdir -p $(OUT_DIR)
	gcc -o $(OUT) ./vuln.c
