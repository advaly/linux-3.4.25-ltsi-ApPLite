/**
 * @file          os_specific_func.h
 *
 * \brief         Header file for OS Specific functions.
 *
 * \b COPYRIGHT : TOSHIBA Corporation Semiconductor and Storage Company
 *                2010-2015 All rights reserved
 *
 * \b Project   : Glenfiddich
 *
 * \b Version   : 0.2
 *
 * \b Release   : None
 *
 * \b Date      : 28-Jun-2013
 */

/**
 * @addtogroup PlatformLayer
 * @{
 */

/**
 * @addtogroup PlatformResourcesAccess
 * @{
 */

#ifndef _OS_SPECIFIC_FUNC_H_
#define _OS_SPECIFIC_FUNC_H_

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/*----------------------- Header Files Inclusions ---------------------------*/
#include <linux/module.h>      /* Dynamic loading of modules into the kernel */
#include <linux/init.h>        /* Used for initialization functions */
#include <linux/pci.h>         /* PCI defines and function prototypes */
#include <linux/errno.h>       /* Errno for system calls */
#include <linux/interrupt.h>   /* Interrupt related macros and functions */
#include <linux/spinlock.h>    /* Generic Lock/Unlock functions */
#include <linux/mutex.h>       /* Mutual exclusion locks */
#include <linux/sched.h>       /* Task related fucntions */
#include <asm/irq.h>           /* Functions/Macros for interrupts */
#include <asm/io.h>            /* I/O related functions */
#include <linux/delay.h>       /* Delay related functions like mdelay etc */
#include <linux/timer.h>       /* Timer related functions like add_timer etc */
#include <linux/wait.h>        /* Declarations for waiting on events */
#include <linux/slab.h>        /* Used for allocaiton/Deallocation of memory */
#include <linux/signal.h>      /* Synchronization of events */
#include <linux/platform_device.h> /* Registration as platform driver */
#include <asm/thread_info.h> /* Thread related macros and function prototypes */
#include <linux/kthread.h>/* Interface for creating/stopping kernel threads */
#include <linux/semaphore.h>/* Semaphore related handling */
#include <linux/completion.h>   /* Header file for completions */
#include <linux/dma-mapping.h>  /* DMA related linux defines and enums */
#include <linux/dmapool.h>
#include "types.h"          /* Header file for type defs data */
/*-------------------------- Macro Definitions ------------------------------*/

/** @addtogroup PFA_DEFINES PFA_DEFINES
 * @{
 */

#ifdef __KERNEL_3_4_25
#define DECLARE_MUTEX(name) \
    struct semaphore name = __SEMAPHORE_INITIALIZER(name, 1)
#define init_MUTEX_LOCKED(os_sem)   sema_init(os_sem, 0)
#endif /* __KERNEL_3_4_25 */
/*
 * Number of resources that can be allocated by OS layer.
 * As of now 32 is the number chosen. Based on need this can be
 * increased to more.
 */
#define _MAX_NUM_RES 32

/* Resource usage macros */
#define _IN_USE 1
#define _NOT_IN_USE 0

/* Semaphore related macros */
#define INIT_SEM(os_sem) DECLARE_MUTEX(os_sem)
#define TAKE_SEM(os_sem) down_interruptible(os_sem)
#define REL_SEM(os_sem) up(os_sem)

#define INIT_SEM_LOCKED(os_sem)  init_MUTEX_LOCKED(os_sem)
#define TAKE_SEM_TIMEOUT(os_sem, ms) down_timeout(os_sem, ms)

#define SPIN_IRQ_SAVE(lock,flags)   spin_lock_irqsave(lock,flags)
#define SPIN_IRQ_RESTORE(lock,flags)    spin_unlock_irqrestore(lock,flags);

/* Macro related to system time, represent the current system time */
#define CUR_TIME jiffies

/**@}*/ // PFA_DEFINES

/*-------------------------- Enum Definitions -------------------------------*/

/*------------------ Data Structures & Custom Typedefs ----------------------*/

/** @addtogroup PFA_Typedefs PFA_Typedefs
 * @{
 */

/* typedef for PCI device structure */
typedef struct pci_dev PCI_DEV;
/* typedef for  PCI device id */
typedef struct pci_device_id PCI_DEV_ID;
/* typedef for  PCI driver structure */
typedef struct pci_driver PCI_DRIVER;
/* typedef for  spin lock structure */
typedef spinlock_t LOCK;
/* typedef for  timer structure */
typedef struct timer_list TIMER;
/* typedef for  task structure */
typedef struct task_struct *TASK;
/* typedef for Interrupt function pointer */
typedef irqreturn_t (*IFPTR)(int, void *);
/* typedef for general function pointer */
typedef int (*TIFPTR)(void *);
/* typedef for timer function pointer */
typedef unsigned int (*TFPTR)(TIMER *,unsigned int);
/* typedef for tasklet structure */
typedef struct tasklet_struct BH;
/* typedef for interrupt return values */
typedef irqreturn_t IRQRET;
/* typedef for semaphore structure */
typedef struct semaphore SEMA;

/* typedef for completions */
typedef struct completion COMPLETION;

/**@}*/ // PFA_Typedefs

/** @defgroup PFA_Structures PFA_Structures
 * @{
 */

/**
 * @brief Timer structure for allocation
 */
typedef struct tag_os_timer_t {
    TIMER tlist;               /**< Timer element */
    _ub32 uiTimerAvailable;    /**< Timer available/not */
}os_timer_t;

/**
 * @brief Spinlock structure for allocation
 */
typedef struct tag_os_lock_t{
    LOCK spin;                /**< Spinlock element */
    _ub32 uiLockAvailable;    /**< Lock available/not */
}os_lock_t;

/**
 * @brief Resource structure for address and Irq
 */
typedef struct tag_os_resource_t{
    _addr uiBase;    /**< Address base */
    _ub32 uiIrq;     /**< IRQ no */
}os_resource_t;

/**@}*/ // PFA_Structures

/*------------------------------- Externs ------------------------------------*/

/*----------------------------- Prototypes -----------------------------------*/

/** @addtogroup PFA_Prototypes PFA_Prototypes
 * @{
 */

/* Function to obtain the resources */
_ub32 os_obtainResource(os_resource_t *pArg);

/* Function to release the resources */
void os_releaseResource(os_resource_t *pArg);

#ifdef __PERFORMANCE_MEASUREMENT
void os_perf_start(int iDir);
void os_perf_stop(int iDir, unsigned long uiSize);
#endif /* __PERFORMANCE_MEASUREMENT */

/**@}*/ // PFA_Prototypes

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _OS_SPECIFIC_FUNC_H_ */

/**@}*//* PlatformResourcesAccess */
/**@}*//* PlatformLayer */

