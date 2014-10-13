// Copyright (c) Athena Dev Teams - Licensed under GNU GPL
// For more information, see LICENCE in the main folder

#ifndef CHAR_INT_MAIL_H
#define CHAR_INT_MAIL_H
#include "../config/xa_patch.h"
struct item;
struct mail_message;

int inter_mail_parse_frommap(int fd);
void mail_sendmail(int send_id, const char* send_name, int dest_id, const char* dest_name, const char* title, const char* body, int zeny, struct item *item);

int inter_mail_sql_init(void);
void inter_mail_sql_final(void);

int mail_savemessage(struct mail_message* msg);
void mapif_Mail_new(struct mail_message *msg);

#endif /* CHAR_INT_MAIL_H */
