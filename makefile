OBJ:= $(patsubst %.c, %.o, $(wildcard *.c))
search.exe: $(OBJ)
	gcc -o $@ $^  
clean:
	rm *.o *.exe