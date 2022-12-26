#include "include/domain/models/YoutubeSearchItem.h"

#include "include/domain/YoutubeItemCollector.h"


std::vector<SearchItem *> YoutubeItemCollector::prepareSearchResult(std::string searchQuery) {
    // обращаемся к webEngine
    SearchItem * a = new YoutubeSearchItem("ShrekPlaceholde", "Shrek", "The best movie ever", "");
    std::vector<SearchItem *> res = {a};
    return res;
}
