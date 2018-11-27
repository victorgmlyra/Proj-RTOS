#include <stdio.h>
#include <pthread.h>
#include <stdint.h>
#include "event.h"
#include "sm.h"
#include "transitions.h"



enum {
        EVENT_E = USER_EVENT,           // Entrada com cartão comum
        EVENT_S,                        // Saída com cartão comum 
        EVENT_A,                        // Entrada com cartão adm
        EVENT_B,                        // Saída com cartão adm
        EVENT_C,                        // Evento de cadastro
        EVENT_R,                        // Evento de remover cadastro
        EVENT_D,                        // Evento de download do ponto
        EVENT_N                         // Evento de envio de nome
};

cb_status init_cb(event_t ev)
{
        printf("Hermano eh um bom companheiro \n");
        Topo_init_tran();
        return EVENT_HANDLED;
}

cb_status principal(event_t ev)
{
        switch(ev) {
        case ENTRY_EVENT:
                printf("principal-ENTRY; \n");
                return EVENT_HANDLED;
        case EXIT_EVENT:
                printf("principal-EXIT; \n");
                return EVENT_HANDLED;
        case INIT_EVENT:
                printf("principal-INIT; \n");
                principal_init_tran();
                return EVENT_HANDLED;
        case EVENT_B:
                printf("principal-B; \n");
                principal_adm_tran();                   
                return EVENT_HANDLED;
        case EVENT_A:
                printf("principal-A; \n");
                principal_block_tran();                 
                return EVENT_HANDLED;
        }

        return EVENT_NOT_HANDLED;
}

cb_status aguardo(event_t ev)
{
        switch(ev) {
        case ENTRY_EVENT:
                printf("aguardo-ENTRY; \n");
                return EVENT_HANDLED;
        case EXIT_EVENT:
                printf("aguardo-EXIT; \n");
                return EVENT_HANDLED;
        case INIT_EVENT:
                printf("aguardo-INIT; \n");
                return EVENT_HANDLED;
        case EVENT_E:
                printf("aguardo-E; \n");
                aguardo_entrada_tran();
                return EVENT_HANDLED;
        case EVENT_S:
                printf("aguardo-S; \n");
                aguardo_saida_tran();
                return EVENT_HANDLED;
        }

        return EVENT_NOT_HANDLED;
}

cb_status entrada(event_t ev)
{
        switch(ev) {
        case ENTRY_EVENT:
                printf("entrada-ENTRY; \n");
                return EVENT_HANDLED;
        case EXIT_EVENT:
                printf("entrada-EXIT; \n");
                return EVENT_HANDLED;
        case INIT_EVENT:
                printf("entrada-INIT");
                entrada_init_tran();
                return EVENT_HANDLED;
        }

        return EVENT_NOT_HANDLED;
}

cb_status saida(event_t ev)
{
        switch(ev) {
        case ENTRY_EVENT:
                printf("saida-ENTRY; \n");
                return EVENT_HANDLED;
        case EXIT_EVENT:
                printf("saida-EXIT; \n");
                return EVENT_HANDLED;
        case INIT_EVENT:
                printf("saida-INIT; \n");
                saida_init_tran();
                return EVENT_HANDLED;
        }

        return EVENT_NOT_HANDLED;
}

cb_status adm(event_t ev)
{
        switch(ev) {
        case ENTRY_EVENT:
                printf("adm-ENTRY; \n");
                return EVENT_HANDLED;
        case EXIT_EVENT:
                printf("adm-EXIT; \n");
                return EVENT_HANDLED;
        case INIT_EVENT:
                printf("adm-INIT; \n");
                return EVENT_HANDLED;
        case EVENT_B:
                printf("adm-B; \n");
                adm_principal_tran();                  
                return EVENT_HANDLED;
        case EVENT_A:
                printf("adm-A; \n");
                adm_block_tran();                 
                return EVENT_HANDLED;
        case EVENT_C:
                printf("adm-C; \n");
                adm_cadastrar_local_tran();
                return EVENT_HANDLED;
        case EVENT_R:
                printf("adm-R; \n");
                adm_remover_local_tran();
                return EVENT_HANDLED;
        case EVENT_D:
                printf("adm-D; \n");
                adm_download_local_tran();
                return EVENT_HANDLED;
        }

        return EVENT_NOT_HANDLED;
}

cb_status cadastrar(event_t ev)
{
        switch(ev) {
        case ENTRY_EVENT:
                printf("cadastrar-ENTRY; \n");
                return EVENT_HANDLED;
        case EXIT_EVENT:
                printf("cadastrar-EXIT; \n");
                return EVENT_HANDLED;
        case INIT_EVENT:
                printf("cadastrar-INIT; \n");
                return EVENT_HANDLED;   
        case EVENT_E:
                printf("cadastrar-E; \n");
                cadastrar_finalizar_local_tran();
                return EVENT_HANDLED;
        }

        return EVENT_NOT_HANDLED;
}

cb_status finalizar(event_t ev)
{
        switch(ev) {
        case ENTRY_EVENT:
                printf("finalizar-ENTRY; \n");
                return EVENT_HANDLED;
        case EXIT_EVENT:
                printf("finalizar-EXIT; \n");
                return EVENT_HANDLED;
        case INIT_EVENT:
                printf("finalizar-INIT; \n");
                return EVENT_HANDLED;   
        case EVENT_N:
                printf("finalzar-N; \n");
                finalizar_adm_local_tran();
                return EVENT_HANDLED;
        }

        return EVENT_NOT_HANDLED;
}


cb_status remover(event_t ev)
{
        switch(ev) {
        case ENTRY_EVENT:
                printf("remover-ENTRY; \n");
                return EVENT_HANDLED;
        case EXIT_EVENT:
                printf("remover-EXIT; \n");
                return EVENT_HANDLED;
        case INIT_EVENT:
                printf("remover-INIT; \n");
                return EVENT_HANDLED;              
        case EVENT_N:
                printf("remover-N; \n");
                remover_confirmacao_local_tran();
                return EVENT_HANDLED;
        }

        return EVENT_NOT_HANDLED;
}

cb_status confirmacao(event_t ev)
{
        switch(ev) {
        case ENTRY_EVENT:
                printf("confirmacao-ENTRY; \n");
                return EVENT_HANDLED;
        case EXIT_EVENT:
                printf("confirmacao-EXIT; \n");
                return EVENT_HANDLED;
        case INIT_EVENT:
                printf("confirmacao-INIT; \n");
                confirmacao_init_tran();
                return EVENT_HANDLED;              
        }

        return EVENT_NOT_HANDLED;
}

cb_status download(event_t ev)
{
        switch(ev) {
        case ENTRY_EVENT:
                printf("download-ENTRY; \n");
                return EVENT_HANDLED;
        case EXIT_EVENT:
                printf("download-EXIT; \n");
                return EVENT_HANDLED;
        case INIT_EVENT:
                printf("download-INIT; \n");
                download_init_tran();
                return EVENT_HANDLED;              
        }

        return EVENT_NOT_HANDLED;
}

cb_status block(event_t ev)
{
        switch(ev) {
        case ENTRY_EVENT:
                printf("block-ENTRY; \n");
                return EVENT_HANDLED;
        case EXIT_EVENT:
                printf("block-EXIT; \n");
                return EVENT_HANDLED;
        case INIT_EVENT:
                printf("block-INIT; \n");
                return EVENT_HANDLED;              
        case EVENT_E:
                printf("block-E; \n");
                block_negado_local_tran();                
                return EVENT_HANDLED;
        case EVENT_A:
                printf("block-A; \n");
                block_principal_tran();
                return EVENT_HANDLED;
        }

        return EVENT_NOT_HANDLED;
}

cb_status negado(event_t ev)
{
        switch(ev) {
        case ENTRY_EVENT:
                printf("negado-ENTRY; \n");
                return EVENT_HANDLED;
        case EXIT_EVENT:
                printf("negado-EXIT; \n");
                return EVENT_HANDLED;
        case INIT_EVENT:
                printf("negado-INIT; \n");
                negado_init_tran();
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
                case 'E':
                case 'e':
                        set_event(EVENT_E);
                        break;
                case 'S':
                case 's':
                        set_event(EVENT_S);
                        break;
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
                case 'R':
                case 'r':
                        set_event(EVENT_R);
                        break;
                case 'N':
                case 'n':
                        set_event(EVENT_N);
                        break;
                default:
                        set_event(EVENT_N+1);
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
