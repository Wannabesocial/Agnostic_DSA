# --- Μεταβλητές Μεταγλώττισης ---
CC       := gcc
CFLAGS   := -Wall -Iinc

# --- Φάκελοι ---
SRC_DIR  := src
INC_DIR  := inc
TEST_DIR := tests
OBJ_DIR  := obj

# --- ΛΙΣΤΑ DSA MODULES ---
# Κάθε module έχει το δικό του .c αρχείο στο src/ και το δικό του test στο tests/
#MODULES  := vector list
MODULES  := vector

# --- ΚΟΙΝΑ ΑΡΧΕΙΑ (COMMON FILES) ---
# Εδώ βάζεις τα ονόματα των .c αρχείων (χωρίς την επέκταση .c) που θέλεις 
# να γίνονται link σε ΟΛΑ τα εκτελέσιμα. Αυτή τη στιγμή είναι άδεια!
# Παράδειγμα για το μέλλον: COMMON_SOURCES := common utils
COMMON_SOURCES := 

# --- Παραγωγή Ονομάτων & Object Files ---
TARGETS     := $(patsubst %, %_test, $(MODULES))
COMMON_OBJS := $(patsubst %, $(OBJ_DIR)/%.o, $(COMMON_SOURCES))

# --- Κύριοι Στόχοι (Targets) ---
.PHONY: all clean

# 1. Default target: Φτιάχνει όλα τα εκτελέσιμα
all: $(TARGETS)

# 2. Στατικός Κανόνας για το Linking των εκτελέσιμων
# Κάθε test_X γίνεται link με το X.o, το test_X.o ΚΑΙ όλα τα COMMON_OBJS
$(TARGETS): %_test: $(OBJ_DIR)/%.o $(OBJ_DIR)/%_test.o $(COMMON_OBJS)
	$(CC) $(CFLAGS) $^ -o $@

# 3. Γενικός κανόνας για τη μεταγλώττιση οποιουδήποτε .c από το src/ σε .o
# Καλύπτει τόσο τα modules (vector.c) όσο και τα common αρχεία (common.c)
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# 4. Μεταγλώττιση των αρχείων ελέγχου από το tests/ σε .o
$(OBJ_DIR)/%.o: $(TEST_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# 5. Δημιουργία του φακέλου obj αν δεν υπάρχει
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

# 6. Καθαρισμός
clean:
	rm -rf $(OBJ_DIR) $(TARGETS)
