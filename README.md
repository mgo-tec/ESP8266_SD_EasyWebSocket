# ESP8266_SD_EasyWebSocket BETA 1.49
Simple library for WebSocket communication with ESP-WROOM-02(ESP8266) and smartphone browser.  
This requires the Arduino core for ESP8266 WiFi chip library.   
https://github.com/esp8266/arduino  
This use SD card (SPI).  

My Blog: https://www.mgo-tec.com
# Change log:
(1.49)   
Added a function to GET Web articles by https (SSL).  
Along with that, include WiFiClientSecure.h.  
Memory reduced sample sketch.  
Other minor fixes.  
  
-NEW Class-  
EWS_https_Web_Get  
(Attention !: Consumes a lot of memory.)  
  
(1.47)  
I added a function that can divide the Websocket header file and include the automatically acquired local IP address.  
EWS_Dev_AutoLIP_HandShake

(1.45)  
A watchdog timer of ESP8266 to create a grace period to operate, has been added here and there yield ().  
As a result, I think the operation is stable.
Sample sketch also has been corrected.  

-NEW class-  
EWS_BrowserReceiveTextTag2  
EWS_Status_Text2  
EWS_WebSocket_Reconnection_Button2  
EWS_Close_Button2  
EWS_Window_ReLoad_Button2  

(1.42)  
Fixed ESP8266DataReceive_SD_write class.
  
(1.41)  
*Upgraded EasyWebSocket beta 1.39 library.  
Bug fix etc...  
  
#【更新履歴】(Japanese)
(1.49)  
Web記事を https ( SSL )でGETする関数を追加。  
それに伴い、WiFiClientSecure.h をインクルード。  
サンプルスケッチの使用メモリを削減した。  
その他、軽微な修正。  
  
-NEW Class-  
EWS_https_Web_Get  
(この関数はメモリを多く消費するので注意)  
  
(1.47)  
以下の関数を追加  

EWS_Dev_AutoLIP_HandShake  

WebSocket用のHTMLヘッダファイルを分割し、ローカルIPアドレスを自動取得して盛り込めるようにしました。  
  
(1.45)  
ESP8266のウォッチドッグタイマを作動させる猶予時間を作るために、所々 yield() を追加しました。  
それにより、動作が安定したと思います。  
サンプルスケッチも修正しました。

-NEW class-  
EWS_BrowserReceiveTextTag2  
EWS_Status_Text2  
EWS_WebSocket_Reconnection_Button2  
EWS_Close_Button2  
EWS_Window_ReLoad_Button2  

(1.42)  
ESP8266DataReceive_SD_write関数を修正しました。  

(1.41)  
当方のEasyWebSocket beta 1.39 ライブラリをSPI接続のSDカードでできるように更新。SPIFFSは使えません。  
SPIFFSよりも速いです。  
細かなバグやライブラリ再編、ボタンデザイン変更など。  

# Credits and license
*Licensed under the GNU LESSER GENERAL PUBLIC LICENSE Version 2.1

Copyright (c) 2016 Mgo-tec  
This library improvement collaborator is Mr.Visyeii.  
  
This library is used by the Arduino IDE(Tested in ver1.6.11).  
This library is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public
License as published by the Free Software Foundation; either
version 2.1 of the License, or (at your option) any later version.  
This library is NO WARRANTY.  
  
Reference LGPL-2.1 license statement --> https://opensource.org/licenses/LGPL-2.1  
  
Reference Blog --> https://www.mgo-tec.com  
  
The esp8266 core for Arduino(Tested in ver2.3.0) --> https://github.com/esp8266/Arduino  
Released under the GNU LESSER GENERAL PUBLIC LICENSE Version 2.1  
  
ESP8266WiFi.h - Included WiFi library for esp8266  
WiFiServer.cpp - The library modification  
Copyright (c) 2014 Ivan Grokhotkov.  
This file is part of the esp8266 core for Arduino environment.  
Released under the GNU LESSER GENERAL PUBLIC LICENSE Version 2.1  
  
Hash.h - Included library  
Copyright (c) 2015 Markus Sattler.  
This file is part of the esp8266 core for Arduino environment.  
Released under the GNU LESSER GENERAL PUBLIC LICENSE Version 2.1  
  
FS.h(SPIFFS-File system) - Included library  
-->https://github.com/esp8266/arduino-esp8266fs-plugin  
Copyright (c) 2015 Ivan Grokhotkov. All rights reserved.  
Released under the GNU LESSER GENERAL PUBLIC LICENSE Version 2.1  
  
# My Blog: 
Other usage is Japanese, please visit my blog.  
https://www.mgo-tec.com