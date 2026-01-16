#ifndef _MTK_IDLE_PROFILE_H
#define _MTK_IDLE_PROFILE_H

#include <linux/types.h>

struct idle_profile {
    unsigned int enter_cnt;
    unsigned int leave_cnt;
    unsigned int duration;
};

#endif /* _MTK_IDLE_PROFILE_H */
