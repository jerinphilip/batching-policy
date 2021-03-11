#pragma once
#include <iostream>
#include <vector>

struct RequestSentence {
  size_t no;
  int nice;
  size_t index;
  size_t length;
};

struct Request {
  int nice;  /// Nice assigned to request.
  size_t no; /// Sequence number.
  std::vector<size_t> sentences;
  RequestSentence sentence(size_t idx) {
    return (RequestSentence){no, nice, idx, sentences[idx]};
  }
};

std::ostream &operator<<(std::ostream &out, const Request &r) {
  out << "Request (";
  {
    out << "Id = " << r.no << ", ";
    out << "nice=" << r.nice << ", ";
    out << "length=" << r.sentences.size();
  }
  out << " )";
  return out;
}

class Batch {
public:
  void add(const RequestSentence &sentence) {
    sentences_.push_back(sentence);
    numTokens_ += sentence.length;
    maxTokens_ = std::max(maxTokens_, sentence.length);
  }
  size_t size() const { return sentences_.size(); }
  void clear() {
    sentences_.clear();
    maxTokens_ = 0;
    numTokens_ = 0;
  };

  size_t numTokens() const { return numTokens_; }
  size_t maxTokens() const { return maxTokens_; }
  float efficiency() const {
    return float(numTokens_) / float(maxTokens_ * sentences_.size());
  }

private:
  std::vector<RequestSentence> sentences_;
  size_t maxTokens_;
  size_t numTokens_;
};

std::ostream &operator<<(std::ostream &out, const Batch &batch) {
  out << "Batch(";
  {
    out << "size=" << batch.size() << ", ";
    out << "max=" << batch.maxTokens() << ", ";
    out << "tokens=" << batch.numTokens() << ", ";
    out << "efficiency=" << batch.efficiency();
  }
  out << ")";
  return out;
}
