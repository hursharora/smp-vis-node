
smp: main.o
	g++ main.o -o smp

main.o: main.cpp
	g++ -c main.cpp

heroku:
	@echo 'Working ...'

.PHONY: heroku

clean:
	rm *.o output

