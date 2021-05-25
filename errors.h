#define USR_MSG_ERROR_PROGRAM_INVOCATION 	"Error de invocación del programa, sintáxis: -fmt (csv/xml) -(in/out) <path> -(in/out) <path>"
#define USR_MSG_ERROR_NULL_POINTER		"Error de dirección por puntero nulo"
#define USR_MSG_ERROR_OPENING_INPUT_FILE 	"Error de apertura archivo de entrada"
#define USR_MSG_ERROR_OPENING_OUTPUT_FILE 	"Error de apertura archivo de salida"
#define USR_MSG_ERROR_DISK_SPACE 		"Error espacio insuficiente en el disco"
#define USR_MSG_ERROR_MEMORY 			"Error memoria insuficiente"
#define USR_MSG_ERROR_CORRUPT_FILE 		"Error archivo de entrada corrupto"

typedef enum {
	OK,
	ERROR_PROGRAM_INVOCATION,
	ERROR_NULL_POINTER,
	ERROR_OPENING_INPUT_FILE,
	ERROR_OPENING_OUTPUT_FILE,
	ERROR_DISK_SPACE,
	ERROR_MEMORY,
	ERROR_CORRUPT_FILE,
	MAX_ERRORS,
} status_t;

status_t show_error(status_t);
