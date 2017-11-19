
MYFLAGS = -std=gnu++0x 
MYFLAGS += -Wall 
MYFLAGS += -pipe 
MYFLAGS += -g  -ggdb
MYFLAGS += -O0  -D_GNU_SOURCE  -DSUS_LINUX -D_REENTRANT
MYFLAGS += -fPIC


INC += -I../api/ 
LIB += -lz -lrt -pthread

OBJS = $(patsubst %.cpp,%.o,$(shell find ./  -name "*.cpp"))
OBJS += $(patsubst %.cpp,%.o,$(shell find ../api/  -name "*.cpp"))

TARGET = demo

all: $(TARGET)

$(TARGET): $(OBJS)
	@echo -e "\033[1;33m\nLinking $< ==> $@\033[0m"
	$(CXX) $(MYFLAGS) -o $@  $^   $(LIB)

	
%.o: %.cpp
	@echo -e "\033[1;33m\nCompiling $< ==> $@\033[0m"
	$(CXX) $(MYFLAGS) $(INC) -o $@ -c $< 
	

.PHONY : clean

clean:
	rm -f $(TARGET) $(OBJS) 