#pragma once
#include "mystring.h"


// type of instruction for enum
typedef enum {
  C_ARITHMETIC,
  C_PUSH,
  C_POP,
  C_LABEL,
  C_GOTO,
  C_IF,
  C_FUNCTION,
  C_RETURN,
  C_CALL
} instruction_t;

typedef enum {
  RESULT_OK,
  ERR_COMMAND_TYPE,
  ERR_COMMAND_ARGS,
} ParserResultCode;

typedef struct {
  ParserResultCode result;
  instruction_t instruction;
} ParserResult;

typedef struct {
  instruction_t type;
  String arg1;
  String arg2;
} Command;

ParserResult commandType(char* line, String msg_buf);
Command parseCommand(char* line);
