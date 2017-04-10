/*
SD_WebSocket for ESP-WROOM-02 ( ESP8266 ) Sample Sketch
for Beta version 1.50
---> https://www.mgo-tec.com
Please rewrite their own the ssid and password.
Please rewrite their own local IP address of "/data/spiffs_01.txt" in the sketch folder.
Use the SD card (SPI), please upload the ews_head.txt file to SD/EWS/ folder.
*/
#include <SD_EasyWebSocket.h>
#include <SD.h>

const uint8_t sclk = 14; //SDcard SCLK
const uint8_t mosi =13; //Master Output Slave Input ESP8266=Master SD = slave 
const uint8_t miso =12; //Master Input Slave Output
const uint8_t cs_SD = 15; //SDcard CS(ChipSelect)

const char* ssid = "xxxx";
const char* password = "xxxx";

const char* HTM_head_file1 = "EWS/LIPhead1.txt"; //HTMLヘッダファイル1
const char* HTM_head_file2 = "EWS/LIPhead2.txt"; //HTMLヘッダファイル2
const char* HTML_body_file = "EWS/dummy.txt"; //HTML body要素ファイル（ここではダミーファイルとしておく）
const char* dummy_file = "EWS/dummy.txt"; //HTMLファイル連結のためのダミーファイル

long ESP_send_Time;

byte cnt = 0;

SD_EasyWebSocket ews;

IPAddress LIP; //ローカルIPアドレス自動取得用

String ret_str;
String txt = "text send?";
bool get_http_req_status = false;

int PingSendTime = 30000;

#define ledPin1 16 //GPIO #16
#define ledPin2 5 //GPIO #5
#define ledPin3 4 //GPIO #4

void setup() 
{
  ews.AP_Connect(ssid, password);
  delay(1000);
  
  LIP = WiFi.localIP(); //ESP8266のローカルIPアドレスを自動取得

  Serial.println(); Serial.println("Initializing SD card...");
  if (!SD.begin(cs_SD,40000000)) {
    Serial.println("Card failed, or not present");
    return;
  }
  Serial.println("card initialized. OK!");
  
  ESP_send_Time = millis();
}

void loop() {
  websocket_handshake();
  
  String str;

  if(ret_str != "_close"){
    if(millis()-ESP_send_Time > 300){//Data transmission from WROOM (ESP8266) every 500ms
      if(cnt > 3){
        cnt = 0;
      }
      switch(cnt){
        case 0:
          str = txt;
          break;
        case 1:
          str = "WebSockets";
          break;
        case 2:
          str = "Hello!!";
          break;
        case 3:
          str = "World!!";
          break;
      }
      ews.EWS_ESP8266_Str_SEND(str, "wroomTXT");
      ESP_send_Time = millis();
      cnt++;
    }

    ret_str = ews.EWS_ESP8266CharReceive(PingSendTime);
    if(ret_str != "\0"){
      Serial.println(ret_str);
      if(ret_str != "Ping"){
        if(ret_str[0] != 't'){
          int ws_data = (ret_str[0]-0x30)*100 + (ret_str[1]-0x30)*10 + (ret_str[2]-0x30);
          switch(ret_str[4]){
            case 'B':
              LED_PWM(1, ledPin1, floor(ws_data/2));
              break;
            case 'G':
              LED_PWM(1, ledPin2, floor(ws_data/2));
              break;
            case 'R':
              LED_PWM(1, ledPin3, floor(ws_data/2));
              break;
            case '_':
              LED_PWM(2, 0, floor(ws_data/2));
              break;
            case 'b':
              LED_PWM(1, ledPin1, ws_data);
              break;
            case 'g':
              LED_PWM(1, ledPin2, ws_data);
              break;
            case 'r':
              LED_PWM(1, ledPin3, ws_data);
              break;
            case '-':
              LED_PWM(2, 0, ws_data);
              break;
            case 'A':
              LED_PWM(3, 0, ws_data);
              break;
            case 'O':
              LED_PWM(4, 0, ws_data);
              break;
          }
        }else if(ret_str[0] == 't'){
          txt = ret_str.substring(ret_str.indexOf('|')+1, ret_str.length()-1);
          Serial.println(txt);
        }
      }
    }
  }else if(ret_str == "_close"){
    ESP_send_Time = millis();
    ret_str = "";
  }
	yield(); //これ重要かも
}

//**************************************************************
void LED_PWM(byte Led_gr, byte Led_Pin, int data_i)
{
Serial.println(data_i);
  switch(Led_gr){
    case 1:
      analogWrite(Led_Pin, data_i);
      break;
    case 2:
      if(data_i < 34){
        analogWrite(ledPin1, data_i*8);
        analogWrite(ledPin2, 0);
        analogWrite(ledPin3, 0);
      }else if(data_i > 33 && data_i < 67){
        analogWrite(ledPin2, (data_i-33)*8);
        analogWrite(ledPin1, 0);
        analogWrite(ledPin3, 0);
      }else if(data_i > 66){
        analogWrite(ledPin3, (data_i-66)*7.78);
        analogWrite(ledPin1, 0);
        analogWrite(ledPin2, 0);
      }
      break;
    case 3:
      analogWrite(ledPin1, 100);
      analogWrite(ledPin2, 100);
      analogWrite(ledPin3, 100);
      break;
    case 4:
      analogWrite(ledPin1, 0);
      analogWrite(ledPin2, 0);
      analogWrite(ledPin3, 0);
      break;
  }
}
//************************* Websocket handshake **************************************
void websocket_handshake(){
  String html_str1, html_str2, html_str3, html_str4, html_str5, html_str6, html_str7;

  get_http_req_status = ews.Get_Http_Req_Status();
  
  if(get_http_req_status == true){
    //ver1.50では、HMTLは基本的にSDカード内のファイルに記述した方が良い
    html_str1 = "<body style='background:#000; color:#fff;'>\r\n";
    html_str1 += "<font size=3>\r\n";
    html_str1 += "ESP-WROOM-02(ESP8266)\r\n";
    html_str1 += "<br>\r\n";
    html_str1 += "SD_EasyWebSocket Beta1.45 Sample\r\n";
    html_str1 += "</font><br>\r\n";
    html_str1 += ews.EWS_BrowserSendRate();
    html_str1 += "<br>\r\n";
    html_str1 += ews.EWS_BrowserReceiveTextTag2("wroomTXT", "from WROOM DATA", "#555", 20,"green");
    html_str1 += "<br>\r\n";
    html_str1 += ews.EWS_Status_Text2("WebSocket Status","#555", 20,"#FF00FF");
    html_str1 += "<br><br>\r\n";
    html_str1 += ews.EWS_TextBox_Send("txt1", "Hello Easy WebSocket Beta1.3","送信");
    html_str1 += "<br><br>\r\n";
    html_str1 += "LED \r\n";
    html_str1 += ews.EWS_On_Momentary_Button("ALL", "全点灯", 65,25,15,"#000000","#AAAAAA");
    html_str1 += ews.EWS_On_Momentary_Button("OUT", "全消灯", 65,25,15,"#FFFFFF","#555555");
    html_str1 += "<br>\r\n";
    
    html_str2 += "<br>LED BLUE... Dim\r\n";
    html_str2 += ews.EWS_Canvas_Slider_T("BLUE",200,40,"#777777","#0000ff"); //CanvasスライダーはString文字列に２つまでしか入らない
    html_str2 += "<br>LED GREEN Dim\r\n";
    html_str2 += ews.EWS_Canvas_Slider_T("GREEN",200,40,"#777777","#00ff00"); //CanvasスライダーはString文字列に２つまでしか入らない
    
    html_str3 += "<br>LED RED..... Dim\r\n";
    html_str3 += ews.EWS_Canvas_Slider_T("RED",200,40,"#777777","#ff0000"); //CanvasスライダーはString文字列に２つまでしか入らない
    html_str3 += "<br><br>\r\n";
    html_str3 += ews.EWS_WebSocket_Reconnection_Button2("WS-Reconnect", "grey", 200, 40, "black" , 17);
    html_str3 += "<br><br>\r\n";  
    html_str3 += ews.EWS_Close_Button2("WS CLOSE", "#bbb", 150, 40, "red", 17);
    html_str3 += ews.EWS_Window_ReLoad_Button2("ReLoad", "#bbb", 150, 40, "blue", 17);
    html_str3 += "</body></html>\r\n";

    //WebSocket ハンドシェイク関数
    ews.EWS_HandShake_main(2, cs_SD, HTM_head_file1, HTM_head_file2, HTML_body_file, dummy_file, LIP, html_str1, html_str2, html_str3, html_str4, html_str5, html_str6, html_str7);
  }
}

