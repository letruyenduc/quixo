#include <stdarg.h>
#include <wchar.h>
#include "message.h"

void showDebugMessage(wchar_t *fmt, ...)
{
    wchar_t message[256];
    va_list arg_ptr;

    va_start(arg_ptr, fmt);
    vswprintf(message, 256, fmt, arg_ptr);
    va_end(arg_ptr);

    showMessageOkButton(message);
}