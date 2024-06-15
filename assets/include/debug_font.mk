DEBUG_FONT_DIR := assets/debug_font

DEBUG_FONT_PALETTE := $(DEBUG_FONT_DIR)/common_tlut_debug_font.png

DEBUG_FONT_PNG := $(DEBUG_FONT_DIR)/common_texture_debug_font.png

DEBUG_FONT_EXPORT_SENTINEL := $(DEBUG_FONT_DIR)/.export

$(BUILD_DIR)/src/data/common_textures.o: $(DEBUG_FONT_PNG:%.png=%.inc.c) $(DEBUG_FONT_PALETTE:%.png=%.inc.c)

$(DEBUG_FONT_PNG:%.png=%.inc.c): %.inc.c : %.png
	@$(PRINT) "$(GREEN)Converting:  $(BLUE) $< -> $@$(NO_COL)\n"
	$(V)$(N64GRAPHICS) -Z $@ -g $< -s u8 -f ci4 -c rgba16 -p $(DEBUG_FONT_PALETTE)

$(DEBUG_FONT_PALETTE:%.png=%.inc.c): %.inc.c : %.png
	@$(PRINT) "$(GREEN)Converting:  $(BLUE) $< -> $@$(NO_COL)\n"
	$(V)$(N64GRAPHICS) -i $@ -g $< -s u8 -f rgba16

$(DEBUG_FONT_PNG) $(DEBUG_FONT_PALETTE): $(DEBUG_FONT_EXPORT_SENTINEL) ;

$(DEBUG_FONT_EXPORT_SENTINEL): $(ASSET_DIR)/debug_font.json
	$(V)$(ASSET_EXTRACT) $(BASEROM) $<
	$(V)$(TOUCH) $@

.PHONY: distclean_debug_font
distclean_debug_font:
	rm -rf $(DEBUG_FONT_DIR)

distclean_assets: distclean_debug_font
