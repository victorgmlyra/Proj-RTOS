#include <stdio.h>
#include <pthread.h>
#include <stdint.h>
#include "event.h"
#include "sm.h"
#include "transitions.h"


enum {
        EVENT_A1 = USER_EVENT,
        EVENT_A2,
        EVENT_B1,
        EVENT_B2,
        EVENT_C,
        EVENT_R,
        EVENT_D,
        EVENT_N
};

uint8_t foo;

cb_status init_cb(event_t ev)
{
        printf("Hermano eh um bom companheiro");
        Topo_init_tran();
        return EVENT_HANDLED;
}

cb_status principal(event_t ev)
{
        switch(ev) {
        case ENTRY_EVENT:
                printf("entrada-ENTRY;");
                return EVENT_HANDLED;
        case EXIT_EVENT:
                printf("entrada-EXIT;");
                return EVENT_HANDLED;
        case INIT_EVENT:
                printf("entrada-INIT;");
                principal_init_tran();
                return EVENT_HANDLED;
        case EVENT_B2:
                printf("entrada-B2;");
                principal_adm_tran();                   //Transição principal->ADM *nao feito ainda
                return EVENT_HANDLED;
        case EVENT_B1:
                printf("entrada-B1;");
                principal_block_tran();                 //Transição principal->block *nao feito ainda
                return EVENT_HANDLED;
        }

        return EVENT_NOT_HANDLED;
}

cb_status aguardo(event_t ev)
{
        switch(ev) {
        case ENTRY_EVENT:
                printf("aguardo-ENTRY;");
                return EVENT_HANDLED;
        case EXIT_EVENT:
                printf("aguardo-EXIT;");
                return EVENT_HANDLED;
        case INIT_EVENT:
                printf("aguardo-INIT;");
                return EVENT_HANDLED;
        case EVENT_A1:
                printf("aguardo-A;");
                aguardo_entrada_tran();
                return EVENT_HANDLED;
        case EVENT_A2:
                printf("aguardo-A2;");
                aguardo_saida_tran();
                return EVENT_HANDLED;
        }

        return EVENT_NOT_HANDLED;
}

cb_status entrada(event_t ev)
{
        switch(ev) {
        case ENTRY_EVENT:
                printf("entrada-ENTRY;");
                return EVENT_HANDLED;
        case EXIT_EVENT:
                printf("entrada-EXIT;");
                return EVENT_HANDLED;
        case INIT_EVENT:
                printf("entrada-INIT");
                entrada_principal_local_tran();
                return EVENT_HANDLED;
        }

        return EVENT_NOT_HANDLED;
}

cb_status s2_cb(event_t ev)
{
        switch(ev) {
        case ENTRY_EVENT:
                printf("s2-ENTRY;");
                return EVENT_HANDLED;
        case EXIT_EVENT:
                printf("s2-EXIT;");
                return EVENT_HANDLED;
        case INIT_EVENT:
                printf("s2-INIT;");
                s2_init_tran();
                return EVENT_HANDLED;
        case EVENT_C:
                printf("s2-C;");
                s2_s1_tran();
                return EVENT_HANDLED;
        case EVENT_F:
                printf("s2-F;");
                s2_s11_tran();
                return EVENT_HANDLED;
        case EVENT_I:
                if (!foo) {
                        foo = 1;
                        printf("s2-I;");
                        return EVENT_HANDLED;
                }
                break;
        }

        return EVENT_NOT_HANDLED;
}

cb_status s21_cb(event_t ev)
{
        switch(ev) {
        case ENTRY_EVENT:
                printf("s21-ENTRY;");
                return EVENT_HANDLED;
        case EXIT_EVENT:
                printf("s21-EXIT;");
                return EVENT_HANDLED;
        case INIT_EVENT:
                printf("s21-INIT;");
                s21_init_tran();
                return EVENT_HANDLED;
        case EVENT_A:
                printf("s21-A;");
                s21_s21_tran();
                return EVENT_HANDLED;
        case EVENT_B:
                printf("s21-B;");
                s21_s211_local_tran();
                return EVENT_HANDLED;
        case EVENT_G:
                printf("s21-G;");
                s21_s11_tran();
                return EVENT_HANDLED;
        }

        return EVENT_NOT_HANDLED;
}

cb_status s211_cb(event_t ev)
{
        switch(ev) {
        case ENTRY_EVENT:
                printf("s211-ENTRY;");
                return EVENT_HANDLED;
        case EXIT_EVENT:
                printf("s211-EXIT;");
                return EVENT_HANDLED;
        case EVENT_D:
                printf("s211-D;");
                s211_s21_local_tran();
                return EVENT_HANDLED;
        case EVENT_H:
                printf("s211-H;");
                s211_s_local_tran();
                return EVENT_HANDLED;
        }

        return EVENT_NOT_HANDLED;
}


pthread_mutex_t handling_mutex;
pthread_cond_t handling_cv;


void *event_thread(void *vargp)
{
        event_t ev;

        while (1) {
                ev = wait_for_events();
                if (ev == EMPTY_EVENT)
                        break;
                printf("\n");
                dispatch_event(ev);
                pthread_mutex_lock(&handling_mutex);
                pthread_cond_signal(&handling_cv);
                pthread_mutex_unlock(&handling_mutex);
        }

        return NULL;
}


int main(int argc, char* argv[])
{
        char *ptr;
        pthread_t tid;

        if (argc < 2) {
                fprintf(stderr, "Usage: %s inputs\n", argv[0]);
                return -1;
        }

        pthread_mutex_init(&handling_mutex, 0);
        pthread_cond_init(&handling_cv, 0);
        pthread_create(&tid, NULL, event_thread, NULL);

        init_machine(init_cb);
        ptr = argv[1];
        while(*ptr) {
                switch (*ptr++) {
                case 'A':
                case 'a':
                        set_event(EVENT_A);
                        break;
                case 'B':
                case 'b':
                        set_event(EVENT_B);
                        break;
                case 'C':
                case 'c':
                        set_event(EVENT_C);
                        break;
                case 'D':
                case 'd':
                        set_event(EVENT_D);
                        break;
                case 'E':
                case 'e':
                        set_event(EVENT_E);
                        break;
                case 'F':
                case 'f':
                        set_event(EVENT_F);
                        break;
                case 'G':
                case 'g':
                        set_event(EVENT_G);
                        break;
                case 'H':
                case 'h':
                        set_event(EVENT_H);
                        break;
                case 'I':
                case 'i':
                        set_event(EVENT_I);
                        break;
                default:
                        set_event(EVENT_I+1);
                        /* continue; */
                }
                pthread_mutex_lock(&handling_mutex);
                pthread_cond_wait(&handling_cv, &handling_mutex);
                pthread_mutex_unlock(&handling_mutex);
        }
        printf("\n");

        set_event(EMPTY_EVENT);
        pthread_join(tid, NULL);

        return 0;
}
