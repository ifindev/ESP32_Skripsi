# ESP32_Skripsi
Arduino code for ESP32 configuration as Wi-Fi Access Point (AP) and Station (STA). Also, STA is configured as web server that can handle Ajax request to refresh the measured RSSI data in the webpage. These programs are adapted and modified from https://circuits4you.com/ projects. See code for full description. 

This code is created for my final undergraduate thesis with the topic of indoor localization using Wi-Fi RSSI data. The `ESP32_AP` repo contain an arduino for configuring ESP32 as AP with custom SSID and password. The `ESP32_RSSI_Graph_webServer` repo contain the code for configuring ESP32 as STA and webserver. 

The webpage for displaying measurement values can be accessed by first configuring ESP32 as STA, then copying the printed IP Adress on the serial monitor. Measurement values can be downloaded as csv file for further processing. Also, the displayed value will be updated based on the latest measurement data using Ajax.

Example of visualized real-time data on the local web and downloaded csv file is shown below. Missing data was due to a temporary connection lost. 

![alt Visualized data](https://github.com/effendev/ESP32_Skripsi/blob/master/data1.jpeg "Visualized data in graph and table")
<p align="center">
	<b>Visualized data in graph and table</b><br>
	<br>
</p>

![alt CSV data](https://github.com/effendev/ESP32_Skripsi/blob/master/data2.jpeg "Downloaded CSV data")

<p align="center">
	<b>Downloaded CSV Data</b><br>
</p>

