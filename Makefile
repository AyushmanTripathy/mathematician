CC = g++
CFLAGS = -Iinclude

DATASET = ./data.ssv
NETWORK = ./network.ssv

GENERATE_EXEC = ./build/generate
CREATE_EXEC = ./build/create
RUN_EXEC = ./build/run

generate: build src/generate.cpp
	@echo "compiling $(GENERATE_EXEC)"
	@$(CC) $(CFLAGS) src/generate.cpp -o $(GENERATE_EXEC)
	@echo "generating dataset $(DATASET)"
	@$(GENERATE_EXEC) $(DATASET)
	@echo "finished $(DATASET)"

create: build $(DATASET) src/create.cpp
	@echo "compiling $(CREATE_EXEC)"
	@$(CC) $(CFLAGS) src/create.cpp -o $(CREATE_EXEC)
	@echo "creating network $(NETWORK) for $(DATASET)"
	@$(CREATE_EXEC) $(DATASET) $(NETWORK)
	@echo "finished $(NETWORK)"

run: build src/run.cpp $(DATASET) $(NETWORK)
	@echo "compiling $(RUN_EXEC)"
	@$(CC) $(CFLAGS) src/parser.cpp src/run.cpp -o $(RUN_EXEC)
	@echo "running network $(NETWORK)"
	@$(RUN_EXEC) $(NETWORK)
	@echo "finished running"

build:
	@mkdir build

clean:
	@rm -rf build
