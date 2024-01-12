#ifndef UTIL_RANDOM_H
#define UTIL_RANDOM_H

#include <random>
#include <vector>
#include <stdexcept>

namespace util {
class Random {
 public:
  /// @brief Prohibit copy and move (singleton).
  Random(const Random &) = delete;
  Random(Random &&) = delete;
  Random &operator=(const Random &) = delete;
  Random &operator=(Random &&) = delete;

  /// @brief Returns the singleton instance of the RandomEngine wrapper.
  static Random *GetInstance();

  /// @brief Generates a random integer between the two given integers.
  ///
  /// @param min The floor.
  /// @param max The ceiling.
  ///
  /// @returns A randomly generated integer between min and max.
  int RandomIntInRange(int min, int max);

  /// @brief Returns a random item from the given vector.
  ///
  /// @tparam T The type of the elements contained in the vector.
  /// @param vec The vector in question.
  ///
  /// @return A random element from the given vector.
  template<typename T>
  T RandomItemFromVector(const std::vector<T> &vec);

  /// @brief Default deconstructor.
  ~Random();
 private:
  std::default_random_engine engine_;
  Random() : engine_(std::random_device{}()) {}
};
} // namespace util

#endif //UTIL_RANDOM_H
