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

/*! \file jpush_api.c
* \brief jpush API deal implementation
* \author Sean Wang
* \date 2016
* \version 1.0
* @ingroup outer_interface

*/


#define JPUSH_API_C

#include <Python.h>

#include "utils/log/log.h"

#include "jpush_api.h"

/***
 * Function init_jpush_interface()
 * Initialize the jpush interface layer
 *
 */
void init_jpush_interface()
{
	/*int ret = 0;
	
	PRT_LOG_T(LOG_ERR, OUTER_INTERFACE, "Start to init jpush interface...\n");
	Py_Initialize();
	PyObject *pModule = NULL;
	PyObject *pFunc = NULL;
	PyObject *pReturn = NULL; 
	PyRun_SimpleString("import sys");
	PyRun_SimpleString("sys.path.append('/home/openair/xiao-zhi-app-service/outer_interface/jpush_api/')");
	// create and set 2 float args(all args format is tuple type)
	PyObject *pArgs = PyTuple_New(1);
	PyTuple_SetItem(pArgs, 0, Py_BuildValue("s", "test python jpush api"));
	pModule = PyImport_ImportModule("jpush_api");
	if (!pModule)
	{
		PRT_LOG_T(LOG_ERR, OUTER_INTERFACE, "Import python module error\n");
	}
	else
	{
		pFunc = PyObject_GetAttrString(pModule, "jpush_push");
		if (!pFunc)
		{
			PRT_LOG_T(LOG_ERR, OUTER_INTERFACE, "Get python function error\n");
		}
		else
		{
			pReturn = PyEval_CallObject(pFunc, pArgs);
			if (!pReturn)
			{
				PRT_LOG_T(LOG_ERR, OUTER_INTERFACE, "Perform python function error\n");
			}
			else
			{
				// convert python return result to int
				PyArg_Parse(pReturn, "i", &ret);
				PRT_LOG_T(LOG_INFO, OUTER_INTERFACE, "ret=%d\n", ret);
			}
		}
	}
	Py_Finalize();*/
}

/***
 * Function send_msg_to_jpush()
 * Sending message info to jpush
 * return: OK 0; NOK -1
 *
 */
int send_msg_to_jpush(char *push_info)
{
	int ret = 0;
	
	PRT_LOG_T(LOG_ERR, OUTER_INTERFACE, "Start to init jpush interface...\n");
	Py_Initialize();
	PyObject *pModule = NULL;
	PyObject *pFunc = NULL;
	PyObject *pReturn = NULL; 
	PyRun_SimpleString("import sys");
	PyRun_SimpleString("sys.path.append('/home/openair/xiao-zhi-app-service/outer_interface/jpush_api/')");
	// create and set 2 float args(all args format is tuple type)
	PyObject *pArgs = PyTuple_New(1);
	PyTuple_SetItem(pArgs, 0, Py_BuildValue("s", push_info));
	pModule = PyImport_ImportModule("jpush_api");
	if (!pModule)
	{
		PRT_LOG_T(LOG_ERR, OUTER_INTERFACE, "Import python module error\n");
		return -1;
	}
	else
	{
		pFunc = PyObject_GetAttrString(pModule, "jpush_push");
		if (!pFunc)
		{
			PRT_LOG_T(LOG_ERR, OUTER_INTERFACE, "Get python function error\n");
			return -1;
		}
		else
		{
			pReturn = PyEval_CallObject(pFunc, pArgs);
			if (!pReturn)
			{
				PRT_LOG_T(LOG_ERR, OUTER_INTERFACE, "Perform python function error\n");
				return -1;
			}
			else
			{
				// convert python return result to int
				PyArg_Parse(pReturn, "i", &ret);
				PRT_LOG_T(LOG_INFO, OUTER_INTERFACE, "ret=%d\n", ret);
			}
		}
	}
	Py_Finalize();
	
	return 0;
}
