#include <iostream>
#include <stdlib.h>
#include "NaiveBayes.h"

int main(int argc, char * argv[]) {
    if(argc != 3) {
      std::cerr << "Error processing command";
      exit (EXIT_FAILURE);
    }

    NaiveBayes classifier;
    classifier.train(argv[1]);
    classifier.test(argv[2]);
    return 0;
}
