ROYAL_RACEWAY_DIR := assets/courses/royal_raceway

ROYAL_RACEWAY_PIRANHA_PLANT_PALETTE := $(ROYAL_RACEWAY_DIR)/gTLUTRoyalRacewayPiranhaPlant.png

ROYAL_RACEWAY_EXPORT_SENTINEL := $(ROYAL_RACEWAY_DIR)/.export

$(BUILD_DIR)/courses/royal_raceway/course_data.o: $(ROYAL_RACEWAY_PIRANHA_PLANT_PALETTE:%.png=%.inc.c)

$(ROYAL_RACEWAY_PIRANHA_PLANT_PALETTE:%.png=%.inc.c): %.inc.c : %.png
	@$(PRINT) "$(GREEN)Converting:  $(BLUE) $< -> $@$(NO_COL)\n"
	$(V)$(N64GRAPHICS) -i $@ -g $< -s u8 -f rgba16

$(ROYAL_RACEWAY_PIRANHA_PLANT_PALETTE): $(ROYAL_RACEWAY_EXPORT_SENTINEL) ;

$(ROYAL_RACEWAY_EXPORT_SENTINEL): $(ASSET_DIR)/courses/royal_raceway.json
	$(V)$(ASSET_EXTRACT) $(BASEROM) $<
	$(V)$(TOUCH) $@

.PHONY: distclean_royal_raceway
distclean_royal_raceway:
	rm -rf $(ROYAL_RACEWAY_DIR)

distclean_assets: distclean_royal_raceway
