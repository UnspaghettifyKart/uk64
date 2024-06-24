PROFILER_O_FILES := $(BUILD_DIR)/mods/profiler/display_profiler.o
PROFILER_C_FILES := mods/profiler/display_profiler.c

PROFILER_O_FILES_DEPS := $(BUILD_DIR)/src/main.o

FILES_HOOKED_O += $(PROFILER_O_FILES_DEPS) $(PROFILER_O_FILES)

$(PROFILER_O_FILES_DEPS): $(PROFILER_O_FILES)

MODS_O_FILES += $(PROFILER_O_FILES)

ALL_DIRS += $(BUILD_DIR)/mods/profiler

disable_profiler:
	$(call clear_roms_files)
	$(V)rm -f $(PROFILER_O_FILES) $(PROFILER_O_FILES_DEPS)
	$(V)./tools/hooks remove $(PROFILER_O_FILES:.o=.c)
	$(V)echo mods/profiler/% >> mods.disabled
	$(V)echo "profiler disabled"