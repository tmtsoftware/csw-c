# Simple wrapper for cmake

BUILD_DIR = build
INSTALL_DIR = /usr/local

all:
	test -d $(BUILD_DIR) || mkdir $(BUILD_DIR)
	(cd $(BUILD_DIR); cmake .. -G "Unix Makefiles"; cmake --build . --verbose)

# May require sudo
install:
	(cd $(BUILD_DIR); $(MAKE) install)

clean:
	rm -rf $(BUILD_DIR)

test: all
	(cd test; runTests.sh)

# May require sudo, actual install dir might be different
uninstall:
	rm -f $(INSTALL_DIR)/lib/libcsw.* $(INSTALL_DIR)/include/csw/csw.h
