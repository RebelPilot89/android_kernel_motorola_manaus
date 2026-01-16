/* SPDX-License-Identifier: GPL-2.0 */
/*
 * Copyright (C) 2018 Western Digital Corporation
 */


#ifndef _UFS_BSG_H
#define _UFS_BSG_H


#include "ufshcd.h"
#include <linux/bsg-lib.h>
#include <scsi/scsi.h>
#include <scsi/scsi_host.h>
#include "ufs.h"




#ifndef CONFIG_SCSI_UFS_BSG
static inline void ufs_bsg_remove(struct ufs_hba *hba) {}
static inline int ufs_bsg_probe(struct ufs_hba *hba) { return 0; }
#endif

#endif /* _UFS_BSG_H */
