# Force recompile and test every time
.PHONY: *

template:
	g++ -Wall -DDEBUG template.cpp -o template.o
	python grader.py template

test:
	python grader.py template

memory:
	g++ -Wall template.cpp -o template.o
	valgrind --leak-check=full template.o

clean:
	rm -rf ./*.o
