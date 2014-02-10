

all:build test



build:
	@echo ">>>>>>>>starting build"	
	@node-gyp configure
	@node-gyp build
	@echo "build finished<<<<<<<<"

test:
	@echo ">>>>>>>>starting test"
	@node main.js	
	@echo "test finished<<<<<<<<"

rebuild:
	@echo ">>>>>>>>starting $@"
	@node-gyp rebuild
	@echo "$@ finished<<<<<<<<"
	

clean:
	@echo ">>>>>>>>start clean"
	@node-gyp clean
	@echo "clean finished<<<<<<<<"


