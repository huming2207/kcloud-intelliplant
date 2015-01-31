# kcloud-intelliplant
One of the sub-projects of Shenzhen Highschool of Science KCloud.
一个深圳科学高中“科高云”项目的子项目

=========
Overview
=========
The IntelliPlant project is one of the sub-projects of Shenzhen Highschool of Science KCloud. 

IntelliPlant 是一个深圳科学高中“科高云”项目的子项目

It's an Arduino based open source crop auto-managing system. 

这是一个基于Arduino的开源农作物管理系统

The project mainly maintained by Jackson Ming Hu in KGTCU, Techonology Clubs Union of Shenzhen Highschool of Science.

此项目主要由深圳科学高中技术社团联合会（IT社）的 胡铭 负责维护更新。

It has two parts, one is server side, the other is client side. The server is an Arduino Uno/ProMini and the client is Arduino Mega.

它包括两个部分，一个是服务端，一个是客户端，服务端用Arduino Uno或ProMini，客户端用Arduino Mega。

The server has a temperature & humidity sensor , an air pressure sensor and an air dust sensor and it controls the pump with a relay

服务端有一个温湿度传感器、一个气压传感器和一个大气粉尘传感器。

and it will automatically calculate the water capacity by the weather condition.

并且它能依据当天天气情况自动计算植物灌溉水量。

The client can get the server's data by wireless UART serial port and then display the data on its screen and upload the data to Yeelink Cloud Platform.

客户端通过无线串口透传模块传输数据，并将实时天气情况显示出来并发送到YeeLink物联网平台上。


=========
TO BE continued...
=========

