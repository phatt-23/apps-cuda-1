PROGRAM = program
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

all: $(MAIN_NAME)

endif

CUDA_OBJS = $(addsuffix .o, $(basename $(wildcard *.cu)))

%.o: %.cu $(wildcard *.h)
	nvcc -c $(CPPFLAGS) $<

$(PROGRAM): $(wildcard *.cpp) $(CUDA_OBJS) $(wildcard *.h)
	g++ $(CPPFLAGS) $(LDFLAGS) $(filter %.cpp %.o, $^) $(LDLIBS) -o $@

run:
	./$(PROGRAM)

clean:
	rm -f *.o $(PROGRAM)