#include "ApprovalTests.hpp"
#include <catch2/catch.hpp>

#include "GildedRose.h"

std::ostream& operator<<(std::ostream& os, const Item& obj)
{
  return os << "name: " << obj.name          //
            << ", sellIn: " << obj.sellIn    //
            << ", quality: " << obj.quality; //
}

TEST_CASE("UpdateQuality")
{
  std::vector<Item> items;
  SECTION("A normal item with 10 sell in days left")
  {
    items.push_back(Item{"foo", 10, 0});
    GildedRose{items}.updateQuality();
    ApprovalTests::Approvals::verify(items[0]);
  }
}