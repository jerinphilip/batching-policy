/// This single-file implementation implements a Batcher, which allows addition
/// of Requests and a method to cleave a Batch off the existing storage.

#include "CLI11.hpp"
#include <iostream>

#include "batcher.h"
#include "brandomgen.h"
#include "data.h"

int main(int argc, char *argv[]) {
  CLI::App app{"Optimal priority-length batching policy testbed"};

  size_t numRequests{10}, randomSeed{42}, maxLengthBreak{1024},
      maxSentences{100}, miniBatchwords{1024}, niceBound{20};
  app.add_option("-n,--num-requests", numRequests, "Number of requests");
  app.add_option("-r,--random-seed", randomSeed, "Seed to random generator");
  app.add_option("-l,--max-length-break", maxLengthBreak,
                 "maximum length of sentence");
  app.add_option("-s,--max-sentences", maxSentences,
                 "maximum number of sentences in a request");
  app.add_option("-b,--mini-batch-words", miniBatchwords,
                 "mini-batch-words capacity limit for batcher");
  CLI11_PARSE(app, argc, argv);

  RandomRequestGen requestGen(randomSeed, maxLengthBreak, niceBound,
                              maxSentences);

  for (size_t requestId = 1; requestId <= numRequests; requestId++) {
    Request request = requestGen(requestId);
    std::cout << request << std::endl;
  }
  return 0;
}
