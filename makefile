all:
	clear
	gcc -Wall main.c functions.c -o perceptron

run:
	clear
	gcc -Wall main.c functions.c -o perceptron
	./perceptron
