// ping_handler.c - corriger les includes
#include <pthread.h>
#include <sys/time.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "eez_ui/actions.h"  // ← eez_ui/ au lieu de ui/
#include "eez_ui/vars.h"     // ← eez_ui/ au lieu de ui/

static pthread_t ping_thread;
static bool ping_running = false;

typedef struct {
    char target[256];
} ping_data_t;

void ping_completed(int time_ms, bool success);
void ping_start_async(const char* target);

void* ping_thread_func(void* arg) {
    ping_data_t* data = (ping_data_t*)arg;
    
    struct timeval start, end;
    gettimeofday(&start, NULL);
    
    char cmd[512];
    snprintf(cmd, sizeof(cmd), "ping -c 1 -W 2 %s > /dev/null 2>&1", data->target);
    int result = system(cmd);
    
    gettimeofday(&end, NULL);
    int time_ms = (end.tv_sec - start.tv_sec) * 1000 + 
                  (end.tv_usec - start.tv_usec) / 1000;
    
    ping_completed(time_ms, (result == 0));
    
    free(data);
    ping_running = false;
    return NULL;
}

void ping_start_async(const char* target) {
    if (ping_running) return;
    
    ping_data_t* data = malloc(sizeof(ping_data_t));
    strncpy(data->target, target, sizeof(data->target)-1);
    data->target[sizeof(data->target)-1] = '\0';
    
    ping_running = true;
    pthread_create(&ping_thread, NULL, ping_thread_func, data);
    pthread_detach(ping_thread);
}

void action_ping_google(lv_event_t * e) {
    printf("Ping button clicked!\n");
    
    // Mettre à jour les variables formatées
    set_var_ping_status_formatted("Status: Pinging...");
    set_var_ping_time_formatted("Last: ... ms");
    set_var_is_idle(false);    // Spinner visible
    
    ping_start_async("8.8.8.8");
}

void ping_completed(int time_ms, bool success) {
    printf("Ping completed: %s, time: %dms\n", success ? "SUCCESS" : "FAILED", time_ms);
    
    // Mettre à jour les variables originales
    if (success) {
        set_var_ping_status("Success");
        set_var_ping_time(time_ms);
        
        // Mettre à jour les variables formatées
        set_var_ping_status_formatted("Status: Success");
        
        char time_formatted[64];
        snprintf(time_formatted, sizeof(time_formatted), "Last: %d ms", time_ms);
        set_var_ping_time_formatted(time_formatted);
    } else {
        set_var_ping_status("Failed");
        set_var_ping_time(0);
        
        // Mettre à jour les variables formatées
        set_var_ping_status_formatted("Status: Failed");
        set_var_ping_time_formatted("Last: Failed");
    }
    
    set_var_is_idle(true);     // Spinner caché
}