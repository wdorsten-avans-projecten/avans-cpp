#ifndef DOMAIN_LAND_H
#define DOMAIN_LAND_H

constexpr int LAND_SIZE = 4;
constexpr int MAX_CITIES = 2;
constexpr int MAX_VILLAGES = 6;
constexpr int MAX_MOUNTAINS = 4;

#include <map>
#include <memory>

#include "random_wrapper.h"

#include "structs/province_statistics.h"
#include "province.h"
#include "king.h"

namespace domain::models {
class Land {
 public:
  Land();
  ~Land();

  void EnterProvince(std::pair<int, int> location, Player *player);
  [[nodiscard]] structs::ProvinceStatistics GetProvinceStatistics(int x, int y) const;
  [[nodiscard]] models::Province *GetCurrentProvince() const;
  [[nodiscard]] std::unique_ptr<King> *GetKing();
  void KillKing();
 private:
  std::unique_ptr<King> king_;
  std::map<std::pair<int, int>, structs::ProvinceStatistics> province_statistics_;
  std::unique_ptr<Province> current_province_;
  std::map<std::pair<int, int>, std::unique_ptr<Province>> previous_provinces_;
};
} // namespace domain::models

#endif // DOMAIN_LAND_H
