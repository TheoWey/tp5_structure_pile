#include "memory.hh"

template <typename T>
void smart_malloc(unique_ptr<T[]> *array, uint8_t *dim_array) {
    (*dim_array)++;
    unique_ptr<T[]> new_array = make_unique<T[]>(*dim_array);
    // Vérifier si l'ancien tableau est vide
    if ((*dim_array) > 1) {
        // Copier les éléments de l'ancien tableau vers le nouveau
        copy(array.get(), array.get() + ((*dim_array) - 1), new_array.get());
    }
    // L'ancien tableau sera automatiquement détruit à la sortie de son scope
    array = move(new_array); // Transférer la propriété au nouveau tableau
}

bool traitement_date(char date[], uint8_t *day, uint8_t *month,
                     uint32_t *year) {
    char extract[3][5] = {"0"};
    uint8_t num_val, val = 0;
    size_t dateLength = strlen(date); // Get the length of the actual string

    // Input validation: Check if the date string is in the correct format
    if (dateLength != 8 || date[2] != '/' || date[5] != '/') {
        // std::cerr << "Invalid date format. Expected DD/MM/YY." << std::endl;
        printf("Format attendu JJ/MM/AAAA : 06/12/2000 par exemple");
        goto error; // Exit the function if the format is incorrect
    }
    for (uint8_t i = 0; i < dateLength; i++) {
        if (date[i] == '/') {
            num_val++;
            val = 0;
            i++;
        }
        if (num_val < 3) {
            extract[num_val][val] = date[i];
            val++;
        }
    }
    *day = atoi(extract[0]);
    *month = atoi(extract[1]);
    if (*month > 12) {
        goto error; // exit fonction if month out of range
    }
    *year = atoi(extract[2]);
    return 1; // function success
error:
    return 0;
}

bool confirm(bool single) {
    char confirmation[3];
    if ((__NEED_CONFIRM__ && !single) || __NEED_CONFIRM_ALL__) {
        printf("Etes vous sur de vouloir faire cette modification?(YES/NO)");
        scanf("%2s", confirmation);
        return strcmp(confirmation, "YES");
    }
    return true;
}