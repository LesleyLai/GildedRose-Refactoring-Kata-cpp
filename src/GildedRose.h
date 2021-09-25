#include <string>
#include <vector>

struct Item {
  std::string name;
  int sellIn;
  int quality;
};

class GildedRose {
public:
  std::vector<Item>& items;
  GildedRose(std::vector<Item>& items);

  void updateQuality();
};
