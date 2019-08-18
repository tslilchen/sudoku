#include <stdio.h>
#include <stdlib.h>

#include "Command.h"
#include "../MemoryError.h"


Command* create_command() {
    Command *command = malloc(sizeof(Command));
    validate_memory_allocation("create_command", command);

    command->type = empty;
    command->format = NULL;
    command->modes = 0;
    command->error = create_error();
    command->data.solve = NULL;
    command->data.edit = NULL;
    command->data.mark_errors = NULL;
    command->data.set = NULL;
    command->data.guess = NULL;
    command->data.generate = NULL;
    command->data.save = NULL;
    command->data.hint = NULL;
    command->data.guess_hint = NULL;

    return command;
}

void destroy_command(Command* command) {
    if (command->data.solve != NULL) {
        free(command->data.solve->path);
        free(command->data.solve);
    }
    if (command->data.edit != NULL) {
        free(command->data.edit->path);
        free(command->data.edit);
    }
    if (command->data.save != NULL) {
        free(command->data.save->path);
        free(command->data.save);
    }
    free(command->data.mark_errors);
    free(command->data.set);
    free(command->data.guess);
    free(command->data.generate);
    free(command->data.hint);
    free(command->data.guess_hint);
    destroy_error(command->error);
    free(command);
}


void invalidate(Command *command, char *error_message, int error_level) {
    if (command->error->level <= error_level) {
        return;
    }

    set_error(command->error, error_message, error_level);
}

bool is_valid(Command *command) {
    return command->error->level >= no_error;
}
