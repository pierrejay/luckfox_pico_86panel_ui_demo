#ifndef _LCUKFOX_86PANEL_UI_H
#define _LCUKFOX_86PANEL_UI_H

#ifdef __cplusplus
extern "C" {
#endif

/*********************
 *      INCLUDES
 *********************/
#include <unistd.h>
#include <netdb.h>
#include <netinet/in.h>
#include <net/route.h>
#include <net/if_arp.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <dirent.h>
#include <sys/time.h>
#include <sys/un.h>
#include <sys/prctl.h>
#include <sys/socket.h>
#include <signal.h>
#include <time.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/stat.h>

#include "lvgl/lvgl.h"

/*********************
 *      DEFINES
**********************/
#define WPA_FILE_PATH "/etc/wpa_supplicant.conf"
#define LUCKFOX_PICO_86PANEL_W "Luckfox Pico 86Panel W"
#define MAX_MUSIC_LIST_LEN 1024

#define IP_SIZE 64
#define MAX_CONF_LEN 64
#define MAX_LINE_LEN 256
#define MAX_NETWORKS 10
#define MAX_FILENAME_LEN 256
#define MAX_CMD_LEN 256

#define MUSIC_DIR_PATH "/music"

/**********************
 *      TYPEDEFS
 **********************/
typedef struct {
    char ssid[MAX_CONF_LEN];
    int signal_level;
    char flags[MAX_CONF_LEN];
} wifi_network;

typedef struct {
    char ssid[MAX_CONF_LEN];
    char passwd[MAX_CONF_LEN];
} wifi_connect_info_t;

struct Music_Node {
    char filename[MAX_FILENAME_LEN];
    int id;
    struct Music_Node* prev;
    struct Music_Node* next;
};

/**********************
 *  GLOBAL VARIABLES
**********************/
/*Device Model*/
extern char device_model[32];

/*SCREEN: ui_ScreenMain*/
extern lv_obj_t * ui_ScreenMain;
extern lv_obj_t * ui_PanelWifi;
extern lv_obj_t * ui_ImageWifi;
extern lv_obj_t * ui_LabelWifiName;
extern lv_obj_t * ui_LabelWifiIP;
extern lv_obj_t * ui_LabelWIP;
extern lv_obj_t * ui_LabelTime;
extern lv_obj_t * ui_PanelEth;
extern lv_obj_t * ui_ImageEth;
extern lv_obj_t * ui_LabelEth;
extern lv_obj_t * ui_LabelEthIP;
extern lv_obj_t * ui_LabelNetIP;
extern lv_obj_t * ui_LabelDate;
extern lv_obj_t * ui_ImageTop;

/*SCREEN: ui_ScreenMain*/
extern lv_obj_t * ui_ScreenWpa;
extern lv_obj_t * ui_PanelList;
extern lv_obj_t * ui_DropdownSSID;
extern lv_obj_t * ui_LabelWLAN;
extern lv_obj_t * ui_PanelBtn;
extern lv_obj_t * ui_ButtonDiscon;
extern lv_obj_t * ui_ImageDiscon;
extern lv_obj_t * ui_ButtonScan;
extern lv_obj_t * ui_ImageScan;
extern lv_obj_t * ui_ButtonBack;
extern lv_obj_t * ui_ImageBack;
extern lv_obj_t * ui_ButtonConnect;
extern lv_obj_t * ui_ImageConnect;
extern lv_obj_t * ui_LabelMGMT;
extern lv_obj_t * ui_LabelPW;
extern lv_obj_t * ui_TextAreaPW;
extern lv_obj_t * ui_LabelRSSI;
extern lv_obj_t * ui_LabelSSID;
extern lv_obj_t * ui_TextAreaSSID;
extern lv_obj_t * ui_TextAreaRSSI;
extern lv_obj_t * ui_TextAreaMgnt;
extern lv_obj_t * ui_Keyboard1;

// SCREEN: ui_ScreenPlayer
extern lv_obj_t * ui_ScreenPlayer;
extern lv_obj_t * ui_PanelRelay0;
extern lv_obj_t * ui_LabelRelay0;
extern lv_obj_t * ui_PanelRelay1;
extern lv_obj_t * ui_LabelRelay1;
extern lv_obj_t * ui_PanelMusicPlayer;
extern lv_obj_t * ui_ImgButtonPrev;
extern lv_obj_t * ui_LabelMusicPlayer;
extern lv_obj_t * ui_ImgButtonNext;
extern lv_obj_t * ui_SliderMusic;
extern lv_obj_t * ui_ImgButtonList;
extern lv_obj_t * ui_ImagePlay;
extern lv_obj_t * ui_ImageMusicMode;
extern lv_obj_t * ui_ImageSoundDown;
extern lv_obj_t * ui_ImageSoundUp;
extern lv_obj_t * ui_ImageMusicClose;
extern lv_obj_t * ui_RollerMusic;
extern lv_obj_t * ui_PanelBoard;
extern lv_obj_t * ui_LabelMusicList;
extern lv_obj_t * ui_initial_actions0;

/**********************
 *  ASSETS
**********************/
LV_IMG_DECLARE(ui__temporary_image);
LV_IMG_DECLARE(ui_img_luckfox_logo_png);    // assets/luckfox logo.png
LV_IMG_DECLARE(ui_img_icon_wifi_on_png);    // assets/icon_wifi_on.png
LV_IMG_DECLARE(ui_img_icon_eth_off_png);    // assets/icon_eth_off.png
LV_IMG_DECLARE(ui_img_icon_top17_png);    // assets/icon_top17.png
LV_IMG_DECLARE(ui_img_icon_music_shuffle_png);    // assets/icon_music_shuffle.png
LV_IMG_DECLARE(ui_img_discon_png);    // assets/Discon.png
LV_IMG_DECLARE(ui_img_icon_wifi_off_png);    // assets/icon_wifi_off.png
LV_IMG_DECLARE(ui_img_scan_png);    // assets/Scan.png
LV_IMG_DECLARE(ui_img_back_png);    // assets/Back.png
LV_IMG_DECLARE(ui_img_icon_eth_on_png);    // assets/icon_eth_on.png
LV_IMG_DECLARE(ui_img_connect_png);    // assets/Connect.png
LV_IMG_DECLARE(ui_img_icon_music_pre_png);    // assets/icon_music_pre.png
LV_IMG_DECLARE(ui_img_icon_music_next_png);    // assets/icon_music_next.png
LV_IMG_DECLARE(ui_img_icon_music_list_png);    // assets/icon_music_list.png
LV_IMG_DECLARE(ui_img_icon_music_list_play_png);    // assets/icon_music_list.png
LV_IMG_DECLARE(ui_img_icon_music_play_png);    // assets/icon_music_play.png
LV_IMG_DECLARE(ui_img_icon_music_pause_png);    // assets/icon_music_pause.png
LV_IMG_DECLARE(ui_img_icon_music_cycle_all_png);    // assets/icon_music_cycle_all.png
LV_IMG_DECLARE(ui_img_icon_music_cycle_one_png);    // assets/icon_music_cycle_one.png
LV_IMG_DECLARE(ui_img_icon_sound_donw_png);    // assets/icon_sound_donw.png
LV_IMG_DECLARE(ui_img_icon_sound_up_png);    // assets/icon_sound_up.png
LV_IMG_DECLARE(ui_img_icon_music_close_png);    // assets/icon_music_close.png

LV_FONT_DECLARE(ui_font_HarmonyOS200);
LV_FONT_DECLARE(ui_font_HarmonyOS48);

/**********************
 *  FUNCTIONS
 **********************/
void ui_init(void);

/*SCREEN: ui_ScreenMain*/
void ui_ScreenMain_screen_init(void);
void ui_event_ScreenMain(lv_event_t * e);
void ui_event_PanelWifi(lv_event_t * e);

/*SCREEN: ui_ScreenWpa*/
void ui_ScreenWpa_screen_init(void);
void ui_event_DropdownSSID(lv_event_t * e);
void ui_event_ButtonDiscon(lv_event_t * e);
void ui_event_ButtonScan(lv_event_t * e);
void ui_event_ButtonBack(lv_event_t * e);
void ui_event_ButtonConnect(lv_event_t * e);
void ui_event_TextAreaPW(lv_event_t * e);
void ui_event_TextAreaSSID(lv_event_t * e);
void ui_event_Keyboard1(lv_event_t * e);

/*SCREEN: ui_ScreenPlayer*/
void ui_ScreenPlayer_screen_init(void);
void ui_event_ScreenPlayer(lv_event_t * e);
void ui_event_PanelRelay0(lv_event_t * e);
void ui_event_PanelRelay1(lv_event_t * e);
void ui_event_ImgButtonPrev(lv_event_t * e);
void ui_event_ImgButtonNext(lv_event_t * e);
void ui_event_SliderMusic(lv_event_t * e);
void ui_event_ImgButtonList(lv_event_t * e);
void ui_event_ImagePlay(lv_event_t * e);
void ui_event_ImageMusicMode(lv_event_t * e);
void ui_event_ImageMusicClose(lv_event_t *e);
void ui_event_RollerMusic(lv_event_t * e);
void ui_event_PanelBoard(lv_event_t * e);

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif
