#include "include/domain/models/YoutubeSearchItem.h"


YoutubeSearchItem::YoutubeSearchItem(std::string preview, std::string videoTitle,
                                     std::string description, std::string link) : preview(preview),
                                                                                  videoTitle(videoTitle),
                                                                                  description(description),
                                                                                  link(link) {};

std::string YoutubeSearchItem::previewImage() {
    return preview;
}

std::string YoutubeSearchItem::title() {
    return videoTitle;
}

std::string YoutubeSearchItem::shortDescription() {
    return description;
}

std::string YoutubeSearchItem::videoLink() {
    return link;
}
