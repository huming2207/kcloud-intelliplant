#!/usr/bin/env python 
# -*- coding: utf-8 -*- 

# # # # # # # # # # # # # # # # # # # # # # # # # # #
#
# SHSS IntelliPlant Client for Raspberry Pi
# By Jackson Hu <huming2207@gmail.com>
# Some of these code are from the online examples.
#
# # # # # # # # # # # # # # # # # # # # # # # # # # #
import os,sys
import requests
import json,time,string
import serial,ConfigParser



config = ConfigParser.RawConfigParser()
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

if len(sys.argv) > 1:
	Hr1 = config.getint('Schedule1', 'Hr')
	Min1 = config.getint('Schedule1', 'Min')
	Sec1 = config.getint('Schedule1', 'Sec')
	Capacity1 = config.getint('Schedule1', 'Capacity')
	MainSwitch1 = config.getint('Schedule1', 'MainSwitch')
	AutoSwitch1 = config.getint('Schedule1', 'AutoSwitch')
	Hr2 = config.getint('Schedule2', 'Hr')
	Min2 = config.getint('Schedule2', 'Min')
	Sec2 = config.getint('Schedule2', 'Sec')
	Capacity2 = config.getint('Schedule2', 'Capacity')
	MainSwitch2 = config.getint('Schedule2', 'MainSwitch')
	AutoSwitch2 = config.getint('Schedule2', 'AutoSwitch')
	Hr3 = config.getint('Schedule3', 'Hr')
	Min3 = config.getint('Schedule3', 'Min')
	Sec3 = config.getint('Schedule3', 'Sec')
	Capacity3 = config.getint('Schedule3', 'Capacity')
	MainSwitch3 = config.getint('Schedule3', 'MainSwitch')
	AutoSwitch3 = config.getint('Schedule3', 'AutoSwitch')
	SolarRatio = config.getint('W2WC', 'Solar')
	HumidRatio = config.getint('W2WC', 'Humid')
	TempRatio = config.getint('W2WC', 'Temp')
	BaroRatio = config.getint('W2WC', 'Baro')
	Schedule1_payload = '2,' + Hr1 + ',' + Min1 + ',' + Sec1 + ',' + Capacity1 + ',' + MainSwitch1 + ',' + AutoSwitch1 + '\r\n'
	Schedule2_payload = '3,' + Hr2 + ',' + Min2 + ',' + Sec2 + ',' + Capacity2 + ',' + MainSwitch2 + ',' + AutoSwitch2 + '\r\n'
	Schedule3_payload = '4,' + Hr3 + ',' + Min3 + ',' + Sec3 + ',' + Capacity3 + ',' + MainSwitch3 + ',' + AutoSwitch3 + '\r\n'
	Weather_payload = '7,' + TempRatio + ',' + HumidRatio + ',' + SolarRatio + ',' + BaroRatio + '\r\n'
	print "Now setting up the Arduino."
	print Schedule1_payload
	print Schedule2_payload
	print Schedule3_payload
	print Weather_payload
	port.write(Schedule1_payload)
	print "......30%"
	sleep(3)
	port.write(Schedule2_payload)
	print "............60%"
	sleep(3)
	port.write(Schedule3_payload)
	print "..............80%"
	sleep(3)
	port.write(Weather_payload)
	print "....................DONE!!!!!!"
	print "Now, re-run the program please!"
	sleep(3)
	port.close()
	exit()
	
	
#吃了炫迈一样停不下来的循环
if __name__=='__main__':
    while 1:
        apikey=config.get("Yeelink","Key")
        apiheaders={'U-ApiKey': apikey,'content-type': 'application/json'}
        cputemp_apiurl=config.get("Yeelink","CPUTemp")
        cpuused_apiurl=config.get("Yeelink","CPUUsed")
        memeryused_apiurl=config.get("Yeelink","RAM")
        dust_apiurl=config.get("Yeelink","Dust")
        temp_apiurl=config.get("Yeelink","Temp")
        baro_apiurl=config.get("Yeelink","Baro")
        humid_apiurl=config.get("Yeelink","Humid")
	
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
        time.sleep(1)
