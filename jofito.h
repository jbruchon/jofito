/* jofito main program header
 * See jofito.c for license information */

#ifndef JOFITO_H
#define JOFITO_H

#ifdef __cplusplus
extern "C" {
#endif

/* Detect Windows and modify as needed */
#if defined _WIN32 || defined __MINGW32__
 #ifndef ON_WINDOWS
  #define ON_WINDOWS 1
 #endif
 #ifndef WIN32_LEAN_AND_MEAN
  #define WIN32_LEAN_AND_MEAN
 #endif
 #include <windows.h>
 #include <io.h>
#endif /* Win32 */

#include <limits.h>
#include <stdint.h>
#include <sys/types.h>
#include <unistd.h>
#include "string_malloc.h"
#include "jody_sort.h"
#include "version.h"

/* Some types are different on Windows */
#ifdef ON_WINDOWS
 typedef uint64_t jofito_ino_t;
 typedef uint32_t jofito_mode_t;
 extern const char dir_sep;
 #ifdef UNICODE
  extern const wchar_t *FILE_MODE_RO;
 #else
  extern const char *FILE_MODE_RO;
 #endif /* UNICODE */

#else /* Not Windows */
 #include <sys/stat.h>
 typedef ino_t jofito_ino_t;
 typedef mode_t jofito_mode_t;
 extern const char *FILE_MODE_RO;
 extern const char dir_sep;
 #ifdef UNICODE
  #error Do not define UNICODE on non-Windows platforms.
  #undef UNICODE
 #endif
#endif /* _WIN32 || __MINGW32__ */

/* Windows + Unicode compilation */
#ifdef UNICODE
 #ifndef PATHBUF_SIZE
  #define WPATH_MAX 8192
  #define PATHBUF_SIZE WPATH_MAX
 #else
  #define WPATH_MAX PATHBUF_SIZE
 #endif /* PATHBUF_SIZE */
  typedef wchar_t wpath_t[WPATH_MAX];
  extern int out_mode;
  extern int err_mode;
 #define M2W(a,b) MultiByteToWideChar(CP_UTF8, 0, a, -1, (LPWSTR)b, WPATH_MAX)
 #define W2M(a,b) WideCharToMultiByte(CP_UTF8, 0, a, -1, (LPSTR)b, WPATH_MAX, NULL, NULL)
#endif /* UNICODE */

#ifdef ON_WINDOWS
 #include "jody_win_stat.h"
#endif

#define ISFLAG(a,b) ((a & b) == b)
#define SETFLAG(a,b) (a |= b)
#define CLEARFLAG(a,b) (a &= (~b))

/* Aggressive verbosity for deep debugging */
#ifdef LOUD_DEBUG
 #ifndef DEBUG
  #define DEBUG
 #endif
 #define LOUD(...) if ISFLAG(flags, F_LOUD) __VA_ARGS__
#else
 #define LOUD(a)
#endif

/* Compile out debugging stat counters unless requested */
#ifdef DEBUG
 #define DBG(a) a
 #ifndef TREE_DEPTH_STATS
  #define TREE_DEPTH_STATS
 #endif
#else
 #define DBG(a)
#endif

/* Behavior modification flags */
extern uint_fast32_t flags, a_flags;
#define F_EXAMPLEFLAG		(1U << 0)

/* Maximum path buffer size to use; must be large enough for a path plus
 * any work that might be done to the array it's stored in. PATH_MAX is
 * not always true. Read this article on the false promises of PATH_MAX:
 * http://insanecoding.blogspot.com/2007/11/pathmax-simply-isnt.html
 * Windows + Unicode needs a lot more space than UTF-8 in Linux/Mac OS X
 */
#ifndef PATHBUF_SIZE
#define PATHBUF_SIZE 4096
#endif

#ifdef __cplusplus
}
#endif

#endif /* JOFITO_H */
