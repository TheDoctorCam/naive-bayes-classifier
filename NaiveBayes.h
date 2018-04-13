#ifndef NAIVE_BAYES_H
#define NAIVE_BAYES_H

#include <iostream>
#include <string.h>
#include <vector>
#include <map>

using std::string;
using std::vector;
using std::map;
using std::multimap;

typedef multimap<int, map<int, map<int,int> *> *> multi_map;
typedef vector<vector<int> * > pointer_vector;

class NaiveBayes {
public:
  NaiveBayes(); //Default constructor
  NaiveBayes(const string & );
  NaiveBayes(const string &, const string &);

  void train(const string &);
  void test(const string &);

private:
  void data_processing(const string &, pointer_vector &, multi_map &);
  void classifier(const pointer_vector &, const multi_map &);

  pointer_vector trainingData;
  pointer_vector testingData;
  multi_map trainingCounts;
  multi_map testingCounts;
  size_t max_length;
};

#endif
