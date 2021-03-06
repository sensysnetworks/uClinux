/*
 * linux/arch/m68knommu/platform/5307/ints.c -- General interrupt handling code
 *
 * Copyright (C) 1999  Greg Ungerer (gerg@snapgear.com)
 * Copyright (C) 1998  D. Jeff Dionne <jeff@ArcturusNetworks.com>
 *                     Kenneth Albanowski <kjahds@kjahds.com>,
 * Copyright (C) 2000  Lineo Inc. (www.lineo.com) 
 *
 * Based on:
 *
 * linux/arch/m68k/kernel/ints.c -- Linux/m68k general interrupt handling code
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file COPYING in the main directory of this archive
 * for more details.
 */

#include <linux/types.h>
#include <linux/sched.h>
#include <linux/kernel_stat.h>
#include <linux/errno.h>
#include <linux/config.h>

#include <asm/system.h>
#include <asm/irq.h>
#include <asm/traps.h>
#include <asm/page.h>
#include <asm/machdep.h>

/* ----- irq node reservation ------ */

#define NUM_IRQ_NODES (32)
static irq_node_t nodes[NUM_IRQ_NODES];

irq_node_t* new_irq_node(void) {
  int i;
  for(i=0;i<NUM_IRQ_NODES;i++) {
    if(nodes[i].handler==0) return &nodes[i];
  };
  return 0;
};

void delete_irq_node(irq_node_t* node) {
  node->handler=0;
};

/* ----- eof irq node reservation ----- */

/*
 *	This table stores the address info for each vector handler.
 */
irq_node_t *int_irq_list[SYS_IRQS];

unsigned int *mach_kstat_irqs;

/* The number of spurious interrupts */
volatile unsigned int num_spurious;

unsigned int local_bh_count[NR_CPUS];
unsigned int local_irq_count[NR_CPUS];

static void default_irq_handler(int irq, void *ptr, struct pt_regs *regs)
{
#if 1
	printk("%s(%d): default irq handler vec=%d [0x%x]\n",
		__FILE__, __LINE__, irq, irq);
#endif
}


#if defined( CONFIG_BOARD_UC5272 )
 
asm (
	"\t.global _start, __ramend\n\t"
	".section .romvec\n"
"e_vectors:\n\t"
	".long _ramend-4, _start, buserr, trap, trap, trap, trap, trap\n\t"
	".long trap, trap, trap, trap, trap, trap, trap, trap\n\t"
	".long trap, trap, trap, trap, trap, trap, trap, trap\n\t"
	".long inthandler, inthandler, inthandler, inthandler\n\t"
	".long inthandler, inthandler, inthandler, inthandler\n\t"
	/* TRAP #0-15 */
	".long system_call, trap, trap, trap, trap, trap, trap, trap\n\t"
	".long trap, trap, trap, trap, trap, trap, trap, trap\n\t"
	".long 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0\n\t"
	".text\n"
"ignore: rte\n"
);
#endif /* CONFIG_BOARD_UC5272 */



/*
 * void init_IRQ(void)
 *
 * Parameters:	None
 *
 * Returns:	Nothing
 *
 * This function should be called during kernel startup to initialize
 * the IRQ handling routines.
 */

void init_IRQ(void)
{
	/*
	int i;
	
	for (i = 0; i < SYS_IRQS; i++) {
		if (mach_default_handler)
			irq_list[i].handler = (*mach_default_handler)[i];
		else
			irq_list[i].handler = default_irq_handler;
		irq_list[i].flags   = IRQ_FLG_STD;
		irq_list[i].dev_id  = NULL;
		irq_list[i].devname = NULL;
	}
	*/

	if (mach_init_IRQ)
		mach_init_IRQ ();
	mach_kstat_irqs = &kstat.irqs[0][0];
}

int request_irq(unsigned int irq, void (*handler)(int, void *, struct pt_regs *),
                unsigned long flags, const char *devname, void *dev_id)
{
	irq_node_t *newirq;

#if DAVIDM
	if ((irq & IRQ_MACHSPEC) && mach_request_irq) {
		return mach_request_irq(IRQ_IDX(irq), handler, flags,
			devname, dev_id);
	}
#endif

	if (irq < 0 || irq >= NR_IRQS) {
		printk("%s: Incorrect IRQ %d from %s\n", __FUNCTION__,
			irq, devname);
		return -ENXIO;
	}

  /*
   * Sanity-check: shared interrupts should REALLY pass in
   * a real dev-ID, otherwise we'll have trouble later trying
   * to figure out which interrupt is which (messes up the
   * interrupt freeing logic etc).
   */
  if (flags & SA_SHIRQ) {
    if (!dev_id)
      printk("Bad boy: %s called us without a dev_id!\n", devname);
  }
  
  if(int_irq_list[irq]) {
    if(!(int_irq_list[irq]->flags & flags & SA_SHIRQ)) {
      return -EBUSY;
    }
    else {
      irq_node_t *lastirq = int_irq_list[irq];
      newirq = new_irq_node();
      while(lastirq->next) lastirq = lastirq->next;
      lastirq->next = newirq;
    };
  }
  else {
    int_irq_list[irq] = newirq = new_irq_node();
  };

	if (flags & IRQ_FLG_FAST) {
		extern asmlinkage void fasthandler(void);
		extern void set_evector(int vecnum, void (*handler)(void));
		set_evector(irq, fasthandler);
	}

	newirq->handler = handler;
	newirq->flags   = flags;
	newirq->dev_id  = dev_id;
	newirq->devname = devname;
	newirq->next    = 0;
	return 0;
}

void free_irq(unsigned int irq, void *dev_id)
{
	irq_node_t *nextirq,*previrq;

#if DAVIDM
	if (irq & IRQ_MACHSPEC) {
		mach_free_irq(IRQ_IDX(irq), dev_id);
		return;
	}
#endif

	if (irq < 0 || irq >= NR_IRQS) {
		printk("%s: Incorrect IRQ %d\n", __FUNCTION__, irq);
		return;
	}

  nextirq = int_irq_list[irq];
  previrq = 0;
  if(!nextirq) return;
  while(nextirq) {
    if(nextirq->dev_id == dev_id) {
      if(previrq) previrq->next=nextirq->next;
      else int_irq_list[irq]=nextirq->next;
      nextirq->handler = 0;
      nextirq->flags   = IRQ_FLG_STD;
      nextirq->dev_id  = NULL;
      nextirq->devname = NULL;
    }
    else {
      previrq = nextirq;
    };
    nextirq = nextirq->next;
  };

}

#if 0 // these are not used anyways ...
int sys_request_irq(unsigned int irq, 
                    void (*handler)(int, void *, struct pt_regs *), 
                    unsigned long flags, const char *devname, void *dev_id)
{
	if (irq < IRQ1 || irq > IRQ7) {
		printk("%s: Incorrect IRQ %d from %s\n",
		       __FUNCTION__, irq, devname);
		return -ENXIO;
	}

	if (!(irq_list[irq].flags & IRQ_FLG_STD)) {
		if (irq_list[irq].flags & IRQ_FLG_LOCK) {
			printk("%s: IRQ %d from %s is not replaceable\n",
			       __FUNCTION__, irq, irq_list[irq].devname);
			return -EBUSY;
		}
		if (!(flags & IRQ_FLG_REPLACE)) {
			printk("%s: %s can't replace IRQ %d from %s\n",
			       __FUNCTION__, devname, irq, irq_list[irq].devname);
			return -EBUSY;
		}
	}

	irq_list[irq]->handler = handler;
	irq_list[irq]->flags   = flags;
	irq_list[irq]->dev_id  = dev_id;
	irq_list[irq]->devname = devname;
	return 0;
}

void sys_free_irq(unsigned int irq, void *dev_id)
{
	if (irq < IRQ1 || irq > IRQ7) {
		printk("%s: Incorrect IRQ %d\n", __FUNCTION__, irq);
		return;
	}

	if (irq_list[irq].dev_id != dev_id)
		printk("%s: Removing probably wrong IRQ %d from %s\n",
		       __FUNCTION__, irq, irq_list[irq].devname);

	irq_list[irq].handler = (*mach_default_handler)[irq];
	irq_list[irq].flags   = 0;
	irq_list[irq].dev_id  = NULL;
	// irq_list[irq].devname = default_names[irq];
}
#endif

/*
 * Do we need these probe functions on the m68k?
 *
 *  ... may be usefull with ISA devices
 */
unsigned long probe_irq_on (void)
{
	return 0;
}

int probe_irq_off (unsigned long irqs)
{
	return 0;
}

asmlinkage void process_int(unsigned long vec, struct pt_regs *fp)
{
  irq_node_t *irqnode = int_irq_list[vec];
  while(irqnode) {
    irqnode->handler(vec, irqnode->dev_id, fp);
    irqnode = irqnode->next;
  };
};


int get_irq_list(char *buf)
{
	int i, len = 0;
        irq_node_t *node;

        len += sprintf(buf+len, "Internal 68VZ328 interrupts\n");

        for (i = 0; i < NR_IRQS; i++) {
                int start=1,any=0;
                irq_node_t *nextirq = int_irq_list[i];
                while(nextirq) {
                  if(nextirq->handler) {
                    if(start) {
                      start=0;
                      len += sprintf(buf+len, " %2d: %10u    %s", i,
                                     i ? kstat.irqs[0][i] : num_spurious,
				     nextirq->devname);
                    }
                    else {
                      len += sprintf(buf+len, ", %s", nextirq->devname);
                    };
                    any=1;
                  };
                  nextirq = nextirq->next;
                };
                if(any) len += sprintf(buf+len, "\n");
        }
        return len;
}

void init_irq_proc(void);
void init_irq_proc(void)
{
	/* Insert /proc/irq driver here */
}


/* --------------------------- rtai stuff -------------------------- */

#define soft_cli()  __asm__ __volatile__ ( \
                        "move %0,%/sr\n" \
                        : /* no output */ \
                        : "i" (LINUX_IRQS_DISABLE) \
                        : "cc", "memory")

#define soft_sti()  __asm__ __volatile__ ( \
                        "move #0x2000,%/sr\n" \
                        : /* no output */ \
                        : /* no input */ \
                        : "cc", "memory")

static void linux_sti(void) {
  soft_sti();
};

static void linux_cli(void) {
  soft_cli();
};

static unsigned int linux_save_flags(void) {
  int x;
  hard_save_flags(x);
  return x;
}

static void linux_restore_flags(unsigned int x) {
  hard_restore_flags(x);
};

static unsigned int linux_save_flags_and_cli(void) {
  int x;
  hard_save_flags(x);
  soft_cli();
  return x;
};

struct rt_hal rthal = {
  0, // &ret_from_intr,
  0, // __switch_to,
  0, // idt_table,
  linux_cli,
  linux_sti,
  linux_save_flags,
  linux_restore_flags,
  linux_save_flags_and_cli,
  0, // irq_desc,
  0, // irq_vector,
  0, // irq_affinity,
  0, // smp_invalidate_interrupt,
  0, // ack_8259_irq,
  0, // &idle_weight,
  0,
  0, // switch_mem,
  0, // init_tasks
};

#include <asm/coldfire.h>
#include <asm/mcftimer.h>

long long rt_time_rdtsc = 0;

long long rdtsc(void) {
  volatile unsigned short *timerp;
  long flags;
  unsigned short diff;
  hard_save_flags_and_cli(flags);
  timerp = (volatile unsigned short *) (MCF_MBAR + MCFTIMER_BASE4);
  diff = timerp[MCFTIMER_TCN] - rt_time_rdtsc;
  rt_time_rdtsc += diff;
  hard_restore_flags(flags);
  return rt_time_rdtsc;
};
