#include "GildedRose.h"

GildedRose::GildedRose(std::vector<Item>& items) : items(items) {}

constexpr const char* aged_brie = "Aged Brie";
constexpr const char* sulfuras = "Sulfuras, Hand of Ragnaros";
constexpr const char* backstage_passes =
    "Backstage passes to a TAFKAL80ETC concert";

void GildedRose::updateQuality()
{
  for (auto& item : items) {
    if (item.name != aged_brie && item.name != backstage_passes) {
      if (item.quality > 0) {
        if (item.name != sulfuras) { item.quality = item.quality - 1; }
      }
    } else {
      if (item.quality < 50) {
        item.quality = item.quality + 1;

        if (item.name == backstage_passes) {
          if (item.sellIn < 11) {
            if (item.quality < 50) { item.quality = item.quality + 1; }
          }

          if (item.sellIn < 6) {
            if (item.quality < 50) { item.quality = item.quality + 1; }
          }
        }
      }
    }

    if (item.name != sulfuras) { item.sellIn = item.sellIn - 1; }

    if (item.sellIn < 0) {
      if (item.name != aged_brie) {
        if (item.name != backstage_passes) {
          if (item.quality > 0) {
            if (item.name != sulfuras) { item.quality = item.quality - 1; }
          }
        } else {
          item.quality = item.quality - item.quality;
        }
      } else {
        if (item.quality < 50) { item.quality = item.quality + 1; }
      }
    }
  }
}
