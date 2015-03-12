# kcloud-intelliplant
One of the sub-projects of Shenzhen Highschool of Science KCloud.

一个深圳科学高中“科高云”项目的子项目

=========
Overview 概览
=========
The IntelliPlant project is one of the sub-projects of Shenzhen High School of Science KCloud. 

It's an Arduino based open source crop auto-managing system. 

The project mainly maintained by Jackson Ming Hu in KGTCU, Techonology Clubs Union of Shenzhen High School of Science.

It has two parts, one is the master (controller) side, the other is slave (arduino nodes) side. The node is an Arduino Uno/ProMini and the client is Arduino Mega.

The node has a temperature & humidity sensor , an air pressure sensor and an air quality sensor and it controls the pump with a relay

and it will automatically calculate the water capacity by the weather condition.

The controller can get the node's data by wireless UART serial port and then display the data on its screen and upload the data to Yeelink Cloud Platform.

IntelliPlant 是一个深圳科学高中“科高云”项目的子项目,这是一个基于Arduino的开源农作物管理系统，此项目主要由深圳科学高中技术社团联合会（IT社）的 胡铭 负责维护更新。

它包括两个部分，一个是主控器，一个是节点，主机用Arduino Uno或ProMini，从机用Arduino Mega。

每个节点有一个温湿度传感器、一个气压传感器和一个空气质量传感器，并且它能依据当天天气情况自动计算植物灌溉水量。

主控器通过无线串口透传模块传输数据，并将实时天气情况显示出来并发送到YeeLink物联网平台上。


=========
Development Environment Requirements 开发环境需求
=========

1. The PC client must use Virtual Studio version newer than 2012 or 2013, otherwise it will reports many strange mistakes.
	PC客户端部分必须使用高于VS2012和2013版本编译开发，否则会报错而且报的错很奇怪。

2. Recommended development environment:
    推荐开发环境：
		--> Arduino IDE 1.60 for arduino node     Arduino IDE 版本1.60   
		--> Virtual Studio 2013r3 Community Edition   VS2013r3社区版
		--> Debian 7.x or OpenWrt 14.04 "Barrier Breaker" for Raspberry Pi with Python 2.7    树莓派 Debian 7 或 OpenWrt 14.04 BB 并带有 Python 2.7 开发环境




=========
About this project 关于本项目
=========

项目作者：深圳科学高中技术类社团联合会 IT社 

项目主管：胡铭 <huming2207@gmail.com>

项目参与者：胡铭 梁君豪 李一川 


Arduino 部分开发：胡铭

计算机软件部分开发与建议：胡铭 梁君豪

硬件与外观设计：李一川


本项目为开源项目，所有代码受GPLv2协议保护，严禁商用。


Project author: IT Club, Technical Club Union of Shenzhen Highschool of Science

			
Project administrator: Jackson Ming Hu <huming2207@gmail.com>

Arduino software development: Jackson Ming Hu

PC Client development & advising: Jackson Ming Hu, Junhao Liang

Hardware design: Yichuan Lee


This project is a open source project and all the source code are protected by GPLv2 licence.
