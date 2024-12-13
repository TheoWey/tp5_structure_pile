#include "memory.hh"

template <typename T>
void smart_malloc(unique_ptr<T[]> *array, uint8_t *dim_array) {
    (*dim_array)++;
    unique_ptr<T[]> new_array = make_unique<T[]>(*dim_array);
    // Verifier si l'ancien tableau est vide
    if ((*dim_array) > 1) {
        // Copier les elements de l'ancien tableau vers le nouveau
        move((*array).get(), (*array).get() + (*dim_array - 1),
             new_array.get());
    }
    // L'ancien tableau sera automatiquement detruit à la sortie de son scope
    *array = move(new_array); // Transferer la propriete au nouveau tableau
}

template void smart_malloc<float>(std::unique_ptr<float[]> *, uint8_t *);
template void smart_malloc<fiche_etu>(std::unique_ptr<fiche_etu[]> *,
                                      uint8_t *);

bool traitement_date(char date[], uint8_t *day, uint8_t *month,
                     uint32_t *year) {
    char extract[3][5] = {"0"};
    uint8_t num_val, val = 0;
    size_t dateLength = strlen(date); // Get the length of the actual string

    // Input validation: Check if the date string is in the correct format
    if (dateLength != 10 || date[2] != '/' || date[5] != '/') {
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
    char confirmation[4];
    if ((__NEED_CONFIRM__ && !single) || __NEED_CONFIRM_ALL__) {
        printf("Etes vous sur de vouloir faire cette modification?(YES/NO)");
        scanf("%3s", confirmation);
        return (strcmp(confirmation, "YES") == 0);
    }
    return true;
}

void clean_str(char *str) {
    for (uint8_t i = 0; i < sizeof(str) / sizeof(char); i++) {
        str[i] = ' ';
        // *(str+1) =' ';
    }
}