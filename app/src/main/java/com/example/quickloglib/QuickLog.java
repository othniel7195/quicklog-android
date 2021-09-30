package com.example.quickloglib;

import android.os.Looper;
import android.os.Process;
import android.util.Log;

import androidx.annotation.Nullable;

public class QuickLog {
    /**
     * 初始化日志服务
     * @param appId 应用唯一标识
     * @param dir 日志存储的路径
     * @param cipherVersion  加密版本号
     * @param cipherKey 秘钥
     */
    public native static void startQuickLog(String appId,
                                            String dir,
                                            int cipherVersion,
                                            String cipherKey);

    /**
     * 添加日志
     * @param level  日志level 2:verbose; 3:debug; 4:info; 5:warning; 6:error
     * @param tag  模块/组件 识别名称
     * @param filename 日志发生的文件名
     * @param funcName 日志发生的函数名
     * @param line 日志发生的行数
     * @param pid  日志发生的进程id
     * @param tid  日志发生的线程id
     * @param mainTid 日志发生时的主线程id
     * @param log  日志body
     */
    public native static void appendLog(int level,
                                         String tag,
                                         String filename,
                                         String funcName,
                                         int line,
                                         int pid,
                                         int tid,
                                         int mainTid,
                                         String log);

    /**
     * 主动同步缓存日志到磁盘
     */
    public native static void flushLog();

    /**
     * 停止日志服务
     */
    public native static void endLog();

    /**
     * 主动拉取日志文件
     * @param dir 日志所在文件夹
     * @param daySpan 当前日期的间隔天数
     * @return 日志文件路径字符串数组
     */
    @Nullable public native static String[] fetchLogFiles(String dir, int daySpan);

    /**
     * 主动删除过期日志文件
     * @param dir 日志所在文件夹
     * @param validTimeSec 日志有效期, 单位秒
     */
    public native static void deleteTimeoutLogFiles(String dir, float validTimeSec);

    static {
        System.loadLibrary("quickloglib");
    }

}
