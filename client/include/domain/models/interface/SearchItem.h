#ifndef SEARCHITEMINTERFACE_H
#define SEARCHITEMINTERFACE_H

#include <string>

class SearchItem {
public:
   // todo: что возвращать?
    virtual std::string previewImage() = 0;

    virtual std::string title() = 0;

    virtual std::string shortDescription() = 0;

    virtual std::string videoLink() = 0;
};

#endif // SEARCHITEMINTERFACE_H
