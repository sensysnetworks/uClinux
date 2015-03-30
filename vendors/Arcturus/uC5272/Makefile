#
#	Makefile -- Build instructions for Arcturus/uC5272
#

ROMFSIMG = $(IMAGEDIR)/romfs.img
IMAGE    = $(IMAGEDIR)/image.bin
ELFIMAGE = $(IMAGEDIR)/image.elf
PROJECTDIR = $(shell dirname $(ROOTDIR))

DIRS = 

ROMFS_DIRS = bin dev etc etc/config etc/ppp/peers home lib mnt proc \
             usr var home/httpd home/httpd/cgi-bin

DEVICES = \
	tty,c,5,0      console,c,5,1      \
	mem,c,1,1      kmem,c,1,2         null,c,1,3       ram0,b,1,0 \
	\
	ram1,b,1,1 \
	\
	ptyp0,c,2,0    ptyp1,c,2,1        ptyp2,c,2,2      ptyp3,c,2,3 \
	ptyp4,c,2,4    ptyp5,c,2,5        ptyp6,c,2,6      ptyp7,c,2,7 \
	ptyp8,c,2,8	\
	\
	tty0,c,4,0     tty1,c,4,1         tty2,c,4,2       tty3,c,4,3 \
	ttyS0,c,4,64   ttyS1,c,4,65 \
	\
	ttyp0,c,3,0    ttyp1,c,3,1        ttyp2,c,3,2      ttyp3,c,3,3 \
	ttyp4,c,3,4    ttyp5,c,3,5        ttyp6,c,3,6      ttyp7,c,3,7 \
	\
	zero,c,1,5     random,c,1,8       urandom,c,1,9 \
	\
	ppp,c,108,0 pppox0,c,144,0 \
	\
	mtd0,c,90,0 mtd1,c,90,2 mtd2,c,90,4			\
	mtd3,c,90,6 mtd4,c,90,8 mtd5,c,90,10			\
	mtd6,c,90,12 mtd7,c,90,14				\
	\
	mtdblock0,b,31,0 mtdblock1,b,31,1 mtdblock2,b,31,2	\
	mtdblock3,b,31,3 mtdblock4,b,31,4 mtdblock5,b,31,5	\
	mtdblock6,b,31,6 mtdblock7,b,31,7			\
	\
	rtsock0,c,121,0 rtsock1,c,121,1 rtsock2,c,121,2		\
	rtsock3,c,121,3 rtsock4,c,121,4 rtsock5,c,121,5

all:
	dirs=$(DIRS) ; \
	for i in $$dirs ; do  make -C $$i || exit $? ; done

clean:
	-dirs=$(DIRS) ; \
	for i in $$dirs; do [ ! -d $$i ] || make -C $$i clean; done

romfs:
	[ -d $(ROMFSDIR)/$$i ] || mkdir -p $(ROMFSDIR)
	for i in $(ROMFS_DIRS); do \
		[ -d $(ROMFSDIR)/$$i ] || mkdir -p $(ROMFSDIR)/$$i; \
	done
	for i in $(DEVICES); do \
		touch $(ROMFSDIR)/dev/@$$i; \
	done
	dirs=$(DIRS) ; for i in $$dirs; do make -C $$i romfs || exit $? ; done
	$(ROMFSINST) -s /bin /sbin
	$(ROMFSINST) -s /bin /usr/sbin
	$(ROMFSINST) -s /bin /usr/bin
	$(ROMFSINST) -s /bin /sbin
	$(ROMFSINST) -s /var/tmp /tmp
	$(ROMFSINST) -s /tmp/connect-errors /etc/ppp/connect-errors
	$(ROMFSINST) -s mtd2 /dev/env
	$(ROMFSINST) -s /tmp/resolv.conf /etc/resolv.conf
	$(ROMFSINST) -s /tmp/chap-secrets /etc/ppp/chap-secrets
	$(ROMFSINST) -s /tmp/pap-secrets /etc/ppp/pap-secrets
	$(ROMFSINST) -s /tmp/custom /etc/ppp/peers/custom
	$(ROMFSINST) /bin
	$(ROMFSINST) /etc/rc
	$(ROMFSINST) /etc/hosts
	$(ROMFSINST) /etc/inittab
	$(ROMFSINST) /etc/profile
	$(ROMFSINST) /etc/nsswitch.conf
	$(ROMFSINST) /etc/config/passwd
	$(ROMFSINST) /etc/services
	$(ROMFSINST) /etc/issue
	$(ROMFSINST) /etc/ppp
	$(ROMFSINST) /etc/apeg
	$(ROMFSINST) /etc/dhcpc
	$(ROMFSINST) vpn /bin/vpn
	$(ROMFSINST) html /home/httpd
	echo "`cat version` -- " `date` > $(ROMFSDIR)/etc/version

$(ROMFSDIR)/boot/linux.img: $(IMAGEDIR)/linux.bin
	@mkdir -p $(@D)
	gzip -9 -c $(IMAGEDIR)/linux.bin > $(IMAGEDIR)/linux.bin.gz
	$(PROJECTDIR)/tools/bin/mkimage -A m68k -O linux -T kernel -C gzip -a 0x20000 \
		-e 0x20400 -n linux -d $(IMAGEDIR)/linux.bin.gz \
		$(ROMFSDIR)/boot/linux.img

#
# in making the image we have to add the romfs into the 
# system image
# The blkmem driver will find it at the end of the data section.
# There have been several ways to actually
# add the rom fils system into the image
# In this port _end_romfs is required to produce the start of the
# ram area.
# this used to be calcualted by setting
#  romfs_size =       some number; in romfs.ld
#
#
image: image.romfs image.jffs2

image.jffs2: $(ROMFSDIR)/boot/linux.img

image.romfs:
	[ -d $(IMAGEDIR) ] || mkdir -p $(IMAGEDIR)
	genromfs -v -V "ROMdisk" -f $(ROMFSIMG) -d $(ROMFSDIR)
	#cat $(ROMFSIMG) | wc -c  
	#$(CROSS_COMPILE)objcopy -O binary --remove-section=.romvec \
	#		--remove-section=.text --remove-section=.ramvec \
	#		--remove-section=.bss --remove-section=.eram \
	#		$(ROOTDIR)/$(LINUXDIR)/linux $(IMAGEDIR)/linux.data
	$(CROSS_COMPILE)objcopy -O binary --remove-section=.ramvec\
		--remove-section=.eram \
		--set-section-flags=.romvec=CONTENTS,ALLOC,LOAD,READONLY,CODE \
		$(ROOTDIR)/$(LINUXDIR)/linux $(IMAGEDIR)/linux.bin
	cat $(IMAGEDIR)/linux.bin $(ROMFSIMG) > $(IMAGE)

vendor_flash:
	$(ROOTDIR)/bin/make_flash
