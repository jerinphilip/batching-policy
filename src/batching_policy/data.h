#pragma once
#include <atomic>
#include <iostream>
#include <memory>
#include <vector>

struct Request {
  int nice;         /// Nice assigned to request.
  size_t no;        /// Sequence number.
  size_t finishPid; /// Process Id where this was finished.
  /// Sentences, just a length representation, rest are ignored.
  std::vector<size_t> sentences;    // ORDER DEPENDENCY
  std::atomic<size_t> remaining{0}; // ORDER DEPENDENCY

  Request(int no, int nice, std::vector<size_t> sentences)
      : no(no), nice(nice), sentences(sentences), remaining(sentences.size()),
        finishPid(0) {}

  void complete(size_t index, size_t pid) {
    if (--remaining == 0) {
      finishPid = pid;
    }
  }
};

struct RequestSentence {
  std::shared_ptr<Request> request;
  size_t index;

  const size_t nice() const { return request->nice; }
  const size_t length() const { return request->sentences[index]; }
  const size_t no() const { return request->no; }

  void complete(size_t pid) { request->complete(index, pid); }
};

class Batch {
public:
  void add(const RequestSentence &sentence) {
    sentences_.push_back(sentence);
    numTokens_ += sentence.length();
    maxTokens_ = std::max(maxTokens_, sentence.length());
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

  void complete(size_t pid) {
    for (auto &sentence : sentences_) {
      sentence.complete(pid);
    }
  }

private:
  std::vector<RequestSentence> sentences_;
  size_t maxTokens_;
  size_t numTokens_;
};

std::ostream &operator<<(std::ostream &out, const Request &r) {
  out << "Request (";
  {
    out << "Id = " << r.no << ", ";
    out << "nice=" << r.nice << ", ";
    out << "sentences=" << r.sentences.size() << ", ";
    out << "finish=" << r.finishPid;
  }
  out << " )";
  return out;
}

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
