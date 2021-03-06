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

#测试串口是否可用
port = serial.Serial("/dev/ttyAMA0", baudrate=9600, timeout=0.3)
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


#获取运行方式，如果收到客户端发送带参数的指令，则进入设置模式
if len(sys.argv) > 1:
	Hr1 = config.get('Schedule1', 'Hr')
	Min1 = config.get('Schedule1', 'Min')
	Sec1 = config.get('Schedule1', 'Sec')
	Capacity1 = config.get('Schedule1', 'Capacity')
	MainSwitch1 = config.get('Schedule1', 'MainSwitch')
	AutoSwitch1 = config.get('Schedule1', 'AutoSwitch')
	Hr2 = config.get('Schedule2', 'Hr')
	Min2 = config.get('Schedule2', 'Min')
	Sec2 = config.get('Schedule2', 'Sec')
	Capacity2 = config.get('Schedule2', 'Capacity')
	MainSwitch2 = config.get('Schedule2', 'MainSwitch')
	AutoSwitch2 = config.get('Schedule2', 'AutoSwitch')
	Hr3 = config.get('Schedule3', 'Hr')
	Min3 = config.get('Schedule3', 'Min')
	Sec3 = config.get('Schedule3', 'Sec')
	Capacity3 = config.get('Schedule3', 'Capacity')
	MainSwitch3 = config.get('Schedule3', 'MainSwitch')
	AutoSwitch3 = config.get('Schedule3', 'AutoSwitch')
	Ratio = config.get('Ratio', 'AutoRatio')
	Schedule1_payload = '2,' + Hr1 + ',' + Min1 + ',' + Sec1 + ',' + Capacity1 + ',' + MainSwitch1 + ',' + AutoSwitch1 + '\r\n'
	Schedule2_payload = '3,' + Hr2 + ',' + Min2 + ',' + Sec2 + ',' + Capacity2 + ',' + MainSwitch2 + ',' + AutoSwitch2 + '\r\n'
	Schedule3_payload = '4,' + Hr3 + ',' + Min3 + ',' + Sec3 + ',' + Capacity3 + ',' + MainSwitch3 + ',' + AutoSwitch3 + '\r\n'
	Ratio_payload = '7,' + Ratio +  '\r\n'
    Time_payload = '1,' + time.strftime("%Y") + ',' + time.strftime("%m") + ',' + time.strftime("%d") + ',' + time.strftime("%H") + ',' + time.strftime("%M") + ',' + time.strftime("%S") + ',' + time.strftime("%w") + '\r\n'
	print "Now setting up the node."
	print Schedule1_payload
	print Schedule2_payload
	print Schedule3_payload
	print Ratio_payload
	port.writeSchedule1_payload
	print "......30%"
	time.sleep(2)
	port.write(Schedule2_payload)
	print "............60%"
	time.sleep(2)
	port.write(Schedule3_payload)
	print "..............80%"
	time.sleep(2)
	port.write(Ratio_payload)
	print "....................DONE!!!!!!"
    print "Setting the time..."
    time.sleep(2)
    port.write(Time_payload)
	print "Now, re-run the program please!"
	time.sleep(2)
    exit()

print "AQI/ppm  Humid/RTH%  Temperature/℃  Baro/Pa  CPU-Temp/℃  CPU-Used/%   RAM-Used/%"


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
        try:
            rcv = readlineCR(port)
            rcv_split = rcv.split(",")
            dust_payload = {'value':rcv_split[1]}
            humid_payload = {'value':rcv_split[2]}
            temp_payload = {'value':rcv_split[3]}
            baro_payload = {'value':filter(str.isdigit, rcv_split[4])}
	
        #有些时候节点会发过来一些很奇怪的数据，这时可能是它死机或出错了，所以这里就发一个指令让它重启一下试试。
        except IndexError:
            port.write("8,1\r\n")
            print "***Caught an error or unreadable data from the node, rebooting the node by default."
            time.sleep(5)
            rcv = readlineCR(port)
            rcv_split = rcv.split(",")
            dust_payload = {'value':rcv_split[1]}
            humid_payload = {'value':rcv_split[2]}
            temp_payload = {'value':rcv_split[3]}
            baro_payload = {'value':filter(str.isdigit, rcv_split[4])}
	
        #上传灰尘传感器数据
        r=requests.post(dust_apiurl, headers=apiheaders, data=json.dumps(dust_payload))
        print rcv_split[1],
	print "      ",
        #上传湿度传感器数据
        r=requests.post(humid_apiurl, headers=apiheaders, data=json.dumps(humid_payload))
        print rcv_split[2],
        print "      ",
        #上传温度传感器数据
        r=requests.post(temp_apiurl, headers=apiheaders, data=json.dumps(temp_payload))
        print rcv_split[3],
        print "         ",
        #上传气压传感器数据
        r=requests.post(baro_apiurl, headers=apiheaders, data=json.dumps(baro_payload))
        print filter(str.isdigit, rcv_split[4]),
        print "      ",

        #上传cpu温度
        cpu_temp=getcputemperature()
        cputemp_payload={'value':cpu_temp}
        r=requests.post(cputemp_apiurl, headers=apiheaders, data=json.dumps(cputemp_payload))
        print cpu_temp,
        print "      ",
	
	

    
        #上传cpu占用率及内存使用率
        tempcpuused=getcpuused()
  	
        for cpuline in tempcpuused:
            if cpuline[:3]=="%Cp":
                cpulineused=cpuline.split(":")[1].split(",")[0].split(" ")[-2]
                cpuused_payload={'value':cpulineused}
                r=requests.post(cpuused_apiurl, headers=apiheaders, data=json.dumps(cpuused_payload))
                print cpulineused,
                print "      ",

            if "Mem:" in cpuline:
               #提取数值，仅用字符串操作时，发现在数值前后有多个不可见字符，这里没怎么搞清楚这些字符是些什么
                memlineused=cpuline.split(":")[1].split(",")[1].strip("used").split(" ")[-2]
                memlinetotal=cpuline.split(":")[1].split(",")[0].strip("total").split(" ")[-2]
                memeryusedratio=float(str(memlineused))/float(str(memlinetotal))
                memeryusedratiostr="%.2f"%(memeryusedratio*100)
                memeryused_payload={'value':memeryusedratiostr}
                r=requests.post(memeryused_apiurl, headers=apiheaders, data=json.dumps(memeryused_payload))
                
                print memeryusedratiostr
                
        time.sleep(1)
