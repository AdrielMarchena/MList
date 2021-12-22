#pragma once

#ifdef MLIST_STATIC_BUILD

#define MLIST_API 

#else

#ifdef MLIST_EXPORTS

#define MLIST_API _declspec(dllexport)
#else
#define MLIST_API _declspec(dllimport)

#endif // MLIST_EXPORTS

#endif //MLIST_STATIC_BUILD