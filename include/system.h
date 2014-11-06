#ifndef SCRIPTIX_SYSTEM_H
#define SCRIPTIX_SYSTEM_H

/* check for SNPRINTF define */
#ifdef _MSC_VER
#define snprintf _snprintf
#define vsnprintf _vsnprintf
#define strncasecmp strnicmp
#endif

#endif
