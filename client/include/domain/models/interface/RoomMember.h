#ifndef ROOMMEMBER_H
#define ROOMMEMBER_H

#include <QString>


class RoomMember {
public:
    virtual QString getUsername() = 0;

    virtual QString getUserId() = 0;

};

#endif // ROOMMEMBER_H
