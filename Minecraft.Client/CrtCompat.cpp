#include <cstring>
#include <cstdio>

namespace std {
    const char* _Winerror_map(int) {
        return "";
    }
}

extern "C" FILE* __cdecl __iob_func(void) {
    struct FILE_STAR_ARRAY { FILE* _ptr[3]; };
    static FILE_STAR_ARRAY files = { {stdin, stdout, stderr} };
    return (FILE*)files._ptr;
}