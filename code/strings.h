#ifndef STRINGS_H
#define STRINGS_H

#if defined(_WIN32) || defined(__WIN32)
    #define WINDOWS
    #define SLASH "\\"
    #define FILESTR "file:///"
    #define HOME "~/"
#else
    #define UNIX
    #define SLASH "/"
    #define FILESTR "file://"
    #define HOME "~/"
#endif

#define QT4
#define HOMEPAGE "http://elpinchetopo.github.com/Abigail/"
#define WIKI "https://github.com/ElPincheTopo/Abigail/wiki"
#define REPO "https://github.com/ElPincheTopo/Abigail"

#endif // STRINGS_H
