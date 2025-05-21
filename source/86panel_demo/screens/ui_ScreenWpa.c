#include "../ui_custom.h"

void ui_ScreenWpa_screen_init(void)
{
    ui_ScreenWpa = lv_obj_create(NULL);
    lv_obj_clear_flag(ui_ScreenWpa, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_set_style_radius(ui_ScreenWpa, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_ScreenWpa, lv_color_hex(0x0D0D0D), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_ScreenWpa, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_img_src(ui_ScreenWpa, &ui_img_luckfox_logo_png, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_img_opa(ui_ScreenWpa, 15, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_PanelList = lv_obj_create(ui_ScreenWpa);
    lv_obj_set_width(ui_PanelList, 720);
    lv_obj_set_height(ui_PanelList, 100);
    lv_obj_clear_flag(ui_PanelList, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_set_style_radius(ui_PanelList, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_PanelList, lv_color_hex(0x1F1F1F), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_PanelList, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui_PanelList, lv_color_hex(0x1F1F1F), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui_PanelList, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui_PanelList, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui_PanelList, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui_PanelList, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui_PanelList, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_DropdownSSID = lv_dropdown_create(ui_PanelList);
    lv_dropdown_set_options(ui_DropdownSSID,
                            "---\n---\n---\n---\n---\n---");
    lv_obj_set_width(ui_DropdownSSID, 440);
    lv_obj_set_height(ui_DropdownSSID, 64);
    lv_obj_set_x(ui_DropdownSSID, 240);
    lv_obj_set_y(ui_DropdownSSID, 18);
    lv_obj_add_flag(ui_DropdownSSID, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
    lv_obj_set_style_text_color(ui_DropdownSSID, lv_color_hex(0x545454), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_DropdownSSID, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_DropdownSSID, &lv_font_montserrat_32, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui_DropdownSSID, 10, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_DropdownSSID, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_DropdownSSID, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui_DropdownSSID, lv_color_hex(0x333333), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui_DropdownSSID, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_set_style_text_color(lv_dropdown_get_list(ui_DropdownSSID), lv_color_hex(0x545454),
                                LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(lv_dropdown_get_list(ui_DropdownSSID), 255,  LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(lv_dropdown_get_list(ui_DropdownSSID), &lv_font_montserrat_30,
                               LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(lv_dropdown_get_list(ui_DropdownSSID), lv_color_hex(0x000000),
                              LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(lv_dropdown_get_list(ui_DropdownSSID), 255,  LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(lv_dropdown_get_list(ui_DropdownSSID), lv_color_hex(0x333333),
                                  LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(lv_dropdown_get_list(ui_DropdownSSID), 255,  LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_set_style_text_color(lv_dropdown_get_list(ui_DropdownSSID), lv_color_hex(0x808080),
                                LV_PART_SELECTED | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(lv_dropdown_get_list(ui_DropdownSSID), 255,  LV_PART_SELECTED | LV_STATE_DEFAULT);

    ui_LabelWLAN = lv_label_create(ui_PanelList);
    lv_obj_set_width(ui_LabelWLAN, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_LabelWLAN, LV_SIZE_CONTENT);
    lv_obj_set_x(ui_LabelWLAN, 39);
    lv_obj_set_y(ui_LabelWLAN, 25);
    lv_label_set_text(ui_LabelWLAN, "WLAN");
    lv_obj_set_style_text_color(ui_LabelWLAN, lv_color_hex(0x545454), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_LabelWLAN, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_LabelWLAN, &ui_font_HarmonyOS48, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui_LabelWLAN, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui_LabelWLAN, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui_LabelWLAN, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui_LabelWLAN, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_PanelBtn = lv_obj_create(ui_ScreenWpa);
    lv_obj_set_width(ui_PanelBtn, 720);
    lv_obj_set_height(ui_PanelBtn, 128);
    lv_obj_set_x(ui_PanelBtn, 0);
    lv_obj_set_y(ui_PanelBtn, 592);
    lv_obj_clear_flag(ui_PanelBtn, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_set_style_radius(ui_PanelBtn, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_PanelBtn, lv_color_hex(0x1F1F1F), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_PanelBtn, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui_PanelBtn, lv_color_hex(0x1F1F1F), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui_PanelBtn, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui_PanelBtn, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui_PanelBtn, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui_PanelBtn, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui_PanelBtn, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_ButtonDiscon = lv_btn_create(ui_PanelBtn);
    lv_obj_set_width(ui_ButtonDiscon, 150);
    lv_obj_set_height(ui_ButtonDiscon, 80);
    lv_obj_set_x(ui_ButtonDiscon, 370);
    lv_obj_set_y(ui_ButtonDiscon, 24);
    lv_obj_add_flag(ui_ButtonDiscon, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
    lv_obj_clear_flag(ui_ButtonDiscon, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_set_style_radius(ui_ButtonDiscon, 20, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_ButtonDiscon, lv_color_hex(0x404040), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_ButtonDiscon, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui_ButtonDiscon, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_spread(ui_ButtonDiscon, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_ImageDiscon = lv_img_create(ui_ButtonDiscon);
    lv_img_set_src(ui_ImageDiscon, &ui_img_discon_png);
    lv_obj_set_width(ui_ImageDiscon, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_ImageDiscon, LV_SIZE_CONTENT);
    lv_obj_set_align(ui_ImageDiscon, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_ImageDiscon, LV_OBJ_FLAG_ADV_HITTEST);
    lv_obj_clear_flag(ui_ImageDiscon, LV_OBJ_FLAG_SCROLLABLE);

    ui_ButtonScan = lv_btn_create(ui_PanelBtn);
    lv_obj_set_width(ui_ButtonScan, 150);
    lv_obj_set_height(ui_ButtonScan, 80);
    lv_obj_set_x(ui_ButtonScan, 30);
    lv_obj_set_y(ui_ButtonScan, 24);
    lv_obj_add_flag(ui_ButtonScan, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
    lv_obj_clear_flag(ui_ButtonScan, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_set_style_radius(ui_ButtonScan, 20, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_ButtonScan, lv_color_hex(0x404040), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_ButtonScan, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui_ButtonScan, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_spread(ui_ButtonScan, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_ImageScan = lv_img_create(ui_ButtonScan);
    lv_img_set_src(ui_ImageScan, &ui_img_scan_png);
    lv_obj_set_width(ui_ImageScan, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_ImageScan, LV_SIZE_CONTENT);
    lv_obj_set_align(ui_ImageScan, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_ImageScan, LV_OBJ_FLAG_ADV_HITTEST);
    lv_obj_clear_flag(ui_ImageScan, LV_OBJ_FLAG_SCROLLABLE);

    ui_ButtonBack = lv_btn_create(ui_PanelBtn);
    lv_obj_set_width(ui_ButtonBack, 150);
    lv_obj_set_height(ui_ButtonBack, 80);
    lv_obj_set_x(ui_ButtonBack, 257);
    lv_obj_set_y(ui_ButtonBack, 0);
    lv_obj_set_align(ui_ButtonBack, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_ButtonBack, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
    lv_obj_clear_flag(ui_ButtonBack, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_set_style_radius(ui_ButtonBack, 20, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_ButtonBack, lv_color_hex(0x404040), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_ButtonBack, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui_ButtonBack, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_spread(ui_ButtonBack, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_ImageBack = lv_img_create(ui_ButtonBack);
    lv_img_set_src(ui_ImageBack, &ui_img_back_png);
    lv_obj_set_width(ui_ImageBack, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_ImageBack, LV_SIZE_CONTENT);
    lv_obj_set_align(ui_ImageBack, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_ImageBack, LV_OBJ_FLAG_ADV_HITTEST);
    lv_obj_clear_flag(ui_ImageBack, LV_OBJ_FLAG_SCROLLABLE);
    ui_ButtonConnect = lv_btn_create(ui_PanelBtn);
    lv_obj_set_width(ui_ButtonConnect, 150);
    lv_obj_set_height(ui_ButtonConnect, 80);
    lv_obj_set_x(ui_ButtonConnect, 200);
    lv_obj_set_y(ui_ButtonConnect, 24);
    lv_obj_add_flag(ui_ButtonConnect, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
    lv_obj_clear_flag(ui_ButtonConnect, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_set_style_radius(ui_ButtonConnect, 20, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_ButtonConnect, lv_color_hex(0x404040), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_ButtonConnect, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui_ButtonConnect, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_spread(ui_ButtonConnect, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_ImageConnect = lv_img_create(ui_ButtonConnect);
    lv_img_set_src(ui_ImageConnect, &ui_img_connect_png);
    lv_obj_set_width(ui_ImageConnect, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_ImageConnect, LV_SIZE_CONTENT);
    lv_obj_set_align(ui_ImageConnect, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_ImageConnect, LV_OBJ_FLAG_ADV_HITTEST);
    lv_obj_clear_flag(ui_ImageConnect, LV_OBJ_FLAG_SCROLLABLE); 

    ui_LabelMGMT = lv_label_create(ui_ScreenWpa);
    lv_obj_set_width(ui_LabelMGMT, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_LabelMGMT, LV_SIZE_CONTENT);
    lv_obj_set_x(ui_LabelMGMT, 39);
    lv_obj_set_y(ui_LabelMGMT, 485);
    lv_label_set_text(ui_LabelMGMT, "PSK");
    lv_obj_set_style_text_color(ui_LabelMGMT, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_LabelMGMT, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_LabelMGMT, &ui_font_HarmonyOS48, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_LabelPW = lv_label_create(ui_ScreenWpa);
    lv_obj_set_width(ui_LabelPW, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_LabelPW, LV_SIZE_CONTENT);
    lv_obj_set_x(ui_LabelPW, 39);
    lv_obj_set_y(ui_LabelPW, 265);
    lv_label_set_text(ui_LabelPW, "Passwd");
    lv_obj_set_style_text_color(ui_LabelPW, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_LabelPW, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_LabelPW, &ui_font_HarmonyOS48, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_TextAreaPW = lv_textarea_create(ui_ScreenWpa);
    lv_obj_set_width(ui_TextAreaPW, 440);
    lv_obj_set_height(ui_TextAreaPW, LV_SIZE_CONTENT); 
    lv_obj_set_x(ui_TextAreaPW, 240);
    lv_obj_set_y(ui_TextAreaPW, 265);
    lv_textarea_set_text(ui_TextAreaPW, "123456");
    lv_textarea_set_one_line(ui_TextAreaPW, true);
    lv_obj_set_style_text_color(ui_TextAreaPW, lv_color_hex(0xA9A8A8), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_TextAreaPW, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_TextAreaPW, &lv_font_montserrat_32, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_TextAreaPW, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_TextAreaPW, 15, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui_TextAreaPW, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui_TextAreaPW, 25, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui_TextAreaPW, 20, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui_TextAreaPW, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui_TextAreaPW, 10, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui_TextAreaPW, 10, LV_PART_MAIN | LV_STATE_DEFAULT);
    // lv_obj_add_style(ui_TextAreaSSID, &style_textarea, LV_PART_CURSOR | LV_STATE_FOCUSED);

    lv_obj_set_style_text_color(ui_TextAreaPW, lv_color_hex(0xFFFFFF), LV_PART_CURSOR | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_TextAreaPW, 255, LV_PART_CURSOR | LV_STATE_DEFAULT);

    ui_LabelRSSI = lv_label_create(ui_ScreenWpa);
    lv_obj_set_width(ui_LabelRSSI, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_LabelRSSI, LV_SIZE_CONTENT);
    lv_obj_set_x(ui_LabelRSSI, 39);
    lv_obj_set_y(ui_LabelRSSI, 373);
    lv_label_set_text(ui_LabelRSSI, "RSSI");
    lv_obj_set_style_text_color(ui_LabelRSSI, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_LabelRSSI, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_LabelRSSI, &ui_font_HarmonyOS48, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_LabelSSID = lv_label_create(ui_ScreenWpa);
    lv_obj_set_width(ui_LabelSSID, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_LabelSSID, LV_SIZE_CONTENT);
    lv_obj_set_x(ui_LabelSSID, 39);
    lv_obj_set_y(ui_LabelSSID, 153);
    lv_label_set_text(ui_LabelSSID, "SSID");
    lv_obj_set_style_text_color(ui_LabelSSID, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_LabelSSID, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_LabelSSID, &ui_font_HarmonyOS48, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_TextAreaSSID = lv_textarea_create(ui_ScreenWpa);
    lv_obj_set_width(ui_TextAreaSSID, 440);
    lv_obj_set_height(ui_TextAreaSSID, LV_SIZE_CONTENT);
    lv_obj_set_x(ui_TextAreaSSID, 240);
    lv_obj_set_y(ui_TextAreaSSID, 146);
    lv_textarea_set_text(ui_TextAreaSSID, "---");
    lv_textarea_set_one_line(ui_TextAreaSSID, true);
    lv_obj_set_style_text_color(ui_TextAreaSSID, lv_color_hex(0xA9A8A8), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_TextAreaSSID, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_TextAreaSSID, &lv_font_montserrat_32, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_TextAreaSSID, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_TextAreaSSID, 15, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui_TextAreaSSID, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui_TextAreaSSID, 25, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui_TextAreaSSID, LV_BORDER_SIDE_FULL, LV_PART_MAIN | LV_STATE_DEFAULT);
    // lv_obj_add_style(ui_TextAreaSSID, &style_textarea, LV_PART_CURSOR | LV_STATE_FOCUSED);

    ui_TextAreaRSSI = lv_textarea_create(ui_ScreenWpa);
    lv_obj_set_width(ui_TextAreaRSSI, 440);
    lv_obj_set_height(ui_TextAreaRSSI, LV_SIZE_CONTENT);
    lv_obj_set_x(ui_TextAreaRSSI, 238);
    lv_obj_set_y(ui_TextAreaRSSI, 371);
    lv_textarea_set_text(ui_TextAreaRSSI, "--dbm");
    lv_textarea_set_one_line(ui_TextAreaRSSI, true);
    lv_obj_set_style_text_color(ui_TextAreaRSSI, lv_color_hex(0xA9A8A8), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_TextAreaRSSI, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_TextAreaRSSI, &lv_font_montserrat_32, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_TextAreaRSSI, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_TextAreaRSSI, 15, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui_TextAreaRSSI, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui_TextAreaRSSI, 25, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui_TextAreaRSSI, 20, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui_TextAreaRSSI, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui_TextAreaRSSI, 10, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui_TextAreaRSSI, 10, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_set_style_text_color(ui_TextAreaRSSI, lv_color_hex(0xFFFFFF), LV_PART_CURSOR | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_TextAreaRSSI, 255, LV_PART_CURSOR | LV_STATE_DEFAULT);

    ui_TextAreaMgnt = lv_textarea_create(ui_ScreenWpa);
    lv_obj_set_width(ui_TextAreaMgnt, 440);
    lv_obj_set_height(ui_TextAreaMgnt, LV_SIZE_CONTENT);
    lv_obj_set_x(ui_TextAreaMgnt, 238);
    lv_obj_set_y(ui_TextAreaMgnt, 480);
    lv_textarea_set_text(ui_TextAreaMgnt, "------");
    lv_textarea_set_one_line(ui_TextAreaMgnt, true);
    lv_obj_set_style_text_color(ui_TextAreaMgnt, lv_color_hex(0xA9A8A8), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_TextAreaMgnt, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_TextAreaMgnt, &lv_font_montserrat_32, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_TextAreaMgnt, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_TextAreaMgnt, 15, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui_TextAreaMgnt, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui_TextAreaMgnt, 25, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_set_style_text_color(ui_TextAreaMgnt, lv_color_hex(0xFFFFFF), LV_PART_CURSOR | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_TextAreaMgnt, 255, LV_PART_CURSOR | LV_STATE_DEFAULT);

    ui_Keyboard1 = lv_keyboard_create(ui_ScreenWpa);
    lv_obj_set_width(ui_Keyboard1, 720);
    lv_obj_set_height(ui_Keyboard1, 365);
    lv_obj_set_x(ui_Keyboard1, 3);
    lv_obj_set_y(ui_Keyboard1, 170);
    lv_obj_set_align(ui_Keyboard1, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_Keyboard1, LV_OBJ_FLAG_HIDDEN);
    lv_obj_set_style_bg_color(ui_Keyboard1, lv_color_hex(0x0D0D0D), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_Keyboard1, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui_Keyboard1, lv_color_hex(0x333333), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui_Keyboard1, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_set_style_bg_color(ui_Keyboard1, lv_color_hex(0x7A7A7A), LV_PART_ITEMS | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_Keyboard1, 255, LV_PART_ITEMS | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui_Keyboard1, lv_color_hex(0xFFFFFF), LV_PART_ITEMS | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_Keyboard1, 255, LV_PART_ITEMS | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_Keyboard1, &lv_font_montserrat_28, LV_PART_ITEMS | LV_STATE_DEFAULT);

    lv_obj_add_event_cb(ui_DropdownSSID, ui_event_DropdownSSID, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_ButtonDiscon, ui_event_ButtonDiscon, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_ButtonScan, ui_event_ButtonScan, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_ButtonBack, ui_event_ButtonBack, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_ButtonConnect, ui_event_ButtonConnect, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_TextAreaPW, ui_event_TextAreaPW, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_TextAreaSSID, ui_event_TextAreaSSID, LV_EVENT_ALL, NULL);
    lv_keyboard_set_textarea(ui_Keyboard1, ui_TextAreaSSID);
    lv_obj_add_event_cb(ui_Keyboard1, ui_event_Keyboard1, LV_EVENT_ALL, NULL);

}
