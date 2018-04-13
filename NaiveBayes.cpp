#include <fstream>
#include "NaiveBayes.h"

NaiveBayes::NaiveBayes() {
  max_length = 0;
}

NaiveBayes::NaiveBayes(const string & training_file) {
  NaiveBayes();
  train(training_file);
}

NaiveBayes::NaiveBayes(const string & training_file, const string & testing_file) {
  NaiveBayes();
  train(training_file);
  test(testing_file);
}

void NaiveBayes::train(const string & file) {
  data_processing(file, this->trainingData, this->trainingCounts);
  classifier(this->trainingData, this->trainingCounts);
}

void NaiveBayes::test(const string & file) {
  data_processing(file, this->testingData, this->testingCounts);
  classifier(this->testingData, this->trainingCounts);
}

void NaiveBayes::classifier(const pointer_vector & pv, const multi_map & mp) {
  // Count number of -1 and 1 classes
  int negativeCount = 0, positiveCount = 0, accuracy = 0;

  for(auto val : pv)
    if (val->at(0) == -1)
      negativeCount++;
    else
      positiveCount++;

  // Calculate probability
  double total = negativeCount + positiveCount;
  double probability_negative = negativeCount / total;
  double probability_positive = positiveCount / total;
  int true_positives = 0, false_positives = 0, true_negatives = 0, false_negatives = 0;

  size_t length = pv.size();
  for(size_t pos = 0; pos < length; ++pos)  {
    vector<double> attr_probability_neg(max_length-1, 1);	// Holds the probablity of each attr
    vector<double> attr_probability_pos(max_length-1, 1);
    int current_label = pv[pos]->at(0);

    // get counts from each class
    size_t width = pv[pos]->size();
    for(size_t count = 1; count < width; ++count) {
      int current_val = pv[pos]->at(count);

      attr_probability_neg.at(count-1) += mp.find(-1)->second->find(count)->second->find(current_val)->second;
      attr_probability_pos.at(count-1) += mp.find(1)->second->find(count)->second->find(current_val)->second;
    }

    // P(X | C)
    double pb_neg = probability_negative;
    double pb_pos = probability_positive;
    int predicted_label;

    size_t size = attr_probability_neg.size();
    for(size_t count = 0; count < size; ++count) {
      pb_neg *= attr_probability_neg.at(count) / (double) negativeCount;
      pb_pos *= attr_probability_pos.at(count) / (double) positiveCount;
    }

    if(pb_neg > pb_pos)
      predicted_label = -1;
    else
      predicted_label = 1;

    if(current_label == predicted_label) accuracy++;
    if(current_label == 1  && predicted_label == 1) true_positives++;
    if(current_label == -1 && predicted_label == 1) false_positives++;
    if(current_label == -1 && predicted_label == -1) true_negatives++;
    if(current_label == 1  && predicted_label == -1) false_negatives++;
  }

  std::cout << true_positives  << ' ' << false_negatives << ' ' << false_positives << ' ' << true_negatives  << '\n';
}

void NaiveBayes::data_processing(const string & file, pointer_vector & pv, multi_map & mp) {
  std::ifstream inFile(file);

  if(!inFile) {
  std::cerr << "Could not open " << file << '\n';
  exit(1);
  }

  string line;

  while(inFile >> std::ws) {
    int label;
    vector<int> * values = new vector<int>;
    size_t pos;

    getline(inFile, line);

    // Checks to see if line is valid.
    pos = line.find(':');
    if(pos == string::npos) break;

    // Get label
    pos = line.find(' ');
    if(pos != string::npos) {
      label = stoi(line.substr(0, pos));
      values->push_back(label);
      line = line.substr(pos + 1);
    }

  // Parse attribute:value pair
  while(pos != string::npos) {
    size_t index = 0;
    pos = line.find(':');
    if(pos != string::npos) {
      index = stoi(line.substr(0, pos)) - 1;
      line = line.substr(pos + 1);
    }

    pos = line.find(' ');
    if(pos != string::npos) {
      while((values->size() - 1) < index)
        values->push_back(0);
      values->push_back(stoi(line.substr(0, pos)));
      line = line.substr(pos+1);
    }
  }

  values->push_back(stoi(line));

if((values->size()) > max_length)
   	max_length = values->size();

  // Load pointer vector
  pv.push_back(values);

  // Load multimap
  size_t length = values->size();
  for(size_t count = 1; count < length; ++count) {
    int val = values->at(count);
    auto ptr = mp.find(label);

    // Create key:value pair
    if(ptr == mp.end()) {
      map<int, int> * temp = new map<int, int>;
      temp->insert(std::make_pair(val, 1));
      map<int, map<int, int> *> * pair = new map<int, map<int,int> *>;
      pair->insert(std::make_pair(count, temp));
      mp.insert(std::make_pair(label, pair));
      temp = 0; //memory management
      pair = 0; //memory management
    }
    else if(ptr->second->find(count) == ptr->second->end()) {
      map<int, int> * temp = new map<int, int>;
      temp->insert(std::make_pair(val, 1));
      ptr->second->insert(std::make_pair(count,temp));
      temp = 0;
    }
    else if(ptr->second->find(count)->second->find(val) == ptr->second->find(count)->second->end() ) {
      ptr->second->find(count)->second->insert(std::make_pair(val, 1));
    }
    else {
      ptr->second->find(count)->second->find(val)->second += 1;
    }
  }
}

  inFile.close();
}
