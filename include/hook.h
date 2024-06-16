#ifndef HOOK_H
#define HOOK_H

#define FUNCTION_RETURN "return"
#define FUNCTION_CALL "call"
#define FUNCTION_OWERWRITE "overwrite"
#define VARIABLE_READ "read"
#define VARIABLE_WRITE "write"
#define CONSTANT "constant"

#define HOOK(function, position, cancellable, priority)
#define AT(position)
#define AT_METHOD(function, position) function##_##position

#endif