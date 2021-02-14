#ifndef INCLUDE_LOGGING_H_
#define INCLUDE_LOGGING_H_

#include <events.h>

void logEvent(Event e);
void logError(const char *msg);

#endif // INCLUDE_LOGGING_H_