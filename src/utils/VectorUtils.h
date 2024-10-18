#pragma once
#include <boost/numeric/ublas/vector.hpp>
#include <ostream>

namespace boost {
namespace numeric {
namespace ublas {


// Overloads the << operator to print vectors to an output stream.
// Note: The type T must support the << operator for std::ostream.
template <typename T>
std::ostream& operator<<(std::ostream& os, const vector<T>& v) {
  os << "[";
  for (std::size_t i = 0; i < v.size(); ++i){
    os << v[i];
    if (i < v.size() - 1)
      os << ", ";
  }
  os << "]";
  return os;
}

} // namespace ublas
} // namespace numeric
} // namespace boost
