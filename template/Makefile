# TODO: rename  
template:
	g++ -Wall template.cpp -o template.o
	./template.o < ./template-test-1.txt
	@tail -n 1 ./template-test-1.txt # print the correct answer
	@# @echo "oikea vastaus: aoeu"

test:
	g++ -Wall template.cpp -o template.o
	valgrind --leak-check=full template.o

clean:
	rm -rf ./*.o
