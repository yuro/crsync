/*
The MIT License (MIT)

Copyright (c) 2015 chenqi

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/
#ifndef CRSYNC_LOG_H
#define CRSYNC_LOG_H

#if defined __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <stdlib.h>

void log_append(char *s);
void log_dump();

void log_timestamp(char *ts);

#define LOG_TIME_STRING_SIZE 20

#define LOG_TIME \
    char ts[LOG_TIME_STRING_SIZE];\
    log_timestamp(ts);

#if defined ANDROID
#include <android/log.h>
#   define LOG_TAG "crsync_core"
#   define LEVEL_D ANDROID_LOG_DEBUG
#   define LEVEL_I ANDROID_LOG_INFO
#   define LEVEL_W ANDROID_LOG_WARN
#   define LEVEL_E ANDROID_LOG_ERROR
#   define LOG_PRINT(level, fmt, ...)  __android_log_print(level, LOG_TAG, "[%s]: " fmt, __func__, ##__VA_ARGS__)
#else
#   define LEVEL_D 'D'
#   define LEVEL_I 'I'
#   define LEVEL_W 'W'
#   define LEVEL_E 'E'
#   define LOG_PRINT(level, fmt, ...)  printf("%s %c [%s]: " fmt, ts, level, __func__, ##__VA_ARGS__)
#endif

#define LOG_FILE(level, fmt, ...) \
    char *s=malloc(256);\
    snprintf(s, 256, "%s %c [%s]: " fmt, ts, level, __func__, ##__VA_ARGS__);\
    log_append(s);

#define LOG_OUTPUT(level, fmt, ...) \
    do{\
        LOG_TIME\
        LOG_PRINT(level, fmt, ##__VA_ARGS__);\
        LOG_FILE(level, fmt, ##__VA_ARGS__);\
    } while(0)

#define CRSYNC_DEBUG 1

#if CRSYNC_DEBUG
#   define LOGD(fmt, ...)  LOG_OUTPUT(LEVEL_D, fmt, ##__VA_ARGS__)
#   define LOGI(fmt, ...)  LOG_OUTPUT(LEVEL_I, fmt, ##__VA_ARGS__)
#   define LOGW(fmt, ...)  LOG_OUTPUT(LEVEL_W, fmt, ##__VA_ARGS__)
#   define LOGE(fmt, ...)  LOG_OUTPUT(LEVEL_E, fmt, ##__VA_ARGS__)
#else
#   define LOGD(...)
#   define LOGI(...)
#   define LOGW(...)
#   define LOGE(...)
#endif //CRSYNC_DEBUG

#if defined __cplusplus
}
#endif

#endif // CRSYNC_LOG_H
