#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <gtk/gtk.h>
#include "declars.h"

/* Global variables */
static GtkTreeStore *tree_store;
static GtkTreeView *tree_view;
static GtkTreeSelection *selector;
static GtkWidget *e_title;
static GtkWidget *e_category;
static GtkWidget *e_author;
static GtkWidget *e_stock;

/* Book's window */
void bookWindow(GtkWidget *widget, gpointer data)
{
    builder = gtk_builder_new_from_file("glade/builder.glade");

    GtkWidget *window = GTK_WIDGET(gtk_builder_get_object(builder, "b_window"));
    GtkWidget *back_button = GTK_WIDGET(gtk_builder_get_object(builder, "b_back_button"));
    GtkWidget *save_button = GTK_WIDGET(gtk_builder_get_object(builder, "b_save_button"));
    GtkWidget *search_bar = GTK_WIDGET(gtk_builder_get_object(builder, "b_search_bar"));
    GtkWidget *add_button = GTK_WIDGET(gtk_builder_get_object(builder, "b_add_button"));
    GtkWidget *edit_button = GTK_WIDGET(gtk_builder_get_object(builder, "b_edit_button"));
    GtkWidget *delete_button = GTK_WIDGET(gtk_builder_get_object(builder, "b_delete_button"));

    tree_store = GTK_TREE_STORE(gtk_builder_get_object(builder, "b_tree_store"));
    tree_view = GTK_TREE_VIEW(gtk_builder_get_object(builder, "b_tree_view"));
    selector = GTK_TREE_SELECTION(gtk_builder_get_object(builder, "b_select"));
    GtkTreeViewColumn *id = GTK_TREE_VIEW_COLUMN(gtk_builder_get_object(builder, "book_id"));
    GtkTreeViewColumn *category = GTK_TREE_VIEW_COLUMN(gtk_builder_get_object(builder, "category"));
    GtkTreeViewColumn *title = GTK_TREE_VIEW_COLUMN(gtk_builder_get_object(builder, "title"));
    GtkTreeViewColumn *author = GTK_TREE_VIEW_COLUMN(gtk_builder_get_object(builder, "author"));
    GtkTreeViewColumn *stock = GTK_TREE_VIEW_COLUMN(gtk_builder_get_object(builder, "stock"));
    GtkCellRenderer *column_1 = GTK_CELL_RENDERER(gtk_builder_get_object(builder, "b_column_1"));
    GtkCellRenderer *column_2 = GTK_CELL_RENDERER(gtk_builder_get_object(builder, "b_column_2"));
    GtkCellRenderer *column_3 = GTK_CELL_RENDERER(gtk_builder_get_object(builder, "b_column_3"));
    GtkCellRenderer *column_4 = GTK_CELL_RENDERER(gtk_builder_get_object(builder, "b_column_4"));
    GtkCellRenderer *column_5 = GTK_CELL_RENDERER(gtk_builder_get_object(builder, "b_column_5"));

    gtk_tree_view_column_add_attribute(id, column_1, "text", 0);
    gtk_tree_view_column_add_attribute(category, column_2, "text", 1);
    gtk_tree_view_column_add_attribute(title, column_3, "text", 2);
    gtk_tree_view_column_add_attribute(author, column_4, "text", 3);
    gtk_tree_view_column_add_attribute(stock, column_5, "text", 4);

    b_load();

    g_signal_connect(back_button, "clicked", G_CALLBACK(destroyWidget), window);
    g_signal_connect(add_button, "clicked", G_CALLBACK(addBookWindow), NULL);
    g_signal_connect(edit_button, "clicked", G_CALLBACK(editBookWindow), selector);
    g_signal_connect(delete_button, "clicked", G_CALLBACK(deleteBook), selector);
    g_signal_connect(search_bar, "search-changed", G_CALLBACK(searchBook), NULL);
    g_signal_connect(save_button, "clicked", G_CALLBACK(b_save), NULL);

    selector = gtk_tree_view_get_selection(GTK_TREE_VIEW(tree_view));

    gtk_widget_show_all(window);
}

/* Generate unique book id */
int uniqueBookId()
{
    gint value;
    GtkTreeIter iter;
    GtkTreeModel *model = gtk_tree_view_get_model(tree_view);

    gtk_tree_model_get_iter_first(model, &iter);
    if (gtk_tree_store_iter_is_valid(tree_store, &iter) == FALSE)
        return 1;

    while (1)
    {
        gtk_tree_model_get(model, &iter, 0, &value, -1);
        if (!gtk_tree_model_iter_next(model, &iter))
            return value + 1;
    }
}

/* Add book */
void addBook(book *info)
{
    GtkTreeIter iter;

    gtk_tree_store_append(tree_store, &iter, NULL);
    gtk_tree_store_set(tree_store, &iter, 0, info->book_id, -1);
    gtk_tree_store_set(tree_store, &iter, 1, info->category, -1);
    gtk_tree_store_set(tree_store, &iter, 2, info->title, -1);
    gtk_tree_store_set(tree_store, &iter, 3, info->author, -1);
    gtk_tree_store_set(tree_store, &iter, 4, info->stock, -1);
}

void insertBook(GtkWidget *widget, gpointer data)
{
    GtkTreePath *path;
    GtkTreeModel *model;
    GtkTreeIter iter;
    const gchar *category;
    const gchar *title;
    book *info = Malloc(book);

    info->book_id = uniqueBookId();
    strcpy(info->category, gtk_entry_get_text(GTK_ENTRY(e_category)));
    strcpy(info->title, gtk_entry_get_text(GTK_ENTRY(e_title)));
    strcpy(info->author, gtk_entry_get_text(GTK_ENTRY(e_author)));
    info->stock = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(e_stock));

    /* Check if member already exist */
    model = gtk_tree_view_get_model(tree_view);
    gtk_tree_model_get_iter_first(model, &iter);
    if (gtk_tree_store_iter_is_valid(tree_store, &iter) == TRUE)
    {
        while (1)
        {
            gtk_tree_model_get(model, &iter, 1, &category, -1);
            gtk_tree_model_get(model, &iter, 2, &title, -1);

            if ((strcmp(category, info->category) == 0) && (strcmp(title, info->title) == 0))
            {
                free(info);
                return;
            }
            if (!gtk_tree_model_iter_next(model, &iter))
                break;
        }
    }
    addBook(info);

    gtk_widget_destroy(data);
    free(info);
}

void addBookWindow(GtkWidget *widget, gpointer data)
{
    builder = gtk_builder_new_from_file("glade/builder.glade");

    GtkWidget *add_book = GTK_WIDGET(gtk_builder_get_object(builder, "add_book"));
    e_category = GTK_WIDGET(gtk_builder_get_object(builder, "e_category"));
    e_title = GTK_WIDGET(gtk_builder_get_object(builder, "e_title"));
    e_author = GTK_WIDGET(gtk_builder_get_object(builder, "e_author"));
    e_stock = GTK_WIDGET(gtk_builder_get_object(builder, "e_stock"));
    GtkWidget *add_apply = GTK_WIDGET(gtk_builder_get_object(builder, "b_add_apply"));
    GtkWidget *add_close = GTK_WIDGET(gtk_builder_get_object(builder, "b_add_close"));

    g_signal_connect(add_apply, "clicked", G_CALLBACK(insertBook), add_book);
    g_signal_connect(add_close, "clicked", G_CALLBACK(destroyWidget), add_book);

    gtk_widget_show_all(add_book);
}

/* Search for book */
static int find_row(GtkTreeModel *model, GtkTreeIter iter, gchar title[50])
{
    const gchar *text;
    GtkTreePath *path;

    while (1)
    {
        gtk_tree_model_get(model, &iter, 2, &text, -1);

        if (strncasecmp(text, title, strlen(title)) == 0)
        {
            path = gtk_tree_model_get_path(model, &iter);
            gtk_tree_view_scroll_to_cell(tree_view, path, NULL, TRUE, 0.5, 0.0);
            gtk_tree_view_set_cursor_on_cell(tree_view, path, NULL, NULL, FALSE);
            return 1;
        }
        if (!gtk_tree_model_iter_next(model, &iter))
            return 0;
    }
}

void searchBook(GtkSearchEntry *search_bar)
{
    gchar title[30];
    GtkTreeIter iter;

    GtkTreeModel *model = gtk_tree_view_get_model(tree_view);

    strcpy(title, gtk_entry_get_text(GTK_ENTRY(search_bar)));
    if (strlen(title) == 0)
        return;

    gtk_tree_model_get_iter_first(model, &iter);

    if (gtk_tree_store_iter_is_valid(tree_store, &iter) == FALSE)
        return;

    find_row(model, iter, title);
}

/* Delete book */
void deleteBook(GtkWidget *widget, gpointer selector)
{
    GtkTreeModel *model;
    GtkTreeIter iter;

    if (gtk_tree_selection_get_selected(GTK_TREE_SELECTION(selector), &model, &iter) == FALSE)
        return;

    gtk_tree_store_remove(tree_store, &iter);
}

/* Edit book */
void editBookEntry(GtkWidget *widget, gpointer data)
{
    GtkTreeModel *model;
    GtkTreeIter iter;
    book *info = Malloc(book);

    gtk_tree_selection_get_selected(GTK_TREE_SELECTION(selector), &model, &iter);

    strcpy(info->category, gtk_entry_get_text(GTK_ENTRY(e_category)));
    strcpy(info->title, gtk_entry_get_text(GTK_ENTRY(e_title)));
    strcpy(info->author, gtk_entry_get_text(GTK_ENTRY(e_author)));
    info->stock = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(e_stock));

    gtk_tree_store_set(tree_store, &iter, 1, info->category, -1);
    gtk_tree_store_set(tree_store, &iter, 2, info->title, -1);
    gtk_tree_store_set(tree_store, &iter, 3, info->author, -1);
    gtk_tree_store_set(tree_store, &iter, 4, info->stock, -1);

    gtk_widget_destroy(data);
    free(info);
}

void editBookWindow(GtkWidget *widget, gpointer selector)
{
    GtkTreeModel *model;
    GtkTreeIter iter;

    if (gtk_tree_selection_get_selected(GTK_TREE_SELECTION(selector), &model, &iter) == FALSE)
        return;

    builder = gtk_builder_new_from_file("glade/builder.glade");

    GtkWidget *add_book = GTK_WIDGET(gtk_builder_get_object(builder, "add_book"));
    e_category = GTK_WIDGET(gtk_builder_get_object(builder, "e_category"));
    e_title = GTK_WIDGET(gtk_builder_get_object(builder, "e_title"));
    e_author = GTK_WIDGET(gtk_builder_get_object(builder, "e_author"));
    e_stock = GTK_WIDGET(gtk_builder_get_object(builder, "e_stock"));
    GtkWidget *add_apply = GTK_WIDGET(gtk_builder_get_object(builder, "b_add_apply"));
    GtkWidget *add_close = GTK_WIDGET(gtk_builder_get_object(builder, "b_add_close"));

    g_signal_connect(add_apply, "clicked", G_CALLBACK(editBookEntry), add_book);
    g_signal_connect(add_close, "clicked", G_CALLBACK(destroyWidget), add_book);

    gtk_widget_show_all(add_book);
}

/* Load infos */
void b_load()
{
    FILE *file = fopen("data/books.bin", "rb");
    if (file == NULL)
        return;

    book *info = Malloc(book);
    while (fread(info, sizeof(book), 1, file))
        addBook(info);

    free(info);
    fclose(file);
}

/* Save changes */
void b_save(GtkWidget *widget, gpointer data)
{
    GtkTreeIter iter;

    FILE *file = fopen("data/books.bin", "wb");
    if (file == NULL)
        return;

    GtkTreeModel *model = gtk_tree_view_get_model(tree_view);
    gtk_tree_model_get_iter_first(model, &iter);
    if (gtk_tree_store_iter_is_valid(tree_store, &iter) == FALSE)
    {
        fclose(file);
        return;
    }

    book *info = Malloc(book);
    while (1)
    {
        const gchar *text;
        const int value;
        gtk_tree_model_get(model, &iter, 0, &value, -1);
        info->book_id = value;
        gtk_tree_model_get(model, &iter, 1, &text, -1);
        strcpy(info->category, text);
        gtk_tree_model_get(model, &iter, 2, &text, -1);
        strcpy(info->title, text);
        gtk_tree_model_get(model, &iter, 3, &text, -1);
        strcpy(info->author, text);
        gtk_tree_model_get(model, &iter, 4, &value, -1);
        info->stock = value;

        fwrite(info, sizeof(book), 1, file);

        if (!gtk_tree_model_iter_next(model, &iter))
            break;
    }
    free(info);
    fclose(file);
}