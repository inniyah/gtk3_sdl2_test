#ifndef SCRIPTIX_SYSTEM_H
#define SCRIPTIX_SYSTEM_H

/* check for SNPRINTF define */
#ifdef _MSC_VER
#define snprintf _snprintf
#endif

/* check for stricmp define */
#ifdef _MSC_VER
#define strcasecmp stricmp
#endif

#endif
