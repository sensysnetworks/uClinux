#ifndef _ASM_M68K_MODULE_H
#define _ASM_M68K_MODULE_H
/*
 * This file contains the m68k architecture specific module code.
 */

#define module_map(x)		kmalloc(x,GFP_KERNEL)
#define module_unmap(x)		kfree(x)
#define module_arch_init(x)	(0)
#define arch_init_modules(x)	do { } while (0)

#endif /* _ASM_M68K_MODULE_H */
