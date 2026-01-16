/* SPDX-License-Identifier: GPL-2.0 */
/*
 * Copyright (C) 2021 MediaTek Inc.
 */

#ifndef __GPUFREQ_MT6879_H__
#define __GPUFREQ_MT6879_H__

/**************************************************
 * GPUFREQ Local Config
 **************************************************/
#define GPUFREQ_BRINGUP                  (0)
#define GPUFREQ_POWER_CTRL_ENABLE        (1)
#define GPUFREQ_DVFS_ENABLE              (1)
#define GPUFREQ_CUST_INIT_ENABLE         (0)
#define GPUFREQ_CUST_INIT_OPPIDX         (0)
#define GPUFREQ_MFG1_CONTROL_ENABLE      (1)

/**************************************************
 * Adjustment Numbers Definitions - ADDED TO FIX ERRORS
 **************************************************/
#define AVS_ADJ_NUM                      ARRAY_SIZE(g_avs_adj)
#define MCL50_ADJ_NUM                    ARRAY_SIZE(g_mcl50_adj)
#define SEGMENT_ADJ_NUM                  ARRAY_SIZE(g_segment_adj)

/**************************************************
 * Clock Setting
 **************************************************/
#define POSDIV_2_MAX_FREQ                (1900000)        /* KHz */
#define POSDIV_2_MIN_FREQ                (750000)         /* KHz */
#define POSDIV_4_MAX_FREQ                (950000)         /* KHz */
#define POSDIV_4_MIN_FREQ                (375000)         /* KHz */
#define POSDIV_8_MAX_FREQ                (475000)         /* KHz */
#define POSDIV_8_MIN_FREQ                (187500)         /* KHz */
#define POSDIV_16_MAX_FREQ               (237500)         /* KHz */
#define POSDIV_16_MIN_FREQ               (125000)         /* KHz */
#define POSDIV_SHIFT                     (24)            /* bit */
#define DDS_SHIFT                        (14)            /* bit */
#define TO_MHZ_HEAD                      (100)
#define TO_MHZ_TAIL                      (10)
#define ROUNDING_VALUE                   (5)
#define MFGPLL_FIN                       (26)            /* MHz */
#define MFG_PLL_CON1                    (g_mfg_pll_base + 0x00C)
#define MFGSC_PLL_CON1                  (g_mfg_pll_base + 0x03C)
#define CLK_MUX_OFS                      (0x1034)
#define CKMUX_SEL_REF_CORE               (4)
#define CKMUX_SEL_REF_PARK               (5)
#define CKMUX_SEL_REF_STACK              (7)
#define CKMUX_SEL_REF_STACK_PARK         (8)
#define PLL4H_FQMTR_CON0                (g_mfg_pll_base + 0x200)
#define PLL4H_FQMTR_CON1                (g_mfg_pll_base + 0x204)
#define GPUPLL_ID                        (0x0)
#define STACKPLL_ID                      (0x3)

/**************************************************
 * Frequency Hopping Setting
 **************************************************/
#define GPUFREQ_FHCTL_ENABLE             (1)
#ifndef FH_MFG_PLLID
#define FH_MFG_PLLID    (0)  // ID usual para mfgpll0
#endif

#ifndef FH_MFGSC_PLLID
#define FH_MFGSC_PLLID  (3)  // ID usual para mfgpll3
#endif

#define MFG_PLL_NAME    FH_MFG_PLLID
#define MFGSC_PLL_NAME  FH_MFGSC_PLLID
/**************************************************
 * Power Domain Setting
 **************************************************/
#define GPUFREQ_PDCv2_ENABLE             (1)
#define GPUFREQ_CHECK_MTCMOS_PWR_STATUS (1)
#define PWR_STATUS_OFS                   (0xF3C)
#define PWR_STATUS_2ND_OFS               (0xF40)
#define MFG_0_1_PWR_MASK                 (0x6)
#define MFG_0_3_PWR_MASK                 (0x1E)
#define MFG_0_4_PWR_MASK                 (0x3E)
#define MFG_0_5_PWR_MASK                 (0x7E)
#define MFG_1_5_PWR_MASK                 (0x7C)
#define MFG_2_5_PWR_MASK                 (0x78)

/**************************************************
 * Shader Core Setting
 **************************************************/
#ifndef T0C0
#define T0C0 (1 << 0)
#define T2C0 (1 << 2)
#define T4C0 (1 << 4)
#endif

#define MFG3_SHADER_STACK0              (T0C0)
#define MFG4_SHADER_STACK2              (T2C0)
#define MFG5_SHADER_STACK4              (T4C0)

#define GPU_SHADER_PRESENT_1 \
	(MFG3_SHADER_STACK0)
#define GPU_SHADER_PRESENT_2 \
	(MFG3_SHADER_STACK0 | MFG4_SHADER_STACK2)
#define GPU_SHADER_PRESENT_3 \
	(MFG3_SHADER_STACK0 | MFG4_SHADER_STACK2 | MFG5_SHADER_STACK4)

#define SHADER_CORE_NUM                 (3)

static struct gpufreq_core_mask_info g_core_mask_table[] = {
	{3, GPU_SHADER_PRESENT_3},
	{2, GPU_SHADER_PRESENT_2},
	{1, GPU_SHADER_PRESENT_1},
};

/**************************************************
 * Reference Power Setting
 **************************************************/
#define GPU_ACT_REF_POWER                (1571)
#define GPU_ACT_REF_FREQ                 (1000000)
#define GPU_ACT_REF_VOLT                 (80000)
#define GPU_LEAKAGE_POWER                (130)

/**************************************************
 * PMIC Setting
 **************************************************/
#define VGPU_MAX_VOLT                    (119375)
#define VGPU_MIN_VOLT                    (30000)
#define VSRAM_MAX_VOLT                   (119375)
#define VSRAM_MIN_VOLT                   (40000)
#define PMIC_STEP                        (625)
#define VSRAM_FIXED_THRESHOLD            (75000)
#define VSRAM_FIXED_VOLT                 (75000)
#define VSRAM_FIXED_DIFF                 (0)
#define VOLT_NORMALIZATION(volt) \
	((volt % 625) ? (volt - (volt % 625) + 625) : volt)

/**************************************************
 * SRAMRC Setting
 **************************************************/
#define GPUFREQ_SAFE_VLOGIC              (60000)
#define VSRAM_LEVEL_0                    (75000)
#define VSRAM_LEVEL_1                    (80000)
#define SRAM_PARK_VOLT                   (75000)

/**************************************************
 * Power Throttling Setting
 **************************************************/
#define GPUFREQ_BATT_OC_ENABLE           (1)
#define GPUFREQ_BATT_PERCENT_ENABLE      (0)
#define GPUFREQ_LOW_BATT_ENABLE          (1)
#define GPUFREQ_BATT_OC_FREQ             (474000)
#define GPUFREQ_BATT_PERCENT_IDX         (0)
#define GPUFREQ_LOW_BATT_FREQ            (474000)

/**************************************************
 * Adaptive Volt Scaling (AVS) Setting
 **************************************************/
#define GPUFREQ_AVS_ENABLE               (0)

/**************************************************
 * Aging Sensor Setting
 **************************************************/
#define GPUFREQ_ASENSOR_ENABLE           (0)
#define GPUFREQ_AGING_KEEP_FGPU          (670000)
#define GPUFREQ_AGING_KEEP_VGPU          (65000)
#define GPUFREQ_AGING_GAP_MIN            (-3)
#define GPUFREQ_AGING_GAP_1              (2)
#define GPUFREQ_AGING_GAP_2              (4)
#define GPUFREQ_AGING_GAP_3              (6)
#define GPUFREQ_AGING_MOST_AGRRESIVE     (0)

/**************************************************
 * Enumeration
 **************************************************/
enum gpufreq_segment {
	MT6879_SEGMENT = 1,
};

enum gpufreq_clk_src {
	CLOCK_SUB = 0,
	CLOCK_MAIN,
};

/**************************************************
 * Structure
 **************************************************/
struct gpufreq_pmic_info {
	struct regulator *reg_vgpu;
	struct regulator *reg_vsram;
};

struct gpufreq_clk_info {
	struct clk *subsys_mfg_cg;
	struct clk *clk_main_parent;
	struct clk *clk_sc_main_parent;
};

struct gpufreq_mtcmos_info {
	struct device *mfg1_dev;
#if !GPUFREQ_PDCv2_ENABLE
	struct device *mfg2_dev;
	struct device *mfg3_dev;
	struct device *mfg4_dev;
	struct device *mfg5_dev;
#endif
};

struct gpufreq_adj_info {
	int oppidx;
	unsigned int freq;
	unsigned int volt;
	unsigned int vsram;
	unsigned int vaging;
};

struct gpufreq_status {
	struct gpufreq_opp_info *signed_table;
	struct gpufreq_opp_info *working_table;
	int buck_count;
	int mtcmos_count;
	int cg_count;
	int power_count;
	unsigned int segment_id;
	int signed_opp_num;
	int segment_upbound;
	int segment_lowbound;
	int opp_num;
	int max_oppidx;
	int min_oppidx;
	int cur_oppidx;
	unsigned int cur_freq;
	unsigned int cur_volt;
	unsigned int cur_vsram;
};

/**************************************************
 * GPU Platform OPP Table Definition
 **************************************************/
#define GPUOP(_freq, _volt, _vsram, _posdiv, _vaging, _power) \
	{                                   \
		.freq = _freq,                  \
		.volt = _volt,                  \
		.vsram = _vsram,                \
		.posdiv = _posdiv,              \
		.vaging = _vaging,              \
		.power = _power                 \
	}

static struct gpufreq_opp_info g_default_gpu[] = {
	GPUOP(1000000, 80000, VSRAM_LEVEL_1, POSDIV_POWER_2, 0, 0),
	GPUOP(986000,  79375, VSRAM_LEVEL_1, POSDIV_POWER_2, 0, 0),
	GPUOP(972000,  78750, VSRAM_LEVEL_1, POSDIV_POWER_2, 0, 0),
	GPUOP(958000,  78125, VSRAM_LEVEL_1, POSDIV_POWER_2, 0, 0),
	GPUOP(945000,  77500, VSRAM_LEVEL_1, POSDIV_POWER_4, 0, 0),
	GPUOP(931000,  76875, VSRAM_LEVEL_1, POSDIV_POWER_4, 0, 0),
	GPUOP(917000,  76250, VSRAM_LEVEL_1, POSDIV_POWER_4, 0, 0),
	GPUOP(903000,  75625, VSRAM_LEVEL_1, POSDIV_POWER_4, 0, 0),
	GPUOP(890000,  75000, VSRAM_LEVEL_0, POSDIV_POWER_4, 0, 0),
	GPUOP(876000,  74375, VSRAM_LEVEL_0, POSDIV_POWER_4, 0, 0),
	GPUOP(862000,  73750, VSRAM_LEVEL_0, POSDIV_POWER_4, 0, 0),
	GPUOP(848000,  73125, VSRAM_LEVEL_0, POSDIV_POWER_4, 0, 0),
	GPUOP(835000,  72500, VSRAM_LEVEL_0, POSDIV_POWER_4, 0, 0),
	GPUOP(821000,  71875, VSRAM_LEVEL_0, POSDIV_POWER_4, 0, 0),
	GPUOP(807000,  71250, VSRAM_LEVEL_0, POSDIV_POWER_4, 0, 0),
	GPUOP(793000,  70625, VSRAM_LEVEL_0, POSDIV_POWER_4, 0, 0),
	GPUOP(780000,  70000, VSRAM_LEVEL_0, POSDIV_POWER_4, 0, 0),
	GPUOP(766000,  69375, VSRAM_LEVEL_0, POSDIV_POWER_4, 0, 0),
	GPUOP(752000,  68750, VSRAM_LEVEL_0, POSDIV_POWER_4, 0, 0),
	GPUOP(738000,  68125, VSRAM_LEVEL_0, POSDIV_POWER_4, 0, 0),
	GPUOP(725000,  67500, VSRAM_LEVEL_0, POSDIV_POWER_4, 0, 0),
	GPUOP(711000,  66875, VSRAM_LEVEL_0, POSDIV_POWER_4, 0, 0),
	GPUOP(697000,  66250, VSRAM_LEVEL_0, POSDIV_POWER_4, 0, 0),
	GPUOP(683000,  65625, VSRAM_LEVEL_0, POSDIV_POWER_4, 0, 0),
	GPUOP(670000,  65000, VSRAM_LEVEL_0, POSDIV_POWER_4, 0, 0),
	GPUOP(652000,  64375, VSRAM_LEVEL_0, POSDIV_POWER_4, 0, 0),
	GPUOP(634000,  63750, VSRAM_LEVEL_0, POSDIV_POWER_4, 0, 0),
	GPUOP(616000,  63125, VSRAM_LEVEL_0, POSDIV_POWER_4, 0, 0),
	GPUOP(598000,  62500, VSRAM_LEVEL_0, POSDIV_POWER_4, 0, 0),
	GPUOP(580000,  61875, VSRAM_LEVEL_0, POSDIV_POWER_4, 0, 0),
	GPUOP(563000,  61250, VSRAM_LEVEL_0, POSDIV_POWER_4, 0, 0),
	GPUOP(545000,  60625, VSRAM_LEVEL_0, POSDIV_POWER_4, 0, 0),
	GPUOP(527000,  60000, VSRAM_LEVEL_0, POSDIV_POWER_4, 0, 0),
	GPUOP(509000,  59375, VSRAM_LEVEL_0, POSDIV_POWER_4, 0, 0),
	GPUOP(491000,  58750, VSRAM_LEVEL_0, POSDIV_POWER_4, 0, 0),
	GPUOP(474000,  58125, VSRAM_LEVEL_0, POSDIV_POWER_4, 0, 0),
	GPUOP(456000,  57500, VSRAM_LEVEL_0, POSDIV_POWER_4, 0, 0),
	GPUOP(438000,  56875, VSRAM_LEVEL_0, POSDIV_POWER_4, 0, 0),
	GPUOP(420000,  56250, VSRAM_LEVEL_0, POSDIV_POWER_4, 0, 0),
	GPUOP(402000,  55625, VSRAM_LEVEL_0, POSDIV_POWER_4, 0, 0),
	GPUOP(385000,  55000, VSRAM_LEVEL_0, POSDIV_POWER_4, 0, 0),
};

#define SIGNED_OPP_GPU_NUM              ARRAY_SIZE(g_default_gpu)

/**************************************************
 * Segment Adjustment
 **************************************************/
#define ADJOP(_oppidx, _freq, _volt, _vsram, _vaging) \
	{                                   \
		.oppidx = _oppidx,              \
		.freq = _freq,                  \
		.volt = _volt,                  \
		.vsram = _vsram,                \
		.vaging = _vaging,              \
	}

static struct gpufreq_adj_info g_segment_adj[] = {
	ADJOP(25, 0, 65000, 0, 0),
	ADJOP(26, 0, 64375, 0, 0),
	ADJOP(27, 0, 64375, 0, 0),
	ADJOP(28, 0, 63750, 0, 0),
	ADJOP(29, 0, 63750, 0, 0),
	ADJOP(30, 0, 63125, 0, 0),
	ADJOP(31, 0, 63125, 0, 0),
	ADJOP(32, 0, 62500, 0, 0),
	ADJOP(33, 0, 62500, 0, 0),
	ADJOP(34, 0, 61875, 0, 0),
	ADJOP(35, 0, 61875, 0, 0),
	ADJOP(36, 0, 61250, 0, 0),
	ADJOP(37, 0, 61250, 0, 0),
	ADJOP(38, 0, 60625, 0, 0),
	ADJOP(39, 0, 60625, 0, 0),
	ADJOP(40, 0, 60000, 0, 0),
};

static struct gpufreq_adj_info g_mcl50_adj[] = {
	ADJOP(0,  0, 68750, VSRAM_LEVEL_0, 0),
	ADJOP(1,  0, 68750, VSRAM_LEVEL_0, 0),
	ADJOP(2,  0, 68125, VSRAM_LEVEL_0, 0),
	ADJOP(3,  0, 67500, VSRAM_LEVEL_0, 0),
	ADJOP(4,  0, 66875, VSRAM_LEVEL_0, 0),
	ADJOP(5,  0, 66250, VSRAM_LEVEL_0, 0),
	ADJOP(6,  0, 65625, VSRAM_LEVEL_0, 0),
	ADJOP(7,  0, 65000, VSRAM_LEVEL_0, 0),
	ADJOP(8,  0, 64375, 0,             0),
	ADJOP(9,  0, 64375, 0,             0),
	ADJOP(10, 0, 63750, 0,             0),
	ADJOP(11, 0, 63125, 0,             0),
	ADJOP(12, 0, 62500, 0,             0),
	ADJOP(13, 0, 62500, 0,             0),
	ADJOP(14, 0, 61875, 0,             0),
	ADJOP(15, 0, 61250, 0,             0),
	ADJOP(16, 0, 60625, 0,             0),
	ADJOP(17, 0, 60625, 0,             0),
	ADJOP(18, 0, 60000, 0,             0),
	ADJOP(19, 0, 59375, 0,             0),
	ADJOP(20, 0, 58750, 0,             0),
	ADJOP(21, 0, 58750, 0,             0),
	ADJOP(22, 0, 58125, 0,             0),
	ADJOP(23, 0, 57500, 0,             0),
	ADJOP(24, 0, 56875, 0,             0),
	ADJOP(25, 0, 56875, 0,             0),
	ADJOP(26, 0, 56875, 0,             0),
	ADJOP(27, 0, 56875, 0,             0),
	ADJOP(28, 0, 56250, 0,             0),
	ADJOP(29, 0, 56250, 0,             0),
	ADJOP(30, 0, 56250, 0,             0),
	ADJOP(31, 0, 56250, 0,             0),
	ADJOP(32, 0, 55625, 0,             0),
	ADJOP(33, 0, 55625, 0,             0),
	ADJOP(34, 0, 55625, 0,             0),
	ADJOP(35, 0, 55625, 0,             0),
	ADJOP(36, 0, 55000, 0,             0),
	ADJOP(37, 0, 55000, 0,             0),
	ADJOP(38, 0, 55000, 0,             0),
	ADJOP(39, 0, 55000, 0,             0),
	ADJOP(40, 0, 54375, 0,             0),
};

static struct gpufreq_adj_info g_avs_adj[] = {
	ADJOP(0,  0, 0, 0, 0),
	ADJOP(8,  0, 0, 0, 0),
	ADJOP(24, 0, 0, 0, 0),
	ADJOP(40, 0, 0, 0, 0),
};

/**************************************************
 * Aging Adjustment
 **************************************************/
static unsigned int g_aging_table[][SIGNED_OPP_GPU_NUM] = {
	{ 
		1875, 1875, 1875, 1875, 1875, 1875, 1875, 1875, 1875, 1875,
		1875, 1875, 1875, 1875, 1875, 1250, 1250, 1250, 1250, 1250,
		1250, 1250, 1250, 1250, 1250, 1250, 1250, 1250, 1250, 625,
		625,  625,  625,  625,  625,  625,  625,  625,  625,  625,
		625,
	},
	{ 
		1875, 1875, 1875, 1875, 1875, 1875, 1875, 1875, 1875, 1875,
		1875, 1875, 1875, 1875, 1875, 1250, 1250, 1250, 1250, 1250,
		1250, 1250, 1250, 1250, 1250, 1250, 1250, 1250, 1250, 625,
		625,  625,  625,  625,  625,  625,  625,  625,  625,  625,
		625,
	},
	{ 
		1875, 1875, 1875, 1875, 1875, 1875, 1875, 1875, 1875, 1875,
		1875, 1875, 1875, 1875, 1875, 1250, 1250, 1250, 1250, 1250,
		1250, 1250, 1250, 1250, 1250, 1250, 1250, 1250, 1250, 625,
		625,  625,  625,  625,  625,  625,  625,  625,  625,  625,
		625,
	},
	{ 
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0,
	},
};

#endif /* __GPUFREQ_MT6879_H__ */
