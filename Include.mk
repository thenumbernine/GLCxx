SHADER_PATH:=$(dir $(lastword $(MAKEFILE_LIST)))

INCLUDE+=$(SHADER_PATH)include
DYNAMIC_LIBS+=$(SHADER_PATH)dist/$(PLATFORM)/$(BUILD)/libShader.dylib

