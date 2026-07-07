# --- Μεταβλητές Μεταγλώττισης ---
CC       := gcc
CFLAGS   := -Wall -Iinc

# --- Φάκελοι ---
SRC_DIR  := src
INC_DIR  := inc
TEST_DIR := tests
OBJ_DIR  := obj

# --- ΛΙΣΤΑ DSA MODULES ---
MODULES  := vector

# --- ΚΟΙΝΑ ΑΡΧΕΙΑ (COMMON FILES) ---
COMMON_SOURCES := 

# --- Παραγωγή Ονομάτων & Object Files ---
TARGETS     := $(patsubst %, %_test, $(MODULES))
COMMON_OBJS := $(patsubst %, $(OBJ_DIR)/%.o, $(COMMON_SOURCES))

# --- Κύριοι Στόχοι (Targets) ---
.PHONY: all clean

# 1. Default target
all: $(TARGETS)

# 2. Κανόνας για το Linking των εκτελέσιμων (π.χ. vector_test)
# Χρησιμοποιούμε τη $(eval) για να ορίσουμε τις ακριβείς εξαρτήσεις για κάθε module ξεχωριστά
define MODULE_LINK_RULE
$(1)_test: $(OBJ_DIR)/$(1).o $(COMMON_OBJS) $$(patsubst $(TEST_DIR)/$(1)/%.c, $(OBJ_DIR)/$(TEST_DIR)/$(1)/%.o, $$(wildcard $(TEST_DIR)/$(1)/*.c))
	$(CC) $(CFLAGS) $$^ -o $$@
endef

# Παραγωγή των κανόνων linking για όλα τα modules
$(foreach mod,$(MODULES),$(eval $(call MODULE_LINK_RULE,$(mod))))

# 3. Μεταγλώττιση των αρχείων από το src/ (π.χ. src/vector.c -> obj/vector.o)
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# 4. Μεταγλώττιση των tests (π.χ. tests/vector/main_test.c -> obj/tests/vector/main_test.o)
$(OBJ_DIR)/$(TEST_DIR)/%.o: $(TEST_DIR)/%.c | $(OBJ_DIR)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

# 5. Δημιουργία του αρχικού φακέλου obj
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

# 6. Καθαρισμός
clean:
	rm -rf $(OBJ_DIR) $(TARGETS)