PROFILER_O_FILES := $(BUILD_DIR)/mods/debug_variable_display_list/debug_variable_display_list.o

PROFILER_O_FILES_DEPS := $(BUILD_DIR)/src/main.o

FILES_HOOKED_O += $(PROFILER_O_FILES_DEPS) $(PROFILER_O_FILES)

$(PROFILER_O_FILES_DEPS): $(PROFILER_O_FILES)
$(PROFILER_O_FILES): CC := $(CROSS)gcc

MODS_O_FILES += $(PROFILER_O_FILES)

ALL_DIRS += $(BUILD_DIR)/mods/debug_variable_display_list