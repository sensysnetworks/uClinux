clean:
	rm -f *.[oa]

dep depend:
	:

image: $(TOPDIR)/linux.bin

$(TOPDIR)/linux.bin: $(TOPDIR)/linux
	$(OBJCOPY) -O binary		\
	   --set-section-flags=.romvec=CONTENTS,ALLOC,LOAD,READONLY,CODE \
	   --remove-section=.ramvec	\
	   --remove-section=.eram	\
	   $(TOPDIR)/linux $@


