#include "movescountlogdirentry.h"

MovesCountLogDirEntry::MovesCountLogDirEntry(QString moveId, QDateTime time, u_int8_t activityId) :
	moveId(moveId), time(time), activityId(activityId)
{
}

MovesCountLogDirEntry::MovesCountLogDirEntry(const MovesCountLogDirEntry &other) :
	moveId(other.moveId), time(other.time), activityId(other.activityId)
{
}

MovesCountLogDirEntry::~MovesCountLogDirEntry()
{
}

MovesCountLogDirEntry& MovesCountLogDirEntry::operator=(const MovesCountLogDirEntry &rhs)
{
    moveId = rhs.moveId;
    time = rhs.time;
    activityId = rhs.activityId;

    return *this;
}
