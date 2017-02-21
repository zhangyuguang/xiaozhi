#! /usr/bin/env python
# -*- coding:utf-8 -*- 
# python version: 2.7.10

import json
import urllib2
import httplib
import sys
import platform
import logging
import jpush as jpush

from conf import app_key, master_secret
from jpush import common

# log config
logging.basicConfig(level=logging.DEBUG,
					format='%(asctime)s %(filename)s[line:%(lineno)d] %(levelname)s %(message)s',
					datefmt='%a, %d %b %Y %H:%M:%S',
					filename='/tmp/zhi-service-py.log',
					filemode='a')
logging.error('This is jpush error message')
logging.debug('This is jpush debug message')
logging.info('This is jpush info message')
logging.warning('This is jpush warning message')

reload(sys) 
sys.setdefaultencoding('utf-8') 

## push API
def jpush_push(notify_info):
	# base on os to deal
	os_type = platform.system()
	if(os_type == "Windows"):
		pass
	elif(os_type == "Linux"):
		print "Start to deal jpush push API\n"
		_jpush = jpush.JPush(app_key, master_secret)
		_jpush.set_logging("DEBUG")
		push = _jpush.create_push()
		push.audience = jpush.all_
		push.notification = jpush.notification(alert=notify_info)
		push.platform = jpush.all_
		try:
			response = push.send()
		except common.Unauthorized as e:
			raise common.Unauthorized("Unauthorized")
			logging.error('Unauthorized exception received')
		except common.APIConnectionException as e:
			raise common.APIConnectionException("Connection")
			logging.error('Connection exception received')
		except common.JPushFailure as e:
			logging.error('JPush failure exception received')
		except:
			logging.error('Other unhandled exception received')
	return 0

# self test used
#jpush_push(u'hello python jpush api')