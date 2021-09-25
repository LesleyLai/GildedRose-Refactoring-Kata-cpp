#include <string>
#include <vector>

struct Item {
  std::string name;
  int sellIn = 0;
  int quality = 0;
};

class GildedRose {
public:
  std::vector<Item>& items;
  explicit GildedRose(std::vector<Item>& items);

  void updateQuality();
};
