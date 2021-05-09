#ifndef DECLARS_H_INCLUDED
#define DECLARS_H_INCLUDED

/* Macros */
#define Malloc(t) (t *)malloc(sizeof(t))

/* Extern variables */
extern GtkBuilder *builder;

/* Member struct */
typedef struct
{
    int member_id;
    char full_name[30];
    char email[30];
    char address[50];
} member;

/* Book struct */
typedef struct
{
    int book_id;
    char category[15];
    char title[50];
    char author[30];
    int stock;
} book;

/* Functions */
void destroyWidget();
/* Member functions */
void memberWindow();
void addMemberWindow();
void editMemberWindow();
void deleteMember();
void searchMember();
void m_laod();
void m_save();
/* Book functions */
void bookWindow();
void addBookWindow();
void editBookWindow();
void deleteBook();
void searchBook();
void b_load();
void b_save();

#endif