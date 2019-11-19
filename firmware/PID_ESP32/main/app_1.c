#include "includes.h"
#include "pidlib.h"

#ifdef CORE1_TASK_DEF

#define EXAMPLE_ESP_WIFI_SSID      "ESP32_WIFI"
#define EXAMPLE_ESP_WIFI_PASS      "esp32wifi"

#ifndef CONFIG_MAX_STA_CONN
#define CONFIG_MAX_STA_CONN 4
#endif


void uint12_to_volt(int num, char buff[], int tam);
void volt_to_uint12(pid_const_t *num, char buff[]);

int clientSock;

/* FreeRTOS event group to signal when we are connected*/
static EventGroupHandle_t wifi_event_group;


static esp_err_t event_handler(void *ctx, system_event_t *event){
	switch(event->event_id) {
		case SYSTEM_EVENT_STA_START:
		esp_wifi_connect();
		break;
	case SYSTEM_EVENT_STA_GOT_IP:
		xEventGroupSetBits(wifi_event_group, 1);
		break;
	case SYSTEM_EVENT_STA_DISCONNECTED:
		esp_wifi_connect();
		xEventGroupClearBits(wifi_event_group, 1);
		break;
	default:
		break;
	}
	return ESP_OK;
}

static void wifi_init_softap(){
	wifi_event_group = xEventGroupCreate();

	tcpip_adapter_init();
	esp_event_loop_init(event_handler, NULL);

	wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
	esp_wifi_init(&cfg);
	wifi_config_t wifi_config = {
		.ap = {
		.ssid = EXAMPLE_ESP_WIFI_SSID,
		.ssid_len = strlen(EXAMPLE_ESP_WIFI_SSID),
		.password = EXAMPLE_ESP_WIFI_PASS,
		.max_connection = CONFIG_MAX_STA_CONN,
		.authmode = WIFI_AUTH_WPA_WPA2_PSK
		},
	};
	if (strlen(EXAMPLE_ESP_WIFI_PASS) == 0) 
		wifi_config.ap.authmode = WIFI_AUTH_OPEN;

	esp_wifi_set_mode(WIFI_MODE_AP);
	esp_wifi_set_config(ESP_IF_WIFI_AP, &wifi_config);
	esp_wifi_start();

}

void sock_read_task(void *arg){

	pid_type *pid;
	pid = (pid_type*)arg;
	char data_recv[8];
	while(recv(clientSock, data_recv, 2000, 0))
		volt_to_uint12(&(pid->ref), data_recv);
	vTaskDelete(NULL);
}

void core1_task(void *arg){

	pid_type *pid;
	pid = (pid_type*)arg;

	esp_err_t ret = nvs_flash_init();
	if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND) {
		nvs_flash_erase();
		ret = nvs_flash_init();
	}

	wifi_init_softap();

	//socket
	struct sockaddr_in clientAddress;
	struct sockaddr_in serverAddress;

	// Create a socket that we will listen upon.
	int sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if(sock < 0)
		return;

	// Bind our server socket to a port.
	serverAddress.sin_family = AF_INET;
	//serverAddress.sin_addr.s_addr = htonl("192.168.4.1");
	serverAddress.sin_port = htons(1234);
	inet_aton("192.168.4.1", &serverAddress.sin_addr);
	int rc  = bind(sock, (struct sockaddr *)&serverAddress, sizeof(serverAddress));
	if(rc < 0)
		return;

	// Flag the socket as listening for new connections.
	rc = listen(sock, 5);
	if(rc < 0)
		return;

	socklen_t clientAddressLength = sizeof(clientAddress);
	clientSock = accept(sock, (struct sockaddr *)&clientAddress, &clientAddressLength);
	if(clientSock < 0)
		return;

	xTaskCreatePinnedToCore(&sock_read_task, "sock_read_task", 1024 * 8, (void*)pid, 5, NULL, 1);

	char data_send[8];

	while(1){
		uint12_to_volt(pid->input, data_send, 8);
		send(clientSock, data_send, strlen(data_send), 0);
		vTaskDelay(1000 / portTICK_PERIOD_MS);
	}

	vTaskDelete(NULL);

}

void uint12_to_volt(int num, char buff[], int tam){
	int volt = num * 3.3 / 4095;
	if(volt > tam - 7)
		return;
	float resto = ((float)num * 3.3 / 4095.0) - volt;
	do {
		*buff++ = (char)((int)volt + 48);
	}	while(volt /= 10);
	*buff++ = '.';
	*buff++ = (char)(resto * 10 + 48);
	*buff++ = (char)(((int)(resto * 100) % 10) + 48);
	*buff++ = 'V';
	*buff++ = '\n';
	*buff++ = '\0';
}



void volt_to_uint12(pid_const_t *num, char buff[]){

	float volt = 0;
	while(*buff >= 48 && *buff < 58)			//integer part
		volt = volt * 10 + (float)((int)*buff++ - 48);
	

	if(*buff != '\0' && *buff++ == '.'){					//float part
		int div = 1;
		while(*buff >= 48 && *buff < 58)
			volt += (float)((int)*buff++ - 48) / (div *= 10);
	}

	else
		return;

	*num = volt * 4096 / 3.3;
}

#endif
