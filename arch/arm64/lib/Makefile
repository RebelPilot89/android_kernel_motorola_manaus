# SPDX-License-Identifier: GPL-2.0-only
#
# Makefile para las librerías específicas de arquitectura ARM64
# Optimizadas para MT6879 (Dimensity 7030) - Kernel Personalizado
#

# Librerías genéricas de manejo de memoria y strings
lib-y		:= clear_user.o delay.o copy_from_user.o		\
		   copy_to_user.o copy_in_user.o copy_page.o		\
		   clear_page.o csum.o memchr.o memcpy.o	\
		   memset.o memcmp.o strcmp.o strncmp.o strlen.o	\
		   strnlen.o strchr.o strrchr.o tishift.o


# Optimizaciones NEON (IA y Multimedia)
ifeq ($(CONFIG_KERNEL_MODE_NEON), y)
obj-$(CONFIG_XOR_BLOCKS)	+= xor-neon.o
CFLAGS_REMOVE_xor-neon.o	+= -mgeneral-regs-only
CFLAGS_xor-neon.o		+= -ffreestanding
endif

# Librería para vaciado de caché (Terminal y Buffers de alta velocidad)
lib-$(CONFIG_ARCH_HAS_UACCESS_FLUSHCACHE) += uaccess_flushcache.o

# Robustez y Seguridad por Hardware (MTE para Dimensity 7030)
obj-$(CONFIG_FUNCTION_ERROR_INJECTION)	+= error-inject.o
obj-$(CONFIG_ARM64_MTE)			+= mte.o
obj-$(CONFIG_KASAN_SW_TAGS)		+= kasan_sw_tags.o
