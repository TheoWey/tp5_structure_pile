#include "memory.hh"

template <typename T>
void smart_malloc(unique_ptr<T[]> *array, uint8_t *dim_array) {
    (*dim_array)++;
    try {
        unique_ptr<T[]> new_array = make_unique<T[]>(*dim_array);
        // Verifier si l'ancien tableau est vide
        if ((*dim_array) > 1) {
            // Copier les elements de l'ancien tableau vers le nouveau
            for (uint8_t i = 0; i < *dim_array - 1; i++) {
                new_array[i] = move((*array)[i]);
            }
        }
        // L'ancien tableau sera automatiquement detruit à la sortie de son
        // scope
        *array = move(new_array); // Transferer la propriete au nouveau tableau
    } catch (const std::exception &e) {
        printf("error in allocation");
        while (1) {
        }
    }
}

template void smart_malloc<float>(std::unique_ptr<float[]> *, uint8_t *);
template void smart_malloc<fiche_etu>(std::unique_ptr<fiche_etu[]> *,
                                      uint8_t *);
template void smart_malloc<grade>(std::unique_ptr<grade[]> *, uint8_t *);
template void smart_malloc<matiere>(std::unique_ptr<matiere[]> *, uint8_t *);

bool traitement_date(char date[], uint8_t *day, uint8_t *month,
                     uint32_t *year) {
    char extract[3][5] = {"0"};
    uint8_t num_val = 0, val = 0;
    size_t dateLength = strlen(date); // Get the length of the actual string

    // Input validation: Check if the date string is in the correct format
    if (dateLength != 10 || date[2] != '/' || date[5] != '/') {
        // std::cerr << "Invalid date format. Expected DD/MM/YY." << std::endl;
        printf("Format attendu JJ/MM/AAAA : 06/12/2000 par exemple\n");
        return false; // function failed
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
    *year = atoi(extract[2]);
    if (*month > 12 || *day > 31) {
        printf("Date invalide\n");
        return false; // function failed
    }
    if (*month == 2) {
        bool isLeapYear =
            (*year % 4 == 0 && (*year % 100 != 0 || *year % 400 == 0));
        if (*day > (isLeapYear ? 29 : 28)) {
            printf("Date invalide\n");
            return false;
        }
    }
    if (*month == 4 || *month == 6 || *month == 9 || *month == 11) {
        if (*day > 30) {
            printf("Date invalide\n");
            return false;
        }
    }
    return true; // function success
}

template <typename Type>
void saisie(Type *var, const char *prompt, const char *format) {
    do {
        printf(prompt);
        scanf(format, var);
    } while (!confirm(true));
}
template void saisie<char>(char *var, const char *prompt, const char *format);
template void saisie<uint8_t>(uint8_t *var, const char *prompt,
                              const char *format);
template void saisie<float>(float *var, const char *prompt,
                               const char *format);

void saisie(date *birthdate) {
    char char_date[11];
    birthdate->age = 0;
    do {
        printf(
            "Age etudiant (saisir date de naissance au format JJ/MM/AAAA) :");
        scanf("%10s", char_date);
        if (traitement_date(char_date, &(birthdate->jour), &(birthdate->mois),
                            &(birthdate->annee))) {
            if (confirm(true)) {
                break;
            }
        }
    } while (true);
}

void saisie(bool *redoublant) {
    char selection[4] = "";
    do {
        clean_str(selection);
        printf("Etudiant redoublant(YES/NO) : ");
        scanf("%3s", selection);
        *redoublant = (strcmp("YES", selection) == 0);
    } while (!confirm(true));
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
        str[i] = '\0';
    }
}