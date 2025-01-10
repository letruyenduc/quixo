#ifndef MESSAGE_H
#define MESSAGE_H

int showMessage(wchar_t *message, wchar_t **options, int optionsCount, int allowEscape);
void showMessageOkButton(wchar_t *message, int allowEscape);

#endif // MESSAGE_H