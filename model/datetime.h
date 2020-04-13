#ifndef DATETIME_H
#define DATETIME_H


#include "date.h"
#include "time.h"

class DateTime : public Date, public Time {
public:
	DateTime();
};

#endif // DATETIME_H
