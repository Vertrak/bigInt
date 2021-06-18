#Author: Felipe L.
#ಠ_ಠ Why are you here?

#compiler
C = gcc
#flags
F = -Wall 
#program file names without .c suffix
P = $(wildcard *.c)
#libraries required to compile
L = -lm
#name of program
N = BigIntTest

all : $(P) $(N)

#compile files into individual programs
$(N) : $(P)
		$(C) $(F) -o $@ $^ $(L)

#Functions!
.PHONY : clean YEET

#Permission to YEET
clean:
		@echo "\n\t      Permission to"
		@echo "\n\n"
		@echo "\tY   E   E   T-----------Y"
		@echo "\t| Y   E   E   T-------Y |"
		@echo "\t| | Y   E   E   T---Y   E"
		@echo "\t| | | Y   E   E   Y   E |"
		@echo "\t| | T   Y   E   Y   E   E"
		@echo "\t| T   E   Y   Y   E   E |"
		@echo "\tT   E   E   Y   E   E   T"
		@echo "\t  E   E   Y   Y   E   T |"
		@echo "\tE   E   Y   E   Y   T | |"
		@echo "\t  E   Y   E   E   Y | | |"
		@echo "\tE   Y---T   E   E   Y | |"
		@echo "\t  Y-------T   E   E   Y |"
		@echo "\tY-----------T   E   E   Y"
		@echo "\n\n"
		@echo "\tG   R   A   N   T   E   D\n"
		@make YEET

#Delete objects and programs
YEET :
		-rm -f $(basename $(P))