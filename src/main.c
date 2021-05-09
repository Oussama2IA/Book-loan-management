#include <gtk/gtk.h>
#include "declars.h"

/* Global variables */
GtkBuilder *builder;

int main(int argc, char **argv)
{
    gtk_init(&argc, &argv);

    builder = gtk_builder_new_from_file("glade/builder.glade");

    GtkWidget *main_window = GTK_WIDGET(gtk_builder_get_object(builder, "main_window"));
    GtkWidget *member_button = GTK_WIDGET(gtk_builder_get_object(builder, "member_button"));
    GtkWidget *book_button = GTK_WIDGET(gtk_builder_get_object(builder, "book_button"));
    GtkWidget *loan_button = GTK_WIDGET(gtk_builder_get_object(builder, "loan_button"));
    GtkWidget *close_button = GTK_WIDGET(gtk_builder_get_object(builder, "close_button"));

    g_signal_connect(main_window, "delete-event", G_CALLBACK(gtk_main_quit), NULL);
    g_signal_connect(member_button, "clicked", G_CALLBACK(memberWindow), NULL);
    g_signal_connect(book_button, "clicked", G_CALLBACK(bookWindow), NULL);
    g_signal_connect(close_button, "clicked", G_CALLBACK(gtk_main_quit), NULL);

    gtk_widget_show_all(main_window);
    gtk_main();
    return 0;
}

void destroyWidget(GtkWidget *widget, gpointer data)
{
    gtk_widget_destroy(data);
}