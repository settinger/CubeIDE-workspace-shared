/*
 * consoleCommands.c
 * The command interface used by console.c
 * Ported from Elecia White's code here:
 * https://wokwi.com/projects/324879108372693587
 *
 * This is where you add commands:
 *     1. Add a protoype
 *          static eCommandResult_T ConsoleCommandVer(const char buffer[]);
 *     2. Add the command to mConsoleCommandTable
 *          {"ver", &ConsoleCommandVer, HELP("Get the version string")},
 *     3. Implement the function, using ConsoleReceiveParam<Type> to get the parameters from the buffer.
 *
 *  Created on: Apr 28, 2022
 *      Author: Sam
 */

#include <string.h>
#include "consoleCommands.h"
#include "console.h"
#include "console_io.h"
#include "version.h"

#define IGNORE_UNUSED_VARIABLE(x) if ( &x == &x ) {}

static commandResult ConsoleCommandComment(const char buffer[]);
static commandResult ConsoleCommandVer(const char buffer[]);
static commandResult ConsoleCommandHelp(const char buffer[]);
static commandResult ConsoleCommandParam_int16(const char buffer[]);
static commandResult ConsoleCommandParamHex_uint16(const char buffer[]);

static const consoleCommandTable myConsoleCommandTable[] = {
    {";", &ConsoleCommandComment, HELP("Comment! You need a space after the semicolon. ")},
    {"help", &ConsoleCommandHelp, HELP("Lists the commands available")},
    {"ver", &ConsoleCommandVer, HELP("Get the version string")},
    {"int", &ConsoleCommandParam_int16, HELP("How to get a signed int16 from params list: int -321")},
    {"u16h", &ConsoleCommandParamHex_uint16, HELP("How to get a hex u16 from the params list: u16h aB12")},

    CONSOLE_COMMAND_TABLE_END // must be LAST
};

static commandResult ConsoleCommandComment(const char buffer[]) {
  // Do nothing

  IGNORE_UNUSED_VARIABLE(buffer);

  return COMMAND_SUCCESS;
}

static commandResult ConsoleCommandHelp(const char buffer[]) {
  uint32_t i;
  uint32_t tableLength;
  commandResult result = COMMAND_SUCCESS;
  IGNORE_UNUSED_VARIABLE(buffer); ///// ??????????
  tableLength = sizeof(myConsoleCommandTable) / sizeof(myConsoleCommandTable[0]);

  for (i=0u; i< tableLength-1u; i++) {
    ConsoleIoSend(myConsoleCommandTable[i].name);
#if CONSOLE_COMMAND_MAX_HELP_LENGTH > 0
    ConsoleIoSend(" : ");
    ConsoleIoSend(myConsoleCommandTable[i].help);
#endif
  }
  return result;
}

static commandResult ConsoleCommandParam_int16(const char buffer[]) {
  int16_t parameterInt;
  commandResult result;
  result = ConsoleReceive_int16(buffer, 1, &parameterInt);
  if (COMMAND_SUCCESS == result) {
    ConsoleIoSend("Parameter is ");
    ConsoleSend_int16(parameterInt);
    ConsoleIoSend(" (0x");
    ConsoleSendHex_uint16((uint16_t)parameterInt);
    ConsoleIoSend(")");
    ConsoleIoSend(ENDLINE);
  }
  return result;
}

static commandResult ConsoleCommandParamHex_uint16(const char buffer[]) {
  uint16_t parameterUint16;
  commandResult result;
  result = ConsoleReceiveHex_uint16(buffer, 1, &parameterUint16);
  if (COMMAND_SUCCESS == result ) {
    ConsoleIoSend("Parameter is 0x");
    ConsoleSendHex_uint16(parameterUint16);
    ConsoleIoSend(ENDLINE);
  }
  return result;
}

static commandResult ConsoleCommandVer(const char buffer[]) {
  commandResult result = COMMAND_SUCCESS;

  IGNORE_UNUSED_VARIABLE(buffer);

  ConsoleIoSend(VERSION_STRING);
  ConsoleIoSend(ENDLINE);
  return result;
}

const consoleCommandTable* ConsoleCommandsGetTable(void) {
  return (myConsoleCommandTable);
}
