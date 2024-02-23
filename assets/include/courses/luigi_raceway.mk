LUIGI_RACEWAY_DIR := assets/courses/luigi_raceway

LUIGI_RACEWAY_PNG := \
$(LUIGI_RACEWAY_DIR)/gTextureLuigiRacewaySignLeft.png \
$(LUIGI_RACEWAY_DIR)/gTextureLuigiRacewaySignRight.png \
$(LUIGI_RACEWAY_DIR)/gTextureLuigiRacewayBalloonBasket.png \
$(LUIGI_RACEWAY_DIR)/gTextureLuigiRacewayBalloonRope.png

LUIGI_RACEWAY_EXPORT_SENTINEL := $(LUIGI_RACEWAY_DIR)/.export

$(BUILD_DIR)/courses/luigi_raceway/course_data.inc.o: $(LUIGI_RACEWAY_PNG:%.png=%.inc.c)

$(LUIGI_RACEWAY_PNG:%.png=%.inc.c): %.inc.c : %.png
	$(N64GRAPHICS) -i $@ -g $< -s u8 -f rgba16

$(LUIGI_RACEWAY_PNG): $(LUIGI_RACEWAY_EXPORT_SENTINEL) ;

$(LUIGI_RACEWAY_EXPORT_SENTINEL): $(ASSET_DIR)/courses/luigi_raceway.json
	$(ASSET_EXTRACT) $(BASEROM) $<
	$(TOUCH) $@

.PHONY: distclean_luigi_raceway
distclean_luigi_raceway:
	rm -rf $(LUIGI_RACEWAY_DIR)

distclean_assets: distclean_luigi_raceway
