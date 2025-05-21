/*********************
 *      INCLUDES
 *********************/
#include "ui.h"
#include "ui_custom.h"

/*********************
 *      DEFINES
 *********************/

/**********************
 *  GLOBAL VARIABLES
 *********************/
/*Device Model*/
char device_model[32];

/*SCREEN: ui_ScreenMain*/
lv_obj_t * ui_ScreenMain;
lv_obj_t * ui_PanelWifi;
lv_obj_t * ui_ImageWifi;
lv_obj_t * ui_LabelWifiName;
lv_obj_t * ui_LabelWifiIP;
lv_obj_t * ui_LabelWIP;
lv_obj_t * ui_LabelTime;
lv_obj_t * ui_PanelEth;
lv_obj_t * ui_ImageEth;
lv_obj_t * ui_LabelEth;
lv_obj_t * ui_LabelEthIP;
lv_obj_t * ui_LabelNetIP;
lv_obj_t * ui_LabelDate;
lv_obj_t * ui_ImageTop;

/*SCREEN: ui_ScreenWpa*/
lv_obj_t * ui_ScreenWpa;
lv_obj_t * ui_PanelList;
lv_obj_t * ui_DropdownSSID;
lv_obj_t * ui_LabelWLAN;
lv_obj_t * ui_PanelBtn;
lv_obj_t * ui_ButtonDiscon;
lv_obj_t * ui_ImageDiscon;
lv_obj_t * ui_ButtonScan;
lv_obj_t * ui_ImageScan;
lv_obj_t * ui_ButtonBack;
lv_obj_t * ui_ImageBack;
lv_obj_t * ui_ButtonConnect;
lv_obj_t * ui_ImageConnect;
lv_obj_t * ui_LabelMGMT;
lv_obj_t * ui_LabelPW;
lv_obj_t * ui_TextAreaPW;
lv_obj_t * ui_LabelRSSI;
lv_obj_t * ui_LabelSSID;
lv_obj_t * ui_TextAreaSSID;
lv_obj_t * ui_TextAreaRSSI;
lv_obj_t * ui_TextAreaMgnt;
lv_obj_t * ui_Keyboard1;

/*SCREEN: ui_ScreenPlayer*/
lv_obj_t * ui_ScreenPlayer;
lv_obj_t * ui_PanelRelay0;
lv_obj_t * ui_LabelRelay0;
lv_obj_t * ui_PanelRelay1;
lv_obj_t * ui_LabelRelay1;
lv_obj_t * ui_PanelMusicPlayer;
lv_obj_t * ui_ImgButtonPrev;
lv_obj_t * ui_LabelMusicPlayer;
lv_obj_t * ui_ImgButtonNext;
lv_obj_t * ui_SliderMusic;
lv_obj_t * ui_ImgButtonList;
lv_obj_t * ui_ImagePlay;
lv_obj_t * ui_ImageMusicMode;
lv_obj_t * ui_ImageSoundDown;
lv_obj_t * ui_ImageSoundUp;
lv_obj_t * ui_ImageMusicClose;
lv_obj_t * ui_RollerMusic;
lv_obj_t * ui_PanelBoard;
lv_obj_t * ui_LabelMusicList;
lv_obj_t * ui_initial_actions0;

/*Flags*/
static bool GestureFlag = true;
static bool CycleFlag   = false;
static bool scan_is_button_pressed = false;

/**********************
 *  STATIC FUNCTIONS
 **********************/
static void _ui_screen_change(lv_obj_t ** target, lv_scr_load_anim_t fademode, int spd, int delay, void (*target_init)(void))
{
    if(*target == NULL)
        target_init();
    lv_scr_load_anim(*target, fademode, spd, delay, false);
}

static void *wifi_connect_thread_handler(void *arg) 
{
    wifi_connect_info_t *wifi = (wifi_connect_info_t *)arg;

    wifi_connect(wifi->ssid, wifi->passwd);
    free(wifi);

    return NULL;
}

/**********************
 *  GLOBAL FUNCTIONS
 **********************/
void ui_event_ScreenMain(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);
    if(event_code == LV_EVENT_GESTURE &&  lv_indev_get_gesture_dir(lv_indev_get_act()) == LV_DIR_BOTTOM) {
        lv_indev_wait_release(lv_indev_get_act());
        _ui_screen_change(&ui_ScreenPlayer, LV_SCR_LOAD_ANIM_MOVE_BOTTOM, 300, 0, &ui_ScreenPlayer_screen_init);
    }
}

void ui_event_PanelWifi(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);
    if(event_code == LV_EVENT_CLICKED) {
        _ui_screen_change(&ui_ScreenWpa, LV_SCR_LOAD_ANIM_FADE_ON, 0, 0, &ui_ScreenWpa_screen_init);
        wifi_scr_init();
    }
}

void ui_event_DropdownSSID(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);
    if (event_code == LV_EVENT_VALUE_CHANGED)
    {
        char ssid[MAX_CONF_LEN];
        memset(ssid, 0, MAX_CONF_LEN);
        lv_dropdown_get_selected_str(ui_DropdownSSID, ssid, MAX_CONF_LEN);
        lv_textarea_set_text(ui_TextAreaSSID, ssid);
        for (int i = 0; i < network_count; i++){
            // printf("ui_id:[%s] len:%zu\n", networks[i].ssid, strlen(networks[i].ssid));
            // printf("ui_ssid:[%s] len:%zu\n", ssid, strlen(ssid));
            if (strstr(networks[i].ssid, ssid) != NULL) {
                char signal_level_str[20];
                snprintf(signal_level_str, sizeof(signal_level_str), "%d dbm", networks[i].signal_level);
                lv_textarea_set_text(ui_TextAreaMgnt,networks[i].flags);
                printf("ui_TextAreaMgnt:%s\n",networks[i].flags);
                lv_textarea_set_text(ui_TextAreaRSSI,signal_level_str);
                printf("ui_TextAreaRSSI:%s\n",signal_level_str);
                break;
            }
        }
    } 
}

void ui_event_ButtonDiscon(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);
    if (event_code == LV_EVENT_RELEASED)
    {
        lv_textarea_set_text(ui_TextAreaSSID,"");
        lv_textarea_set_text(ui_TextAreaPW,"");
        wifi_disconnect("wlan0");
    } 
}

void ui_event_ButtonScan(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);
     if (event_code == LV_EVENT_RELEASED && scan_is_button_pressed == false)
    {
        scan_is_button_pressed = true;
        wifi_scanning_ssid();
        scan_is_button_pressed = false;
    } 
}

void ui_event_ButtonBack(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);
    if(event_code == LV_EVENT_CLICKED) {
        _ui_screen_change(&ui_ScreenMain, LV_SCR_LOAD_ANIM_FADE_ON, 0, 0, &ui_ScreenMain_screen_init);
    }
}

void ui_event_ButtonConnect(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);
    if (event_code == LV_EVENT_RELEASED)
    {
        const char *ssid = lv_textarea_get_text(ui_TextAreaSSID);
        const char *passwd = lv_textarea_get_text(ui_TextAreaPW);
        if (strlen(ssid) != 0 && strlen(passwd) != 0) {
            wifi_connect_info_t *wifi = malloc(sizeof(wifi_connect_info_t));
            strcpy(wifi->ssid, ssid);
            strcpy(wifi->passwd, passwd);

            pthread_t wifi_connect_thread;
            pthread_create(&wifi_connect_thread, NULL, wifi_connect_thread_handler, wifi);
            pthread_detach(wifi_connect_thread);
        }
    }
}

void ui_event_TextAreaPW(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);
    if(event_code == LV_EVENT_CLICKED) {
        lv_keyboard_set_textarea(ui_Keyboard1,  ui_TextAreaPW);
        lv_obj_clear_flag(ui_Keyboard1, LV_OBJ_FLAG_HIDDEN);
    }
}

void ui_event_TextAreaSSID(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);
    if(event_code == LV_EVENT_CLICKED) {
        lv_keyboard_set_textarea(ui_Keyboard1,  ui_TextAreaSSID);
        lv_obj_clear_flag(ui_Keyboard1, LV_OBJ_FLAG_HIDDEN);
    }
}

void ui_event_Keyboard1(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);
    if(event_code ==  LV_EVENT_READY || event_code == LV_EVENT_CANCEL) {
        lv_obj_add_flag(target, LV_OBJ_FLAG_HIDDEN);
    }
}

void ui_event_ScreenPlayer(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);
    if(event_code == LV_EVENT_GESTURE &&  lv_indev_get_gesture_dir(lv_indev_get_act()) == LV_DIR_TOP && GestureFlag == true) {
        lv_indev_wait_release(lv_indev_get_act());
        _ui_screen_change(&ui_ScreenMain, LV_SCR_LOAD_ANIM_MOVE_TOP, 300, 0, &ui_ScreenMain_screen_init);
    }
}

void ui_event_PanelRelay0(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);
    if(event_code == LV_EVENT_CLICKED) {
        if(lv_obj_get_style_bg_grad_dir(ui_PanelRelay0,LV_PART_MAIN) == LV_GRAD_DIR_VER)
        {
            set_gpio(32,0);
            lv_obj_set_style_text_color(ui_LabelRelay0, lv_color_hex(0x696969), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_color(ui_PanelRelay0, lv_color_hex(0x1F1F1F), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_grad_dir(ui_PanelRelay0, LV_GRAD_DIR_NONE, LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        else
        {
            set_gpio(32,1);
            lv_obj_set_style_text_color(ui_LabelRelay0, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_color(ui_PanelRelay0, lv_color_hex(0xEC6900), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_grad_color(ui_PanelRelay0, lv_color_hex(0xF6AC05), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_grad_dir(ui_PanelRelay0, LV_GRAD_DIR_VER, LV_PART_MAIN | LV_STATE_DEFAULT);
        }
    }
}

void ui_event_PanelRelay1(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);
    if(event_code == LV_EVENT_CLICKED) {
        if(lv_obj_get_style_bg_grad_dir(ui_PanelRelay1,LV_PART_MAIN) == LV_GRAD_DIR_VER)
        {
            set_gpio(33,0);
            lv_obj_set_style_text_color(ui_LabelRelay1, lv_color_hex(0x696969), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_color(ui_PanelRelay1, lv_color_hex(0x1F1F1F), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_grad_dir(ui_PanelRelay1, LV_GRAD_DIR_NONE, LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        else
        {
            set_gpio(33,1);
            lv_obj_set_style_text_color(ui_LabelRelay1, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_color(ui_PanelRelay1, lv_color_hex(0xEC6900), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_grad_color(ui_PanelRelay1, lv_color_hex(0xF6AC05), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_grad_dir(ui_PanelRelay1, LV_GRAD_DIR_VER, LV_PART_MAIN | LV_STATE_DEFAULT);
        }
    }
}

void ui_event_ImgButtonPrev(lv_event_t * e)
{
    char roller_str[MAX_MUSIC_LIST_LEN];
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);
    if(event_code == LV_EVENT_CLICKED && playing_music_node != NULL) {
        if(!CycleFlag)
        {        
            music_scan_list(roller_str);
            lv_roller_set_options(ui_RollerMusic, roller_str, LV_ROLLER_MODE_NORMAL);
            if(strcmp(roller_str, "NOT FOUND") == 0)
                return;
            playing_music_node = playing_music_node->prev;
            lv_roller_set_selected(ui_RollerMusic, playing_music_node->id, LV_ANIM_OFF);
            music_set_pos(playing_music_node->id);
        }
        else
        {
            music_scan_list(roller_str);
            lv_roller_set_options(ui_RollerMusic, roller_str, LV_ROLLER_MODE_NORMAL);
            if(strcmp(roller_str, "NOT FOUND") == 0)
                return;
            music_set_pos(playing_music_node->id);
        }
        
    }
}

void ui_event_ImgButtonNext(lv_event_t * e)
{
    char roller_str[MAX_MUSIC_LIST_LEN];
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);
    if(event_code == LV_EVENT_PRESSED && playing_music_node != NULL) {
        if(!CycleFlag)
        {
            music_scan_list(roller_str);
            lv_roller_set_options(ui_RollerMusic, roller_str, LV_ROLLER_MODE_NORMAL);
            if(strcmp(roller_str, "NOT FOUND") == 0)
                return;
            playing_music_node = playing_music_node->next;
            lv_roller_set_selected(ui_RollerMusic, playing_music_node->id, LV_ANIM_OFF);
            music_set_pos(playing_music_node->id);
        }
        else
        {
            music_scan_list(roller_str);
            lv_roller_set_options(ui_RollerMusic, roller_str, LV_ROLLER_MODE_NORMAL);
            if(strcmp(roller_str, "NOT FOUND") == 0)
                return;
            music_set_pos(playing_music_node->id);
        }
    }
}

void ui_event_SliderMusic(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);
    if(event_code == LV_EVENT_VALUE_CHANGED) {
        int volume = lv_slider_get_value(target);
        music_set_volume(volume);
    }
}

void ui_event_ImgButtonList(lv_event_t * e)
{
    char roller_str[MAX_MUSIC_LIST_LEN];
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);
    if(event_code == LV_EVENT_RELEASED) {
        // lv_obj_clear_flag(ui_RollerMusic, LV_OBJ_FLAG_HIDDEN); 
        music_scan_list(roller_str);
        lv_roller_set_options(ui_RollerMusic, roller_str, LV_ROLLER_MODE_NORMAL);
    
        lv_obj_clear_flag(ui_PanelBoard, LV_OBJ_FLAG_HIDDEN);
        GestureFlag = false;
    }
}

void ui_event_ImagePlay(lv_event_t * e)
{
    char roller_str[MAX_MUSIC_LIST_LEN];
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);
    if(event_code == LV_EVENT_PRESSED) {
        lv_state_t btn_state = lv_obj_get_state(target);
        if(btn_state &= LV_STATE_CHECKED)
        {
            music_scan_list(roller_str);
            lv_roller_set_options(ui_RollerMusic, roller_str, LV_ROLLER_MODE_NORMAL);
            music_pause(1);
        }
        else
        {
            music_scan_list(roller_str);
            lv_roller_set_options(ui_RollerMusic, roller_str, LV_ROLLER_MODE_NORMAL);
            if(strcmp(roller_str, "NOT FOUND") == 0)
                return;
            music_pause(0);
        } 
    }
}

void ui_event_ImageMusicMode(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);
    if(event_code == LV_EVENT_PRESSED) {
        lv_state_t btn_state = lv_obj_get_state(target);
        if(btn_state &= LV_STATE_CHECKED)
        {
            music_set_mode(0);
            CycleFlag = false;
        }
        else
        {
            music_set_mode(1);
            CycleFlag = true;
        } 
    }
}

void ui_event_RollerMusic(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);
    if(event_code == LV_EVENT_VALUE_CHANGED && playing_music_node != NULL) {
        char buf[32];
        lv_roller_get_selected_str(target,  buf, sizeof(buf));

        while(strcmp(playing_music_node->filename, buf))
        {
            playing_music_node = playing_music_node->next;    
        }
        music_set_pos(playing_music_node->id);
    }
}

void ui_event_ImageMusicClose(lv_event_t *e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);
    if(event_code == LV_EVENT_CLICKED)
    {
        lv_obj_add_flag(ui_RollerMusic,LV_OBJ_FLAG_HIDDEN);
        GestureFlag = true;
    }
}

void ui_event_PanelBoard(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);
    if(event_code == LV_EVENT_CLICKED)
    {
        lv_obj_add_flag(ui_PanelBoard,LV_OBJ_FLAG_HIDDEN);
        GestureFlag = true;
    }
}

void system_get_device_model(char *model)
{
    FILE *fp = popen("cat /proc/device-tree/model", "r");
    if (fp == NULL) {
        perror("popen error: ");
        return;
    }
    fgets(model, 32, fp);
    pclose(fp);
}

void ui_init(void)
{
    lv_disp_t * dispp = lv_disp_get_default();
    lv_theme_t * theme = lv_theme_default_init(dispp, lv_palette_main(LV_PALETTE_BLUE), lv_palette_main(LV_PALETTE_RED),
                                               false, LV_FONT_DEFAULT);
    lv_disp_set_theme(dispp, theme);

    system_get_device_model(device_model);

    custom_init();
    ui_ScreenMain_screen_init();
    if(strcmp(device_model, LUCKFOX_PICO_86PANEL_W) == 0) 
        ui_ScreenWpa_screen_init();
    ui_ScreenPlayer_screen_init();
    ui_initial_actions0 = lv_obj_create(NULL);
    lv_disp_load_scr(ui_ScreenMain);
}
