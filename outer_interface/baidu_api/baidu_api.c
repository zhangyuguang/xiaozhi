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

/*! \file baidu_api.c
* \brief baidu API deal implementation
* \author Sean Wang
* \date 2016
* \version 1.0
* @ingroup outer_interface

*/


#define BAIDU_API_C

#include <Python.h>

#include "utils/log/log.h"

#include "baidu_api.h"

/***
 * Function init_baidu_interface()
 * Initialize the baidu interface layer
 *
 */
void init_baidu_interface()
{
/*
	int ret = 0;
	
	PRT_LOG_T(LOG_ERR, OUTER_INTERFACE, "Start to init baidu interface...\n");
	Py_Initialize();
	PyObject *pModule = NULL;
	PyObject *pFunc = NULL;
	PyObject *pReturn = NULL; 
	PyRun_SimpleString("import sys");
	PyRun_SimpleString("sys.path.append('/home/openair/xiao-zhi-app-service/outer_interface/baidu_api/')");
	// create and set 2 float args(all args format is tuple type)
	PyObject *pArgs = PyTuple_New(2);
	PyTuple_SetItem(pArgs, 0, Py_BuildValue("f", 39.983424));
	PyTuple_SetItem(pArgs, 1, Py_BuildValue("f", 116.322987));
	pModule = PyImport_ImportModule("baidu_api");
	if (!pModule)
	{
		PRT_LOG_T(LOG_ERR, OUTER_INTERFACE, "Import python module error\n");
	}
	else
	{
		pFunc = PyObject_GetAttrString(pModule, "baidu_geocoding");
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
	Py_Finalize();
*/
}

/***
 * Function send_msg_to_baidu()
 * Sending message info to baidu
 * return: OK 0; NOK -1
 *
 */
int send_msg_to_baidu(char *api_type, char *query_info)
{
	int ret = 0;
	
	PRT_LOG_T(LOG_INFO, OUTER_INTERFACE, "Start to init baidu interface...\n");
	PRT_LOG_T(LOG_INFO, OUTER_INTERFACE, "Requst api_type=%s query_info=%s\n", api_type, query_info);
	Py_Initialize();
	PyObject *pModule = NULL;
	PyObject *pFunc = NULL;
	PyObject *pReturn = NULL; 
	PyRun_SimpleString("import sys");
	PyRun_SimpleString("sys.path.append('/home/openair/xiao-zhi-app-service/outer_interface/baidu_api/')");
	// create and set 2 float args(all args format is tuple type)
	//PyObject *pArgs = PyTuple_New(2);
	//PyTuple_SetItem(pArgs, 0, Py_BuildValue("f", 39.983424));
	//PyTuple_SetItem(pArgs, 1, Py_BuildValue("f", 116.322987));
	PyObject *pArgs = PyTuple_New(1);
	PyTuple_SetItem(pArgs, 0, Py_BuildValue("s", query_info));
	pModule = PyImport_ImportModule("baidu_api");
	if (!pModule)
	{
		PRT_LOG_T(LOG_ERR, OUTER_INTERFACE, "Import python module error\n");
	}
	else
	{
		//pFunc = PyObject_GetAttrString(pModule, "baidu_geocoding");
		pFunc = PyObject_GetAttrString(pModule, api_type);
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
	Py_Finalize();
}
