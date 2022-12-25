#ifndef ROOMMEMBER_H
#define ROOMMEMBER_H

#include <QString>


class RoomMember {
public:
    virtual QString getUsername() = 0;

    virtual QString getUserId() = 0;

    virtual QString getCurrentTimeStamp() = 0;

    virtual void setTimeStamp(const QString &timeStamp) = 0;

};

#endif // ROOMMEMBER_H
