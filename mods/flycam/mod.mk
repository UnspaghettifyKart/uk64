FLYCAM_O_FILES := $(BUILD_DIR)/mods/flycam/flycam.o

FLYCAM_O_FILES_DEPS := $(BUILD_DIR)/src/render_player.o $(BUILD_DIR)/src/racing/math_util.o $(BUILD_DIR)/src/racing/render_courses.o $(BUILD_DIR)/src/camera.o

FILES_HOOKED_O += $(FLYCAM_O_FILES_DEPS) $(FLYCAM_O_FILES)

$(FLYCAM_O_FILES_DEPS): $(FLYCAM_O_FILES)
$(FLYCAM_O_FILES): CC := $(CROSS)gcc

MODS_O_FILES += $(FLYCAM_O_FILES)

ALL_DIRS += $(BUILD_DIR)/mods/flycam