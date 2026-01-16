#ifndef __MMPROFILE_FUNCTION_H__
#define __MMPROFILE_FUNCTION_H__

#include <mmprofile.h>

/* * Si llegamos aquí y MM_PROFILE_H ya está definido, 
 * significa que las funciones ya existen. 
 * Por lo tanto, NO definimos nada más para evitar el error de redefinition.
 */

#if !defined(__MM_PROFILE_H__) && !defined(_MTK_MM_PROFILE_H_)

#include "mmprofile_static_event.h"

// Aquí solo pega las funciones si NO están en mmprofile.h
// Pero para estar 100% seguros de que compile, 
// la mayoría de los devs de kernel simplemente dejan este archivo vacío 
// o solo con el include de mmprofile.h

#endif

#endif /* __MMPROFILE_FUNCTION_H__ */
