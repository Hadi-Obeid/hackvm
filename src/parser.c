#include <stdbool.h>
#include "parser.h"


ParserResult parserInit(char* filename) {
  FILE* f = fopen(filename, "r");
  if (f == NULL) {
    return (ParserResult) {ERR_FILE, {0}};
  }
  ParserResult result;
  result.result = RESULT_OK;
  result.parser = (Parser) {.file=f, .line_no=1};
  return result;
}

bool hasMoreCommands(Parser parser) {
  return !feof(parser.file);
}

ParserResult advance(Parser parser) {
    String b = (String) {0};
    while (!feof(parser.file) && b.len < 1) {
      fgets(parser.line_buf, LINE_BUF_LEN, parser.file);
      b = str_split_s(&from_cstr(parser.line_buf), &from_cstr("//"));
      //printf("%.*s", b.len, b.data);
    }
    return (ParserResult) {RESULT_OK, {.line=b}};
}

ParserResult parserClose(Parser p) {
  fclose(p.file);
  return (ParserResult) {RESULT_OK, {.ok=RESULT_OK}};
}


ParserResult commandType(String line, String msg_buf) {
  // read commandtype from line, line is immutable
  String no_comment = str_split_s(&line, &from_cstr("//"));
  String first = str_split(&no_comment, ' ');

  // arithmetic operations
  if (str_eq(first, from_cstr("add")) || 
      str_eq(first, from_cstr("sub")) ||
      str_eq(first, from_cstr("neg")) ||
      str_eq(first, from_cstr("or")) ||
      str_eq(first, from_cstr("and")) ||
      str_eq(first, from_cstr("gt")) ||
      str_eq(first, from_cstr("lt")) ||
      str_eq(first, from_cstr("eq"))
  )
    return (ParserResult) {RESULT_OK, {.instruction = C_ARITHMETIC}};
  if (str_eq(first, from_cstr("push")))
    return (ParserResult) {RESULT_OK, {.instruction = C_PUSH}};
  if (str_eq(first, from_cstr("pop")))
    return (ParserResult) {RESULT_OK, {.instruction = C_POP}};
  if (str_eq(first, from_cstr("function")))
    return (ParserResult) {RESULT_OK, {.instruction = C_FUNCTION}};
  if (str_eq(first, from_cstr("call")))
    return (ParserResult) {RESULT_OK, {.instruction = C_CALL}};
  if (str_eq(first, from_cstr("label")))
    return (ParserResult) {RESULT_OK, {.instruction = C_LABEL}};
  if (str_eq(first, from_cstr("return")))
    return (ParserResult) {RESULT_OK, {.instruction = C_RETURN}};

  snprintf(msg_buf.data, msg_buf.len, "Error message");
  return (ParserResult) {ERR_COMMAND_TYPE, {.instruction = C_ARITHMETIC}};
}


