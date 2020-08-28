
heroku:
  @echo 'Working ...'

.PHONY: heroku

smp: main.o
	g++ main.o -o smp

main.o: main.cpp
	g++ -c main.cpp

clean:
	rm *.o output

