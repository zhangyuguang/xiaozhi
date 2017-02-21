CC = gcc

CFLAGS  = -g -w
LIBS = -lpthread -lm -lpython2.7 -lmysqlclient

ifeq ($(XIAO_ZHI_APP_TOP),)
export XIAO_ZHI_APP_TOP=$(shell pwd)
endif

TOP_DIR = $(XIAO_ZHI_APP_TOP)

include $(XIAO_ZHI_APP_TOP)/utils/Makefile.inc
include $(XIAO_ZHI_APP_TOP)/outer_interface/Makefile.inc
include $(XIAO_ZHI_APP_TOP)/inner_interface/Makefile.inc
#include $(XIAO_ZHI_APP_TOP)/vendor_management/Makefile.inc
#include $(XIAO_ZHI_APP_TOP)/envent_push/Makefile.inc
include $(XIAO_ZHI_APP_TOP)/collab_filter/Makefile.inc
include $(XIAO_ZHI_APP_TOP)/pattern_recognition/Makefile.inc

OBJS  = $(UTILS_OBJS) $(OUTER_INTERFACE_OBJS) $(INNER_INTERFACE_OBJS) $(VENDOR_MANAGEMENT_OBJS)
OBJS += $(EVENT_PUSH_OBJS) $(COLLAB_FILTER_OBJS) $(PATTERN_RECOGNITION_OBJS)

PY_OBJS = $(OUTER_INTERFACE_PY_OBJS)

DIRS  = $(TOP_DIR) $(UTILS_INC) $(OUTER_INTERFACE_INC) $(INNER_INTERFACE_INC) $(VENDOR_MANAGEMENT_INC)
DIRS += $(EVENT_PUSH_INC) $(COLLAB_FILTER_INC) $(PATTERN_RECOGNITION_INC)

all: xiao_zhi_app_service

$(OBJS): %.o : %.c
	@echo Compiling $<
	@$(CC) -c $(CFLAGS) -I$(DIRS) -o $@ $<

xiao_zhi_app_service: $(OBJS) xiao_zhi_main.c
	@echo "Compiling xiao_zhi_main.c ..."
	@$(CC)  xiao_zhi_main.c -I$(DIRS) -o xiao_zhi_app_service $(CFLAGS) $(OBJS) $(COLLAB_FILTER_LDFLAG) $(LIBS)

clean:
	rm -rf xiao_zhi_app_service
	rm -rf $(OBJS)
	rm -rf $(PY_OBJS)
	rm -rf *.o

print:
	@echo $(XIAO_ZHI_APP_TOP)
	@echo $(CFLAGS)
	@echo $(DIRS)
	@echo $(OBJS)
	@echo $(PY_OBJS)
	@echo $(LIBS)
