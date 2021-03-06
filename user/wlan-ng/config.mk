WLAN_VERSION=0
WLAN_PATCHLEVEL=2
WLAN_SUBLEVEL=1
WLAN_EXTRAVERSION=-pre1
# PRISM2_PCMCIA is not defined
# PRISM2_PLX is not defined
PRISM2_PCI=y
# PRISM2_USB is not defined
LINUX_SRC=$(ROOTDIR)/$(LINUXDIR)
# CONFIG_NETLINK is not defined
CONFIG_PACKET=y
KERNEL_CFLAGS=-D__KERNEL__ -I$(LINUX_SRC)/include -fno-builtin -Wall -Wstrict-prototypes -Wno-trigraphs -O2 -fno-strict-aliasing -fno-common 
KERNEL_MODFLAGS=-DMODULE
TARGET_ROOT_ON_HOST=$(ROMFSDIR)
MODDIR=/lib/modules/$(KERNELRELEASE)
TARGET_MODDIR=$(TARGET_ROOT_ON_HOST)/$(MODDIR)
INST_EXEDIR=/sbin
TARGET_INST_EXEDIR=$(TARGET_ROOT_ON_HOST)/$(INST_EXEDIR)
RC_DIR=/etc
SYSV_INIT=y
# INSTALL_DEPMOD is not defined
HOST_COMPILE=
HOST_CFLAGS=-Wall -Wstrict-prototypes -O2 -fomit-frame-pointer
HOST_AS=$(HOST_COMPILE)as
HOST_LD=$(HOST_COMPILE)ld
HOST_CC=$(HOST_COMPILE)gcc
HOST_CPP=$(HOST_CC) -E
HOST_AR=$(HOST_COMPILE)ar
HOST_NM=$(HOST_COMPILE)nm
HOST_STRIP=$(HOST_COMPILE)strip
HOST_OBJCOPY=$(HOST_COMPILE)objcopy
HOST_OBJDUMP=$(HOST_COMPILE)objdump
HOST_RANLIB=$(HOST_COMPILE)ranlib
HOST_MAKE=make
CROSS_COMPILE=
# CROSS_COMPILE_ENABLED is not defined
#AS=$(HOST_COMPILE)as
#LD=$(HOST_COMPILE)ld
#CC=$(HOST_COMPILE)gcc
#CPP=$(HOST_CC) -E
#AR=$(HOST_COMPILE)ar
#NM=$(HOST_COMPILE)nm
#STRIP=$(HOST_COMPILE)strip
#OBJCOPY=$(HOST_COMPILE)objcopy
#OBJDUMP=$(HOST_COMPILE)objdump
#RANLIB=$(HOST_COMPILE)ranlib
#MAKE=make
#WLAN_DEBUG=y
