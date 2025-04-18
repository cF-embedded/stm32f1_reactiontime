/*
 * File:    platform_specific.h
 * Author:  GAndaLF
 * Brief:   Platform specific definitions.
 */

#ifndef _PLATFORM_SPECIFIC_H_
#define _PLATFORM_SPECIFIC_H_

/* System includes */
#include "stm32f1xx.h"
#include <errno.h>
#include <stdbool.h>
#include <stddef.h>

/* RTOS includes */
#include "FreeRTOS.h"
#include "FreeRTOSConfig.h"
#include "queue.h"
#include "semphr.h"
#include "task.h"
#include "timers.h"


/**
 * @defgroup utils_platform
 * @{
 */

/**
 * Keyword to declare function or variable as private.
 *
 * PRIVATE keyword is used for symbols that should be available externally only
 * for certain test or debug builds and should be static in production.
 */
#define PRIVATE static

/** Core clock frequency */
#define MCU_CLOCK_FREQ 72000000UL

/**
 * Create RTOS task.
 *
 * @param ptr           Pointer to task function.
 * @param name          Name string.
 * @param stack         Task stack size.
 * @param prio          Task priority.
 *
 * @return              Task handle.
 */
#define rtos_task_create(ptr, name, stack, prio, handle) xTaskCreate(ptr, (const char*)name, stack, NULL, prio, handle)

/**
 * Set task priority.
 *
 * @param task          Task handle.
 * @param prio          Task priority.
 */
#define rtos_task_priority_set(task, prio) vTaskPrioritySet(task, prio)

/**
 * Delay task for specified amount of milliseconds.
 *
 * @param ms            Number of milliseconds the task should be delayed.
 */
#define rtos_delay(ms) vTaskDelay(ms / portTICK_RATE_MS)

/**
 * Delay task for specified amount of millisecond since last_ptr.
 *
 * @param last_ptr      Pointer to start ticks.
 * @param ms            Number of milliseconds the task should be delayed.
 */
#define rtos_delay_until(last_ptr, ms) vTaskDelayUntil(last_ptr, ms)

/**
 * Get current system tick count.
 *
 * @return              Tick count.
 */
#define rtos_tick_count_get() xTaskGetTickCount()

/**
 * Create RTOS queue.
 *
 * @param len           Length of the queue.
 * @param item_size     Size of the single item on the queue.
 *
 * @return              Queue handle.
 */
#define rtos_queue_create(len, item_size) xQueueCreate(len, item_size)

/**
 * Send data to the queue.
 *
 * @param queue_ptr     Queue handle.
 * @param data_ptr      Pointer to data to send.
 * @param ms            Time to wait for queue to be ready.
 *
 * @return              true on success, false on timeout.
 */
#define rtos_queue_send(queue_ptr, data_ptr, ms) xQueueSend(queue_ptr, (void*)data_ptr, ms / portTICK_RATE_MS)

/**
 * Receive data from the queue.
 *
 * @param queue_ptr     Queue handle.
 * @param data_ptr      Pointer to data to receive.
 * @param ms            Time to wait for data to be received.
 *
 * @return              true on success, false on timeout.
 */
#define rtos_queue_receive(queue_ptr, data_ptr, ms) xQueueReceive(queue_ptr, (void*)data_ptr, ms / portTICK_RATE_MS)

/**
 * Receive data from the queue.
 *
 * @param queue_ptr     Queue handle.
 * @param data_ptr      Pointer to data to receive.
 * @param yield         Value information for OS to change actual task after isr
 *
 * @return              true on success, false on timeout.
 */
#define rtos_queue_receive_isr(queue_ptr, data_ptr, yield) xQueueReceiveFromISR(queue_ptr, (void*)data_ptr, yield)

/**
 * Send data to the queue.
 *
 * @param queue_ptr     Queue handle.
 * @param data_ptr      Pointer to data to send.
 * @param yield         Value information for OS to change actual task after isr
 *
 * @return              true on success, false on timeout.
 */
#define rtos_queue_send_isr(queue_ptr, data_ptr, yield) xQueueSendFromISR(queue_ptr, (void*)data_ptr, yield)

/**
 * Create RTOS semaphore.
 *
 * @return              Handle to semaphore to be created.
 */
#define rtos_sem_bin_create() xSemaphoreCreateBinary()

/**
 * Acquire semaphore.
 *
 * @param sem_ptr       Semaphore handle.
 * @param ms            Time to wait for a semaphore.
 *
 * @return              true on success, false on timeout.
 */
#define rtos_sem_take(sem_ptr, ms) xSemaphoreTake(sem_ptr, ms / portTICK_RATE_MS)

/**
 * Release semaphore.
 *
 * @param sem_ptr       Semaphore handle.
 *
 * @return              true on success, false on error.
 */
#define rtos_sem_give(sem_ptr) xSemaphoreGive(sem_ptr)

/**
 * Acquire semaphore from the interrupt.
 *
 * @param sem_ptr       Semaphore handle.
 * @param yield         Flag indicating if context switch is needed.
 */
#define rtos_sem_take_isr(sem_ptr, yield) xSemaphoreTakeFromISR(sem_ptr, yield)

/**
 * Release semaphore from the interrupt.
 *
 * @param sem_ptr       Semaphore handle.
 * @param yield         Flag indicating if context switch is needed.
 */
#define rtos_sem_give_isr(sem_ptr, yield) xSemaphoreGiveFromISR(sem_ptr, yield)

/**
 * Create RTOS mutex.
 *
 * @return              Mutex handle.
 */
#define rtos_mutex_create() xSemaphoreCreateMutex()

/**
 * Acquire mutex.
 *
 * @param mutex_ptr     Mutex handle.
 * @param ms            Time to wait on a mutex.
 *
 * @return              true on success, false on timeout.
 */
#define rtos_mutex_take(mutex_ptr, ms) xSemaphoreTake(mutex_ptr, ms / portTICK_RATE_MS)

/**
 * Release mutex.
 *
 * @param mutex_ptr     Mutex handle.
 *
 * @return              true on success, false on timeout.
 */
#define rtos_mutex_give(mutex_ptr) xSemaphoreGive(mutex_ptr)
/* Mutexes should not be given/taken from ISR */

/**
 * Enter critical section.
 */
#define rtos_critical_section_enter() taskENTER_CRITICAL()

/**
 * Exit critical section.
 */
#define rtos_critical_section_exit() taskEXIT_CRITICAL()

/** Type of RTOS queue. */
typedef void* queue_t;

/** Type of RTOS semaphore. */
typedef void* sem_t;

/** Type of RTOS mutex. */
typedef void* mutex_t;

/** Type of RTOS tick. */
typedef TickType_t tick_t;

#define TEST_ENDLESS_LOOP()


/**
 * @}
 */

#endif /* _PLATFORM_SPECIFIC_H_ */
