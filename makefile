# https://www.youtube.com/@formation-video/playlists
# Directory control
PROJDIR := $(realpath $(CURDIR)/..)
OBJDIR   = build\obj
BUILDDIR = build
SRCDIR   = src
INCDIR   = include


SRC       = $(wildcard $(SRCDIR)/*.cc)				# Utilisation du répertoire src pour les fichiers .c
HEADER_H  = $(SRC:$(SRCDIR)/%.cc=$(INCDIR)/%.h)
HEADER_HH = $(SRC:$(SRCDIR)/%.cc=$(INCDIR)/%.hh)
HEADER    = $(HEADER_HH)	# Utilisation du répertoire include pour les fichiers .h
OBJ       = $(SRC:$(SRCDIR)/%.cc=$(OBJDIR)/%.o) 	# Utilisation du répertoire Build/obj pour les fichiers .o

# Linkers
CXX    = g++
DEBUG_FLAGS = -Wall -g -I$(INCDIR)
OPT_FLAGS   = -Wall -O2 -I$(INCDIR)

TARGET = prog.exe

# Create the build directory if it doesn't exist
$(shell mkdir $(BUILDDIR))

# Create the object directory if it doesn't exist
$(shell mkdir $(OBJDIR))

# Default rule
all: FLAGS = $(OPT_FLAGS)
all: $(BUILDDIR)/$(TARGET)

# Debug build
debug: FLAGS = $(DEBUG_FLAGS)
debug: clean all

# Optimized build
release: FLAGS = $(OPT_FLAGS)
release: clean all

$(OBJDIR)/%.o: $(SRCDIR)/%.cc $(HEADER)
	$(CXX) $(FLAGS) -o $@ -c $< 

$(BUILDDIR)/$(TARGET): $(OBJ)
	$(CXX) $(FLAGS) -o $@ $^ 

# Clean rule
clean:
	del /F /Q $(OBJDIR)\*.o $(TARGET)
	rmdir /S /Q $(OBJDIR)  # Supprime le répertoire Build