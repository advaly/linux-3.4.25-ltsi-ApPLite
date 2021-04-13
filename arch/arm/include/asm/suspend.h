#ifndef __ASM_ARM_SUSPEND_H
#define __ASM_ARM_SUSPEND_H

extern void cpu_resume(void);
extern int cpu_suspend(unsigned long, int (*)(unsigned long));

extern u32 __nosave_backup_phys;
extern u32 __nosave_begin_phys;
extern u32 __nosave_end_phys;

#endif
