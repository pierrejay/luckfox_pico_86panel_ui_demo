#include "../ui_custom.h"

void ui_ScreenPlayer_screen_init(void)
{
    ui_ScreenPlayer = lv_obj_create(NULL);
    lv_obj_clear_flag(ui_ScreenPlayer, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_set_style_bg_color(ui_ScreenPlayer, lv_color_hex(0x0D0D0D), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_ScreenPlayer, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_img_src(ui_ScreenPlayer, &ui_img_luckfox_logo_png, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_img_opa(ui_ScreenPlayer, 15, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_PanelRelay0 = lv_obj_create(ui_ScreenPlayer);
    lv_obj_set_width(ui_PanelRelay0, 320);
    lv_obj_set_height(ui_PanelRelay0, 160);
    lv_obj_set_x(ui_PanelRelay0, 30);
    lv_obj_set_y(ui_PanelRelay0, 530);
    lv_obj_clear_flag(ui_PanelRelay0, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_set_style_radius(ui_PanelRelay0, 20, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_PanelRelay0, lv_color_hex(0x1F1F1F), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_PanelRelay0, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui_PanelRelay0, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_LabelRelay0 = lv_label_create(ui_PanelRelay0);
    lv_obj_set_width(ui_LabelRelay0, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_LabelRelay0, LV_SIZE_CONTENT);
    lv_obj_set_align(ui_LabelRelay0, LV_ALIGN_CENTER);
    lv_label_set_text(ui_LabelRelay0, "Relay 0");
    lv_obj_set_style_text_color(ui_LabelRelay0, lv_color_hex(0x696969), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_LabelRelay0, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_LabelRelay0, &lv_font_montserrat_48, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_PanelRelay1 = lv_obj_create(ui_ScreenPlayer);
    lv_obj_set_width(ui_PanelRelay1, 320);
    lv_obj_set_height(ui_PanelRelay1, 160);
    lv_obj_set_x(ui_PanelRelay1, 370);
    lv_obj_set_y(ui_PanelRelay1, 530);
    lv_obj_clear_flag(ui_PanelRelay1, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_set_style_radius(ui_PanelRelay1, 20, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_PanelRelay1, lv_color_hex(0x1F1F1F), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_PanelRelay1, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui_PanelRelay1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_LabelRelay1 = lv_label_create(ui_PanelRelay1);
    lv_obj_set_width(ui_LabelRelay1, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_LabelRelay1, LV_SIZE_CONTENT);
    lv_obj_set_align(ui_LabelRelay1, LV_ALIGN_CENTER);
    lv_label_set_text(ui_LabelRelay1, "Relay 1");
    lv_obj_set_style_text_color(ui_LabelRelay1, lv_color_hex(0x696969), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_LabelRelay1, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_LabelRelay1, &lv_font_montserrat_48, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_PanelMusicPlayer = lv_obj_create(ui_ScreenPlayer);
    lv_obj_set_width(ui_PanelMusicPlayer, 660);
    lv_obj_set_height(ui_PanelMusicPlayer, 480);
    lv_obj_set_x(ui_PanelMusicPlayer, 30);
    lv_obj_set_y(ui_PanelMusicPlayer, 30);
    lv_obj_clear_flag(ui_PanelMusicPlayer, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_set_style_radius(ui_PanelMusicPlayer, 20, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_PanelMusicPlayer, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_PanelMusicPlayer, 15, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui_PanelMusicPlayer, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui_PanelMusicPlayer, 30, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui_PanelMusicPlayer, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui_PanelMusicPlayer, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui_PanelMusicPlayer, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui_PanelMusicPlayer, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_ImgButtonPrev = lv_imgbtn_create(ui_PanelMusicPlayer);
    lv_imgbtn_set_src(ui_ImgButtonPrev, LV_IMGBTN_STATE_RELEASED, NULL, &ui_img_icon_music_pre_png, NULL);
    lv_imgbtn_set_src(ui_ImgButtonPrev, LV_IMGBTN_STATE_PRESSED, NULL, &ui_img_icon_music_pre_png, NULL);
    lv_imgbtn_set_src(ui_ImgButtonPrev, LV_IMGBTN_STATE_DISABLED, NULL, &ui_img_icon_music_pre_png, NULL);
    lv_imgbtn_set_src(ui_ImgButtonPrev, LV_IMGBTN_STATE_CHECKED_PRESSED, NULL, &ui_img_icon_music_pre_png, NULL);
    lv_imgbtn_set_src(ui_ImgButtonPrev, LV_IMGBTN_STATE_CHECKED_RELEASED, NULL, &ui_img_icon_music_pre_png, NULL);
    lv_imgbtn_set_src(ui_ImgButtonPrev, LV_IMGBTN_STATE_CHECKED_DISABLED, NULL, &ui_img_icon_music_pre_png, NULL);
    lv_obj_set_height(ui_ImgButtonPrev, 72);
    lv_obj_set_width(ui_ImgButtonPrev, LV_SIZE_CONTENT);
    lv_obj_set_x(ui_ImgButtonPrev, 102);
    lv_obj_set_y(ui_ImgButtonPrev, 138);

    ui_LabelMusicPlayer = lv_label_create(ui_PanelMusicPlayer);
    lv_obj_set_width(ui_LabelMusicPlayer, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_LabelMusicPlayer, LV_SIZE_CONTENT);
    lv_obj_set_x(ui_LabelMusicPlayer, 0);
    lv_obj_set_y(ui_LabelMusicPlayer, -190);
    lv_obj_set_align(ui_LabelMusicPlayer, LV_ALIGN_CENTER);
    lv_label_set_text(ui_LabelMusicPlayer, "---------");
    lv_obj_set_style_text_color(ui_LabelMusicPlayer, lv_color_hex(0xA9A8A8), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_LabelMusicPlayer, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_LabelMusicPlayer, &lv_font_montserrat_30, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_ImgButtonNext = lv_imgbtn_create(ui_PanelMusicPlayer);
    lv_imgbtn_set_src(ui_ImgButtonNext, LV_IMGBTN_STATE_RELEASED, NULL, &ui_img_icon_music_next_png, NULL);
    lv_imgbtn_set_src(ui_ImgButtonNext, LV_IMGBTN_STATE_PRESSED, NULL, &ui_img_icon_music_next_png, NULL);
    lv_imgbtn_set_src(ui_ImgButtonNext, LV_IMGBTN_STATE_DISABLED, NULL, &ui_img_icon_music_next_png, NULL);
    lv_imgbtn_set_src(ui_ImgButtonNext, LV_IMGBTN_STATE_CHECKED_PRESSED, NULL, &ui_img_icon_music_next_png, NULL);
    lv_imgbtn_set_src(ui_ImgButtonNext, LV_IMGBTN_STATE_CHECKED_RELEASED, NULL, &ui_img_icon_music_next_png, NULL);
    lv_imgbtn_set_src(ui_ImgButtonNext, LV_IMGBTN_STATE_CHECKED_DISABLED, NULL, &ui_img_icon_music_next_png, NULL);
    lv_obj_set_height(ui_ImgButtonNext, 72);
    lv_obj_set_width(ui_ImgButtonNext, LV_SIZE_CONTENT);
    lv_obj_set_x(ui_ImgButtonNext, 486);
    lv_obj_set_y(ui_ImgButtonNext, 138);

    ui_SliderMusic = lv_slider_create(ui_PanelMusicPlayer);
    lv_slider_set_value(ui_SliderMusic, 65, LV_ANIM_OFF);
    if(lv_slider_get_mode(ui_SliderMusic) == LV_SLIDER_MODE_RANGE) lv_slider_set_left_value(ui_SliderMusic, 0, LV_ANIM_OFF);
    lv_obj_set_width(ui_SliderMusic, 500);
    lv_obj_set_height(ui_SliderMusic, 10);
    lv_obj_set_x(ui_SliderMusic, 80);
    lv_obj_set_y(ui_SliderMusic, 421);
    lv_obj_set_style_bg_color(ui_SliderMusic, lv_color_hex(0x333232), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_SliderMusic, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_set_style_bg_color(ui_SliderMusic, lv_color_hex(0x7D7D7D), LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_SliderMusic, 255, LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_color(ui_SliderMusic, lv_color_hex(0xC4C4C4), LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui_SliderMusic, LV_GRAD_DIR_HOR, LV_PART_INDICATOR | LV_STATE_DEFAULT);

    lv_obj_set_style_bg_color(ui_SliderMusic, lv_color_hex(0xC4C4C4), LV_PART_KNOB | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_SliderMusic, 255, LV_PART_KNOB | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui_SliderMusic, 12, LV_PART_KNOB | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui_SliderMusic, 12, LV_PART_KNOB | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui_SliderMusic, 12, LV_PART_KNOB | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui_SliderMusic, 12, LV_PART_KNOB | LV_STATE_DEFAULT);

    ui_ImgButtonList = lv_imgbtn_create(ui_PanelMusicPlayer);
    lv_imgbtn_set_src(ui_ImgButtonList, LV_IMGBTN_STATE_RELEASED, NULL, &ui_img_icon_music_list_png, NULL);
    lv_imgbtn_set_src(ui_ImgButtonList, LV_IMGBTN_STATE_PRESSED, NULL, &ui_img_icon_music_list_png, NULL);
    lv_imgbtn_set_src(ui_ImgButtonList, LV_IMGBTN_STATE_DISABLED, NULL, &ui_img_icon_music_list_png, NULL);
    lv_imgbtn_set_src(ui_ImgButtonList, LV_IMGBTN_STATE_CHECKED_PRESSED, NULL, &ui_img_icon_music_list_png, NULL);
    lv_imgbtn_set_src(ui_ImgButtonList, LV_IMGBTN_STATE_CHECKED_RELEASED, NULL, &ui_img_icon_music_list_png, NULL);
    lv_imgbtn_set_src(ui_ImgButtonList, LV_IMGBTN_STATE_CHECKED_DISABLED, NULL, &ui_img_icon_music_list_png, NULL);
    lv_obj_set_height(ui_ImgButtonList, 50);
    lv_obj_set_width(ui_ImgButtonList, LV_SIZE_CONTENT);
    lv_obj_set_x(ui_ImgButtonList, 411);
    lv_obj_set_y(ui_ImgButtonList, 296);

    ui_ImagePlay = lv_imgbtn_create(ui_PanelMusicPlayer);
    lv_imgbtn_set_src(ui_ImagePlay, LV_IMGBTN_STATE_RELEASED, NULL, &ui_img_icon_music_play_png, NULL);
    lv_imgbtn_set_src(ui_ImagePlay, LV_IMGBTN_STATE_PRESSED, NULL, &ui_img_icon_music_play_png, NULL);
    lv_imgbtn_set_src(ui_ImagePlay, LV_IMGBTN_STATE_DISABLED, NULL, &ui_img_icon_music_play_png, NULL);
    lv_imgbtn_set_src(ui_ImagePlay, LV_IMGBTN_STATE_CHECKED_PRESSED, NULL, &ui_img_icon_music_pause_png, NULL);
    lv_imgbtn_set_src(ui_ImagePlay, LV_IMGBTN_STATE_CHECKED_RELEASED, NULL, &ui_img_icon_music_pause_png, NULL);
    lv_imgbtn_set_src(ui_ImagePlay, LV_IMGBTN_STATE_CHECKED_DISABLED, NULL, &ui_img_icon_music_pause_png, NULL);
    lv_obj_set_width(ui_ImagePlay, 148);
    lv_obj_set_height(ui_ImagePlay, 148);
    lv_obj_set_x(ui_ImagePlay, 246);
    lv_obj_set_y(ui_ImagePlay, 90);
    lv_obj_add_flag(ui_ImagePlay, LV_OBJ_FLAG_CHECKABLE);
    lv_obj_add_flag(ui_ImagePlay, LV_OBJ_FLAG_CLICKABLE);

    ui_ImageMusicMode = lv_imgbtn_create(ui_PanelMusicPlayer);
    lv_imgbtn_set_src(ui_ImageMusicMode, LV_IMGBTN_STATE_RELEASED, NULL, &ui_img_icon_music_cycle_all_png, NULL);
    lv_imgbtn_set_src(ui_ImageMusicMode, LV_IMGBTN_STATE_PRESSED, NULL, &ui_img_icon_music_cycle_all_png, NULL);
    lv_imgbtn_set_src(ui_ImageMusicMode, LV_IMGBTN_STATE_DISABLED, NULL, &ui_img_icon_music_cycle_all_png, NULL);
    lv_imgbtn_set_src(ui_ImageMusicMode, LV_IMGBTN_STATE_CHECKED_PRESSED, NULL, &ui_img_icon_music_cycle_one_png, NULL);
    lv_imgbtn_set_src(ui_ImageMusicMode, LV_IMGBTN_STATE_CHECKED_RELEASED, NULL, &ui_img_icon_music_cycle_one_png, NULL);
    lv_imgbtn_set_src(ui_ImageMusicMode, LV_IMGBTN_STATE_CHECKED_DISABLED, NULL, &ui_img_icon_music_cycle_one_png, NULL);
    lv_obj_set_width(ui_ImageMusicMode, 60);
    lv_obj_set_height(ui_ImageMusicMode, 60);
    lv_obj_set_x(ui_ImageMusicMode, 199);
    lv_obj_set_y(ui_ImageMusicMode, 296);
    lv_obj_add_flag(ui_ImageMusicMode, LV_OBJ_FLAG_CHECKABLE);
    lv_obj_add_flag(ui_ImageMusicMode, LV_OBJ_FLAG_CLICKABLE);

    ui_ImageSoundDown = lv_img_create(ui_PanelMusicPlayer);
    lv_img_set_src(ui_ImageSoundDown, &ui_img_icon_sound_donw_png);
    lv_obj_set_width(ui_ImageSoundDown, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_ImageSoundDown, LV_SIZE_CONTENT);
    lv_obj_set_x(ui_ImageSoundDown, 34);
    lv_obj_set_y(ui_ImageSoundDown, 408);
    lv_obj_add_flag(ui_ImageSoundDown, LV_OBJ_FLAG_ADV_HITTEST);
    lv_obj_clear_flag(ui_ImageSoundDown, LV_OBJ_FLAG_SCROLLABLE);

    ui_ImageSoundUp = lv_img_create(ui_PanelMusicPlayer);
    lv_img_set_src(ui_ImageSoundUp, &ui_img_icon_sound_up_png);
    lv_obj_set_width(ui_ImageSoundUp, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_ImageSoundUp, LV_SIZE_CONTENT);
    lv_obj_set_x(ui_ImageSoundUp, 594);
    lv_obj_set_y(ui_ImageSoundUp, 408);
    lv_obj_add_flag(ui_ImageSoundUp, LV_OBJ_FLAG_ADV_HITTEST);
    lv_obj_clear_flag(ui_ImageSoundUp, LV_OBJ_FLAG_SCROLLABLE);


    ui_PanelBoard = lv_obj_create(ui_ScreenPlayer);
    lv_obj_set_width(ui_PanelBoard, 720);
    lv_obj_set_height(ui_PanelBoard, 720);
    lv_obj_set_align(ui_PanelBoard, LV_ALIGN_CENTER);
    lv_obj_clear_flag(ui_PanelBoard, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_set_style_bg_color(ui_PanelBoard, lv_color_hex(0x0D0D0D), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_PanelBoard, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui_PanelBoard, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui_PanelBoard, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui_PanelBoard, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui_PanelBoard, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui_PanelBoard, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui_PanelBoard, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_add_flag(ui_PanelBoard, LV_OBJ_FLAG_HIDDEN);

    ui_RollerMusic = lv_roller_create(ui_PanelBoard);
    lv_roller_set_options(ui_RollerMusic,
                          "---\n---\n---",
                          LV_ROLLER_MODE_NORMAL);
    lv_obj_set_width(ui_RollerMusic, 720);
    lv_obj_set_height(ui_RollerMusic, 576);
    lv_obj_set_x(ui_RollerMusic, 0);
    lv_obj_set_y(ui_RollerMusic, 144);
    // lv_obj_add_flag(ui_RollerMusic, LV_OBJ_FLAG_HIDDEN);
    lv_obj_set_style_text_color(ui_RollerMusic, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_RollerMusic, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_RollerMusic, &lv_font_montserrat_30, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui_RollerMusic, 10, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_RollerMusic, lv_color_hex(0x1F1F1F), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_RollerMusic, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui_RollerMusic, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_set_style_text_color(ui_RollerMusic, lv_color_hex(0xFFA300), LV_PART_SELECTED | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_RollerMusic, 255, LV_PART_SELECTED | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_RollerMusic, lv_color_hex(0xFFFFFF), LV_PART_SELECTED | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_RollerMusic, 25, LV_PART_SELECTED | LV_STATE_DEFAULT);

    ui_LabelMusicList = lv_label_create(ui_RollerMusic);
    lv_obj_set_width(ui_LabelMusicList, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_LabelMusicList, LV_SIZE_CONTENT);
    lv_obj_set_x(ui_LabelMusicList, 0);
    lv_obj_set_y(ui_LabelMusicList, -232);
    lv_obj_set_align(ui_LabelMusicList,LV_ALIGN_CENTER);
    lv_label_set_text(ui_LabelMusicList, "Music List");
    lv_obj_set_style_text_color(ui_LabelMusicList, lv_color_hex(0x545454), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_LabelMusicList, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_LabelMusicList, &lv_font_montserrat_30, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_ImageMusicClose = lv_imgbtn_create(ui_RollerMusic);
    lv_imgbtn_set_src(ui_ImageMusicClose, LV_IMGBTN_STATE_RELEASED, NULL, &ui_img_icon_music_close_png, NULL);
    lv_imgbtn_set_src(ui_ImageMusicClose, LV_IMGBTN_STATE_PRESSED, NULL, &ui_img_icon_music_close_png, NULL);
    lv_imgbtn_set_src(ui_ImageMusicClose, LV_IMGBTN_STATE_DISABLED, NULL, &ui_img_icon_music_close_png, NULL);
    lv_imgbtn_set_src(ui_ImageMusicClose, LV_IMGBTN_STATE_CHECKED_PRESSED, NULL, &ui_img_icon_music_close_png, NULL);
    lv_imgbtn_set_src(ui_ImageMusicClose, LV_IMGBTN_STATE_CHECKED_RELEASED, NULL, &ui_img_icon_music_close_png, NULL);
    lv_imgbtn_set_src(ui_ImageMusicClose, LV_IMGBTN_STATE_CHECKED_DISABLED, NULL, &ui_img_icon_music_close_png, NULL);
    lv_obj_set_width(ui_ImageMusicClose, 36);
    lv_obj_set_height(ui_ImageMusicClose, 36);
    lv_obj_set_x(ui_ImageMusicClose, 612);
    lv_obj_set_y(ui_ImageMusicClose, 12);
    lv_obj_add_flag(ui_ImageMusicClose, LV_OBJ_FLAG_CHECKABLE);
    lv_obj_add_flag(ui_ImageMusicClose, LV_OBJ_FLAG_CLICKABLE);
    lv_obj_add_flag(ui_ImageMusicClose, LV_OBJ_FLAG_HIDDEN);

    lv_obj_add_event_cb(ui_PanelRelay0, ui_event_PanelRelay0, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_PanelRelay1, ui_event_PanelRelay1, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_ImgButtonPrev, ui_event_ImgButtonPrev, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_ImgButtonNext, ui_event_ImgButtonNext, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_SliderMusic, ui_event_SliderMusic, LV_EVENT_ALL, NULL); //Volume
    lv_obj_add_event_cb(ui_ImgButtonList, ui_event_ImgButtonList, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_ImagePlay, ui_event_ImagePlay, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_ImageMusicMode, ui_event_ImageMusicMode, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_RollerMusic, ui_event_RollerMusic, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_ImageMusicClose, ui_event_ImageMusicClose, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_ScreenPlayer, ui_event_ScreenPlayer, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_PanelBoard, ui_event_PanelBoard, LV_EVENT_ALL, NULL);
    
    char roller_str[MAX_MUSIC_LIST_LEN];
    music_scan_list(roller_str);
    lv_roller_set_options(ui_RollerMusic, roller_str, LV_ROLLER_MODE_NORMAL);
}
