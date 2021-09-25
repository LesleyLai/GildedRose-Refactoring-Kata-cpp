#include "ApprovalTests.hpp"
#include <catch2/catch.hpp>

#include "GildedRose.h"

std::ostream& operator<<(std::ostream& os, const Item& obj)
{
  return os << "name: " << obj.name          //
            << ", sellIn: " << obj.sellIn    //
            << ", quality: " << obj.quality; //
}

bool operator==(const Item& lhs, const Item& rhs)
{
  return lhs.name == rhs.name && lhs.sellIn == rhs.sellIn &&
         lhs.quality == rhs.quality;
}

TEST_CASE("UpdateQuality")
{
  using ApprovalTests::Approvals;

  std::vector<Item> items;
  SECTION("both sell in days and quality decrease normally")
  {
    items.push_back(Item{"foo", 10, 10});
    GildedRose{items}.updateQuality();
    REQUIRE(items[0] == Item{"foo", 9, 9});
  }

  SECTION("Quality should never be negative")
  {
    items.push_back(Item{"foo", 10, 0});
    GildedRose{items}.updateQuality();
    REQUIRE(items[0] == Item{"foo", 9, 0});
  }
}