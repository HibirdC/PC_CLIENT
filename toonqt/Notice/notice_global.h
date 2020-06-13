#ifndef NOTICE_GLOBAL_H
#define NOTICE_GLOBAL_H

#ifdef NOTICE_LIB
# define NOTICE_EXPORT Q_DECL_EXPORT
#else
# define NOTICE_EXPORT Q_DECL_IMPORT
#endif


#define KB 1024
#define MB ((1024) * (1024))
#define GB ((1024) * (1024) * (1024))

#endif // NOTICE_GLOBAL_H
