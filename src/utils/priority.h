/**
 * @file priority.h
 * @author cF-embedded (cf@embedded.pl)
 * @brief tasks and interrupts priorities
 * @date 2024-04-28
 *
 * @copyright Copyright (c) 2024
 *
 */

#ifndef PRIORITY_H
#define PRIORITY_H

/** Position estimation task stacksize */
#define GAME_TASK_STACKSIZE (configMINIMAL_STACK_SIZE * 10)
/** Position estimation task priority */
#define GAME_TASK_PRIORITY (tskIDLE_PRIORITY + 1)

/**
 * @}
 */

#endif /* PRIORITY_H */
