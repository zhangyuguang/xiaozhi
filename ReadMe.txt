##############################
## XiaoZhi APP Service Part ##
##############################


1. Logging Level
	LOG_EMERG   0 /*!< \brief system is unusable */
	LOG_ALERT   1 /*!< \brief action must be taken immediately */
	LOG_CRIT    2 /*!< \brief critical conditions */
	LOG_ERR     3 /*!< \brief error conditions */
	LOG_WARNING 4 /*!< \brief warning conditions */
	LOG_NOTICE  5 /*!< \brief normal but significant condition */
	LOG_INFO    6 /*!< \brief informational */
	LOG_DEBUG   7 /*!< \brief debug-level messages */
	LOG_FILE    8 /*!< \brief message sequence chart -level  */
	LOG_TRACE   9 /*!< \brief trace-level messages */
Remark: for python code realted log info, is printed to /tmp/zhi-service-py.log

2. Compile and Run
	$export XIAO_ZHI_APP_TOP=/$(PATH of xiao-zhi-app-service)    'eg: /home/openair/xiao-zhi-app-service
	$cd $(xiao-zhi-app-service)
	$make xiao_zhi_app_service
	$./xiao_zhi_app_service -l 3 -f zhi-service.log     'Set log level to 3 and print log to file zhi-service.log
