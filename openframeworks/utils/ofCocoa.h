#pragma once

void cocoaInit(void);

/*! \brief Displays alert dialog on OSX
 * \param title   Message title
 * \param message An error message to the uswer
 * \param type    0 warning, 1 informational, and 2 critical (NSAlertStyle)
*/
void cocoaAlert(const char *title, const char *message, unsigned type);
