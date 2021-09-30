# For more information about using CMake with Android Studio, read the
# documentation: https://d.android.com/studio/projects/add-native-code.html

# Sets the minimum version of CMake required to build the native library.

cmake_minimum_required(VERSION 3.10.2)

# Declares and names the project.

project("quickloglib")

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Release")
endif()

set(log_root_path
        ../../../../../../QuickLog/QuickLog
        )

set(log_sources
        ${log_root_path}/common/aes128_log/aes_ctr.c
        ${log_root_path}/common/cJson/cJSON.c
        ${log_root_path}/common/openssl/aes_cfb.c
        ${log_root_path}/common/openssl/aes_core.c
        ${log_root_path}/common/openssl/cfb128.c
        ${log_root_path}/common/json_util.c
        ${log_root_path}/common/log_cipher.c
        ${log_root_path}/quick_log/log_buffer.c
        ${log_root_path}/quick_log/log_bytes.c
        ${log_root_path}/quick_log/log_deflater.c
        ${log_root_path}/quick_log/log_file.c
        ${log_root_path}/quick_log/log_format.c
        ${log_root_path}/quick_log/log_util.c
        ${log_root_path}/quick_log/log_writer.c
        ${log_root_path}/quick_log/quick_log.c
        )

set(log_protect_headers
        ${log_root_path}/common/aes128_log/aes_ctr.h
        ${log_root_path}/common/cJson/cJSON.h
        ${log_root_path}/common/openssl/aes_cfb128.h
        ${log_root_path}/common/openssl/aes_local.h
        ${log_root_path}/common/openssl/modes.h
        ${log_root_path}/common/openssl/opensslconf.h
        ${log_root_path}/common/json_util.h
        ${log_root_path}/common/log_cipher.h
        ${log_root_path}/quick_log/log.h
        ${log_root_path}/log_constants.h
        )
set(log_public_headers
        ${log_root_path}/quick_log.h
        )

add_library( # Sets the name of the library.
        quickloglib
        SHARED
        # Provides a relative path to your source file(s).
        quick-log.c
        ${log_sources}
        ${log_protect_headers}
        ${log_public_headers})

find_library( # Sets the name of the path variable.
        log-lib

        # Specifies the name of the NDK library that
        # you want CMake to locate.
        log)
find_library(ZLIB z)
# Specifies libraries CMake should link to your target library. You
# can link multiple libraries, such as libraries you define in this
# build script, prebuilt third-party libraries, or system libraries.
target_include_directories(quickloglib
        PUBLIC
        ${PROJECT_SOURCE_DIR}/include
        )
target_link_libraries( # Specifies the target library.
        quickloglib

        # Links the target library to the log library
        # included in the NDK.
        ${log-lib} ${ZLIB})

