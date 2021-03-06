#include <avr/pgmspace.h>
#include "ch.h"
#include "hal.h"
#include "event.h"
#include "sm.h"
#include "transitions.h"
#include "chprintf.h"
#include "src/MFRC522.h"
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


//static const char nome[] PROGMEM = "MENSAGEM";
//chprintf((BaseSequentialStream*)&SD1, nome);

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
        chprintf((BaseSequentialStream*)&SD1, "Hermano eh um bom companheiro \n");
        Topo_init_tran();
        return EVENT_HANDLED;
}

cb_status principal(event_t ev)
{
        switch(ev) {
        case ENTRY_EVENT:
                chprintf((BaseSequentialStream*)&SD1, "principal-ENTRY; \n");
                return EVENT_HANDLED;
        case EXIT_EVENT:
                chprintf((BaseSequentialStream*)&SD1, "principal-EXIT; \n");
                return EVENT_HANDLED;
        case INIT_EVENT:
                chprintf((BaseSequentialStream*)&SD1, "principal-INIT; \n");
                principal_init_tran();
                return EVENT_HANDLED;
        case EVENT_B:
                chprintf((BaseSequentialStream*)&SD1, "principal-B; \n");
                principal_adm_tran();
                return EVENT_HANDLED;
        case EVENT_A:
                chprintf((BaseSequentialStream*)&SD1, "principal-A; \n");
                principal_block_tran();
                return EVENT_HANDLED;
        }

        return EVENT_NOT_HANDLED;
}

cb_status aguardo(event_t ev)
{
        switch(ev) {
        case ENTRY_EVENT:
                chprintf((BaseSequentialStream*)&SD1, "aguardo-ENTRY; \n");
                return EVENT_HANDLED;
        case EXIT_EVENT:
                chprintf((BaseSequentialStream*)&SD1, "aguardo-EXIT; \n");
                return EVENT_HANDLED;
        case INIT_EVENT:
                chprintf((BaseSequentialStream*)&SD1, "aguardo-INIT; \n");
                return EVENT_HANDLED;
        case EVENT_E:
                chprintf((BaseSequentialStream*)&SD1, "aguardo-E; \n");
                aguardo_entrada_tran();
                return EVENT_HANDLED;
        case EVENT_S:
                chprintf((BaseSequentialStream*)&SD1, "aguardo-S; \n");
                aguardo_saida_tran();
                return EVENT_HANDLED;
        }

        return EVENT_NOT_HANDLED;
}

cb_status entrada(event_t ev)
{
        switch(ev) {
        case ENTRY_EVENT:
                chprintf((BaseSequentialStream*)&SD1, "entrada-ENTRY; \n");
                return EVENT_HANDLED;
        case EXIT_EVENT:
                chprintf((BaseSequentialStream*)&SD1, "entrada-EXIT; \n");
                return EVENT_HANDLED;
        case INIT_EVENT:
                chprintf((BaseSequentialStream*)&SD1, "entrada-INIT");
                entrada_init_tran();
                return EVENT_HANDLED;
        }

        return EVENT_NOT_HANDLED;
}

cb_status saida(event_t ev)
{
        switch(ev) {
        case ENTRY_EVENT:
                chprintf((BaseSequentialStream*)&SD1, "saida-ENTRY; \n");
                return EVENT_HANDLED;
        case EXIT_EVENT:
                chprintf((BaseSequentialStream*)&SD1, "saida-EXIT; \n");
                return EVENT_HANDLED;
        case INIT_EVENT:
                chprintf((BaseSequentialStream*)&SD1, "saida-INIT; \n");
                saida_init_tran();
                return EVENT_HANDLED;
        }

        return EVENT_NOT_HANDLED;
}

cb_status adm(event_t ev)
{
        switch(ev) {
        case ENTRY_EVENT:
                chprintf((BaseSequentialStream*)&SD1, "adm-ENTRY; \n");
                return EVENT_HANDLED;
        case EXIT_EVENT:
                chprintf((BaseSequentialStream*)&SD1, "adm-EXIT; \n");
                return EVENT_HANDLED;
        case INIT_EVENT:
                chprintf((BaseSequentialStream*)&SD1, "adm-INIT; \n");
                return EVENT_HANDLED;
        case EVENT_B:
                chprintf((BaseSequentialStream*)&SD1, "adm-B; \n");
                adm_principal_tran();
                return EVENT_HANDLED;
        case EVENT_A:
                chprintf((BaseSequentialStream*)&SD1, "adm-A; \n");
                adm_block_tran();
                return EVENT_HANDLED;
        case EVENT_C:
                chprintf((BaseSequentialStream*)&SD1, "adm-C; \n");
                adm_cadastrar_local_tran();
                return EVENT_HANDLED;
        case EVENT_R:
                chprintf((BaseSequentialStream*)&SD1, "adm-R; \n");
                adm_remover_local_tran();
                return EVENT_HANDLED;
        case EVENT_D:
                chprintf((BaseSequentialStream*)&SD1, "adm-D; \n");
                adm_download_local_tran();
                return EVENT_HANDLED;
        }

        return EVENT_NOT_HANDLED;
}

cb_status cadastrar(event_t ev)
{
        switch(ev) {
        case ENTRY_EVENT:
                chprintf((BaseSequentialStream*)&SD1, "cadastrar-ENTRY; \n");
                return EVENT_HANDLED;
        case EXIT_EVENT:
                chprintf((BaseSequentialStream*)&SD1, "cadastrar-EXIT; \n");
                return EVENT_HANDLED;
        case INIT_EVENT:
                chprintf((BaseSequentialStream*)&SD1, "cadastrar-INIT; \n");
                return EVENT_HANDLED;
        case EVENT_E:
                chprintf((BaseSequentialStream*)&SD1, "cadastrar-E; \n");
                cadastrar_finalizar_local_tran();
                return EVENT_HANDLED;
        }

        return EVENT_NOT_HANDLED;
}

cb_status finalizar(event_t ev)
{
        switch(ev) {
        case ENTRY_EVENT:
                chprintf((BaseSequentialStream*)&SD1, "finalizar-ENTRY; \n");
                return EVENT_HANDLED;
        case EXIT_EVENT:
                chprintf((BaseSequentialStream*)&SD1, "finalizar-EXIT; \n");
                return EVENT_HANDLED;
        case INIT_EVENT:
                chprintf((BaseSequentialStream*)&SD1, "finalizar-INIT; \n");
                return EVENT_HANDLED;
        case EVENT_N:
                chprintf((BaseSequentialStream*)&SD1, "finalzar-N; \n");
                finalizar_adm_local_tran();
                return EVENT_HANDLED;
        }

        return EVENT_NOT_HANDLED;
}


cb_status remover(event_t ev)
{
        switch(ev) {
        case ENTRY_EVENT:
                chprintf((BaseSequentialStream*)&SD1, "remover-ENTRY; \n");
                return EVENT_HANDLED;
        case EXIT_EVENT:
                chprintf((BaseSequentialStream*)&SD1, "remover-EXIT; \n");
                return EVENT_HANDLED;
        case INIT_EVENT:
                chprintf((BaseSequentialStream*)&SD1, "remover-INIT; \n");
                return EVENT_HANDLED;
        case EVENT_N:
                chprintf((BaseSequentialStream*)&SD1, "remover-N; \n");
                remover_confirmacao_local_tran();
                return EVENT_HANDLED;
        }

        return EVENT_NOT_HANDLED;
}

cb_status confirmacao(event_t ev)
{
        switch(ev) {
        case ENTRY_EVENT:
                chprintf((BaseSequentialStream*)&SD1, "confirmacao-ENTRY; \n");
                return EVENT_HANDLED;
        case EXIT_EVENT:
                chprintf((BaseSequentialStream*)&SD1, "confirmacao-EXIT; \n");
                return EVENT_HANDLED;
        case INIT_EVENT:
                chprintf((BaseSequentialStream*)&SD1, "confirmacao-INIT; \n");
                confirmacao_init_tran();
                return EVENT_HANDLED;
        }

        return EVENT_NOT_HANDLED;
}

cb_status download(event_t ev)
{
        switch(ev) {
        case ENTRY_EVENT:
                chprintf((BaseSequentialStream*)&SD1, "download-ENTRY; \n");
                return EVENT_HANDLED;
        case EXIT_EVENT:
                chprintf((BaseSequentialStream*)&SD1, "download-EXIT; \n");
                return EVENT_HANDLED;
        case INIT_EVENT:
                chprintf((BaseSequentialStream*)&SD1, "download-INIT; \n");
                download_init_tran();
                return EVENT_HANDLED;
        }

        return EVENT_NOT_HANDLED;
}

cb_status block(event_t ev)
{
        switch(ev) {
        case ENTRY_EVENT:
                chprintf((BaseSequentialStream*)&SD1, "block-ENTRY; \n");
                return EVENT_HANDLED;
        case EXIT_EVENT:
                chprintf((BaseSequentialStream*)&SD1, "block-EXIT; \n");
                return EVENT_HANDLED;
        case INIT_EVENT:
                chprintf((BaseSequentialStream*)&SD1, "block-INIT; \n");
                return EVENT_HANDLED;
        case EVENT_E:
                chprintf((BaseSequentialStream*)&SD1, "block-E; \n");
                block_negado_local_tran();
                return EVENT_HANDLED;
        case EVENT_A:
                chprintf((BaseSequentialStream*)&SD1, "block-A; \n");
                block_principal_tran();
                return EVENT_HANDLED;
        }

        return EVENT_NOT_HANDLED;
}

cb_status negado(event_t ev)
{
        switch(ev) {
        case ENTRY_EVENT:
                chprintf((BaseSequentialStream*)&SD1, "negado-ENTRY; \n");
                return EVENT_HANDLED;
        case EXIT_EVENT:
                chprintf((BaseSequentialStream*)&SD1, "negado-EXIT; \n");
                return EVENT_HANDLED;
        case INIT_EVENT:
                chprintf((BaseSequentialStream*)&SD1, "negado-INIT; \n");
                negado_init_tran();
                return EVENT_HANDLED;
        }

        return EVENT_NOT_HANDLED;
}

void caps (char cod[20]){
        
        for(int i = 0; i < 20; i++){
                cod[i]=toupper(cod[i]);
        }
        
}

static THD_WORKING_AREA(waThread1, 32);
static THD_FUNCTION(Thread1, arg) {
        (void)arg;
        chRegSetThreadName("RFID");
        palSetPadMode(IOPORT2, PB5, PAL_MODE_OUTPUT_PUSHPULL);     /* SCK. */
        palSetPadMode(IOPORT2, PB4, PAL_MODE_OUTPUT_PUSHPULL);     /* MISO.*/
        palSetPadMode(IOPORT2, PB3, PAL_MODE_OUTPUT_PUSHPULL);     /* MOSI.*/
        MFRC522 rfid(IOPORT2, PB2, IOPORT4, PD3);
        rfid.PCD_Init();
        while (true) {
                char cod[20] = "";
                // Look for new cards
                if ( ! rfid.PICC_IsNewCardPresent()) {
                        continue;
                }
                // Select one of the cards
                if ( ! rfid.PICC_ReadCardSerial()) {
                        continue;
                }
                //Mostra UID na serial 
                //chprintf((BaseSequentialStream*)&SD1, "UID da tag :");
                char buffer[33];
                for (uint8_t i = 0; i < rfid.uid.size; i++) 
                {
                        //chprintf((BaseSequentialStream*)&SD1, rfid.uid.uidByte[i] < 0x10 ? " 0" : " ");
                        //chprintf((BaseSequentialStream*)&SD1, "%x", rfid.uid.uidByte[i]);
                        strcat(cod, (rfid.uid.uidByte[i] < 0x10 ? " 0" : " "));
                        strcat(cod, itoa(rfid.uid.uidByte[i], buffer, 16));
                }
                caps(cod);
                //chprintf((BaseSequentialStream*)&SD1, "\n %s \n", cod);
                

                if(!strcmp (cod," 2E AF 25 D9")){       //chaveiro hermano
                        set_event(EVENT_B);
                }
                if(!strcmp (cod," B0 AC 60 A8")){       // Cartao
                        set_event(EVENT_E);
                }
                chThdSleepMilliseconds(500);
        }
}

int main(int argc, char* argv[])
{
        halInit();
        chSysInit();
        chThdCreateStatic(waThread1, sizeof(waThread1), NORMALPRIO+1, Thread1, NULL);

        init_machine(init_cb);
        //chprintf((BaseSequentialStream*)&SD1, "Ta rodando \n");
        while(1){
                dispatch_event(wait_for_events());
        };

        return 0;
}
