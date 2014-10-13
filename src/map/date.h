// Copyright (c) Athena Dev Teams - Licensed under GNU GPL
// For more information, see LICENCE in the main folder

#ifndef MAP_DATE_H
#define MAP_DATE_H
#include "../config/xa_patch.h"
#include "../common/cbasetypes.h"

int date_get_year(void);
int date_get_month(void);
int date_get_day(void);
int date_get_hour(void);
int date_get_min(void);
int date_get_sec(void);

bool is_day_of_sun(void);
bool is_day_of_moon(void);
bool is_day_of_star(void);

#endif /* MAP_DATE_H */
