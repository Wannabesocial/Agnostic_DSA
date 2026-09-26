# --- Μεταβλητές Μεταγλώττισης ---
CC       := gcc
STD      := -std=c11

# Αυστηρά Flags Προειδοποιήσεων & Ασφάλειας
WARN     := -Wall -Wextra -Wpedantic \
            -Wshadow -Wconversion -Wsign-conversion \
            -Wunused -Wvla

# Flags Εντοπισμού Σφαλμάτων & Μνήμης (Sanitizers)
DEBUG    := -g3 -fsanitize=address,undefined

CFLAGS   := $(STD) $(WARN) $(DEBUG) -Iinc

# --- Φάκελοι ---
SRC_DIR  := src
INC_DIR  := inc
TEST_DIR := tests
BIN_DIR  := bin

# --- ΛΙΣΤΑ DSA MODULES ---
MODULES  := vector

# --- ΚΟΙΝΑ ΑΡΧΕΙΑ (COMMON FILES) ---
COMMON_SOURCES := 

# --- Παραγωγή Ονομάτων & Object Files ---
TARGETS      := $(patsubst %, $(BIN_DIR)/%_test, $(MODULES))
COMMON_OBJS  := $(patsubst %, $(BIN_DIR)/%.o, $(COMMON_SOURCES))

# --- Κύριοι Στόχοι (Targets) ---
.PHONY: all clean $(MODULES)

# 1. Default target (χτίζει όλα τα modules στο bin/)
all: $(TARGETS)

# 2. Στόχος για μεμονωμένο module (π.χ. 'make vector' -> χτίζει μόνο το bin/vector_test)
$(MODULES): %: $(BIN_DIR)/%_test

# 3. Κανόνας για το Linking των εκτελέσιμων μέσα στο bin/
define MODULE_LINK_RULE
$(BIN_DIR)/$(1)_test: $(BIN_DIR)/$(1).o $(COMMON_OBJS) $$(patsubst $(TEST_DIR)/$(1)/%.c, $(BIN_DIR)/$(TEST_DIR)/$(1)/%.o, $$(wildcard $(TEST_DIR)/$(1)/*.c))
	$(CC) $(CFLAGS) $$^ -o $$@
endef

# Παραγωγή των κανόνων linking για όλα τα modules
$(foreach mod,$(MODULES),$(eval $(call MODULE_LINK_RULE,$(mod))))

# 4. Μεταγλώττιση των αρχείων C από το src/ -> bin/*.o
$(BIN_DIR)/%.o: $(SRC_DIR)/%.c | $(BIN_DIR)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

# 5. Μεταγλώττιση των tests -> bin/tests/<module>/*.o
$(BIN_DIR)/$(TEST_DIR)/%.o: $(TEST_DIR)/%.c | $(BIN_DIR)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

# 6. Δημιουργία του φακέλου bin
$(BIN_DIR):
	mkdir -p $(BIN_DIR)

# 7. Καθαρισμός
clean:
	rm -rf $(BIN_DIR)