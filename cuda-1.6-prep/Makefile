PROGRAM = program

SRC_DIR = src
OBJ_DIR = obj

LDLIBS = $(shell pkgconf --libs cuda) 
IFLAGS_CUDA = $(shell pkgconf --cflags cuda)
OPENCVLIB = $(shell pkgconf --list-package-names | grep opencv )

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

CPP_SRCS = $(wildcard $(SRC_DIR)/*.cpp)
CPP_OBJS = $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(CPP_SRCS))

########################################################################

# Rule to compile CUDA source files into object files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cu $(wildcard $(SRC_DIR)/inc/*.h)
	nvcc -c $(CPPFLAGS) $< -o $@ $(DIAG_SUPRESS)

# Rule for CPP files into .o files 
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp 
	g++ -c $(CPPFLAGS) $< -o $@ $(IFLAGS_CUDA)

# Linking rule to generate the executable
$(PROGRAM): $(CPP_OBJS) $(CUDA_OBJS) $(wildcard $(SRC_DIR)/inc/*.h)
	g++ $(CPPFLAGS) $(LDFLAGS) $(filter %.o, $^) $(LDLIBS) $(IFLAGS_CUDA) -o $@

# Clean rule to remove object files and the program
clean:
	rm -f $(OBJ_DIR)/*.o $(PROGRAM)
	
run:
	./$(PROGRAM) 

dirs:
	mkdir -p obj
	mkdir -p src
	mkdir -p src/inc

