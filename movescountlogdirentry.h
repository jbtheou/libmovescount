#ifndef MOVESCOUNTLOGDIRENTRY_H
#define MOVESCOUNTLOGDIRENTRY_H

#include <QObject>
#include <QDateTime>

class MovesCountLogDirEntry
{
public:
    explicit MovesCountLogDirEntry(QString moveId, QDateTime time, u_int8_t activityId);
    MovesCountLogDirEntry(const MovesCountLogDirEntry &other);
    ~MovesCountLogDirEntry();

    MovesCountLogDirEntry& operator=(const MovesCountLogDirEntry &rhs);

    QString moveId;
    QDateTime time;
    u_int8_t activityId;
};

#endif // MOVESCOUNTLOGDIRENTRY_H
