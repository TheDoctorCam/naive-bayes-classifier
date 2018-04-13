CC=g++
CFLAGS=-Wall -O3 -std=c++11
PROGRAM=NaiveBayes

all: main.o NaiveBayes.o
	$(CC) -o $(PROGRAM) main.o NaiveBayes.o

main.o: main.cpp
	$(CC) $(CFLAGS) -c main.cpp

BayesClassifier.o: NaiveBayes.cpp
	$(CC) $(CFLAGS) -c NaiveBayes.cpp

clean:
	rm -f *.o $(PROGRAM)
