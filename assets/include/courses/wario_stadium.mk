WARIO_STADIUM_DIR := assets/courses/wario_stadium

WARIO_STADIUM_SIGN := \
$(WARIO_STADIUM_DIR)/gTextureWarioStadiumSignTopLeft.png    \
$(WARIO_STADIUM_DIR)/gTextureWarioStadiumSignBottomLeft.png \
$(WARIO_STADIUM_DIR)/gTextureWarioStadiumSignTopRight.png   \
$(WARIO_STADIUM_DIR)/gTextureWarioStadiumSignBottomRight.png

WARIO_STADIUM_EXPORT_SENTINEL := $(WARIO_STADIUM_DIR)/.export

ASSET_DIRECTORIES += $(WARIO_STADIUM_DIR)

$(BUILD_DIR)/courses/star_cup/wario_stadium/course_data.inc.o: $(WARIO_STADIUM_SIGN:%.png=%.inc.c)

$(WARIO_STADIUM_SIGN:%.png=%.inc.c): %.inc.c : %.png
	$(N64GRAPHICS) -i $@ -g $< -s u8 -f rgba16

$(WARIO_STADIUM_SIGN): $(WARIO_STADIUM_EXPORT_SENTINEL) ;

$(WARIO_STADIUM_EXPORT_SENTINEL): $(ASSET_DIR)/courses/wario_stadium.json
	$(ASSET_EXTRACT) $(BASEROM) $<
	touch $@