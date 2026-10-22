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
  ERR_FILE,
  ERR_COMMAND_TYPE,
  ERR_COMMAND_ARGS,
} ParserResultCode;

typedef struct {
  instruction_t type;
  String arg1;
  String arg2;
} Command;

#define LINE_BUF_LEN 128
typedef struct {
  FILE* file;
  char line_buf[LINE_BUF_LEN];
  size_t line_no;
} Parser;

typedef struct {
  ParserResultCode result;
  union {
    char ok;
    instruction_t instruction;
    Parser parser;
    String line;
  };
} ParserResult;



bool hasMoreCommands(Parser parser);
ParserResult advance(Parser parser);
ParserResult parserInit(char* filename);
ParserResult parserClose(Parser p);
ParserResult commandType(String line, String msg_buf);
Command parseCommand(char* line);
