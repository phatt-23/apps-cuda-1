PROGRAM = program

SRC_DIR = src
OBJ_DIR = obj

LDLIBS = $(shell pkgconf --libs cuda) $(shell pkgconf --cflags cuda)
OPENCVLIB=$(shell pkgconf --list-package-names | grep opencv )

ifeq ($(OPENCVLIB),)
all:
	@echo OpenCV lib not found!
	@exit 
else
CPPFLAGS += -g
CPPFLAGS += $(shell pkgconf --cflags $(OPENCVLIB))
LDFLAGS += $(shell pkgconf --libs-only-L $(OPENCVLIB))
LDLIBS += $(shell pkgconf --libs-only-l $(OPENCVLIB))

all: $(PROGRAM)

endif

DIAG_SUPRESS = -diag-suppress 611

# Locate CUDA source files in the specified directory
CUDA_SRCS = $(wildcard $(SRC_DIR)/*.cu)
# Generate object file paths in the object directory
CUDA_OBJS = $(patsubst $(SRC_DIR)/%.cu,$(OBJ_DIR)/%.o,$(CUDA_SRCS))

# Rule to compile CUDA source files into object files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cu $(wildcard $(SRC_DIR)/*.h)
	nvcc -c $(CPPFLAGS) $< -o $@ $(DIAG_SUPRESS)

# Linking rule to generate the executable
$(PROGRAM): $(wildcard $(SRC_DIR)/*.cpp) $(CUDA_OBJS) $(wildcard $(SRC_DIR)/*.h)
	g++ $(CPPFLAGS) $(LDFLAGS) $(filter %.cpp %.o, $^) $(LDLIBS) -o $@

run:
	./$(PROGRAM)

# Clean rule to remove object files and the program
clean:
	rm -f $(OBJ_DIR)/*.o $(PROGRAM)

dirs:
	mkdir -p obj
	mkdir -p src
	mkdir -p src/inc