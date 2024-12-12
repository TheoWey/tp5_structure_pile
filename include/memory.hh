#pragma region // librairie externes

#include <cstring>
#include <memory>
#include <stdio.h>
#include <stdlib.h>
#include <cstdint>

#pragma endregion // librairie externes

#ifndef MEMOIRE_HH
#define MEMOIRE_HH

#pragma region // manage dependancy

#include "etudiant.hh"

#pragma endregion // manage dependancy

#pragma region // declaration des variables

#define __NEED_CONFIRM__ true // ask for validation when all modification done
#define __NEED_CONFIRM_ALL__ true // ask for validation after all modification

using namespace std;

#pragma endregion // declaration des variables

#pragma region // declaration des fonctions

/**
 * @brief Dynamically allocates and resizes an array of elements.
 *
 * This function dynamically allocates memory for an array of elements of type
 * `T` and resizes it if necessary. It uses `unique_ptr` to manage the memory
 * allocation and automatically release it when the function exits.
 *
 * @tparam T The type of elements in the array.
 * @param array A pointer to a pointer to the array of elements.
 * @param dim_array A pointer to the dimension of the array.
 */
template <typename T>
void smart_malloc(unique_ptr<T[]> *array, uint8_t *dim_array);

/**
 * @brief Extracts day, month, and year from a date string.
 *
 * This function takes a date string in the format "DD/MM/YYYY" and extracts the
 * day, month, and year components.
 *
 * @param date The date string in the format "DD/MM/YYYY".
 * @param day A pointer to a uint8_t variable where the extracted day will be
 * stored.
 * @param month A pointer to a uint8_t variable where the extracted month will
 * be stored.
 * @param year A pointer to a uint32_t variable where the extracted year will be
 * stored.
 *
 * @return `true` if the date string is valid and the extraction was successful,
 * `false` otherwise.
 *
 * @example
 * char date[] = "06/01/2018";
 * uint8_t day, month;
 * uint32_t year;
 * traitement_date(date, &day, &month, &year);
 */
bool traitement_date(char date[], uint8_t *day, uint8_t *month, uint32_t *year);

/**
 * @brief Prompts the user for confirmation and returns a boolean value.
 *
 * This function prompts the user for confirmation with a "YES/NO" question.
 * It reads the user's input and returns `true` if the input is "YES"
 * (case-insensitive), otherwise it returns `false`.
 *
 * @return `true` if the user confirms, `false` otherwise.
 */
bool confirm(bool single);

/**
 * @brief Cleans up a string by filling it with spaces.
 *
 * This function parses each character in the string
 * string passed as an argument and replaces it with a space.
 *
 * @param str Pointer to the string to be cleaned.
 */
void clean_str(char *str);

#pragma endregion // declaration des fonctions
#endif
