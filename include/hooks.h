#ifndef HOOK_H
#define HOOK_H

#define FUNCTION_RETURN "return"
#define FUNCTION_CALL "call"
#define FUNCTION_OWERWRITE "overwrite"
#define VARIABLE_READ "read"
#define VARIABLE_WRITE "write"
#define CONSTANT "constant"

#define HOOK(file, function, position, ...)
#define AT(...)

#define HOOK_METHOD(file, function) (#file #function)
#endif
