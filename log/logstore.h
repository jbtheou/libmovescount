/*
 * (C) Copyright 2013 Emil Ljungdahl
 *
 * This file is part of Openambit.
 *
 *
 */
#ifndef LOGSTORE_H
#define LOGSTORE_H

#include <QObject>
#include <QDateTime>
#include <QList>
#include <QIODevice>
#include <QXmlStreamReader>
#include <QXmlStreamWriter>
#include <libambit.h>

#include "logentry.h"

class LogStore
{
public:
	class LogDirEntry
	{
	public:
		QString device;
		QDateTime time;
		QString filename;
	};

	explicit LogStore(void);
	LogEntry *store(ambit_device_info_t *deviceInfo,
			ambit_personal_settings_t *personalSettings,
			ambit_log_entry_t *logEntry);
	LogEntry *store(LogEntry *entry);
	void storeMovescountId(QString device,
				QDateTime time,
				QString movescountId);
	bool logExists(QString device, ambit_log_header_t *logHeader);
	LogEntry *read(QString device, QDateTime time);
	LogEntry *read(LogDirEntry dirEntry);
	LogEntry *read(QString filename);
	QList < LogDirEntry > dir(QString device = "");
	QString datEntryPath(QString device, QDateTime time);

private:
	QString logEntryPath(QString device, QDateTime time);
	LogEntry *storeInternal(QString serial,
				QDateTime dateTime,
				ambit_device_info_t *deviceInfo,
				ambit_personal_settings_t *personalSettings,
				ambit_log_entry_t *logEntry,
				QString movescountId = "");
	LogEntry *readInternal(QString path);
	QString storagePath;
	class XMLReader
	{
	public:
		XMLReader(LogEntry *logEntry);
		bool read(QIODevice *device);
		QString errorString(void) const;
	private:
		void readRoot(void);
		void readSerial(void);
		void readTime(void);
		void readMovescountId(void);
		void readDeviceInfo(void);
		void readPersonalSettings(void);
		void readLog(void);
		void readLogHeader(void);
		void readLogSamples(void);
		void readPeriodicSample(QList < ambit_log_sample_periodic_value_t > *valueContent);
		QXmlStreamReader xml;
		LogEntry *logEntry;
	};

	class XMLWriter
	{
	public:
		XMLWriter(ambit_device_info_t *deviceInfo,
			QDateTime time,
			QString movescountId,
			ambit_personal_settings_t *personalSettings,
			ambit_log_entry_t *logEntry);
		bool write(QIODevice *device);
	private:
		bool writeDeviceInfo(void);
		bool writePersonalSettings(void);
		bool writeLogEntry(void);
		bool writeLogSample(ambit_log_sample_t *sample);
		bool writePeriodicSample(ambit_log_sample_t *sample);
		ambit_device_info_t *deviceInfo;
		QDateTime time;
		QString movescountId;
		QXmlStreamWriter xml;
		ambit_personal_settings_t *personalSettings;
		ambit_log_entry_t *logEntry;
	};
};
#endif
