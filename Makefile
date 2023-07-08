CC = g++
CFLAGS = -Iinclude -std=c++17

DATASET = ./dataset
NETWORK = ./network.ssv

GENERATE_EXEC = ./build/generate
INIT_EXEC = ./build/init
RUN_EXEC = ./build/run
TRAIN_EXEC = ./build/train
TEST_EXEC = ./build/test

run: build src/run.cpp $(DATASET) $(NETWORK)
	@echo "compiling $(RUN_EXEC)"
	@$(CC) $(CFLAGS) src/network.cpp src/parser.cpp src/run.cpp -o $(RUN_EXEC)
	@echo "running network $(NETWORK)"
	@$(RUN_EXEC) $(NETWORK)
	@echo "finished running"

$(DATASET):
	@make generate

$(NETWORK):
	@make init

generate: build src/generate.cpp
	@mkdir $(DATASET)
	@echo "compiling $(GENERATE_EXEC)"
	@$(CC) $(CFLAGS) src/generate.cpp src/init_dataset.cpp -o $(GENERATE_EXEC)
	@echo "creating dataset $(DATASET)"
	@$(GENERATE_EXEC) $(DATASET)
	@echo "finished"

init: build $(DATASET) src/init.cpp
	@echo "compiling $(INIT_EXEC)"
	@$(CC) $(CFLAGS) src/init.cpp -o $(INIT_EXEC)
	@echo "creating network $(NETWORK) for $(DATASET)"
	@$(INIT_EXEC) $(DATASET) $(NETWORK)
	@echo "finished $(NETWORK)"

train: build src/train.cpp $(DATASET) $(NETWORK)
	@echo "compiling $(TRAIN_EXEC)"
	@$(CC) $(CFLAGS) src/dataset.cpp src/generate.cpp src/network.cpp src/parser.cpp src/train.cpp -o $(TRAIN_EXEC)
	@echo "started training $(NETWORK) on $(DATASET)"
	@$(TRAIN_EXEC) $(NETWORK) $(DATASET)
	@echo "finished training"

test: build src/test.cpp $(DATASET) $(NETWORK)
	@echo "compiling $(TEST_EXEC)"
	@$(CC) $(CFLAGS) src/network.cpp src/parser.cpp src/test.cpp -o $(TEST_EXEC)
	@echo "testing $(NETWORK)"
	@$(TEST_EXEC) $(NETWORK)
	@echo "finished testing"

build:
	@mkdir build

purge:
	@rm -r $(NETWORK) $(DATASET)

clean:
	@rm -rf build
