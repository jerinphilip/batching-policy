#pragma once
#include "comparators.h"
#include "data.h"

#include <functional>
#include <queue>
#include <set>
#include <utility>

#include <cassert>

/// @jerinphilip wants to be able to swapout different containers etc, let's
/// stick to this interface and have compiler complain when I violate these.

class AbstractBatcher {
public:
  AbstractBatcher(size_t miniBatchWords) {
    miniBatchWords_ = miniBatchWords;
    /// More hyperparameters to be added.
  }
  bool operator>>(Batch &batch) { return cleaveBatch(batch); }
  /// Generates a batch based on current priority / length.
  virtual bool cleaveBatch(Batch &batch) = 0;
  /// Adds a Request onto the scheduling / batching.
  virtual void addRequest(std::shared_ptr<Request> request) = 0;

protected:
  size_t miniBatchWords_{0};
};

class GreedyBatcher : public AbstractBatcher {
public:
  GreedyBatcher(size_t miniBatchWords, size_t maxLengthBreak)
      : AbstractBatcher(miniBatchWords), bucket_(maxLengthBreak + 1) {}

  bool cleaveBatch(Batch &batch) {
    batch.clear();
    size_t paddedBatchSize = 0;

    for (size_t length = 0; length < bucket_.size(); length++) {
      auto p = bucket_[length].begin();
      while (p != bucket_[length].end()) {
        paddedBatchSize = (batch.size() + 1) * length;
        if (paddedBatchSize <= miniBatchWords_) {
          auto q = p++;
          batch.add(*q);
          bucket_[length].erase(q);
        } else {
          // Check if elements exist
          assert(batch.size() > 0);
          return true;
        }
      }
    }
    bool isValidBatch = batch.size() > 0;
    return isValidBatch;
  }

  void addRequest(std::shared_ptr<Request> request) {
    for (size_t idx = 0; idx < request->sentences.size(); idx++) {
      RequestSentence sentence = (RequestSentence){request, idx};
      bucket_[sentence.length()].insert(sentence);
    }
  }

protected:
  std::vector<std::set<RequestSentence, proper_priority>> bucket_;
};
