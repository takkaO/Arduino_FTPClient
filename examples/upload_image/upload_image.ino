/******************************************************************************

ESP32-CAM remote image access via FTP. Take pictures with ESP32 and upload it via FTP making it accessible for the outisde network.
Leonardo Bispo
July - 2019
https://github.com/ldab/ESP32_FTPClient

Distributed as-is; no warranty is given.

******************************************************************************/
#include "Arduino.h"
#include "octocat.h"
#include <Arduino_FTPClient.h>
#include <WiFi.h>
#include <WiFiClient.h>

#define WIFI_SSID "ASUS_image"
#define WIFI_PASS "0236443222"

char ftp_server[] = "192.168.0.220";
char ftp_user[]   = "admin";
char ftp_pass[]   = "admin";

// you can pass a FTP timeout and debbug mode on the last 2 arguments
Arduino_FTPClient ftp(ftp_server, ftp_user, ftp_pass, 5000, 2);
WiFiClient client;
WiFiClient data_client;

void setup() {
	Serial.begin(115200);
	ftp.setClients(client, data_client);
	//ftp.setClient(client);
	//ftp.setDataClient(data_client);

	WiFi.begin(WIFI_SSID, WIFI_PASS);

	Serial.println("Connecting Wifi...");
	while (WiFi.status() != WL_CONNECTED) {
		delay(500);
		Serial.print(".");
	}
	Serial.println("");
	Serial.print("IP address: ");
	Serial.println(WiFi.localIP());

	ftp.openConnection();

	// Get directory content
	// ftp.initFile("Type A");
	// String list[128];
	// ftp.changeWorkDir("/public_html/zyro/gallery_gen/");
	// ftp.contentList("", list);
	// Serial.println("\nDirectory info: ");
	// for (int i = 0; i < sizeof(list); i++) {
	// 	if (list[i].length() > 0)
	// 		Serial.println(list[i]);
	// 	else
	// 		break;
	// }

	// Make a new directory
	ftp.initFile("Type A");
	ftp.makeDir("my_new_dir");

	// Create the new file and send the image
	ftp.changeWorkDir("my_new_dir");
	ftp.initFile("Type I");
	ftp.newFile("octocat.jpg");
	ftp.writeData(octocat_pic, sizeof(octocat_pic));
	ftp.closeFile();

	// Create the file new and write a string into it
	ftp.initFile("Type A");
	ftp.newFile("hello_world.txt");
	ftp.write("Hello World");
	ftp.closeFile();

	ftp.closeConnection();
}

void loop() {
}