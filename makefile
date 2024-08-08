all: program

program:
	g++ main.cpp -o app

clean:
	rm -f app
