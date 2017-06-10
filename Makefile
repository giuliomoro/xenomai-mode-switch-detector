SKIN ?= alchemy
CFLAGS=$(shell /usr/xenomai/bin/xeno-config --skin=$(SKIN) --cflags)
LDFLAGS=$(shell /usr/xenomai/bin/xeno-config --skin=$(SKIN) --ldflags)

all: mode_switches_detector
mode_switches_detector:
	gcc mode_switches_detector.c -o mode_switches_detector $(CFLAGS) $(LDFLAGS)

run: mode_switches_detector
	./mode_switches_detector --shared-registry

clean:
	rm mode_switches_detector

.PHONY: mode_switches_detector
