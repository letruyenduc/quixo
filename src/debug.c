#include <stdarg.h>
#include <wchar.h>
#include "message.h"

/**
 * Auteur : Kevin
 * Description : Affiche un message de débogage
 * Paramètres :
 * - fmt : Le format du message
 * - ... : Les arguments du message
 * Traitement :
 * - On crée un message à partir du format et des arguments
 * - On affiche le message
 */
void showDebugMessage(wchar_t *fmt, ...)
{
    wchar_t message[256];
    va_list arg_ptr;

    va_start(arg_ptr, fmt);
    vswprintf(message, 256, fmt, arg_ptr);
    va_end(arg_ptr);

    showMessageOkButton(message, 1);
}