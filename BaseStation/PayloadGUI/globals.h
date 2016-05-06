#ifndef GLOBALS_H
#define GLOBALS_H

// ALL THE GLOBAL DECLARATIONS

// don't use #include <QString> here, instead do this:

//QT_BEGIN_NAMESPACE
//class QString;
//QT_END_NAMESPACE

#include "Network.h"

// that way you aren't compiling QString into every header file you put this in...
// aka faster build times.

#define MAGIC_NUM 42

extern qreal g_some_double; // Note the important use of extern!
extern QString g_some_string;
extern Network net;

#endif // GLOBALS_H
