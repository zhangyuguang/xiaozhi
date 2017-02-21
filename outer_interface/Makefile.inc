OUTER_IF_DIR  = $(XIAO_ZHI_APP_TOP)/outer_interface
BAIDU_API_DIR = $(XIAO_ZHI_APP_TOP)/outer_interface/baidu_api
JPUSH_API_DIR = $(XIAO_ZHI_APP_TOP)/outer_interface/jpush_api

OUTER_IF_OBJS  = $(OUTER_IF_DIR)/outer_if.o
BAIDU_API_OBJS = $(BAIDU_API_DIR)/baidu_api.o
JPUSH_API_OBJS = $(JPUSH_API_DIR)/jpush_api.o

OUTER_INTERFACE_OBJS = $(OUTER_IF_OBJS) $(BAIDU_API_OBJS) $(JPUSH_API_OBJS)

OUTER_INTERFACE_PY_OBJS = $(BAIDU_API_DIR)/baidu_api.pyc $(BAIDU_API_DIR)/conf.pyc $(JPUSH_API_DIR)/jpush_api.pyc $(JPUSH_API_DIR)/conf.pyc

OUTER_INTERFACE_INC = \
    -I$(OUTER_IF_DIR)    \
    -I$(BAIDU_API_DIR)    \
    -I$(JPUSH_API_DIR)
