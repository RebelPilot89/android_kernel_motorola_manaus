#ifndef _MTK_GPU_LOADING_H
#define _MTK_GPU_LOADING_H

#include <linux/types.h>

static inline int mtk_get_gpu_loading(unsigned int *loading)
{
    /* Dummy implementation - always return 0% loading */
    if (loading)
        *loading = 0;
    return 0;
}

#endif /* _MTK_GPU_LOADING_H */
