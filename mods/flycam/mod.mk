$(BUILD_DIR)/src/render_player.o: $(BUILD_DIR)/mods/flycam/flycam.o
$(BUILD_DIR)/src/racing/math_util.o: $(BUILD_DIR)/mods/flycam/flycam.o
$(BUILD_DIR)/src/racing/render_courses.o: $(BUILD_DIR)/mods/flycam/flycam.o
$(BUILD_DIR)/src/camera.o: $(BUILD_DIR)/mods/flycam/flycam.o

O_FILES += $(BUILD_DIR)/mods/flycam/flycam.o

MODS_SEGMENT += $(BUILD_DIR)/mods/flycam/flycam.o(.text);
MODS_SEGMENT += $(BUILD_DIR)/mods/flycam/flycam.o(.data);
MODS_SEGMENT += $(BUILD_DIR)/mods/flycam/flycam.o(.rodata);
MODS_SEGMENT_BSS += $(BUILD_DIR)/mods/flycam/flycam.o(.bss);


ALL_DIRS += $(BUILD_DIR)/mods/flycam