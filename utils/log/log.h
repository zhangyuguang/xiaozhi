/**********************************************************************
 *
 *  Copyright(c) 2016 Alcatel-Lucent.
 *  All rights reserved.
 *
 *  ALL RIGHTS ARE RESERVED BY ALCATEL-LUCENT.  ACCESS TO THIS
 *  SOURCE CODE IS STRICTLY RESTRICTED UNDER CONTRACT. THIS CODE IS TO
 *  BE KEPT STRICTLY CONFIDENTIAL.
 *
 *  UNAUTHORIZED MODIFICATIONS OF THIS FILE WILL VOID YOUR SUPPORT
 *  CONTRACT WITH ALCATEL-LUCENT.  IF SUCH MODIFICATIONS ARE FOR
 *  THE PURPOSE OF CIRCUMVENTING LICENSING LIMITATIONS, LEGAL ACTION
 *  MAY RESULT.
 *
 ***********************************************************************/

/*! \file log.h
* \brief xiao-zhi-app service log generator
* \author Sean Wang
* \date 2016
* \version 1.0
* @ingroup utils

*/

#ifndef __LOG_H__
#define __LOG_H__


/*--- INCLUDES ---------------------------------------------------------------*/
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <syslog.h>
#include <assert.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdarg.h>
#include <time.h>
#include <errno.h>
/*----------------------------------------------------------------------------*/

#ifdef __cplusplus
extern "C" {
#endif

extern FILE *log_file_g;
extern int log_level_g;

/** @defgroup _log_level Message levels defined by LOG
 *  @ingroup _macro
 *  @brief LOG defines 9 levels of messages for users. Importance of these levels decrease gradually from 0 to 8
 * @{*/
#ifndef LOG_EMERG
# define  LOG_EMERG   0 /*!< \brief system is unusable */
#endif
#ifndef LOG_ALERT
# define  LOG_ALERT   1 /*!< \brief action must be taken immediately */
#endif
#ifndef LOG_CRIT
# define  LOG_CRIT    2 /*!< \brief critical conditions */
#endif
#ifndef LOG_ERR
# define  LOG_ERR     3 /*!< \brief error conditions */
#endif
#ifndef LOG_WARNING
# define  LOG_WARNING 4 /*!< \brief warning conditions */
#endif
#ifndef LOG_NOTICE
# define  LOG_NOTICE  5 /*!< \brief normal but significant condition */
#endif
#ifndef LOG_INFO
# define  LOG_INFO    6 /*!< \brief informational */
#endif
#ifndef LOG_DEBUG
# define  LOG_DEBUG   7 /*!< \brief debug-level messages */
#endif
#ifndef LOG_FILE
# define  LOG_FILE    8 /*!< \brief message sequence chart -level  */
#endif
#ifndef LOG_TRACE
# define  LOG_TRACE   9 /*!< \brief trace-level messages */
#endif

#define NUM_LOG_LEVEL 10 /*!< \brief the number of message levels users have with LOG */
/* @}*/

#define __FILENAME__ (strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__)

#define PRT_LOG(level, ...)		\
	if (level <= log_level_g)				\
	{						\
		if (log_file_g != NULL) 			\
		{					\
			time_t t = time(NULL);		\
			char *p = ctime(&t);		\
			p[strlen(p)-1] = '	';	\
			fprintf(log_file_g, "%s", p);	\
			fprintf(log_file_g, "%-16s\t", __FILENAME__);	\
			fprintf(log_file_g, "%5d: ", __LINE__);	\
			fprintf(log_file_g, __VA_ARGS__);	\
			fflush(log_file_g);		\
		}					\
	}

#define PRT_LOG_T(level,type, ...)		\
	if (6 <= log_level_g)				\
	{						\
		if (log_file_g != NULL) 			\
		{					\
			time_t t = time(NULL);		\
			char *p = ctime(&t);		\
			p[strlen(p)-1] = '	';	\
			fprintf(log_file_g, "%s", p);	\
			fprintf(log_file_g, "%-16s\t", __FILENAME__);	\
			fprintf(log_file_g, "%5d: ", __LINE__);	\
			fprintf(log_file_g, "[%s]", get_comp_name(type));	\
			fprintf(log_file_g, __VA_ARGS__);	\
			fflush(log_file_g);		\
		}					\
	}

#define LOG_A(type, ...) \
		if (1 <= log_level_g)				\
		{						\
			if (log_file_g != NULL) 			\
			{					\
				time_t t = time(NULL);		\
				char *p = ctime(&t);		\
				p[strlen(p)-1] = '	';	\
				fprintf(log_file_g, "%s", p);	\
				fprintf(log_file_g, "%-16s\t", __FILENAME__);	\
				fprintf(log_file_g, "%5d: ", __LINE__);	\
				fprintf(log_file_g, "[%s]", get_comp_name(type));	\
				fprintf(log_file_g, __VA_ARGS__);	\
				fflush(log_file_g);		\
			}					\
		}

#define LOG_C(type, ...) \
		if (2 <= log_level_g)				\
		{						\
			if (log_file_g != NULL) 			\
			{					\
				time_t t = time(NULL);		\
				char *p = ctime(&t);		\
				p[strlen(p)-1] = '	';	\
				fprintf(log_file_g, "%s", p);	\
				fprintf(log_file_g, "%-16s\t", __FILENAME__);	\
				fprintf(log_file_g, "%5d: ", __LINE__);	\
				fprintf(log_file_g, "[%s]", get_comp_name(type));	\
				fprintf(log_file_g, __VA_ARGS__);	\
				fflush(log_file_g);		\
			}					\
		}

#define LOG_E(type, ...) \
		if (3 <= log_level_g)				\
		{						\
			if (log_file_g != NULL) 			\
			{					\
				time_t t = time(NULL);		\
				char *p = ctime(&t);		\
				p[strlen(p)-1] = '	';	\
				fprintf(log_file_g, "%s", p);	\
				fprintf(log_file_g, "%-16s\t", __FILENAME__);	\
				fprintf(log_file_g, "%5d: ", __LINE__);	\
				fprintf(log_file_g, "[%s]", get_comp_name(type));	\
				fprintf(log_file_g, __VA_ARGS__);	\
				fflush(log_file_g);		\
			}					\
		}

#define LOG_W(type, ...) \
		if (4 <= log_level_g)				\
		{						\
			if (log_file_g != NULL) 			\
			{					\
				time_t t = time(NULL);		\
				char *p = ctime(&t);		\
				p[strlen(p)-1] = '	';	\
				fprintf(log_file_g, "%s", p);	\
				fprintf(log_file_g, "%-16s\t", __FILENAME__);	\
				fprintf(log_file_g, "%5d: ", __LINE__);	\
				fprintf(log_file_g, "[%s]", get_comp_name(type));	\
				fprintf(log_file_g, __VA_ARGS__);	\
				fflush(log_file_g);		\
			}					\
		}

#define LOG_N(type, ...) \
		if (5 <= log_level_g)				\
		{						\
			if (log_file_g != NULL) 			\
			{					\
				time_t t = time(NULL);		\
				char *p = ctime(&t);		\
				p[strlen(p)-1] = '	';	\
				fprintf(log_file_g, "%s", p);	\
				fprintf(log_file_g, "%-16s\t", __FILENAME__);	\
				fprintf(log_file_g, "%5d: ", __LINE__);	\
				fprintf(log_file_g, "[%s]", get_comp_name(type));	\
				fprintf(log_file_g, __VA_ARGS__);	\
				fflush(log_file_g);		\
			}					\
		}

#define LOG_I(type, ...) \
		if (6 <= log_level_g)				\
		{						\
			if (log_file_g != NULL) 			\
			{					\
				time_t t = time(NULL);		\
				char *p = ctime(&t);		\
				p[strlen(p)-1] = '	';	\
				fprintf(log_file_g, "%s", p);	\
				fprintf(log_file_g, "%-16s\t", __FILENAME__);	\
				fprintf(log_file_g, "%5d: ", __LINE__);	\
				fprintf(log_file_g, "[%s]", get_comp_name(type));	\
				fprintf(log_file_g, __VA_ARGS__);	\
				fflush(log_file_g);		\
			}					\
		}

#define LOG_D(type, ...) \
		if (7 <= log_level_g)				\
		{						\
			if (log_file_g != NULL) 			\
			{					\
				time_t t = time(NULL);		\
				char *p = ctime(&t);		\
				p[strlen(p)-1] = '	';	\
				fprintf(log_file_g, "%s", p);	\
				fprintf(log_file_g, "%-16s\t", __FILENAME__);	\
				fprintf(log_file_g, "%5d: ", __LINE__);	\
				fprintf(log_file_g, "[%s]", get_comp_name(type));	\
				fprintf(log_file_g, __VA_ARGS__);	\
				fflush(log_file_g);		\
			}					\
		}

#define LOG_T(type, ...) \
		if (9 <= log_level_g)				\
		{						\
			if (log_file_g != NULL) 			\
			{					\
				time_t t = time(NULL);		\
				char *p = ctime(&t);		\
				p[strlen(p)-1] = '	';	\
				fprintf(log_file_g, "%s", p);	\
				fprintf(log_file_g, "%-16s\t", __FILENAME__);	\
				fprintf(log_file_g, "%5d: ", __LINE__);	\
				fprintf(log_file_g, "[%s]", get_comp_name(type));	\
				fprintf(log_file_g, __VA_ARGS__);	\
				fflush(log_file_g);		\
			}					\
		}

typedef enum {
	MIN_LOG_COMPONENTS = 0,
	PHY = MIN_LOG_COMPONENTS,
	OUTER_INTERFACE,
	INNER_INTERFACE,
	VENDOR_MANAGEMENT,
	ENVENT_PUSH,
	COLLAB_FILTER,
	PATTERN_RECOGNITION,
	MAX_LOG_COMPONENTS,
	OAI_IOTA_INTERFACE,
}
comp_name_t;

/*--- INTERFACES ---------------------------------------------------------------*/
#ifdef LOG_C
#	define private_log(x) x
#	define public_log(x) x
#else
#	define private_log(x)
#	define public_log(x) extern x
#endif

/** @defgroup LOG Interfaces
 * @{*/
public_log(char * get_comp_name(comp_name_t type);)
public_log(void str_to_num(char* source, char* dest, int len);)
public_log(void dump_msg_in_hex(char *buffer, int size);)
public_log(void init_log(char *log_file_name);)
/* @}*/
/*----------------------------------------------------------------------------*/
#ifdef __cplusplus
}
#endif


#endif /* __LOG_H__ */

