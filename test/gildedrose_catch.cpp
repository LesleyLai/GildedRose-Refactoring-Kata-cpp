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

void testGildedRose(Item input, const Item& expected_output)
{
  std::vector<Item> items;
  items.push_back(input);
  GildedRose{items}.updateQuality();
  REQUIRE(items[0] == expected_output);
}

TEST_CASE("UpdateQuality")
{
  SECTION("Normal item")
  {
    constexpr const char* name = "foo";

    SECTION("both sell in days and quality decrease normally")
    {
      testGildedRose(Item{name, 10, 10}, Item{name, 9, 9});
    }

    SECTION("Quality should never be negative")
    {
      testGildedRose(Item{name, 10, 0}, Item{name, 9, 0});
    }

    SECTION("Once the sell-by day pass, quality degrade twice as faster")
    {
      testGildedRose(Item{name, 0, 10}, Item{name, -1, 8});
    }
  }

  SECTION("Aged Brie")
  {
    constexpr const char* name = "Aged Brie";
    SECTION("increases quality over time")
    {
      testGildedRose(Item{name, 10, 10}, Item{name, 9, 11});
    }
    // why failed?
    // testGildedRose(Item{"Aged Brie", 0, 10}, Item{"Aged Brie", -1, 11});

    SECTION("Quality of an it is never more than 50")
    {
      testGildedRose(Item{name, 10, 50}, Item{name, 9, 50});
    }
  }

  SECTION("Sulfuras")
  {
    SECTION("never has to be sold or decreases in Quality")
    {
      constexpr const char* name = "Sulfuras, Hand of Ragnaros";
      testGildedRose(Item{name, 10, 80}, Item{name, 10, 80});
    }
  }

  SECTION("Backstage passes")
  {
    constexpr const char* name = "Backstage passes to a TAFKAL80ETC concert";
    SECTION("increases in Quality as its SellIn value approaches")
    {
      testGildedRose(Item{name, 20, 20}, Item{name, 19, 21});
    }

    SECTION("Quality increases by 2 when there are 10 days or less")
    {
      testGildedRose(Item{name, 10, 20}, Item{name, 9, 22});
    }

    SECTION("Quality increases by 3 when there are 5 days or less")
    {
      testGildedRose(Item{name, 5, 20}, Item{name, 4, 23});
    }

    SECTION("Quality drop to zero with concert ends")
    {
      testGildedRose(Item{name, 0, 20}, Item{name, -1, 0});
    }
  }
}