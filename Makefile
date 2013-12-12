
SUBDIRS = misc-modules

all: subdirs

subdirs:
	for n in $(SUBDIRS); do $(MAKE) -C $$n || exit 1; done
modules:
	for n in $(SUBDIRS); do $(MAKE) -C $$n modules || exit 1; done
modules_install:
	for n in $(SUBDIRS); do $(MAKE) -C $$n modules_install || exit 1; done

clean:
	for n in $(SUBDIRS); do $(MAKE) -C $$n clean; done


