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
  void add(const RequestSentence &sentence) { sentences_.push_back(sentence); }
  size_t size() const { return sentences_.size(); }
  void clear() { sentences_.clear(); };

private:
  std::vector<RequestSentence> sentences_;
};
