/*
 * (C) Copyright 2013 Emil Ljungdahl
 *
 * This file is part of Openambit.
 *
 */
#include "logentry.h"

LogEntry::LogEntry() :
    deviceInfo(NULL),
    personalSettings(NULL),
    logEntry(NULL)
{
}

LogEntry::LogEntry(const LogEntry &other)
{
    u_int32_t i;

    device = other.device;
    time = other.time;
    movescountId = other.movescountId;

    if (other.deviceInfo != NULL) {
        deviceInfo = (ambit_device_info_t*)malloc(sizeof(ambit_device_info_t));
        memcpy(deviceInfo, other.deviceInfo, sizeof(ambit_device_info_t));
    }
    else {
        deviceInfo = NULL;
    }

    if (other.personalSettings != NULL) {
        personalSettings = (ambit_personal_settings_t*)malloc(sizeof(ambit_personal_settings_t));
        memcpy(personalSettings, other.personalSettings, sizeof(ambit_personal_settings_t));
    }
    else {
        personalSettings = NULL;
    }

    if (other.logEntry != NULL) {
        logEntry = (ambit_log_entry_t*)malloc(sizeof(ambit_log_entry_t));
        memcpy(logEntry, other.logEntry, sizeof(ambit_log_entry_t));
        if (other.logEntry->samples != NULL) {
            logEntry->samples = (ambit_log_sample_t*)malloc(sizeof(ambit_log_sample_t)*other.logEntry->samples_count);
            memcpy(logEntry->samples, other.logEntry->samples, sizeof(ambit_log_sample_t)*other.logEntry->samples_count);
            for (i=0; i<other.logEntry->samples_count; i++) {
                if (other.logEntry->samples[i].type == ambit_log_sample_type_periodic) {
                    if (other.logEntry->samples[i].u.periodic.values != NULL) {
                        logEntry->samples[i].u.periodic.values = (ambit_log_sample_periodic_value_t*)malloc(sizeof(ambit_log_sample_periodic_value_t)*other.logEntry->samples[i].u.periodic.value_count);
                        memcpy(logEntry->samples[i].u.periodic.values, other.logEntry->samples[i].u.periodic.values, sizeof(ambit_log_sample_periodic_value_t)*other.logEntry->samples[i].u.periodic.value_count);
                    }
                }
                if (other.logEntry->samples[i].type == ambit_log_sample_type_gps_base) {
                    if (other.logEntry->samples[i].u.gps_base.satellites != NULL) {
                        logEntry->samples[i].u.gps_base.satellites = (ambit_log_gps_satellite_t*)malloc(sizeof(ambit_log_gps_satellite_t)*logEntry->samples[i].u.gps_base.satellites_count);
                        memcpy(logEntry->samples[i].u.gps_base.satellites, other.logEntry->samples[i].u.gps_base.satellites, sizeof(ambit_log_gps_satellite_t)*logEntry->samples[i].u.gps_base.satellites_count);
                    }
                }
                if (other.logEntry->samples[i].type == ambit_log_sample_type_unknown) {
                    if (other.logEntry->samples[i].u.unknown.datalen > 0 && other.logEntry->samples[i].u.unknown.data != NULL) {
                        logEntry->samples[i].u.unknown.data = (uint8_t*)malloc(other.logEntry->samples[i].u.unknown.datalen);
                        memcpy(logEntry->samples[i].u.unknown.data, other.logEntry->samples[i].u.unknown.data, other.logEntry->samples[i].u.unknown.datalen);
                    }
                }
            }
        }
    }
}

LogEntry& LogEntry::operator=(const LogEntry &rhs)
{
    LogEntry tmp(rhs);

    std::swap(device, tmp.device);
    std::swap(time, tmp.time);
    std::swap(movescountId, tmp.movescountId);
    std::swap(deviceInfo, tmp.deviceInfo);
    std::swap(personalSettings, tmp.personalSettings);
    std::swap(logEntry, tmp.logEntry);

    return *this;
}

LogEntry::~LogEntry()
{
    u_int32_t i;

    if (deviceInfo != NULL) {
        free(deviceInfo);
        deviceInfo = NULL;
    }

    if (personalSettings != NULL) {
        free(personalSettings);
        personalSettings = NULL;
    }

    if (logEntry != NULL) {
        if (logEntry->samples != NULL) {
            for (i=0; i<logEntry->samples_count; i++) {
                if (logEntry->samples[i].type == ambit_log_sample_type_periodic) {
                    if (logEntry->samples[i].u.periodic.values != NULL) {
                        free(logEntry->samples[i].u.periodic.values);
                    }
                }
                if (logEntry->samples[i].type == ambit_log_sample_type_gps_base) {
                    if (logEntry->samples[i].u.gps_base.satellites != NULL) {
                        free(logEntry->samples[i].u.gps_base.satellites);
                    }
                }
                if (logEntry->samples[i].type == ambit_log_sample_type_unknown) {
                    if (logEntry->samples[i].u.unknown.data != NULL) {
                        free(logEntry->samples[i].u.unknown.data);
                    }
                }
            }
            free(logEntry->samples);
        }
        free(logEntry);
    }

    logEntry = NULL;
}

bool LogEntry::isUploaded(){
    if (this->movescountId == NULL){
        return false;
    }
    return true;
}
