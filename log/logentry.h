/*
 * (C) Copyright 2013 Emil Ljungdahl
 *
 * This file is part of Openambit.
 *
 */
#ifndef LOGENTRY_H
#define LOGENTRY_H

#include <QDateTime>
#include <libambit.h>

class LogEntry
{
public:
	explicit LogEntry(void);
	LogEntry(const LogEntry & other);
	~LogEntry(void);

	LogEntry & operator = (const LogEntry & rhs);

	bool isUploaded(void);

	QString device;
	QDateTime time;
	QString movescountId;
	ambit_device_info_t *deviceInfo;
	ambit_personal_settings_t *personalSettings;
	ambit_log_entry_t *logEntry;
};

#endif
