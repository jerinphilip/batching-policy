#pragma once
#include "data.h"
#include <type_traits>

bool _proper_priority(const RequestSentence &first,
                      const RequestSentence &second) {
  if (first.nice == second.nice) {
    if (first.no == second.no) {
      return first.index < second.index;
    } else {
      return first.no < second.no;
    }
  } else {
    return first.nice < second.nice;
  }
}

bool _invert_priority(const RequestSentence &first,
                      const RequestSentence &second) {
  if (first.nice == second.nice) {
    if (first.no == second.no) {
      return first.index > second.index;
    } else {
      return first.no > second.no;
    }
  } else {
    return first.nice > second.nice;
  }
}

using proper_priority =
    std::integral_constant<decltype(&_proper_priority), &_proper_priority>;

using invert_priority =
    std::integral_constant<decltype(&_invert_priority), &_invert_priority>;
