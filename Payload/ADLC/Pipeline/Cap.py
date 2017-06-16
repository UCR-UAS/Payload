#!/usr/bin/env python

import zmq
import proto.location_pb2
import time
import threading
import os

last_geotag_msg = proto.location_pb2.PlaneLocation()
geotag_msg_lock = threading.Lock()
def geotag_subscribe_loop():
	context = zmq.Context()
	socket = context.socket(zmq.SUB)
	socket.connect("tcp://localhost:7777")
	# sub to all messages
	socket.setsockopt(zmq.SUBSCRIBE, "")

	global last_geotag_msg
	global geotag_msg_lock
	while True:
		blob = socket.recv()
		message = proto.location_pb2.PlaneLocation()
		message.ParseFromString(blob)
		with geotag_msg_lock:
			last_geotag_msg = message
		

def start_geotag_subscribe_loop():
	gt_t = threading.Thread(target=geotag_subscribe_loop)
	gt_t.daemon = True
	gt_t.start()

def get_last_geotag_msg():
	global last_geotag_msg
	global geotag_msg_lock
	with geotag_msg_lock:
		return last_geotag_msg

def main():
	start_geotag_subscribe_loop()
	while 1:
		msg1 = get_last_geotag_msg()
		msg2 = get_last_geotag_msg()
	#for x in range(5):
		yaw_deg = (msg1.yaw_degrees+msg2.yaw_degrees)/2;
		yaw_nsew = "N"
		if yaw_deg > 337.5 or yaw_deg < 22.5:
			yaw_nsew = "W"	
		elif yaw_deg > 292.5:
			yaw_nsew = "SW"
		elif yaw_deg > 247.5:
			yaw_nsew = "S"
		elif yaw_deg > 202.5:
			yaw_nsew = "SE"
		elif yaw_deg > 157.5:
			yaw_nsew = "E"
		elif yaw_deg > 112.5:
			yaw_nsew = "NE"
		elif yaw_deg > 67.5:
			yaw_nsew = "N"
		else:
			yaw_nsew = "NW"
                print msg1.yaw_degrees
		#NewName = str((msg1.lat_degrees+msg2.lat_degrees)/2)+\
		#":"+str((msg1.lon_degrees+msg2.lon_degrees)/2)+\
		#":"+yaw_nsew+".JPG"
		#os.system("mv *.JPG cap/"+NewName)

if __name__ == "__main__":
	main()


