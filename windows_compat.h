#ifndef WINDOWS_COMPAT_H
#define WINDOWS_COMPAT_H

#ifdef _WIN32
#include <windows.h>
#include <io.h>
#include <direct.h>

#define usleep(microseconds) Sleep((microseconds) / 1000)

#define access _access
#define getcwd _getcwd
#define chdir _chdir
#define unlink _unlink

#endif // _WIN32

#endif // WINDOWS_COMPAT_H
