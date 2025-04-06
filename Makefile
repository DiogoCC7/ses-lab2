OUT_DIR = ./bin
OUT = $(OUT_DIR)/vuln.o

DOCKER_IMAGE = klee/klee:3.0

run:
	$(OUT)

.PHONY: compile
compile:
	mkdir -p $(OUT_DIR)
	gcc -o $(OUT) ./vuln.c

.PHONY: klee
klee:
	docker pull $(DOCKER_IMAGE)
	docker run --rm -v $(shell pwd):/work -w /work $(DOCKER_IMAGE) klee $(ARGS)
