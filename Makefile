EXECUTABLE       = trab1
SRC              = ./src
INCLUDE          = ./include
OBJ              = ./obj
FLAGS            = -lm -pedantic -Wall -g
ADD_FLAGS        = -Wextra
COMPILER         = gcc   

# Path and extesions
C_FILES        = $(wildcard $(SRC)/*.c | $(SRC)/**/*.c)
OBJ_PATH_FILES = $(patsubst $(SRC)%,$(OBJ)%,$(C_FILES))
OBJ_FILES      = $(patsubst %.c,%.o,$(OBJ_PATH_FILES))

#===========================================================#
# Main target
all: clean create_dir $(OBJ_FILES) $(EXECUTABLE)

# Creatig objects directory
create_dir: 
	@ mkdir $(OBJ)

# Compiling cpp files
$(OBJ)/%.o: $(SRC)/%.c 
	@ $(COMPILER) -c $< -o $@

# Creating executable
$(EXECUTABLE): 
	@ $(COMPILER) $< $(OBJ)/*.o -o $@ $(FLAGS)

# Cleaning workspace
clean:
	@ rm -rf $(OBJ) $(EXECUTABLE) *.txt

run:
	@ ./trab1 test/in/1.txt 2 out1.txt
	@ ./trab1 test/in/2.txt 4 out2.txt
	@ ./trab1 test/in/3.txt 5 out3.txt
	@ ./trab1 test/in/4.txt 5 out4.txt
	@ ./trab1 test/in/5.txt 10 out5.txt

diff:
	@ diff out1.txt test/out/1.txt
	@ diff out2.txt test/out/2.txt
	@ diff out3.txt test/out/3.txt
	@ diff out4.txt test/out/4.txt
	@ diff out5.txt test/out/5.txt	