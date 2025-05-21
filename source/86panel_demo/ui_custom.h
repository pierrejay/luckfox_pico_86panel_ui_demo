#ifndef _UI_CUSTOM_H
#define _UI_CUSTOM_H

#ifdef __cplusplus
extern "C" {
#endif

/*********************
 *      INCLUDES
 *********************/
#include "ui.h"

/**********************
 *  GLOBAL VARIABLES
**********************/
extern lv_timer_t * ui_Timer;
extern int timer_count;

extern struct wpa_ctrl *ctrl;
extern int network_count;
extern wifi_network networks[];

extern struct Music_Node *playing_music_node;  
extern struct Music_Node *playing_music_head;  

/**********************
 *      FUNCTIONS
 **********************/
void custom_init();

void main_timer_release();
void main_timer_init();

int wifi_disconnect(const char *interface);
void wifi_connect(const char* ssid, const char* password);
void wifi_scr_init();
int wifi_scanning_ssid();

int set_gpio(int gpio_pin, int val);
int gpio_export(int gpio_pin);
int gpio_out_direction(int gpio_pin);

void music_pause(int sta);
void music_set_pos(int music_id);
void music_set_mode(int mode);
void music_set_volume(int volume);
int music_scan_list(char *mp3_string);
int music_player_thread_init();
int music_player_thread_exit();
int music_app_init();
int music_app_quit();

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif
