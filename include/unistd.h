#pragma once
#ifndef _UNISTD_H_
#define _UNISTD_H_

#ifdef _WIN32
#include <windows.h>
#include <io.h>
#include <direct.h>

#ifdef access
#undef access
#endif
static inline int access(const char* path, int mode) {
    return _access(path, mode);
}

#ifdef getcwd
#undef getcwd
#endif
static inline char* getcwd(char* buffer, int maxlen) {
    return _getcwd(buffer, maxlen);
}

#ifdef chdir
#undef chdir
#endif
static inline int chdir(const char* path) {
    return _chdir(path);
}

#ifdef unlink
#undef unlink
#endif
static inline int unlink(const char* filename) {
    return _unlink(filename);
}

#ifdef usleep
#undef usleep
#endif
static inline void usleep(unsigned long microseconds) {
    Sleep(microseconds / 1000);
}

#endif // _WIN32
#endif // _UNISTD_H_