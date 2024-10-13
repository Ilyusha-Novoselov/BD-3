#include "functions.h"

int main() {
    const char* login = "pmi-b1501";
    const char* password = "Dewfauj4";
    const char* schema = "pmib1501";

    connect_db(login, password);
    connect_schema(schema);

    table_rollback();

    return 0;
}