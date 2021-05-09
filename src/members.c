#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <gtk/gtk.h>
#include "declars.h"

/* Global variables */
static GtkTreeStore *tree_store;
static GtkTreeView *tree_view;
static GtkTreeSelection *selector;
static GtkWidget *e_name;
static GtkWidget *e_email;
static GtkWidget *e_address;

/* Member's window */
void memberWindow(GtkWidget *widget, gpointer data)
{
    builder = gtk_builder_new_from_file("glade/builder.glade");

    GtkWidget *window = GTK_WIDGET(gtk_builder_get_object(builder, "m_window"));
    GtkWidget *back_button = GTK_WIDGET(gtk_builder_get_object(builder, "m_back_button"));
    GtkWidget *save_button = GTK_WIDGET(gtk_builder_get_object(builder, "m_save_button"));
    GtkWidget *search_bar = GTK_WIDGET(gtk_builder_get_object(builder, "m_search_bar"));
    GtkWidget *add_button = GTK_WIDGET(gtk_builder_get_object(builder, "m_add_button"));
    GtkWidget *edit_button = GTK_WIDGET(gtk_builder_get_object(builder, "m_edit_button"));
    GtkWidget *delete_button = GTK_WIDGET(gtk_builder_get_object(builder, "m_delete_button"));

    tree_store = GTK_TREE_STORE(gtk_builder_get_object(builder, "m_tree_store"));
    tree_view = GTK_TREE_VIEW(gtk_builder_get_object(builder, "m_tree_view"));
    selector = GTK_TREE_SELECTION(gtk_builder_get_object(builder, "m_select"));
    GtkTreeViewColumn *id = GTK_TREE_VIEW_COLUMN(gtk_builder_get_object(builder, "member_id"));
    GtkTreeViewColumn *name = GTK_TREE_VIEW_COLUMN(gtk_builder_get_object(builder, "name"));
    GtkTreeViewColumn *email = GTK_TREE_VIEW_COLUMN(gtk_builder_get_object(builder, "email"));
    GtkTreeViewColumn *address = GTK_TREE_VIEW_COLUMN(gtk_builder_get_object(builder, "address"));
    GtkCellRenderer *column_1 = GTK_CELL_RENDERER(gtk_builder_get_object(builder, "m_column_1"));
    GtkCellRenderer *column_2 = GTK_CELL_RENDERER(gtk_builder_get_object(builder, "m_column_2"));
    GtkCellRenderer *column_3 = GTK_CELL_RENDERER(gtk_builder_get_object(builder, "m_column_3"));
    GtkCellRenderer *column_4 = GTK_CELL_RENDERER(gtk_builder_get_object(builder, "m_column_4"));

    gtk_tree_view_column_add_attribute(id, column_1, "text", 0);
    gtk_tree_view_column_add_attribute(name, column_2, "text", 1);
    gtk_tree_view_column_add_attribute(email, column_3, "text", 2);
    gtk_tree_view_column_add_attribute(address, column_4, "text", 3);

    m_laod();

    g_signal_connect(back_button, "clicked", G_CALLBACK(destroyWidget), window);
    g_signal_connect(add_button, "clicked", G_CALLBACK(addMemberWindow), NULL);
    g_signal_connect(edit_button, "clicked", G_CALLBACK(editMemberWindow), selector);
    g_signal_connect(delete_button, "clicked", G_CALLBACK(deleteMember), selector);
    g_signal_connect(search_bar, "search-changed", G_CALLBACK(searchMember), NULL);
    g_signal_connect(save_button, "clicked", G_CALLBACK(m_save), NULL);

    selector = gtk_tree_view_get_selection(GTK_TREE_VIEW(tree_view));

    gtk_widget_show_all(window);
}

/* Generate unique member id */
int uniqueMemeberId()
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

/* Add member */
void addMember(member *info)
{
    GtkTreeIter iter;

    gtk_tree_store_append(tree_store, &iter, NULL);
    gtk_tree_store_set(tree_store, &iter, 0, info->member_id, -1);
    gtk_tree_store_set(tree_store, &iter, 1, info->full_name, -1);
    gtk_tree_store_set(tree_store, &iter, 2, info->email, -1);
    gtk_tree_store_set(tree_store, &iter, 3, info->address, -1);
}

void insertMember(GtkWidget *widget, gpointer data)
{
    GtkTreeModel *model;
    const gchar *full_name;
    GtkTreeIter iter;
    member *info = Malloc(member);

    info->member_id = uniqueMemeberId();
    strcpy(info->full_name, gtk_entry_get_text(GTK_ENTRY(e_name)));
    strcpy(info->email, gtk_entry_get_text(GTK_ENTRY(e_email)));
    strcpy(info->address, gtk_entry_get_text(GTK_ENTRY(e_address)));

    /* Check if member already exist */
    model = gtk_tree_view_get_model(tree_view);
    gtk_tree_model_get_iter_first(model, &iter);
    if (gtk_tree_store_iter_is_valid(tree_store, &iter) == TRUE)
    {
        while (1)
        {
            gtk_tree_model_get(model, &iter, 1, &full_name, -1);

            if (strcmp(full_name, info->full_name) == 0)
            {
                free(info);
                return;
            }
            if (!gtk_tree_model_iter_next(model, &iter))
                break;
        }
    }
    addMember(info);

    gtk_widget_destroy(data);
    free(info);
}

void addMemberWindow(GtkWidget *widget, gpointer data)
{
    builder = gtk_builder_new_from_file("glade/builder.glade");

    GtkWidget *add_member = GTK_WIDGET(gtk_builder_get_object(builder, "add_member"));
    e_name = GTK_WIDGET(gtk_builder_get_object(builder, "e_name"));
    e_email = GTK_WIDGET(gtk_builder_get_object(builder, "e_email"));
    e_address = GTK_WIDGET(gtk_builder_get_object(builder, "e_address"));
    GtkWidget *add_apply = GTK_WIDGET(gtk_builder_get_object(builder, "m_add_apply"));
    GtkWidget *add_close = GTK_WIDGET(gtk_builder_get_object(builder, "m_add_close"));

    g_signal_connect(add_apply, "clicked", G_CALLBACK(insertMember), add_member);
    g_signal_connect(add_close, "clicked", G_CALLBACK(destroyWidget), add_member);

    gtk_widget_show_all(add_member);
}

/* Search for member */
static int find_row(GtkTreeModel *model, GtkTreeIter iter, gchar full_name[30])
{
    const gchar *text;
    GtkTreePath *path;

    while (1)
    {
        gtk_tree_model_get(model, &iter, 1, &text, -1);

        if (strncasecmp(text, full_name, strlen(full_name)) == 0)
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

void searchMember(GtkSearchEntry *search_bar)
{
    gchar full_name[30];
    GtkTreeIter iter;

    GtkTreeModel *model = gtk_tree_view_get_model(tree_view);

    strcpy(full_name, gtk_entry_get_text(GTK_ENTRY(search_bar)));
    if (strlen(full_name) == 0)
        return;

    gtk_tree_model_get_iter_first(model, &iter);

    if (gtk_tree_store_iter_is_valid(tree_store, &iter) == FALSE)
        return;

    find_row(model, iter, full_name);
}

/* Delete member */
void deleteMember(GtkWidget *widget, gpointer selector)
{
    GtkTreeModel *model;
    GtkTreeIter iter;

    if (gtk_tree_selection_get_selected(GTK_TREE_SELECTION(selector), &model, &iter) == FALSE)
        return;

    gtk_tree_store_remove(tree_store, &iter);
}

/* Edit member */
void editMemberEntry(GtkWidget *widget, gpointer data)
{
    GtkTreeModel *model;
    GtkTreeIter iter;
    member *info = Malloc(member);

    gtk_tree_selection_get_selected(GTK_TREE_SELECTION(selector), &model, &iter);

    strcpy(info->full_name, gtk_entry_get_text(GTK_ENTRY(e_name)));
    strcpy(info->email, gtk_entry_get_text(GTK_ENTRY(e_email)));
    strcpy(info->address, gtk_entry_get_text(GTK_ENTRY(e_address)));

    gtk_tree_store_set(tree_store, &iter, 1, info->full_name, -1);
    gtk_tree_store_set(tree_store, &iter, 2, info->email, -1);
    gtk_tree_store_set(tree_store, &iter, 3, info->address, -1);

    gtk_widget_destroy(data);
    free(info);
}

void editMemberWindow(GtkWidget *widget, gpointer selector)
{
    GtkTreeModel *model;
    GtkTreeIter iter;

    if (gtk_tree_selection_get_selected(GTK_TREE_SELECTION(selector), &model, &iter) == FALSE)
        return;

    builder = gtk_builder_new_from_file("glade/builder.glade");

    GtkWidget *add_member = GTK_WIDGET(gtk_builder_get_object(builder, "add_member"));
    e_name = GTK_WIDGET(gtk_builder_get_object(builder, "e_name"));
    e_email = GTK_WIDGET(gtk_builder_get_object(builder, "e_email"));
    e_address = GTK_WIDGET(gtk_builder_get_object(builder, "e_address"));
    GtkWidget *add_apply = GTK_WIDGET(gtk_builder_get_object(builder, "m_add_apply"));
    GtkWidget *add_close = GTK_WIDGET(gtk_builder_get_object(builder, "m_add_close"));

    g_signal_connect(add_apply, "clicked", G_CALLBACK(editMemberEntry), add_member);
    g_signal_connect(add_close, "clicked", G_CALLBACK(destroyWidget), add_member);

    gtk_widget_show_all(add_member);
}

/* Load infos */
void m_laod()
{
    FILE *file = fopen("data/members.bin", "rb");
    if (file == NULL)
        return;

    member *info = Malloc(member);
    while (fread(info, sizeof(member), 1, file))
        addMember(info);

    free(info);
    fclose(file);
}

/* Save changes */
void m_save(GtkWidget *widget, gpointer data)
{
    GtkTreeIter iter;

    FILE *file = fopen("data/members.bin", "wb");
    if (file == NULL)
        return;

    GtkTreeModel *model = gtk_tree_view_get_model(tree_view);
    gtk_tree_model_get_iter_first(model, &iter);
    if (gtk_tree_store_iter_is_valid(tree_store, &iter) == FALSE)
    {
        fclose(file);
        return;
    }

    member *info = Malloc(member);
    while (1)
    {
        const gchar *text;
        const int value;
        gtk_tree_model_get(model, &iter, 0, &value, -1);
        info->member_id = value;
        gtk_tree_model_get(model, &iter, 1, &text, -1);
        strcpy(info->full_name, text);
        gtk_tree_model_get(model, &iter, 2, &text, -1);
        strcpy(info->email, text);
        gtk_tree_model_get(model, &iter, 3, &text, -1);
        strcpy(info->address, text);

        fwrite(info, sizeof(member), 1, file);

        if (!gtk_tree_model_iter_next(model, &iter))
            break;
    }
    free(info);
    fclose(file);
}