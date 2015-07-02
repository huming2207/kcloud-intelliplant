# HuStudio IntelliPlant
One of the sub-projects of Shenzhen Highschool of Science former "KCloud" private cloud service project.

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

=========
Development Environment Requirements 
=========

1. The PC client must use Virtual Studio version newer than 2012 or 2013, otherwise it will reports many strange mistakes.

2. Recommended development environment:

		--> Arduino IDE 1.60 for arduino node
		
		--> Virtual Studio 2013r3
		
		--> Debian 7.x or OpenWrt 14.04 "Barrier Breaker" for Raspberry Pi with Python 2.7   




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
