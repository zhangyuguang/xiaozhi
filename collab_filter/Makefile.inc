JAVA_HOME = /usr/lib/jvm/jdk1.8.0_102
JRE_HOME = $(JAVA_HOME)/jre

COLLAB_FILTER_DIR  = $(XIAO_ZHI_APP_TOP)/collab_filter

COLLAB_FILTER_OBJS = $(COLLAB_FILTER_DIR)/collab_filter.o

COLLAB_FILTER_INC = \
    -I$(COLLAB_FILTER_DIR) \
    -I$(JAVA_HOME)/include \
    -I$(JAVA_HOME)/include/linux

COLLAB_FILTER_LDFLAG = -L$(JRE_HOME)/lib/i386/client

LIBS += -ljvm

