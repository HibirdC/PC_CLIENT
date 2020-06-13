#ifndef TNMVD_GLOBAL_H
#define TNMVD_GLOBAL_H

#include <QtCore/qglobal.h>

#ifdef TNMVD_LIB
# define TNMVD_EXPORT Q_DECL_EXPORT
#else
# define TNMVD_EXPORT Q_DECL_IMPORT
#endif

enum Cust_Type{
	cust_rect = 1,
	cust_hexagon,
	cust_ellipse,
	cust_radius,
	nothing
};

#endif // TNMVD_GLOBAL_H
