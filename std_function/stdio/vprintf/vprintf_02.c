/*
Example of Using vprintf in a More Complex Context:
Consider a more complex scenario where you want to create a function that conditionally logs messages based on a 
verbosity level.
*/

#include <stdio.h>
#include <stdarg.h>

void log_message(int verbosity_level, int message_level, const char *format, ...) {
    if (verbosity_level < message_level) {
        return;
    }
    
    va_list args;
    va_start(args, format);
    
    // Print the message only if the verbosity level allows it
    vprintf(format, args);
    
    va_end(args);
}

int main() {
    int verbosity = 2;
    
    log_message(verbosity, 1, "Error: Something went wrong\n");
    log_message(verbosity, 2, "Warning: This is a warning\n");
    log_message(verbosity, 3, "Info: Informational message\n");
    
    return 0;
}

/*
Explanation:
In this example, log_message only prints messages if the verbosity_level is greater than or equal to the message_level.
vprintf is used to handle the variable arguments and print the formatted message based on the provided format.
Conclusion:
vprintf is useful when handling a variable number of arguments and when you want to print them using a specific format.
It is commonly used in conjunction with macros like va_start, va_end, and va_arg to process variable argument 
lists in C.
It provides the same functionality as printf, but allows you to pass a va_list of arguments instead of directly 
providing them.
*/