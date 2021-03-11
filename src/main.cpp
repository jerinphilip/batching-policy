/// This single-file implementation implements a Batcher, which allows addition
/// of Requests and a method to cleave a Batch off the existing storage.

#include "3rd_party/CLI11.hpp"
#include <iostream>

#include "batching_policy/batcher.h"
#include "batching_policy/brandomgen.h"
#include "batching_policy/data.h"
#include "batching_policy/translator.h"

#include <memory>

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

  GreedyBatcher batcher(miniBatchwords, maxLengthBreak);

  std::vector<std::shared_ptr<Request>> requests;
  for (size_t requestId = 1; requestId <= numRequests; requestId++) {
    std::shared_ptr<Request> request =
        std::shared_ptr<Request>(new Request(requestGen(requestId)));
    batcher.addRequest(request);
    requests.push_back(request);
    std::cout << *request << std::endl;
  }

  Translator translator;
  Batch batch;
  while (batcher >> batch) {
    std::cout << batch << std::endl;
    translator.translate(batch);
  }

  for (auto &request : requests) {
    std::cout << *request << std::endl;
  }

  return 0;
}
