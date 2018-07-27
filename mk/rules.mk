#Control the build verbosity
ifeq ("$(VERBOSE)","1")
	Q :=
        VECHO = @printf
else
	Q := @
        VECHO = @true
endif

%.bin: %.elf
	$(VECHO) "  OBJCOPY\t$@\n"
	$(Q)$(OBJCOPY) -Obinary $< $@

$(NAME).elf: $(OBJS)
	$(VECHO) "  LD\t\t$@\n"
	$(Q) $(CC) $(LDFLAGS) -o $@ $^

%.o: %.c
	$(VECHO) "  CC\t\t$@\n"
	$(Q) $(CC) -o $@ $(CFLAGS) -c $<

%.o: %.S
	$(VECHO) "  AS\t\t$@\n"
	$(Q) $(CC) -o $@ $(CFLAGS) -c $<

%.lds: %.lds.S
	$(VECHO) "  HOSTCC\t\t$@\n"
	$(Q) $(HOSTCC) -E -P -Iinclude -DROMSZ=$(ROMSZ) -DRAMSZ=$(RAMSZ) -o $@ $<

kernel/syscall.c: include/kernel/syscalls.h
	$(VECHO) "  GEN\t\t$@\n"
	$(Q)$(PYTHON) scripts/gen-syscalls.py --source > $@

include/kernel/syscalls.h:
	$(VECHO) "  GEN\t\t$@\n"
	$(Q)$(PYTHON) scripts/gen-syscalls.py --header > $@
