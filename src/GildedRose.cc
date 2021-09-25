#include "GildedRose.h"

GildedRose::GildedRose(std::vector<Item>& items) : items(items) {}

namespace {

constexpr const char* aged_brie = "Aged Brie";
constexpr const char* sulfuras = "Sulfuras, Hand of Ragnaros";
constexpr const char* backstage_passes =
    "Backstage passes to a TAFKAL80ETC concert";
constexpr const char* conjured = "Conjured";

void decrease_quality(Item& item, int amount)
{
  item.quality = std::max(0, item.quality - amount);
}

void increase_quality(Item& item, int amount)
{
  item.quality = std::min(50, item.quality + amount);
}

void decrease_quality_as_multiple_fast_as_normal_items(Item& item, int multiple)
{
  if (item.sellIn < 0) {
    decrease_quality(item, 2 * multiple);
  } else {
    decrease_quality(item, multiple);
  }
}

void updates_quality(Item& item)
{
  if (item.name == aged_brie) {
    increase_quality(item, 1);
  } else if (item.name == backstage_passes) {
    if (item.sellIn < 0) {
      item.quality = 0;
    } else if (item.sellIn < 6) {
      increase_quality(item, 3);
    } else if (item.sellIn < 11) {
      increase_quality(item, 2);
    } else {
      increase_quality(item, 1);
    }
  } else if (item.name == conjured) {
    decrease_quality_as_multiple_fast_as_normal_items(item, 2);
  } else if (item.name != sulfuras) {
    decrease_quality_as_multiple_fast_as_normal_items(item, 1);
  }
}

} // anonymous namespace

void GildedRose::updateQuality()
{
  for (auto& item : items) {
    if (item.name != sulfuras) { --item.sellIn; }

    updates_quality(item);
  }
}
