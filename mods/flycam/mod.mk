$(BUILD_DIR)/src/render_player.o: $(BUILD_DIR)/mods/flycam/flycam.o
$(BUILD_DIR)/src/racing/math_util.o: $(BUILD_DIR)/mods/flycam/flycam.o
$(BUILD_DIR)/src/racing/render_courses.o: $(BUILD_DIR)/mods/flycam/flycam.o
$(BUILD_DIR)/src/camera.o: $(BUILD_DIR)/mods/flycam/flycam.o

O_FILES += $(BUILD_DIR)/mods/flycam/flycam.o

ALL_DIRS += $(BUILD_DIR)/mods/flycam