#ifndef WiFiMessageParser_h
#define WiFiMessageParser_h

//These are this prefix lines
#define COMMAND_ID "command"
#define REQUEST_ID "request"
#define REQUESTALL_ID "requestAll"
#define COMMAND_RECEIVED "cmdrcv"
#define END_TRANSMISSION "Quit"

//These are the recognized commands
#define HANDSHAKE           "handshake"
#define ATTEMPT_PIN_UNLOCK  "tryTPCode"
#define CHECK_ADMIN_PW      "checkAdminPW"
#define UPDATE_ADMIN_PW     "updateAPW"
#define UPDATE_PIN          "updatePIN"
#define UPDATE_LOCKDOWN     "updateLockdown"
#define LOCK_SAFE           "updateLock"

//These are the requestable fields
#define STATE_OPEN          "state_open"
#define STATE_LOCKED        "state_locked"
#define STATE_LOCKDOWN      "state_lockdown"

#endif
