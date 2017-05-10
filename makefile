CC=g++
FLAGS=
SRC=*.cpp 

default: build run clean

clean:
	@echo "Cleaning stuff..."
	@rm -rf *.o

run:
	@echo "Running:"
	@./runner d "abyz" 1

build: $(SRC)
	@echo "Building runner..."
	@$(CC) -c $(SRC)
	@$(CC) *.o -o runner $(FLAGS)

