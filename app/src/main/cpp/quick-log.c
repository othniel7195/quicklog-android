//
// Created by jimmy on 2021/9/22.
//
#include <jni.h>
#include <malloc.h>
#include "quick_log.h"

JNIEXPORT void JNICALL
Java_com_example_quickloglib_QuickLog_startQuickLog(JNIEnv *env,
                                                    jclass type,
                                                    jstring appId_,
                                                    jstring dir_,
                                                    jint cipherVersion,
                                                    jstring cipherKey_) {
    const char *appId = (*env)->GetStringUTFChars(env, appId_, 0);
    const char *dir = (*env)->GetStringUTFChars(env, dir_, 0);
    const char *cipherKey = (*env)->GetStringUTFChars(env, cipherKey_, 0);
    start_quick_log(appId, dir, cipherVersion, cipherKey, NULL);
    (*env)->ReleaseStringUTFChars(env, appId_, appId);
    (*env)->ReleaseStringUTFChars(env, dir_, dir);
    (*env)->ReleaseStringUTFChars(env, cipherKey_, cipherKey);
}

JNIEXPORT void JNICALL
Java_com_example_quickloglib_QuickLog_appendLog(JNIEnv *env, jclass type, jint level, jstring tag_,
                                              jstring filename_, jstring funcName_, jint line,
                                              jint pid, jint tid, jint mainTid, jstring log_) {
    const char *tag = (*env)->GetStringUTFChars(env, tag_, 0);

    const char *filename = NULL;
    if (filename_ != NULL) filename = (*env)->GetStringUTFChars(env, filename_, 0);
    const char *funcName = NULL;
    if (funcName_ != NULL) funcName = (*env)->GetStringUTFChars(env, funcName_, 0);

    const char *log = (*env)->GetStringUTFChars(env, log_, 0);

    quick_log_level logLevel;
    switch (level) {
        case 2:
            logLevel = verbose;
            break;
        case 3:
            logLevel = debug;
            break;
        case 4:
            logLevel = info;
            break;
        case 5:
            logLevel = warning;
            break;
        case 6:
            logLevel = error;
            break;
        default:
            logLevel = error;
    }

    quick_log_help_info *info = malloc(sizeof(quick_log_help_info));
    info->level = logLevel;
    info->tag = tag;
    info->filename = filename;
    info->func_name = funcName;
    info->line = line;
    gettimeofday(&info->timeval, NULL);
    info->pid = pid;
    info->tid = tid;
    info->main_tid = mainTid;

    append_log(info, log);

    (*env)->ReleaseStringUTFChars(env, tag_, tag);
    if (filename != NULL)(*env)->ReleaseStringUTFChars(env, filename_, filename);
    if (funcName != NULL) (*env)->ReleaseStringUTFChars(env, funcName_, funcName);
    (*env)->ReleaseStringUTFChars(env, log_, log);
}

JNIEXPORT void JNICALL
Java_com_example_quickloglib_QuickLog_flushLog(JNIEnv *env, jclass type) {
    flush_log();
}


JNIEXPORT void JNICALL
Java_com_example_quickloglib_QuickLog_endLog(JNIEnv *env, jclass type) {
    end_quick_log();
}

JNIEXPORT jobjectArray JNICALL
Java_com_example_quickloglib_QuickLog_fetchLogFiles(JNIEnv *env, jclass type, jstring dir_,
                                                    jint day_span_) {
    const char *dir = (*env)->GetStringUTFChars(env, dir_, 0);

    int count;
    char **files = fetch_log_files(dir, day_span_, &count);
    (*env)->ReleaseStringUTFChars(env, dir_, dir);
    if (count <= 0) return NULL;

    jobjectArray fileStrings = (*env)->NewObjectArray(env, count,
                                                      (*env)->FindClass(env, "java/lang/String"),
                                                      (*env)->NewStringUTF(env, ""));
    int index = 0;
    char **filesCopy = files;
    while (*filesCopy) {
        (*env)->SetObjectArrayElement(env, fileStrings, index,
                                      (*env)->NewStringUTF(env, *filesCopy));
        free(*filesCopy);
        filesCopy++;
    }
    free(files);

    return (fileStrings);
}


JNIEXPORT void JNICALL
Java_com_example_quickloglib_QuickLog_deleteTimeoutLogFiles(JNIEnv *env, jclass clazz, jstring dir_,
                                                            jfloat valid_time_sec_) {
    const char *dir = (*env)->GetStringUTFChars(env, dir_, 0);
    delete_timeout_log_files(dir, valid_time_sec_);
    (*env)->ReleaseStringUTFChars(env, dir_, dir);
}