#ifndef AH_PAGE_H_INCLUDED
#define AH_PAGE_H_INCLUDED

#include <string>
#include "ah_api_common.h"
#include "local.h"

using namespace std;

/**
   ЕДИНЫЙ ФОРМАТ СТРАНИЦ:

    |                                        - символ начала страницы
    [4 байта - адрес предыдушей страницы]    - данные двухсвязного списка  // если 0 - то это начало списка
    [4 байта - адрес следующей страницы]     - данные двухсвязного списка  // если 0 - это конец списка

    [байт статуса страницы]                  - > если 0 страница - не используется
                                               > если 1 страница - используется
    [байт типа страницы]                     - тип страницы
    [байт типа страницы 2 ]                  - тип страницы 2  // служебный ID
    [4 байта - размер страницы]              - в байтах
    [4 байта - размер данных страницы]       - в байтах
    [данные страницы]                        - данные страницы
    *                                        - символ конца страницы
*/

/// размер окна фрейма страницы - в байтах
#define PAGE_FRAGMENT_SIZE 64

/// СТАТУС СТРАНИЦЫ
#define AH_PAGE_STATUS_UNUSED   0
#define AH_PAGE_STATUS_USED     1
#define AH_PAGE_STATUS_LOCK     2


/**
    Возвращает массив строк в соответствии с форматом.
    В случае ошибки возвращает NULL
    Внимание! после того как массив использован его надо освободить 'Str2dArray_free'
*/

/// ФУНКЦИИ РАБОТЫ СО СТРАНИЦАМИ
/**
    записывает одну страницу в файл 'f' используя указаный формат
    данные в формате: %{СТРОКА ФОРМАТА}
    формат записи:

        %INT8         - 1 байтовое целое От -128 до 127
        %UINT8        - 1 байтовое целое От 0 до 255
        %INT16        - 2 байтовое целое От -32768 до 32767
        %UINT16       - 2 байтовое целое От 0 до 65535
        %INT32        - 4 байт От -2147483648 до 2147483647
        %UINT32       - 4 байт От 0 до 4294967295
        %INT64        - 8 байт От -9223372036854775808 до 9223372036854775807
        %UINT64       - 8 байт От 0 до 18446744073709551615
        %INTPTR       - 8 байт
        %UINTPTR      - 8 байт
        %FLOAT        - 4 байт +/- 3.4e +/- 38 (~7 digits)
        %DOUBLE       - 8 байт +/- 1.7e +/- 308 (~15 digits)

        %BUFF         - двоичные данные; формат записи: [длинна 4 байта][данные]
        %STR          - строка; формат записи: [длинна строки 4 байта][строка]
        %VCHARXXXX    - varchar - строка с фиксированной длинной; формат записи: [длинна строки 4 байта][данные]

    ! работает от текущего позиции файла.

    return: size write data_page
*/
/*int _ah_page__write_page(  FILE *f
                         , uint32_t prev_ref
                         , uint32_t next_ref
                         , uint8_t status_page
                         , uint8_t type_page
                         , uint8_t type_page_2
                         , char *format
                         , ... );*/

int _ah_page__write_page_a(  FILE *f
                           , uint32_t prev_ref
                           , uint32_t next_ref
                           , uint8_t status_page
                           , uint8_t type_page
                           , uint8_t type_page_2
                           , vector<InfoColum*> &mass_format
                           , struct VoidArray *data_list
            );

/**
 * обновление данных (те типы данных что при обновлении просто затирают старые значения)
 * без изменения местоположения фрейма страницы
 */
int _ah_page__write_page_b(  FILE *f
                           , uint32_t prev_ref
                           , uint32_t next_ref
                           , uint8_t status_page
                           , uint8_t type_page
                           , uint8_t type_page_2
                           , vector<InfoColum*> &mass_format
                           , struct VoidArray *data_list
                           , vector<uint8_t> mask_update
            );

/**
    подсчет размера данных
*/
int _ah_page_calculate_size_page_data( vector<InfoColum*> &mass_format, struct VoidArray *data_list );

/** чтение заголовка страницы
    ! работает от текущего позиции файла.
    ! указывает на начало данных страницы

    return: 0 - ошибка чтения данных
*/
int _ah_page_read_header_page(  FILE *f
                              , uint32_t *prev_ref
                              , uint32_t *next_ref
                              , uint8_t   *status_page
                              , uint8_t   *type_page
                              , uint8_t   *type_page_2
                              , uint32_t  *total_size_page
                              , uint32_t  *size_data_page );


int _ah_page_read_header_page_1(  FILE *f
                                , uint32_t *prev_ref
                                , uint32_t *next_ref );

/** чтение данных из файла в соотвествии с форматом (см. функцию '_rf_write_page')

    Добавочные формат чтения:
        %FPOS - потучить ftell file (unsigned long == uintptr_t)

    ! работает от текущего позиции файла.

    важно!!!!
    для строк и _DataBuffer
    необходимо освобождать память
    free

    return: 0 - ошибка чтения данных
*/
/*int _ah_page_read_all_page(  FILE      *f
                           , uint32_t  *prev_ref
                           , uint32_t  *next_ref
                           , uint8_t   *status_page
                           , uint8_t   *type_page
                           , uint8_t   *type_page_2
                           , uint32_t  *total_size_page
                           , uint32_t  *size_data_page
                           , char      *format
                           , ... );*/

/** читает данные в файл в соответсвии с форматом
    ! работает от текущего позиции файла.
*/
/*
void _ah_page_read_from_format(  FILE *f
                               , char *format
                               , ... );
*/
/**
    ! работает от текущего позиции файла.
*/
void _ah_page_read_from_format_a( FILE *f
                                , vector<InfoColum*> &mass_format
                                , struct VoidArray **data_list_res);


/**
    ! работает от текущего позиции файла.

    учитывает маску-чтения данных
*/
void _ah_page_read_from_format_b( FILE *f
                                , vector<InfoColum*> &mass_format
                                , struct VoidArray **data_list
                                , vector<uint8_t> &mask_read );

/**
    новые значения для страниц-фремов
*/
void __set_page_prev_ref(FILE *f, uint32_t fpos, uint32_t prev_ref);
void __set_page_next_ref(FILE *f, uint32_t fpos, uint32_t next_ref);
void __set_status_page(FILE *f, uint32_t fpos, uint8_t value);

#endif // AH_PAGE_H_INCLUDED
