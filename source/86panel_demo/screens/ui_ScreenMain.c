#include "../ui_custom.h"

void ui_ScreenMain_screen_init(void)
{
    ui_ScreenMain = lv_obj_create(NULL);
    lv_obj_clear_flag(ui_ScreenMain, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_set_style_bg_color(ui_ScreenMain, lv_color_hex(0x0D0D0D), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_ScreenMain, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_img_src(ui_ScreenMain, &ui_img_luckfox_logo_png, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_img_opa(ui_ScreenMain, 15, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_PanelWifi = lv_obj_create(ui_ScreenMain);
    lv_obj_set_width(ui_PanelWifi, 320);
    lv_obj_set_height(ui_PanelWifi, 200);
    lv_obj_set_x(ui_PanelWifi, 30);
    lv_obj_set_y(ui_PanelWifi, 490);
    lv_obj_clear_flag(ui_PanelWifi, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_set_style_radius(ui_PanelWifi, 15, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_PanelWifi, lv_color_hex(0x1F1F1F), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_PanelWifi, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui_PanelWifi, lv_color_hex(0x3F3622), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui_PanelWifi, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui_PanelWifi, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui_PanelWifi, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui_PanelWifi, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui_PanelWifi, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    // Wifi Panel
    ui_ImageWifi = lv_img_create(ui_PanelWifi);
    lv_img_set_src(ui_ImageWifi, &ui_img_icon_wifi_on_png);
    lv_obj_set_width(ui_ImageWifi, 72);
    lv_obj_set_height(ui_ImageWifi, 72);
    lv_obj_set_x(ui_ImageWifi, 30);
    lv_obj_set_y(ui_ImageWifi, 36);
    lv_obj_clear_flag(ui_ImageWifi, LV_OBJ_FLAG_SCROLLABLE);

    ui_LabelWifiName = lv_label_create(ui_PanelWifi);
    lv_obj_set_width(ui_LabelWifiName, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_LabelWifiName, LV_SIZE_CONTENT);
    lv_obj_set_x(ui_LabelWifiName, 118);
    lv_obj_set_y(ui_LabelWifiName, 56);
    lv_label_set_text(ui_LabelWifiName, "------------");
    lv_obj_set_style_text_color(ui_LabelWifiName, lv_color_hex(0xA9A8A8), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_LabelWifiName, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_LabelWifiName, &lv_font_montserrat_28, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_img_set_src(ui_ImageWifi, &ui_img_icon_wifi_off_png);

    ui_LabelWifiIP = lv_label_create(ui_PanelWifi);
    lv_obj_set_width(ui_LabelWifiIP, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_LabelWifiIP, LV_SIZE_CONTENT);
    lv_obj_set_x(ui_LabelWifiIP, 118);
    lv_obj_set_y(ui_LabelWifiIP, 130);
    lv_label_set_text(ui_LabelWifiIP, "---.---.---.---");
    lv_obj_set_style_text_color(ui_LabelWifiIP, lv_color_hex(0xA9A8A8), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_LabelWifiIP, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_LabelWifiIP, &lv_font_montserrat_22, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_LabelWIP = lv_label_create(ui_PanelWifi);
    lv_obj_set_width(ui_LabelWIP, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_LabelWIP, LV_SIZE_CONTENT);
    lv_obj_set_x(ui_LabelWIP, 54);
    lv_obj_set_y(ui_LabelWIP, 130);
    lv_label_set_text(ui_LabelWIP, "IP:");
    lv_obj_set_style_text_color(ui_LabelWIP, lv_color_hex(0xA9A8A8), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_LabelWIP, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_LabelWIP, &lv_font_montserrat_22, LV_PART_MAIN | LV_STATE_DEFAULT);

    // Time Panel
    ui_LabelTime = lv_label_create(ui_ScreenMain);
    lv_obj_set_width(ui_LabelTime, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_LabelTime, LV_SIZE_CONTENT);
    lv_obj_set_x(ui_LabelTime, -5);
    lv_obj_set_y(ui_LabelTime, -150);
    lv_obj_set_align(ui_LabelTime, LV_ALIGN_CENTER);
    lv_label_set_text(ui_LabelTime, "00:00");
    lv_obj_set_style_text_color(ui_LabelTime, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_LabelTime, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_LabelTime, &ui_font_HarmonyOS200, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_PanelEth = lv_obj_create(ui_ScreenMain);
    lv_obj_set_width(ui_PanelEth, 320);
    lv_obj_set_height(ui_PanelEth, 200);
    lv_obj_set_x(ui_PanelEth, 370);
    lv_obj_set_y(ui_PanelEth, 490);
    lv_obj_set_style_radius(ui_PanelEth, 15, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_PanelEth, lv_color_hex(0x1F1F1F), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_PanelEth, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui_PanelEth, lv_color_hex(0x1F1F1F), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui_PanelEth, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui_PanelEth, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui_PanelEth, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui_PanelEth, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui_PanelEth, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    // Ether Panel
    ui_ImageEth = lv_img_create(ui_PanelEth);
    lv_img_set_src(ui_ImageEth, &ui_img_icon_eth_off_png);
    lv_obj_set_width(ui_ImageEth, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_ImageEth, LV_SIZE_CONTENT);
    lv_obj_set_x(ui_ImageEth, 30);
    lv_obj_set_y(ui_ImageEth, 36);

    ui_LabelEth = lv_label_create(ui_PanelEth);
    lv_obj_set_width(ui_LabelEth, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_LabelEth, LV_SIZE_CONTENT);
    lv_obj_set_x(ui_LabelEth, 118);
    lv_obj_set_y(ui_LabelEth, 56);
    lv_label_set_text(ui_LabelEth, "------------");
    lv_obj_set_style_text_color(ui_LabelEth, lv_color_hex(0xA9A8A8), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_LabelEth, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_LabelEth, &lv_font_montserrat_28, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_LabelEthIP = lv_label_create(ui_PanelEth);
    lv_obj_set_width(ui_LabelEthIP, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_LabelEthIP, LV_SIZE_CONTENT);
    lv_obj_set_x(ui_LabelEthIP, 118);
    lv_obj_set_y(ui_LabelEthIP, 130);
    lv_label_set_text(ui_LabelEthIP, "---.---.---.---");
    lv_obj_set_style_text_color(ui_LabelEthIP, lv_color_hex(0xA9A8A8), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_LabelEthIP, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_LabelEthIP, &lv_font_montserrat_22, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_LabelNetIP = lv_label_create(ui_PanelEth);
    lv_obj_set_width(ui_LabelNetIP, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_LabelNetIP, LV_SIZE_CONTENT);
    lv_obj_set_x(ui_LabelNetIP, 54);
    lv_obj_set_y(ui_LabelNetIP, 130);
    lv_label_set_text(ui_LabelNetIP, "IP:");
    lv_obj_set_style_text_color(ui_LabelNetIP, lv_color_hex(0xA9A8A8), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_LabelNetIP, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_LabelNetIP, &lv_font_montserrat_22, LV_PART_MAIN | LV_STATE_DEFAULT);

    // Date Panel
    ui_LabelDate = lv_label_create(ui_ScreenMain);
    lv_obj_set_width(ui_LabelDate, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_LabelDate, LV_SIZE_CONTENT);
    lv_obj_set_align(ui_LabelDate, LV_ALIGN_CENTER);
    lv_label_set_text(ui_LabelDate, "XXXX-XX-XX XXX");
    lv_obj_set_style_text_color(ui_LabelDate, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_LabelDate, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_LabelDate, &lv_font_montserrat_36, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_ImageTop = lv_img_create(ui_ScreenMain);
    lv_img_set_src(ui_ImageTop, &ui_img_icon_top17_png);
    lv_obj_set_width(ui_ImageTop, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_ImageTop, LV_SIZE_CONTENT);
    lv_obj_set_x(ui_ImageTop, 300);
    lv_obj_set_y(ui_ImageTop, 0);
    lv_obj_add_flag(ui_ImageTop, LV_OBJ_FLAG_ADV_HITTEST);
    lv_obj_clear_flag(ui_ImageTop, LV_OBJ_FLAG_SCROLLABLE);

    
    if(strcmp(device_model, LUCKFOX_PICO_86PANEL_W) == 0) {
        lv_obj_add_flag(ui_ImageWifi, LV_OBJ_FLAG_ADV_HITTEST);
        lv_obj_add_event_cb(ui_PanelWifi, ui_event_PanelWifi, LV_EVENT_ALL, NULL);  
    }
    lv_obj_add_event_cb(ui_ScreenMain, ui_event_ScreenMain, LV_EVENT_ALL, NULL);
   
    main_timer_init();
}
