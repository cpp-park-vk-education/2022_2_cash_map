#ifndef YOUTUBEITEMCOLLECTOR_H
#define YOUTUBEITEMCOLLECTOR_H

#include "include/domain/interface/SearchItemCollector.h"

class YoutubeItemCollector : public SearchItemCollector {
public:
    YoutubeItemCollector() = default;
    ~YoutubeItemCollector() = default;

    virtual std::vector<SearchItem *> prepareSearchResult(std::string searchQuery) override;
};

#endif // YOUTUBEITEMCOLLECTOR_H
