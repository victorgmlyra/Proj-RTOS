#ifndef TRANSITIONS_H
#define TRANSITIONS_H
#include "event.h"
#include "sm.h"


cb_status principal(event_t ev);
cb_status aguardo(event_t ev);
cb_status entrada(event_t ev);
cb_status saida(event_t ev);
cb_status adm(event_t ev);
cb_status cadastrar(event_t ev);
cb_status finalizar(event_t ev);
cb_status remover(event_t ev);
cb_status confirmacao(event_t ev);
cb_status download(event_t ev);
cb_status block(event_t ev);
cb_status negado(event_t ev);


#define Topo_init_tran() do {                   \
                push_state(principal);          \
                dispatch(ENTRY_EVENT);          \
                dispatch(INIT_EVENT);           \
        } while (0)

#define principal_init_tran() do {              \
                push_state(aguardo);            \
                dispatch(ENTRY_EVENT);          \
        } while (0)

#define principal_adm_tran() do {               \
                exit_inner_states();            \
                dispatch(EXIT_EVENT);           \
                replace_state(adm);             \
                dispatch(ENTRY_EVENT);          \
        } while (0)

#define principal_block_tran() do {             \
                exit_inner_states();            \
                dispatch(EXIT_EVENT);           \
                replace_state(block);           \
                dispatch(ENTRY_EVENT);          \
        } while (0)

#define aguardo_entrada_tran() do {             \
                dispatch(EXIT_EVENT);           \
                replace_state(entrada);         \
                dispatch(ENTRY_EVENT);          \
                dispatch(INIT_EVENT);           \
        } while (0)

#define aguardo_saida_tran() do {               \
                dispatch(EXIT_EVENT);           \
                replace_state(saida);           \
                dispatch(ENTRY_EVENT);          \
                dispatch(INIT_EVENT);           \
        } while (0)

#define entrada_init_tran() do {                \
                dispatch(EXIT_EVENT);           \
                replace_state(aguardo);         \
                dispatch(ENTRY_EVENT);          \              
        } while (0)

#define saida_init_tran() do {                  \
                dispatch(EXIT_EVENT);           \
                replace_state(aguardo):                    \
                dispatch(ENTRY_EVENT);           \
        } while (0)

#define adm_principal_tran() do {               \
                exit_inner_states();            \
                dispatch(EXIT_EVENT);           \
                replace_state(principal);       \
                dispatch(ENTRY_EVENT);          \
                dispatch(INIT_EVENT);           \
        } while (0)

#define adm_block_tran()  do {                  \
                exit_inner_states();            \
                dispatch(EXIT_EVENT);           \
                replace_state(block);           \
                dispatch(ENTRY_EVENT);          \
        } while(0)

#define adm_cadastrar_local_tran() do {         \
                exit_inner_states();            \
                push_state(cadastrar);          \
                dispatch(ENTRY_EVENT);          \
        } while(0)

#define adm_remover_local_tran() do {           \
                exit_inner_states();            \
                push_state(remover);            \
                dispatch(ENTRY_EVENT);          \
        } while (0)

#define adm_download_local_tran() do {          \
                exit_inner_states();            \
                push_state(download);           \
                dispatch(ENTRY_EVENT);          \
                dispatch(INIT_EVENT);           \
        } while (0)

#define cadastrar_finalizar_tran() do {         \
                exit_inner_states();            \
                dispatch(EXIT_EVENT);           \
                replace_state(aguardo);         \
                dispatch(ENTRY_EVENT);          \
                dispatch(INIT_EVENT);           \
        } while(0)

#define cadastrar_finalizar_local_tran() do {   \
                exit_inner_states();            \
                push_state(finalizar);          \
                dispatch(ENTRY_EVENT);          \
        } while(0)

#define finalizar_adm_local_tran() do {         \
                dispatch(EXIT_EVENT);           \
                pop_state();                    \
                dispatch(EXIT_EVENT);           \
                pop_state();                    \
        } while(0)

#define remover_confirmacao_local_tran() do {   \
                exit_inner_states();            \
                push_state(confirmacao);        \
                dispatch(ENTRY_EVENT);          \
                dispatch(INIT_EVENT);           \
        } while (0)

#define confirmacao_init_tran() do {            \
                dispatch(EXIT_EVENT);           \
                pop_state();                    \
                dispatch(EXIT_EVENT);           \
                pop_state();                    \
        } while(0)

#define download_init_tran() do {               \
                dispatch(EXIT_EVENT);           \
                pop_state();                    \
        } while(0)

#define block_negado_local_tran() do {          \
                exit_inner_states();            \
                push_state(negado);             \
                dispatch(ENTRY_EVENT);          \
                dispatch(INIT_EVENT);           \
        } while(0)

#define block_principal_tran() do {             \
                exit_inner_states();            \
                dispatch(EXIT_EVENT);           \
                replace_state(principal);       \
                dispatch(ENTRY_EVENT);          \
                dispatch(INIT_EVENT);           \
        } while(0)

#define negado_init_tran() do {                 \
                dispatch(EXIT_EVENT);           \
                pop_state();                    \
        } while(0)

#endif /* TRANSITIONS_H */
