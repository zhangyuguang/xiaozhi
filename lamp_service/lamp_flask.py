#!flask/bin/python
#python -m compileall xxx.py
# -*- coding:utf-8 -*- 

import logging, sys
from flask import Flask, jsonify, make_response, request, render_template, json
from time import *
import flask, json, sys, time, itertools, socket

reload(sys) 
sys.setdefaultencoding('utf-8') 

# log config
logging.basicConfig(level=logging.DEBUG,
					format='%(asctime)s %(filename)s[line:%(lineno)d] %(levelname)s %(message)s',
					datefmt='%a, %d %b %Y %H:%M:%S',
					filename='/tmp/zhi-service-py.log',
					filemode='a')
logging.error('This is flask error message')
logging.debug('This is flask debug message')
logging.info('This is flask info message')
logging.warning('This is flask warning message')

if not "/home/openair/xiao-zhi-app-service/outer_interface/baidu_api/" in sys.path:
	sys.path.append("/home/openair/xiao-zhi-app-service/outer_interface/baidu_api/")
if not 'baidu_api' in sys.modules:
    baidu_api = __import__('baidu_api')
else:
    eval('import baidu_api')
    baidu_api = eval('reload(baidu_api)')

def secs2str(secs):
	return strftime("%Y-%m-%d %H:%M:%S",localtime(secs))

app = flask.Flask(__name__)

'''
@app.route("/")
def index():
    return render_template("index.html")
'''

@app.route('/')
def start():
    return 'This is Hackathon Server!'



tasks = [
    {
        'id': 1,
        'data_time': 2016-10-12,
        'location': u'Qingdao, LaoShan, ZhuZhou Road, 159, Lucent', 
        'add_inf': u'Ture',
		'Street ID': 159
	},
	{
        'id': 2,
        'status': u'Learn Python',
        'description': u'Need to find a good Python tutorial on the web', 
        'done': False
	}
]

info = [
    {
        'id': 1,
        'status': u'Buy groceries',
        'description': u'Milk, Cheese, Pizza, Fruit, Tylenol', 
        'done': False
    },
    {
        'id': 2,
        'status': u'Learn Python',
        'description': u'Need to find a good Python tutorial on the web', 
        'done': False
    }
]

#	app = filter(lambda t: t['id'] == 1, task_app)
#	return jsonify({'app': app[0]})


@app.route('/Hackathon', methods=['GET'])
def get_tasks():
    return jsonify({'tasks': tasks})


@app.errorhandler(404)
def not_found(error):
    return make_response(jsonify({'error': 'Not found'}), 404)

	
@app.route('/Hackathon/<int:task_id>', methods=['GET'])
#@app.route('/login', methods=['GET'])
def get_one_task(task_id):
    task = filter(lambda t: t['id'] == task_id, tasks)
    if len(task) == 0:
        abort(404)
    return jsonify({'task': task[0]})


#for test html
'''
@app.route('/login', methods = ['GET', 'POST'])
def post_task():
    #if not request.json or not 'title' in request.json:
     #   abort(400)
		
    if request.method == "POST":
        id = request.form.get('id')
        #info = request.form.get('password')
        if id =="1":
            #return "<h1>info, %s !</h1>" %id
			task = filter(lambda t: t['id'] == 1, tasks)
			return jsonify({'task': task[0]})
			#return jsonify({'tasks': tasks})
		
        else:
            return "<h1>login Failure1 !</h1>"    
    else:
        return "<h1>login Failure !</h1>"
'''

@app.route('/Hackathon', methods=['POST'])
def create_task():
    if not request.json or not 'title' in request.json:
        abort(400)
    task = {
        'id': tasks[-1]['id'] + 1,
        'title': request.json['title'],
        'description': request.json.get('description', ""),
        'done': False
    }
    tasks.append(task)
    return jsonify({'task': task}), 201

def getBaseReturnValue(data,msg,code):
    json_data = json.dumps({'datas':data,'msg':msg,'success':code},ensure_ascii=False,encoding='gb2312')
    return json_data

#./curl -d "[1,1,2,3,5,8]" -H "Content-Type:application/json" http://localhost:5000/Hackathon/test
#./curl -d '{"""operation""":"""REQ-RSP""", """c_id""":"""1""", """info""":"""home"""}' -H "Content-Type:application/json" http://127.0.0.1:5000/Hackathon/test
#192.168.31.41

@app.route('/Hackathon/test', methods = ['GET', 'POST'])
def get_info():
    #if request.method == "POST":
	
#	posts = [1,2,3,4,5,6,7]
#	index = request.args.get('1')
#	return jsonify(index)

	
#	index = request.get_data()
#	index = request.get_json('title')
	var = request.json.get('operation', "")
	
	
	index = json.dumps(flask.request.json)
	va = json.loads(index)
#	task = filter(lambda t: t['operation_id'] == id, task_app)

	dict1 = {	
			'status': 0,
			'ret_num': 0,
			'ret_inf': 
				{
					'name': 'Ocean University of China',
					'location': 
						{
							'lng': 135,
							'lat': 44
						},
					'address': 'SongLing Road 238',
					'telephone': '15253262580',
					'uid': 1,
					'street_id': 238,
					'detail_flag': 1,
					'detai_info': 2
				}						
			}
			
	dict2 = {	
			'status': 0,
			'ret_num': 1,
			'ret_inf': 
				{
					'name': 'Lucent',
					'location': 
						{
							'lng': 90,
							'lat': 50
						},
					'address': 'ZhuZhou Road 159',
					'telephone': '15253262580',
					'uid': 1,
					'street_id': 159,
					'detail_flag': 1,
					'detai_info': 2
				}						
			}	
	
	operation = str(va.get('operation', 'not found'))
	c_id = str(va.get('c_id', 'not found'))
	info = str(va.get('info', 'not found'))

	
	if (c_id == "1") and (info == "home"):
		return jsonify({'dict': dict1})

	elif(c_id == "2") and (info == "work"):
		return jsonify({'dict': dict2}) 
	
	else:
	#	return "<h1>Error, could not get!</h1>"
		return "operation =, %s" %var

### location info update API
#curl -i -H "Content-Type: application/json" -X POST -d '''{"c_id":"500","date_time":"123406389", "lat":"36.172029","lng":"120.463802"}''' http://192.168.168.128:5000/inner-api-v1/location_api/update
#./curl -d '{"""date_time""":"""2016-10-15 8:30:00""", """lat""":"""138""","""lng""":"""52"""}' -H "Content-Type:application/json" http://192.168.168.128:5000/inner-api-v1/location_api/update
@app.route('/inner-api-v1/location_api/update', methods = ['GET', 'POST'])
def location_update_info():
	c_id = request.json.get('c_id', "")
	date_time = request.json.get('date_time', "")
	tmp_date_time = date_time
	lat = request.json.get('lat', "")
	lng = request.json.get('lng', "")
	print "App reported Data-Time is %s\n" %(secs2str(float(tmp_date_time)))
	addr = baidu_api.baidu_geocoding(lat, lng)
	
	dict1 = {
				'c_id': 500,
				'status': 0
			}
	
	dict2 = {
				'c_id' : 300,
				'status': 0
			}
	status1 = str(dict1['status'])
	
	if (lat == "36.172029") and (lng == "120.463802") and (c_id == '500'):
	#if (lat == "36.150775") and (lng == "120.481603") and (c_id == '500'):
		address = ('192.168.168.128', 8080)
		fd = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
		res = fd.connect(address)
		if res == -1:
			print "error connect!"
		send_info = '0' + c_id +  date_time + 'ZSDL'
		fd.sendall(send_info)
		fd.close()
		return jsonify({'dict': dict1})
	else:
	#	return "<h1>Error, could not get!</h1>"
		return status1
	
#	return "<h1>Error, could not update!</h1>"


		
#	level = jsonify({"operation_id": "info"})
#	level = {"operation_id": "info"}
#	return level
#	return index

		
		
#	for operation_id in task_app:
		
#		task = {"id": 4,
#				"type":False}
#		new = result.append(task)
#		return jsonify({'task_app': task_app})
	
	
#		return "Received: " + new
#	return'post_id = {0}'.format(id)
#	result = []
'''	
	if index != None:
		
		task = {"id": 4,
				"type":False}
		result.append(task)
		#return "<h1>index =, %s !</h1>" %index
		return jsonify({'task': task}), 201
	else:
		return "<h1>index =, %s !</h1>" %index

	while index == "read":
		if index == "title":
			for item in  tasks:
				task = {"id": 4,
						"type":False}
				result.append(task)
				return jsonify({'task': task}), 201
		else:
			return "<h1>index, %s !</h1>" %index
		
def http_get():
    url='http://localhost:5000/Hackathon/test'   
    response = urllib2.urlopen(url)         
    return response.read()                   
    
ret = http_get()
print("RET %r" % (ret))
'''

		
		
#	except KeyError,e:
#		print(e)
		#return getBaseReturnValue(data=[],msg="Error",code=False)  



if __name__ == '__main__':
	app.run(host='192.168.168.128', port=5000)

