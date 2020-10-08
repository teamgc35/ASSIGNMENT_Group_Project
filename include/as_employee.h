#ifndef __AS_EMPLOYEE_H__
#define __AS_EMPLOYEE_H__

#include "as_general.h"

enum TYPE_EMPLOYMENT
{
    FULL_TIME,
    PARTIME,
    CASUAL,
    CONTRACT,
    TRAINNING,
};

enum POSITION
{
    MANAGER,
    SUPERVISOR,
    STAFF,
};

enum PAY_TYPE
{
    WEEKLY,
    MONTHLY,
    FORNIGHT,
};

typedef struct employee_t
{
    int employee_id;
    char name[MAX_NAME_LENGTH];
    uint32_t hours_worked;
    float payment_rate;
    enum TYPE_EMPLOYMENT emp_type;
    enum POSITION position;
    enum PAY_TYPE pay_type;
}employee_t;


#endif