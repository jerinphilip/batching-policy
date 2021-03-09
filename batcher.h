#pragma once
#include "data.h"
/// @jerinphilip wants to be able to swapout different containers etc, let's
/// stick to this interface and have compiler complain when I violate these.

class AbstractBatcher {
public:
  AbstractBatcher(size_t miniBatchWords) {
    miniBatchWords_ = miniBatchWords;
    /// More hyperparameters to be added.
  }
  /// Generates a batch based on current priority / length.
  virtual void cleaveBatch(Batch &batch) = 0;
  /// Adds a Request onto the scheduling / batching.
  virtual void addRequest(Request &request) = 0;

protected:
  size_t miniBatchWords_{0};
};

class Batcher : public AbstractBatcher {
  Batcher(size_t miniBatchWords) : AbstractBatcher(miniBatchWords) {}
};
