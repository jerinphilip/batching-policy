#pragma once
/// Handles batch generation from random parameters.

#include "data.h"
#include <random>

class RandomRequestGen {
public:
  RandomRequestGen(size_t seed, size_t maxLengthBreak, size_t niceBound,
                   size_t maxSentences)
      : maxLengthBreak_(maxLengthBreak), niceBound_(niceBound),
        maxSentences_(maxSentences) {
    randomIntGen_.seed(seed);
  }

  Request operator()(size_t requestId) {
    Request request;

    request.no = requestId;
    request.nice = nice();
    int numSentencesVal = numSentences();

    for (size_t idx = 0; idx < numSentencesVal; idx++) {
      request.sentences.push_back(sequenceLength());
    }
    return request;
  }

private:
  /// Generates random number of sentences between [1, maxSentences_]
  size_t numSentences() {
    size_t numSentencesVal = (randomIntGen_() % maxSentences_) + 1;
    return numSentencesVal;
  }

  size_t sequenceLength() {
    size_t lengthVal = randomIntGen_() % maxLengthBreak_;
    return lengthVal;
  }

  /// Returns a nice-value between [-niceBound_, niceBound]
  int nice() {
    size_t niceVal = randomIntGen_() % (2 * niceBound_ + 1);
    niceVal -= niceBound_; // substract to be between [-x, x]
    return niceVal;
  }

  std::mt19937 randomIntGen_;
  size_t niceBound_;
  size_t maxLengthBreak_;
  size_t maxSentences_;
};
