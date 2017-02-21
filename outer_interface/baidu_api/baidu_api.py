#! /usr/bin/env python
# -*- coding:utf-8 -*- 
# python version: 2.7.10

import json
import urllib2
import httplib
import sys
import platform
import logging

from conf import map_key

# log config
logging.basicConfig(level=logging.DEBUG,
					format='%(asctime)s %(filename)s[line:%(lineno)d] %(levelname)s %(message)s',
					datefmt='%a, %d %b %Y %H:%M:%S',
					filename='/tmp/zhi-service-py.log',
					filemode='a')
logging.error('This is baidu error message')
logging.debug('This is baidu debug message')
logging.info('This is baidu info message')
logging.warning('This is baidu warning message')

reload(sys) 
sys.setdefaultencoding('utf-8') 

## Place API --- Web service API
def baidu_place(location):
	url = 'http://api.map.baidu.com/place/v2/search?query='+location.encode('utf-8')+'&page_size=10&page_num=0&scope=1&region='+u'青岛'+'&output=json&ak='+map_key
	temp = urllib2.urlopen(url)
	print "The return result is %s\n" %temp
	
	# base on os to deal
	os_type = platform.system()
	if(os_type == "Windows"):
		pass
	elif(os_type == "Linux"):
		result = temp.read()
		print "The map API return result is: %s\n" %(result)
		decode_json = json.loads(result)
		print "The JSON decode result is: %s\n" %decode_json
		print decode_json.keys()
		for i in range(10):
			address = decode_json["results"][i]["address"]
			print "The address[%d] is: %s\n" %(i, address.encode('utf-8'))
			name = decode_json["results"][i]["name"]
			print "The name[%d] is: %s\n" %(i, name.encode('utf-8'))
	return 0

## Place Detail API --- Web service API
def baidu_place_detail():
	url = 'http://api.map.baidu.com/place/v2/detail?uid=5a8fb739999a70a54207c130&output=json&scope=2&ak='+map_key
	temp = urllib2.urlopen(url)
	print "The return result is %s\n" %temp

## Place Suggestion API --- Web service API
def baidu_place_suggestion():
	url = 'http://api.map.baidu.com/place/v2/suggestion?query='+u'天安门'+'&region=131&output=json&ak='+map_key
	temp = urllib2.urlopen(url)
	print "The return result is %s\n" %temp

## Geocoding API --- Web service API
def baidu_geocoding(lat, lng):
	# set proxy: proxy address
	#proxy_handler = urllib2.ProxyHandler({'http': 'http://cnproxy.cn.alcatel-lucent.com/proxy.pac:8080'})
	#proxy_auth_handler = urllib2.ProxyBasicAuthHandler()
	# set proxy: change to own domain/user_name password
	#proxy_auth_handler.add_password(None, 'http://www.baidu.com/', 'DOMAIN/LOGIN', 'PWD')
	#opener = urllib2.build_opener(proxy_handler, proxy_auth_handler)
	# install it globally so it can be used with urlopen
	#urllib2.install_opener(opener)
	url = 'http://api.map.baidu.com/geocoder/v2/?&location='+str(lat)+','+str(lng)+'&output=json&ak='+map_key
	temp = urllib2.urlopen(url)
	#print "The url return result is %s\n" %(temp)
	
	# base on os to deal
	os_type = platform.system()
	if(os_type == "Windows"):
		result = temp.read().encode('utf-8')
		print "The map API return result is: %s\n" %(result.decode('utf-8'))
		decode_json = json.loads(result)
		print "The JSON decode result is: %s\n" %decode_json
		info = decode_json["result"]["sematic_description"]
		print "The detail info is: %s\n" %info
		return 0
	elif(os_type == "Linux"):
		result = temp.read()
		print "The map API return result is: %s\n" %(result)
		decode_json = json.loads(result)
		print "The JSON decode result is: %s\n" %decode_json
		info = decode_json["result"]["sematic_description"]
		print "Currently APP loaction info is: %s\n" %(info.encode('utf-8'))
		return info.encode('utf-8')
		#return info

## Geocoding API --- Web service API
def baidu_geocoding_place(address):
	# set proxy: proxy address
	#proxy_handler = urllib2.ProxyHandler({'http': 'http://cnproxy.cn.alcatel-lucent.com/proxy.pac:8080'})
	#proxy_auth_handler = urllib2.ProxyBasicAuthHandler()
	# set proxy: change to own domain/user_name password
	#proxy_auth_handler.add_password(None, 'http://www.baidu.com/', 'DOMAIN/LOGIN', 'PWD')
	#opener = urllib2.build_opener(proxy_handler, proxy_auth_handler)
	# install it globally so it can be used with urlopen
	#urllib2.install_opener(opener)
	url = 'http://api.map.baidu.com/geocoder/v2/?&address='+address+'&output=json&ak='+map_key
	temp = urllib2.urlopen(url)
	print "The url return result is %s\n" %(temp)
	
	# base on os to deal
	os_type = platform.system()
	if(os_type == "Windows"):
		result = temp.read().encode('utf-8')
		print "The map API return result is: %s\n" %(result.decode('utf-8'))
		decode_json = json.loads(result)
		print "The JSON decode result is: %s\n" %decode_json
		lat = decode_json["result"]["location"]["lat"]
		print "The lat is: %f\n" %lat
		lng = decode_json["result"]["location"]["lng"]
		print "The lng is: %f\n" %lng
	elif(os_type == "Linux"):
		result = temp.read()
		print "The map API return result is: %s\n" %(result)
		decode_json = json.loads(result)
		print "The JSON decode result is: %s\n" %decode_json
		lat = decode_json["result"]["location"]["lat"]
		print "The lat is: %f\n" %(lat)
		lng = decode_json["result"]["location"]["lng"]
		print "The lng is: %f\n" %(lng)
	return 0

# self test used
#baidu_place()
#baidu_geocoding(39.983424, 116.322987)
#u'山河城小区': lat-36.172029; lng-120.463802;
#baidu_geocoding_place(u'山河城小区')
#u'枣山东路': lat-36.150775; lng-120.481603;
#baidu_geocoding_place(u'枣山东路')