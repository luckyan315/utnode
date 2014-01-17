


ADDON_NM=struct
TEST_SCRIPT_NM	?= $(addsuffix .js, $(ADDON_NM))
ADDON_SRC		?= $(addsuffix .cc, $(ADDON_NM))


all:build test


build: $(ADDON_SRC)
	@echo ">>>>>>>>starting build"	
	@node-gyp configure
	@node-gyp build
	@echo "build finished<<<<<<<<"

test: $(TEST_SCRIPT_NM)
	@echo ">>>>>>>>starting test"
	@node $<
	@echo "test finished<<<<<<<<"

rebuild:func.cc
	@echo ">>>>>>>>starting $@"
	@node-gyp rebuild
	@echo "$@ finished<<<<<<<<"
	

clean:
	@echo ">>>>>>>>start clean"
	@node-gyp clean
	@echo "clean finished<<<<<<<<"


