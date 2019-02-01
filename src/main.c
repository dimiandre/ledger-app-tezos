/*******************************************************************************
*   Ledger Blue
*   (c) 2016 Ledger
*
*  Licensed under the Apache License, Version 2.0 (the "License");
*  you may not use this file except in compliance with the License.
*  You may obtain a copy of the License at
*
*      http://www.apache.org/licenses/LICENSE-2.0
*
*  Unless required by applicable law or agreed to in writing, software
*  distributed under the License is distributed on an "AS IS" BASIS,
*  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
*  See the License for the specific language governing permissions and
*  limitations under the License.
********************************************************************************/

#include "apdu_baking.h"
#include "apdu_pubkey.h"
#include "apdu_sign.h"
#include "apdu.h"
#include "globals.h"
#include "memory.h"

__attribute__((noreturn))
void app_main(void) {
    // TODO: Consider using static initialization of a const, instead of this
    for (size_t i = 0; i < NUM_ELEMENTS(global.handlers); i++) {
        global.handlers[i] = handle_apdu_error;
    }
    global.handlers[INS_VERSION] = handle_apdu_version;
    global.handlers[INS_GET_PUBLIC_KEY] = handle_apdu_get_public_key;
    global.handlers[INS_PROMPT_PUBLIC_KEY] = handle_apdu_get_public_key;
#ifdef BAKING_APP
    global.handlers[INS_AUTHORIZE_BAKING] = handle_apdu_get_public_key;
    global.handlers[INS_RESET] = handle_apdu_reset;
    global.handlers[INS_QUERY_AUTH_KEY] = handle_apdu_query_auth_key;
    global.handlers[INS_QUERY_HWM] = handle_apdu_hwm;
#endif
    global.handlers[INS_SIGN] = handle_apdu_sign;
#ifndef BAKING_APP
    global.handlers[INS_SIGN_UNSAFE] = handle_apdu_sign;
#endif
    global.handlers[INS_GIT] = handle_apdu_git;
    main_loop(global.handlers);
}
