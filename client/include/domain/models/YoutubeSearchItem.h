#ifndef YOUTUBESEARCHITEM_H
#define YOUTUBESEARCHITEM_H


#include "include/domain/models/interface/SearchItem.h"



class YoutubeSearchItem : public SearchItem {
public:
    YoutubeSearchItem(std::string preview, std::string videoTitle, std::string description, std::string link);
    ~YoutubeSearchItem() = default;
    YoutubeSearchItem(YoutubeSearchItem &item) = default;
    YoutubeSearchItem(YoutubeSearchItem &&item) = default;
    YoutubeSearchItem &operator=(YoutubeSearchItem &item) = default;
    YoutubeSearchItem &operator=(YoutubeSearchItem &&item) = default;

    virtual std::string previewImage() override;

    virtual std::string title() override;

    virtual std::string shortDescription() override;

    virtual std::string videoLink() override;

private:
    std::string preview;
    std::string videoTitle;
    std::string description;
    std::string link;
};


#endif // YOUTUBESEARCHITEM_H
