# kcloud-intelliplant
One of the sub-projects of Shenzhen Highschool of Science KCloud.

一个深圳科学高中“科高云”项目的子项目

=========
Overview 概览
=========
The IntelliPlant project is one of the sub-projects of Shenzhen Highschool of Science KCloud. 

It's an Arduino based open source crop auto-managing system. 

The project mainly maintained by Jackson Ming Hu in KGTCU, Techonology Clubs Union of Shenzhen Highschool of Science.

It has two parts, one is the master side, the other is slave side. The server is an Arduino Uno/ProMini and the client is Arduino Mega.

The server has a temperature & humidity sensor , an air pressure sensor and an air dust sensor and it controls the pump with a relay

and it will automatically calculate the water capacity by the weather condition.

The client can get the server's data by wireless UART serial port and then display the data on its screen and upload the data to Yeelink Cloud Platform.

IntelliPlant 是一个深圳科学高中“科高云”项目的子项目,这是一个基于Arduino的开源农作物管理系统，此项目主要由深圳科学高中技术社团联合会（IT社）的 胡铭 负责维护更新。

它包括两个部分，一个是主机，一个是从机，主机用Arduino Uno或ProMini，从机用Arduino Mega。

服务端有一个温湿度传感器、一个气压传感器和一个大气粉尘传感器，并且它能依据当天天气情况自动计算植物灌溉水量。

客户端通过无线串口透传模块传输数据，并将实时天气情况显示出来并发送到YeeLink物联网平台上。


=========
Development Environment Requirements 开发环境需求
=========

1. The PC client must use Virtual Studio version newer than 2012 or 2013, otherwise it will reports many strange mistakes.

2. The Arduino SDK must use version 1.0.x, otherwise the IIC LCD does not work.

1. PC客户端部分必须使用高于VS2012和2013版本编译开发，否则会报错而且报的错很奇怪。

2. Arduino SDK 必须使用1.0.x版本，否则IIC LCD不能正常工作。