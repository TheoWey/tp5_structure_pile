#include "memory.hh"

template <typename T>
void smart_malloc(unique_ptr<T[]> *array, uint8_t *dim_array) {
    *dim_array++;
    unique_ptr<T[]> new_array = make_unique<T[]>(*dim_array);
    // Vérifier si l'ancien tableau est vide
    if (*dim_array > 1) {
        // Copier les éléments de l'ancien tableau vers le nouveau
        copy(array.get(), array.get() + (*dim_array - 1),
             new_array.get());
    }
    // L'ancien tableau sera automatiquement détruit à la sortie de son scope
    array = move(new_array); // Transférer la propriété au nouveau tableau
}

