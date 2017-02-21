LOG_DIR      = $(XIAO_ZHI_APP_TOP)/utils/log
DB_DIR   = $(XIAO_ZHI_APP_TOP)/utils/db
SOCKET_DIR   = $(XIAO_ZHI_APP_TOP)/utils/socket

LOG_OBJS     = $(LOG_DIR)/log.o
DB_OBJS     = $(DB_DIR)/db_mysql.o
SOCKET_OBJS  = $(SOCKET_DIR)/socket.o

UTILS_OBJS   = $(LOG_OBJS) $(DB_OBJS) $(SOCKET_OBJS)

UTILS_INC = \
    -I$(LOG_DIR)    \
    -I$(DB_DIR)    \
    -I$(SOCKET_DIR)

