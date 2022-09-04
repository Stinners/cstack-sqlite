#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

// ======================= Input Buffer =============================//

typedef struct {
    char* buffer;
    size_t buffer_length;
    ssize_t input_length;
} InputBuffer;

InputBuffer* new_input_buffer() {
    InputBuffer* input_buffer = (InputBuffer*)malloc(sizeof(InputBuffer));
    input_buffer->buffer = NULL;
    input_buffer->buffer_length = 0;
    input_buffer->input_length = 0;

    return input_buffer;
}

void print_prompt() { printf("db > "); }

void read_input(InputBuffer* buf) {
    ssize_t bytes_read = getline(&(buf->buffer), &(buf->buffer_length), stdin);

    if (bytes_read <= 0) {
        printf("Error reading input: Exiting\n");
        exit(EXIT_FAILURE);
    }

    // Truncate the endline 
    buf->input_length = bytes_read - 1;
    buf->buffer[bytes_read - 1] = 0;
}

void close_input_buffer(InputBuffer* buf) {
    free(buf->buffer);
    free(buf);
}

// ======================= Command handling =============================//

typedef enum {
    META_COMMAND_SUCCESS,
    META_COMMAND_UNRECOGNIZED_COMMAND,
} MetaCommandResult;

MetaCommandResult do_meta_command(InputBuffer* input_buffer) {
    if (strcmp(input_buffer->buffer, ".exit") == 0) {
        exit(EXIT_SUCCESS);
    } else {
        return META_COMMAND_UNRECOGNIZED_COMMAND;
    }
}

// ======================= Statement handling =============================//

typedef enum {
    PREPARE_SUCCESS,
    PREPARE_UNRECOGNIZED_STATEMENT,
} PrepareResult;

typedef enum {
    STATEMENT_INSERT, 
    STATEMENT_SELECT 
} StatementType;

typedef struct {
    StatementType type;
} Statement;

PrepareResult prepare_statement(InputBuffer* buf, Statement* statement) {
    if (strncmp(buf->buffer, "insert", 6) == 0) {
        statement->type = STATEMENT_INSERT;
        return PREPARE_SUCCESS;
    } else if (strcmp(buf->buffer, "select") == 0) {
        statement->type = STATEMENT_SELECT;
        return PREPARE_SUCCESS;
    } else {
        return PREPARE_UNRECOGNIZED_STATEMENT;
    }
}

void execute_statement(Statement* stmt) {
    switch (stmt->type) {
        case (STATEMENT_INSERT):
          printf("This is where we would do an insert.\n");
          break;
        case (STATEMENT_SELECT):
          printf("This is where we would do a select.\n");
          break;
    }
}

int main(int argc, char* argv[]) {
    InputBuffer* input_buffer = new_input_buffer();
    while (true) {
        print_prompt();
        read_input(input_buffer);

        // Handle special commands 
        if (input_buffer->buffer[0] == '.') {
            switch (do_meta_command(input_buffer)) {
                case (META_COMMAND_SUCCESS):
                    break;
                case (META_COMMAND_UNRECOGNIZED_COMMAND):
                    printf("Unrecognized command '%s'\n", input_buffer->buffer);
                    break;
            }
        }

        // Handle SQL statements
        else {
            Statement statement;
            switch (prepare_statement(input_buffer, &statement)) {
                case (PREPARE_SUCCESS):
                    break;
                case (PREPARE_UNRECOGNIZED_STATEMENT):
                    printf("Unrecognized keyword at start of '%s'.\n", input_buffer->buffer);
                    continue;
            }

            execute_statement(&statement);
            printf("Executed\n");
        }
    }
}
