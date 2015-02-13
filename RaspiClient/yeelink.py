#!/usr/bin/env python 
# -*- coding: utf-8 -*- 

# # # # # # # # # # # # # # # # # # # # # # # # # # #
#
# SHSS IntelliPlant Client for Raspberry Pi
# By Jackson Hu <huming2207@gmail.com>
# Some of these code are from the online examples.
#
# # # # # # # # # # # # # # # # # # # # # # # # # # #
import os
import requests
import json,time,string
import serial,ConfigParser

config = ConfigParser.RawConfigParser()
#if os.path.exists("settings.conf")
#    print "Configuration file does not exist. Exit..."
#    exit()
config.read("Settings.conf")


def readlineCR(port):
    rv = ""
    while True:
        ch = port.read()
        rv += ch
        if ch=='\r' or ch=='':
            return rv

port = serial.Serial("/dev/ttyAMA0", baudrate=9600, timeout=3.0)
if port.isOpen == False:
    print "Serial port is unavailable, Exit..."
    exit()

#获取cpu温度
def getcputemperature():
    cputemp=os.popen('vcgencmd measure_temp').readline()
    sumcputemp=cputemp.replace("temp=","").replace("'C\n","")
    return sumcputemp

#获取CPU及内存使用情况
def getcpuused():
    return(os.popen("top -n1"))

apikey=config.get("Yeelink","Key")

#apikey为用户id
apiheaders={'U-ApiKey': apikey,'content-type': 'application/json'}

#CPU温度使用 25322 传感器
cputemp_apiurl=config.get("Yeelink","CPUTemp")

#cpu 使用情况使用 25356 传感器
cpuused_apiurl=config.get("Yeelink","CPUUsed")

#内存占用率使用 25357 传感器
memeryused_apiurl=config.get("Yeelink","RAM")

#粉尘传感器
dust_apiurl=config.get("Yeelink","Dust")

#温度传感器
temp_apiurl=config.get("Yeelink","Temp")

#气压传感器
baro_apiurl=config.get("Yeelink","Baro")

#湿度传感器
humid_apiurl=config.get("Yeelink","Humid")

#吃了炫迈一样停不下来的循环
if __name__=='__main__':
    while 1:
        
	#预处理数据
	rcv = readlineCR(port)
	rcv_split = rcv.split(",")
	dust_payload = {'value':rcv_split[1]}
	humid_payload = {'value':rcv_split[2]}
	temp_payload = {'value':rcv_split[3]}
	baro_payload = {'value':filter(str.isdigit, rcv_split[4])}
	
	
	#上传灰尘传感器数据
	r=requests.post(dust_apiurl, headers=apiheaders, data=json.dumps(dust_payload))
	print dust_payload
	
	#上传湿度传感器数据
	r=requests.post(humid_apiurl, headers=apiheaders, data=json.dumps(humid_payload))
	print humid_payload

	#上传温度传感器数据
	r=requests.post(temp_apiurl, headers=apiheaders, data=json.dumps(temp_payload))
	print temp_payload

	#上传气压传感器数据
	r=requests.post(baro_apiurl, headers=apiheaders, data=json.dumps(baro_payload))
	print baro_payload
	

	#上传cpu温度
        cpu_temp=getcputemperature()
        cputemp_payload={'value':cpu_temp}
        r=requests.post(cputemp_apiurl, headers=apiheaders, data=json.dumps(cputemp_payload))
        print cpu_temp
	
	

    
        #上传cpu占用率及内存使用率
        tempcpuused=getcpuused()
  	
        for cpuline in tempcpuused:

            if cpuline[:3]=="%Cp":
                #cpulineused=cpuline.split(":")[1].split(",")[0].strip("us").split(" ")[1]
     
                cpulineused=cpuline.split(":")[1].split(",")[0].split(" ")[-2]
                cpuused_payload={'value':cpulineused}
                r=requests.post(cpuused_apiurl, headers=apiheaders, data=json.dumps(cpuused_payload))
                print "CPU USED %:"+cpulineused
            if "Mem:" in cpuline:
               #提取数值，仅用字符串操作时，发现在数值前后有多个不可见字符，这里没怎么搞清楚这些字符是些什么
                memlineused=cpuline.split(":")[1].split(",")[1].strip("used").split(" ")[-2]

                memlinetotal=cpuline.split(":")[1].split(",")[0].strip("total").split(" ")[-2]
 
                memeryusedratio=float(str(memlineused))/float(str(memlinetotal))
                memeryusedratiostr="%.2f"%(memeryusedratio*100)
                memeryused_payload={'value':memeryusedratiostr}
                r=requests.post(memeryused_apiurl, headers=apiheaders, data=json.dumps(memeryused_payload))
                
                print memeryusedratiostr
                print "================"
        time.sleep(3)
