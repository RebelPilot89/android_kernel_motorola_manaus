#ifndef _MTK_COOLER_SETTING_H
#define _MTK_COOLER_SETTING_H

/* Cooler settings */
#define MAX_COOLER_NUM 5
#define COOLER_NAME_LEN 32

struct mtk_cooler_setting {
    int cooler_id;
    char name[COOLER_NAME_LEN];
};

#endif /* _MTK_COOLER_SETTING_H */
