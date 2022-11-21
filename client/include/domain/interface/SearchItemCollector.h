#ifndef SEARCHITEMCOLLECTOR_H
#define SEARCHITEMCOLLECTOR_H

#include "include/domain/models/interface/SearchItem.h"

#include <QObject>
#include <vector>

class SearchItemCollector : public QObject {
    Q_OBJECT
public:
    virtual std::vector<SearchItem *> prepareSearchResult(std::string searchQuery) = 0;
};

#endif // SEARCHITEMCOLLECTOR_H
