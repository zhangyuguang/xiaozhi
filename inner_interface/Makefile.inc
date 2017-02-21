INNER_IF_DIR   = $(XIAO_ZHI_APP_TOP)/inner_interface
APP_API_DIR   = $(XIAO_ZHI_APP_TOP)/inner_interface/app_api

INNER_IF_OBJS  = $(INNER_IF_DIR)/inner_if.o
LOCATION_API_OBJS  = $(APP_API_DIR)/location_api.o

INNER_INTERFACE_OBJS  = $(INNER_IF_OBJS) $(LOCATION_API_OBJS)

INNER_INTERFACE_INC = \
    -I$(INNER_IF_DIR)    \
    -I$(APP_API_DIR)
