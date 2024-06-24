DEBUG_VARIABLE_O_FILES := $(BUILD_DIR)/mods/debug_variable_display_list/debug_variable_display_list.o
DEBUG_VARIABLE_C_FILES := mods/debug_variable_display_list/debug_variable_display_list.c

DEBUG_VARIABLE_O_FILES_DEPS := $(BUILD_DIR)/src/main.o

FILES_HOOKED_O += $(DEBUG_VARIABLE_O_FILES_DEPS) $(DEBUG_VARIABLE_O_FILES)

$(DEBUG_VARIABLE_O_FILES_DEPS): $(DEBUG_VARIABLE_O_FILES)

MODS_O_FILES += $(DEBUG_VARIABLE_O_FILES)

ALL_DIRS += $(BUILD_DIR)/mods/debug_variable_display_list

disable_debug_variable:
	$(call clear_roms_files)
	$(V)rm -f $(DEBUG_VARIABLE_O_FILES) $(DEBUG_VARIABLE_O_FILES_DEPS)
	$(V)./tools/hooks remove $(DEBUG_VARIABLE_C_FILES)
	$(V)echo mods/debug_variable_display_list/% >> mods.disabled
	$(V)echo "debug variable display list disabled"