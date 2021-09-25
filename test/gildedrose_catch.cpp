#include "ApprovalTests.hpp"
#include <catch2/catch.hpp>

#include "GildedRose.h"

std::ostream &operator<<(std::ostream &os, const Item &obj) {
  return os << "name: " << obj.name          //
            << ", sellIn: " << obj.sellIn    //
            << ", quality: " << obj.quality; //
}

TEST_CASE("UpdateQuality") {
  std::vector<Item> items;
  items.push_back(Item{"foo", 0, 0});
  GildedRose app(items);
  app.updateQuality();
  REQUIRE("fixme" == app.items[0].name);
}