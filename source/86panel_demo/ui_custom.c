/*********************
 *      INCLUDES
 *********************/
#include "ui_custom.h"

/**********************
 *  GLOBAL VARIABLES
 *********************/
/*Timer*/
lv_timer_t * ui_Timer;
int timer_count = 60;

/*Wlan*/
wifi_network networks[MAX_NETWORKS];
int network_count = 0;

/*Music*/
static int32_t fd_mpv;
static pid_t music_pid;
static struct sigaction music_act;
struct sockaddr_un music_addr;
static time_t music_dir_last_mtime = 0;
static char current_mp3_string[MAX_MUSIC_LIST_LEN];

struct Music_Node *playing_music_node;  
struct Music_Node *playing_music_head;

/**********************
 *  STATIC FUNCTIONS
 **********************/
static void update_wifi_status(void);
static void lvgl_taskmain_cb(lv_timer_t *timer);
static void update_eth_status(void);
static char* update_time(void);
static void format_and_update_labels(const char *time_str);
static void wifi_conf_get(char* ssid, char* passwd);

/*Timer*/
static void lvgl_taskmain_cb(lv_timer_t *timer)
{
    if(timer_count % 5 == 0){
        if(strcmp(device_model, LUCKFOX_PICO_86PANEL_W) == 0) 
            update_wifi_status();
        update_eth_status();
    }
    //if(timer_count / 3600 == 1){
    if(timer_count / 60 == 1){
        timer_count = 0;
        char* update = update_time();
        //if(update == NULL){
        //    lv_label_set_text(ui_LabelDate, "XXXX-XX-XX XXX");
        //    lv_label_set_text(ui_LabelTime, "00:00");
        //    perror("update_time return NULL");
        //    return;
        //}else{
        //    format_and_update_labels(update);
        //} 
        if(update == NULL){
            perror("update_time return NULL");
            return;
        }else{
            format_and_update_labels(update);
        }
    }
    time_t now = time(NULL);
    struct tm *tm_now = localtime(&now);
    char current_time_str[30];
    strftime(current_time_str, sizeof(current_time_str), "%Y-%m-%d %b %H:%M:%S", tm_now);
    format_and_update_labels(current_time_str);
    timer_count++;
}

static void update_wifi_status(void)
{
    FILE *fp;
    char command[MAX_LINE_LEN];
    char result[MAX_LINE_LEN];
    char ssid[MAX_LINE_LEN] = {0};
    char ip[MAX_LINE_LEN] = {0};
    strcpy(command, "wpa_cli status");
 
    fp = popen(command, "r");
    if (fp == NULL) {
        printf("Failed to run command\n");
        pclose(fp);
        return ;
    }
    while (fgets(result, sizeof(result)-1, fp) != NULL)
    {
       if(strstr(result, "wpa_state=SCANNING"))
        {
            break;
        }else if (strstr(result, "ssid=")) {
            sscanf(result, "ssid=%[^ \n]", ssid);
        } else if (strstr(result, "ip_address=")) {
            sscanf(result, "ip_address=%[^ \n]", ip);
        }
    }
    if(strlen(ssid) == 0) 
    {
        lv_label_set_text(ui_LabelWifiName, "------------");
        lv_obj_set_style_text_color(ui_LabelWifiName, lv_color_hex(0xA9A8A8), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_border_color(ui_PanelWifi, lv_color_hex(0x1F1F1F), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_text_color(ui_LabelWLAN, lv_color_hex(0x545454), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_img_set_src(ui_ImageWifi, &ui_img_icon_wifi_off_png);
    }
    else
    {
        lv_label_set_text(ui_LabelWifiName, ssid);
        lv_obj_set_style_border_color(ui_PanelWifi, lv_color_hex(0x3F3622), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_text_color(ui_LabelWifiName, lv_color_hex(0xF6AC05), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_text_color(ui_LabelWLAN, lv_color_hex(0xF6AC05), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_img_set_src(ui_ImageWifi, &ui_img_icon_wifi_on_png);
    }
    lv_obj_set_style_text_font(ui_LabelWifiName, &lv_font_montserrat_24, LV_PART_MAIN | LV_STATE_DEFAULT);
    if(strlen(ip) == 0)
    {
        lv_label_set_text(ui_LabelWifiIP, "No IP");
        lv_obj_set_style_text_font(ui_LabelWifiIP, &lv_font_montserrat_18, LV_PART_MAIN | LV_STATE_DEFAULT);
    }
    else
    {
        lv_label_set_text(ui_LabelWifiIP, ip);
        lv_obj_set_style_text_font(ui_LabelWifiIP, &lv_font_montserrat_24, LV_PART_MAIN | LV_STATE_DEFAULT);
    }
    pclose(fp);
}

static void update_eth_status(void)
{
    static int last_carrier_state = -1;
    int current_carrier_state = 0;

    FILE *carrier_file = fopen("/sys/class/net/eth0/carrier", "r");
    if (carrier_file != NULL) {
        fscanf(carrier_file, "%d", &current_carrier_state);
        fclose(carrier_file);
    }

    if (current_carrier_state != last_carrier_state) {
        if (current_carrier_state == 1) {
            if (system("pgrep udhcpc") == 0) {
                system("killall udhcpc");
            }
            system("udhcpc -i eth0 > /tmp/udhcpc.log 2>&1 &");
        }
        last_carrier_state = current_carrier_state;
    }

    FILE *fp;
    char command[MAX_LINE_LEN];
    char result[MAX_LINE_LEN];
    char eth_name[MAX_LINE_LEN] = {0};
    char eth_ip_address[MAX_LINE_LEN] = {0};
    strcpy(command, "ifconfig");

    fp = popen(command, "r");
    if (fp == NULL) {
        printf("Failed to run command\n");
        return;
    }

    int in_eth_block = 0;
    int has_ip = 0;
    while (fgets(result, sizeof(result) - 1, fp) != NULL)
    {
        if (strstr(result, "eth0")) {
            in_eth_block = 1;
            sscanf(result, "%s", eth_name);
            lv_label_set_text(ui_LabelEth, eth_name);
            continue;
        }

        if (in_eth_block && result[0] == '\n') {
            in_eth_block = 0;
            break;
        }

        if (in_eth_block && strstr(result, "inet addr:")) {
            char *ip_start = strstr(result, "inet addr:");
            if (ip_start) {
                ip_start += 10;
                char *ip_end = strchr(ip_start, ' ');
                if (ip_end) {
                    *ip_end = '\0';
                }
                strncpy(eth_ip_address, ip_start, MAX_LINE_LEN - 1);
                eth_ip_address[MAX_LINE_LEN - 1] = '\0';
                has_ip = 1;
            }
            break;
        }
    }
    pclose(fp);

    if ( current_carrier_state == 0 )
    	has_ip = 0;

    if (has_ip) {
        lv_label_set_text(ui_LabelEthIP, eth_ip_address);
        lv_obj_set_style_border_color(ui_PanelEth, lv_color_hex(0x3F3622), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_text_color(ui_LabelEth, lv_color_hex(0xF6AC05), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_img_set_src(ui_ImageEth, &ui_img_icon_eth_on_png);
    } else {
        lv_label_set_text(ui_LabelEth, "------------");
        lv_label_set_text(ui_LabelEthIP, "No IP");
        lv_obj_set_style_text_color(ui_LabelEth, lv_color_hex(0xA9A8A8), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_border_color(ui_PanelEth, lv_color_hex(0x1F1F1F), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_img_set_src(ui_ImageEth, &ui_img_icon_eth_off_png);
    }
}

static char* update_time(void)
{
    static char time_str[20];
    const char *ntp_server = "202.120.2.101";

    int sockfd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (sockfd == -1)
    {
        perror("socket error");
        return NULL;
    }

    struct timeval timeout = {5, 0};
    setsockopt(sockfd, SOL_SOCKET, SO_RCVTIMEO, (char *)&timeout, sizeof(timeout));

    struct addrinfo hints,*results;
    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_DGRAM;
    hints.ai_protocol = IPPROTO_UDP;
    int status = getaddrinfo(ntp_server, "123", &hints, &results);
    if (status != 0)
    {
        printf("getaddrinfo error: %s" ,gai_strerror(status));
        return NULL;
    }
    struct sockaddr_in ntp_addr;
    memcpy(&ntp_addr, results->ai_addr, sizeof(struct sockaddr_in));
    freeaddrinfo(results);
    ntp_addr.sin_port = htons(123);

    char ntp_pkt[48];
    memset(ntp_pkt, 0, sizeof(ntp_pkt));
    ntp_pkt[0] = 0x1b;

    if (sendto(sockfd, ntp_pkt, sizeof(ntp_pkt), 0, (struct sockaddr *)&ntp_addr, sizeof(ntp_addr)) == -1)
    {
        perror("sendto error");
        close(sockfd);
        return NULL;
    }

    int nbytes;
    char buf[1024];
    struct sockaddr_in srv_addr;
    socklen_t srv_addr_len = sizeof(srv_addr);
    while ((nbytes = recvfrom(sockfd, buf, sizeof(buf), 0, (struct sockaddr *)&srv_addr, &srv_addr_len)) == -1)
    {
        if (errno == EAGAIN)
        {
            printf("Timeout occurred while waiting for NTP response.\n");
        }
        else
        {
            perror("recvfrom error");
        }
        close(sockfd);
        return NULL;
    }
    if (nbytes == sizeof(ntp_pkt))
    {
        char command[64];
        unsigned long long *timestamp = (unsigned long long *)&buf[40];
        time_t linux_time = ntohl(*timestamp) - 2208988800UL;

        //linux_time = linux_time + 8*3600;
		struct tm *tm_ntp = localtime(&linux_time);
        
        char temp_time_str[20];
        strftime(temp_time_str, sizeof(temp_time_str), "%Y-%m-%d %H:%M:%S", tm_ntp);
		strftime(time_str, sizeof(time_str), "%Y-%m-%d %b %H:%M:%S", tm_ntp);
		snprintf(command, sizeof(command), "date -s \"%s\"", temp_time_str);
    	system(command);
		system("hwclock -w");
		system("sync");
    }
    else
    {
        printf("Received invalid NTP packet."); 
    }
    close(sockfd);
    return time_str;
}

static void format_and_update_labels(const char *time_str) 
{
    char date_part[30];
    char time_part[20];
    const char *space1 = strchr(time_str, ' ');
    const char *space2 = strchr(space1 + 1, ' ');

    if (space1 && space2) {
        snprintf(date_part, sizeof(date_part), "%.10s %.3s", 
                 time_str,  
                 space1 + 1);

        snprintf(time_part, sizeof(time_part), "%.*s", 5,space2 + 1);
        
        lv_label_set_text(ui_LabelDate, date_part);
        lv_label_set_text(ui_LabelTime, time_part);
    } else {
        fprintf(stderr, "Invalid time string format.\n");
    }
}

/*Wlan*/
static void wifi_conf_get(char* ssid, char* passwd)
{
    FILE *file = fopen(WPA_FILE_PATH, "r");
    if (file == NULL) {
        printf("Failed to open file.\n");
        return ;
    }

    char line[MAX_LINE_LEN];
    int inside_network_block = 0;

    while (fgets(line, MAX_LINE_LEN, file)) {
        // Enter network={} block
        if (strstr(line, "network={")) {
            inside_network_block = 1;
            continue;
        }
        // Exit network={} block
        if (strstr(line, "}")) {
            inside_network_block = 0;
        }
        // Inside network={} block
        if (inside_network_block) {
            if (strstr(line, "ssid=")) {
                sscanf(line, " ssid=\"%[^\"]\"", ssid);
            }
            if (strstr(line, "psk=")) {
                sscanf(line, " psk=\"%[^\"]\"", passwd);
            }
        }
    }
    fclose(file);
    return ;
}

/*Music*/
static void sigaction_exit_handler(int sig) { exit(0); }

static void init_music_node_list(struct Music_Node** head) {
    *head = NULL;
}

static void insert_music_node(struct Music_Node** head, char* filename, int id) {
    struct Music_Node* newNode = (struct Music_Node*)malloc(sizeof(struct Music_Node));
    if (newNode == NULL) {
        printf("Memory allocation failed\n");
        exit(1);
    }
    strcpy(newNode->filename, filename);
    newNode->id = id;

    if (*head == NULL) {
        *head = newNode;
        newNode->prev = newNode;
        newNode->next = newNode;
    } else {
        struct Music_Node* tail = (*head)->prev;
        tail->next = newNode;
        newNode->prev = tail;
        newNode->next = *head;
        (*head)->prev = newNode;
    }
}

static void free_music_node_list(struct Music_Node* head) {
    if (head != NULL) {
        struct Music_Node* current = head->next;
        while (current != head) {
            struct Music_Node* temp = current;
            current = current->next;
            free(temp);
        }
        free(head);
    }
}

/**********************
 *  GLOBAL FUNCTIONS
 **********************/

/*Wlan*/
int wifi_scanning_ssid()
{
    network_count  = 0;
    char command[] = "wpa_cli -i wlan0 scan_results";
    FILE *fp = popen(command, "r");
    if (fp == NULL) {
        perror("Error opening pipe");
        return -1;
    }

    char line[MAX_LINE_LEN];
    // Skip the first two lines as they contain header information
    fgets(line, MAX_LINE_LEN, fp);

    // Parse each line to extract the SSID
    while (fgets(line, MAX_LINE_LEN, fp) != NULL) {
        char *token = strtok(line, "\t ");
        int count = 0;
        while (token != NULL) {
            if (count == 4) { // SSID
                strncpy(networks[network_count].ssid, token, MAX_CONF_LEN);
                networks[network_count].ssid[MAX_CONF_LEN - 1] = '\0'; // Ensure null-termination
            } else if (count == 2) { // Signal level
                networks[network_count].signal_level = atoi(token);
            } else if (count == 3) { // Flags
                strncpy(networks[network_count].flags, token, MAX_CONF_LEN);
                networks[network_count].flags[MAX_CONF_LEN - 1] = '\0'; // Ensure null-termination
            }
            token = strtok(NULL, "\t ");
            count++;
        }
        if (strlen(networks[network_count].ssid) > 0) {
            network_count++;
        }
        if (network_count >= MAX_NETWORKS) {
            break;
        }
    }

    // Create a string with SSIDs separated by '\n'
    char ssid_string[MAX_NETWORKS * (MAX_CONF_LEN + 1)]; // 1 additional character for '\n'
    ssid_string[0] = '\0'; // Ensure ssid_string is empty initially

    for (int i = 0; i < network_count; i++) {
        if(strcmp(networks[i].ssid,"\n") && strlen(networks[i].ssid) < 16 )
        {
            strcat(ssid_string, networks[i].ssid);
        }
    }

    // Print the SSID string
    printf("SSID String:\n%s", ssid_string); 
    if(ssid_string == NULL || *ssid_string == '\0')
    {
        if(ui_DropdownSSID != NULL)
        {
            lv_dropdown_set_options(ui_DropdownSSID, "scanning");
        }
    }
    else
	{
        if(ui_DropdownSSID != NULL)
        {
            strcat(ssid_string, "\n...");
            lv_dropdown_set_options(ui_DropdownSSID, ssid_string);
        }
    }

    pclose(fp);
    return 0;

}

void wifi_connect(const char* ssid, const char* password)
{
    FILE *wpa_supplicant_pipe;
    char buffer[MAX_CONF_LEN];

    // open wpa_supplicant pipe
    wpa_supplicant_pipe = popen("wpa_cli", "w");
    if (wpa_supplicant_pipe == NULL) {
        perror("popen");
        exit(1);
    }
    printf("connect test\n");
    // set network ssid adn psk
    memset(buffer,0,MAX_CONF_LEN);
    snprintf(buffer, MAX_CONF_LEN, "set_network 0 ssid \"%s\"\n", ssid);
    fputs(buffer, wpa_supplicant_pipe);
    
    memset(buffer,0,MAX_CONF_LEN);
    snprintf(buffer, MAX_CONF_LEN, "set_network 0 psk \"%s\"\n", password);
    fputs(buffer, wpa_supplicant_pipe);

    // save wifi conf
    fputs("save_config\n", wpa_supplicant_pipe);
    pclose(wpa_supplicant_pipe);

    // save wifi conf to /etc/wpa_supplicant.conf
    FILE *file = fopen(WPA_FILE_PATH, "r");
    if (file == NULL) {
        printf("Failed to open file.\n");
        return ;
    }

    FILE *temp_file = fopen("temp_wpa_supplicant.conf", "w");
    if (temp_file == NULL) {
        printf("Failed to create temporary file.\n");
        fclose(file);
        return ;
    }

    char line[MAX_LINE_LEN];
    int inside_network_block = 0;

    while (fgets(line, MAX_LINE_LEN, file)) {
        // Enter network={} block
        if (strstr(line, "network={")) {
            inside_network_block = 1;
            fputs(line, temp_file);
            continue;
        }
        // Exit network={} block
        if (strstr(line, "}")) {
            inside_network_block = 0;
        }
        // Inside network={} block
        if (inside_network_block) {
            if (strstr(line, "ssid=")) {
                memset(buffer,0,MAX_CONF_LEN);
                sprintf(buffer, "        ssid=\"%s\"\n",ssid);
                fputs(buffer, temp_file);
            }
            else if (strstr(line, "psk=")) {
                memset(buffer,0,MAX_CONF_LEN);
                sprintf(buffer, "        psk=\"%s\"\n",password);
                fputs(buffer, temp_file);
            }
            else {
                fputs(line, temp_file);
            }
        }
        else {
            fputs(line, temp_file);
        }
    }

    fclose(file);
    fclose(temp_file);

    remove(WPA_FILE_PATH);    
    rename("temp_wpa_supplicant.conf", WPA_FILE_PATH);
    //printf("SSID and PSK replaced successfully.\n");

    // reconnect wifi
    // system("killall -9 wpa_cli");
    system("killall -9 wpa_supplicant");
    system("killall -9 udhcpc");

    sleep(1);
    system("wpa_supplicant -B -i wlan0 -c /etc/wpa_supplicant.conf");
    sleep(1);
    system("wpa_cli reconfigure &");
    sleep(5);
    system("udhcpc -i wlan0 &");
    return ;
}

int wifi_disconnect(const char *interface) {
      char command[128];
    snprintf(command, sizeof(command), "wpa_cli -i %s disconnect", interface);
    int ret = system(command);
    if (ret == -1) {
        perror("system");
        return -1;
    }

    snprintf(command, sizeof(command), "ifconfig %s 0.0.0.0", interface);
    ret = system(command);
    if (ret == -1) {
        perror("system");
        return -1;
    }

    return 0;
}

void wifi_scr_init()
{
    char ssid[MAX_CONF_LEN];
    char passwd[MAX_CONF_LEN];

    memset(ssid, 0, MAX_CONF_LEN);
    memset(passwd, 0, MAX_CONF_LEN);
    wifi_conf_get(ssid,passwd);

    if (strlen(ssid) == 0) {
        ssid[0] = '\0';
    }
    if (strlen(passwd) == 0) {
        passwd[0] = '\0';
    }

    lv_textarea_set_text(ui_TextAreaSSID, ssid);
    lv_textarea_set_text(ui_TextAreaPW, passwd);
}

/*Music*/
void music_pause(int sta)
{
    char cmd[256];
    sprintf(cmd, "{ \"command\": [\"set_property\", \"pause\",%s] }\n", sta ? "true" : "false");
    // printf("%s\n", cmd);
    write(fd_mpv, cmd, strlen(cmd));
}

void music_set_pos(int music_id)
{
    int read_flag = 0;
    char cmd[256];
    sprintf(cmd, "{ \"command\": [\"set_property\", \"playlist-pos\", %d] }\n",music_id);
    //printf("%s\n", cmd);
    write(fd_mpv, cmd, strlen(cmd)); 
    // set name
    lv_label_set_text(ui_LabelMusicPlayer, playing_music_node->filename);
}

void music_set_volume(int volume)
{
    char cmd[256];
    sprintf(cmd, "{ \"command\": [\"set_property\", \"volume\", %d] }\n",volume);
    //printf("%s\n", cmd);
    write(fd_mpv, cmd, strlen(cmd));        
}

void music_set_mode(int mode)
{
    char cmd[256];
    sprintf(cmd, "{ \"command\": [\"set_property\", \"loop\",%s] }\n", mode ? "true" : "false");
    //printf("%s\n", cmd);
    write(fd_mpv, cmd, strlen(cmd)); 
}

int music_scan_list(char *mp3_string)
{
    DIR *dir;
    struct dirent *entry;
    int id_num = 0;
    int i;
    char cmd[256];
    struct stat dir_stat;
    
    if (stat(MUSIC_DIR_PATH, &dir_stat) != 0) {
        perror("stat error: ");
    }else if (music_dir_last_mtime != 0 && dir_stat.st_mtime == music_dir_last_mtime) {
        strcpy(mp3_string, (const char *)current_mp3_string);
        return 0;
    }

    if (dir_stat.st_mtime == 0) {
        music_dir_last_mtime = dir_stat.st_mtime;
    }else{
        music_dir_last_mtime = dir_stat.st_mtime;
        music_player_thread_exit();
        music_player_thread_init(); 
    }
    
    // Clear Loaded File
    if (playing_music_head != NULL) {
        free_music_node_list(playing_music_head);
    }

    init_music_node_list(&playing_music_head);
    dir = opendir(MUSIC_DIR_PATH); 
    if (dir == NULL) {
        perror("opendir error: ");
        mp3_string[0] = '\0';
        strcat(mp3_string, "NOT FOUND");
        lv_label_set_text(ui_LabelMusicPlayer, "---------");
 
        strcpy(current_mp3_string, (const char *)mp3_string);
        //lv_label_set_text(ui_LabelMusicList, "Music List(0)");
        return -1; 
    }
 
    // Read files from music dir
    while ((entry = readdir(dir)) != NULL) {
        if (entry->d_type == DT_REG) { // common file
            // check .mp3
            char *ext = strrchr(entry->d_name, '.');
            if (ext != NULL && strcmp(ext, ".mp3") == 0) {
                // insert Music Node
                insert_music_node(&playing_music_head, entry->d_name,id_num);
                id_num++;
                //add to mpv list            
                sprintf(cmd, "{ \"command\": [\"loadfile\", \"/music/%s\",\"append\"] }\n",entry->d_name);
                write(fd_mpv, cmd, strlen(cmd));
            }
        }
    }
    closedir(dir);

    // Create roller str
    mp3_string[0] = '\0';
    if (playing_music_head != NULL) {
        struct Music_Node* current = playing_music_head;
        playing_music_node = playing_music_head; 
        for(i = 0;i < id_num;i++) {
            if(i != 0) {
                if(strlen(mp3_string) + strlen(current->filename) + 1 < MAX_MUSIC_LIST_LEN) {
                    strcat(mp3_string,"\n");
                } else {
                    break;
                }     
            }
            if(strlen(mp3_string) + strlen(current->filename) < MAX_MUSIC_LIST_LEN) {
                strcat(mp3_string, current->filename);
            } else {
                break;
            }
            current = current->next;
        }
    }

    if(id_num == 0) {
        lv_label_set_text(ui_LabelMusicPlayer, "---------");
        strcat(mp3_string, "NOT FOUND");
    }

    strcpy(current_mp3_string, mp3_string);
    music_app_init();
    //char MusicList[20];
    //snprintf(MusicList,sizeof(MusicList),"Music List(%d)",id_num);
    //lv_label_set_text(ui_LabelMusicList,MusicList);
    // printf("idnum:%d\n",id_num);

    return 0;
}

int music_player_thread_init()
{
	music_pid = vfork();
	if (music_pid == 0) // child thread
	{  
        char cmd[256];
        prctl(PR_SET_PDEATHSIG, SIGKILL);
        execlp("mpv", "mpv", "--quiet", "--no-terminal", "--no-video", "--idle=yes", "--term-status-msg=", "--input-ipc-server=/tmp/mpvsocket", NULL);        
        return 0;
	}
	else if (music_pid > 0) // parent thread
	{

        sleep(1);
        close(0);

        music_act.sa_handler = sigaction_exit_handler;
        sigfillset(&music_act.sa_mask);
        music_act.sa_flags = SA_RESTART; /* don't fiddle with EINTR */
        sigaction(SIGUSR1, &music_act, NULL);
        music_addr.sun_family = AF_UNIX;
        strcpy(music_addr.sun_path, "/tmp/mpvsocket");
        
        fd_mpv = socket(AF_UNIX, SOCK_STREAM, 0);
        if (fd_mpv == -1)
        {   
            perror("Create socket failed\n");
            return -1;
        }
        sleep(0.1);
    	// socket connect
		if (connect(fd_mpv, (struct sockaddr *)&music_addr, sizeof(music_addr)) == -1)
        {
            perror("Cannot connect to socket \n");
            return -1;
        }
    }
    else
    {
        perror("fork error:\n");
        return -1;
    }

    return 0;
}

int music_player_thread_exit()
{
    system("killall mpv");
    return 0;
}

int music_app_init()
{
    music_set_pos(0);
    music_pause(1);
    music_set_volume(50);
    music_set_mode(1);
    return 0;
}

int music_app_quit()
{
    music_pause(1);
    return 0;
}

/*Gpio*/
int gpio_export(int gpio_pin)
{
    FILE *export_file = fopen("/sys/class/gpio/export", "w");
    if (export_file == NULL) {
        perror("Failed to open GPIO export file");
        return -1;
    }
    fprintf(export_file, "%d", gpio_pin);
    fclose(export_file);
    return 0;
}

int gpio_out_direction(int gpio_pin)
{
    char direction_path[50];
    snprintf(direction_path, sizeof(direction_path), "/sys/class/gpio/gpio%d/direction", gpio_pin);
    FILE *direction_file = fopen(direction_path, "w");
    if (direction_file == NULL) {
        perror("Failed to open GPIO direction file");
        return -1;
    }   
    fprintf(direction_file, "out");
    fclose(direction_file);
    return 0;
}

int set_gpio(int gpio_pin, int val)
{
    int len;
    char buff[10];
    char filename[64];
    int ret = 0;
    int result = 0;

    memset(filename, 0x0, sizeof(filename));
    sprintf(filename, "/sys/class/gpio/gpio%d/value", gpio_pin);
    FILE *value_file = fopen(filename, "w");
    if (value_file == NULL)
    {
        ret = gpio_export(gpio_pin);
        if (ret < 0)
        {
            return ret;
        }
        else
        {
            result = gpio_out_direction(gpio_pin);
            if(result < 0)
                return result;
            if (value_file == NULL)
                return ret;
        }
    }
    memset(buff, 0x0, sizeof(buff));
    len = sprintf(buff, "%s", val ? "1" : "0");
    fprintf(value_file,"%s",buff);
    if (ret != len)
    {
        fclose(value_file);
        return ret;
    }
    fclose(value_file);
    return 0;
}

/*Timer*/
void main_timer_init()
{
    timer_count = 0;
    char* update = update_time();
    if(update != NULL){
        format_and_update_labels(update);
    }
    
    ui_Timer = lv_timer_create(lvgl_taskmain_cb, 1000, 0);
    lv_timer_set_repeat_count(ui_Timer, -1); 
}

void main_timer_release()
{
    lv_timer_del(ui_Timer);
}

void custom_init()
{
    // Time Zone
    setenv("TZ", "UTC-8", 1);
    tzset();

    // Relay
    gpio_export(32);
    gpio_out_direction(32);

    gpio_export(33);
    gpio_out_direction(33);
    
    // Music
    system("mpv 2>&1 >/dev/null");
    music_player_thread_init();
}
