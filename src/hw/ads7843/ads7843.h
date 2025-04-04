/**
 * @file ads7843.h
 * @author cF-embedded (cf@embedded.pl)
 * @brief ads7843 touch screen controller hw configuration
 *
 * @copyright Copyright (c) 2024
 *
 */

#ifndef _ADS7843_H
#define _ADS7843_H

#include "platform_specific.h"

#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */

    /**
     * @defgroup hw_core
     * @{
     */

    /**
     * @brief function to hw initialize ads7843
     *
     */
    void ads7843_init(void);
/**
 * @}
 */
#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _ADS7843_H */
