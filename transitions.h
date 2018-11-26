#ifndef TRANSITIONS_H
#define TRANSITIONS_H
#include "event.h"
#include "sm.h"


cb_status principal(event_t ev);
cb_status aguardo(event_t ev);
cb_status entrada(event_t ev);
cb_status s2_cb(event_t ev);
cb_status s21_cb(event_t ev);
cb_status s211_cb(event_t ev);


#define Topo_init_tran() do {                   \
                push_state(principal);               \
                dispatch(ENTRY_EVENT);          \
                push_state(s2_cb);              \
                dispatch(ENTRY_EVENT);          \
                dispatch(INIT_EVENT);           \
        } while (0)

#define principal_init_tran() do {                      \
                push_state(aguardo);              \
                dispatch(ENTRY_EVENT);          \
                push_state(entrada);             \
                dispatch(ENTRY_EVENT);          \
        } while (0)

#define principal_adm_tran() do {                 \
                exit_inner_states();            \
                push_state(aguardo);              \
                dispatch(ENTRY_EVENT);          \
                push_state(entrada);             \
                dispatch(ENTRY_EVENT);          \
        } while (0)

#define principal_block_tran() do {                     \
                push_state(entrada);             \
                dispatch(ENTRY_EVENT);          \
        } while (0)

#define aguardo_entrada_tran() do {                  \
                exit_inner_states();            \
                dispatch(EXIT_EVENT);           \
                pop_state();                    \
                dispatch(INIT_EVENT);           \
        } while (0)

#define aguardo_saida_tran() do {                       \
                exit_inner_states();            \
                dispatch(EXIT_EVENT);           \
                dispatch(ENTRY_EVENT);          \
                dispatch(INIT_EVENT);           \
        } while (0)

#define entrada_principal_local_tran() do {                \
                exit_inner_states();            \
                push_state(entrada);             \
                dispatch(ENTRY_EVENT);          \
        } while (0)

#define saida_principal_tran() do {                       \
                exit_inner_states();            \
                dispatch(EXIT_EVENT);           \
                replace_state(s2_cb);           \
                dispatch(ENTRY_EVENT);          \
                dispatch(INIT_EVENT);           \
        } while (0)

#define adm_principal_tran() do {                     \
                exit_inner_states();            \
                dispatch(EXIT_EVENT);           \
                replace_state(s2_cb);           \
                dispatch(ENTRY_EVENT);          \
                push_state(s21_cb);             \
                dispatch(ENTRY_EVENT);          \
                push_state(s211_cb);            \
                dispatch(ENTRY_EVENT);          \
        } while (0)

#define adm_block_tran()  do {                 \
                dispatch(EXIT_EVENT);           \
                pop_state();                    \
                dispatch(EXIT_EVENT);           \
                pop_state();                    \
                dispatch(INIT_EVENT);           \
        } while(0)

#define adm_cadastrar_tran() do {                \
                dispatch(EXIT_EVENT);           \
                pop_state();                    \
                dispatch(INIT_EVENT);           \
        } while(0)

#define adm_remover_tran() do {                    \
                dispatch(EXIT_EVENT);           \
                pop_state();                    \
                dispatch(EXIT_EVENT);           \
                replace_state(s2_cb);           \
                dispatch(ENTRY_EVENT);          \
                push_state(s21_cb);             \
                dispatch(ENTRY_EVENT);          \
                push_state(s211_cb);            \
                dispatch(ENTRY_EVENT);          \
        } while (0)

#define adm_download_tran() do {                     \
                push_state(s21_cb);             \
                dispatch(ENTRY_EVENT);          \
                push_state(s211_cb);            \
                dispatch(ENTRY_EVENT);          \
        } while (0)

#define cadastrar_finalizar_tran() do {                       \
                exit_inner_states();            \
                dispatch(EXIT_EVENT);           \
                replace_state(aguardo);           \
                dispatch(ENTRY_EVENT);          \
                dispatch(INIT_EVENT);           \
        } while(0)

#define finalizar_adm_tran() do {                      \
                exit_inner_states();            \
                dispatch(EXIT_EVENT);           \
                replace_state(aguardo);           \
                dispatch(ENTRY_EVENT);          \
                push_state(entrada);             \
                dispatch(ENTRY_EVENT);          \
        } while(0)

#define remover_confirmacao_tran() do {                    \
                push_state(s211_cb);            \
                dispatch(ENTRY_EVENT);          \
        } while (0)

#define confirmacao_adm_tran() do {                     \
                exit_inner_states();            \
                dispatch(EXIT_EVENT);           \
                dispatch(ENTRY_EVENT);          \
                dispatch(INIT_EVENT);           \
        } while(0)

#define download_adm_tran() do {              \
                exit_inner_states();            \
                push_state(s211_cb);            \
                dispatch(ENTRY_EVENT);          \
        } while(0)

#define bloqueado_negado_tran() do {                     \
                exit_inner_states();            \
                dispatch(EXIT_EVENT);           \
                pop_state();                    \
                dispatch(EXIT_EVENT);           \
                replace_state(aguardo);           \
                dispatch(ENTRY_EVENT);          \
                push_state(entrada);             \
                dispatch(ENTRY_EVENT);          \
        } while(0)

#define bloqueado_principal_tran() do {                \
                dispatch(EXIT_EVENT);           \
                pop_state();                    \
                dispatch(EXIT_EVENT);           \
                pop_state();                    \
                dispatch(EXIT_EVENT);           \
                pop_state();                    \
                dispatch(INIT_EVENT);           \
        } while(0)

#endif /* TRANSITIONS_H */
