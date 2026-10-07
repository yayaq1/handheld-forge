# Harbor Lights – minimal GBDK-2020 template (original placeholder)
# Requires GBDK_DIR (default /opt/gbdk)

GBDK_DIR ?= /opt/gbdk
LCC      = $(GBDK_DIR)/bin/lcc

SLUG     ?= harbor_lights
VERSION  ?= 0.1
ROM_NAME = $(SLUG)_v$(VERSION).gbc

BUILD    = build
SRC      = src/main.c
OBJ      = $(BUILD)/main.o

CFLAGS   = -Wa-l -Wl-m -Wl-j -Wm-yc -Wm-yn=HARBORLIGHTS
# -Wm-yc = CGB compatible; -Wm-yn = internal ROM name (15 chars max)

.PHONY: all clean dirs

all: dirs $(BUILD)/$(ROM_NAME)
	@cp -f $(BUILD)/$(ROM_NAME) $(BUILD)/$(SLUG).gbc
	@echo "Built $(BUILD)/$(ROM_NAME)"
	@md5sum $(BUILD)/$(ROM_NAME) 2>/dev/null || md5 $(BUILD)/$(ROM_NAME) 2>/dev/null || true

dirs:
	@mkdir -p $(BUILD)

$(BUILD)/$(ROM_NAME): $(OBJ)
	$(LCC) $(CFLAGS) -o $@ $(OBJ)

$(OBJ): $(SRC)
	$(LCC) $(CFLAGS) -c -o $@ $(SRC)

clean:
	rm -rf $(BUILD)/*.o $(BUILD)/*.lst $(BUILD)/*.map $(BUILD)/*.ihx \
	       $(BUILD)/*.noi $(BUILD)/*.sym $(BUILD)/*.cdb $(BUILD)/*.gbc
