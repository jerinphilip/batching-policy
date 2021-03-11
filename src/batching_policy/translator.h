#pragma once
#include "data.h"

class Translator {
public:
  Translator() {}

  void translate(Batch &batch) {
    ++id_;
    batch.complete(id_);
  }

private:
  size_t id_{0};
};
