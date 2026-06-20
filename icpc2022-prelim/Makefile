CONTEST_ID := $(notdir $(CURDIR))
PROBLEMS := A B C D E F G H

TOLOWER = $(shell echo $(1) | tr A-Z a-z)
TOUPPER = $(shell echo $(1) | tr a-z A-Z)

ZIP_FILES := $(foreach p,$(PROBLEMS),$(CONTEST_ID)-$(call TOLOWER,$(p)).zip)

.PHONY: all

all: $(ZIP_FILES)

# 補完のための空ターゲット
$(ZIP_FILES):

.SECONDEXPANSION:
# icpcxxxx-prelim-a.zip のルール
# 依存: A ディレクトリ内のファイル
$(CONTEST_ID)-%.zip: $$(call TOUPPER,$$*) $$(shell find $$(call TOUPPER,$$*) -type f 2>/dev/null)
	rm -f $@
	cd $(call TOUPPER,$*) && zip -r ../$@ ./*

clean:
	rm -f $(ZIP_FILES)
