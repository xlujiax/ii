#pragma once

#include "gtk.h"

static struct przycisk {
  char *opis, *wyjscie;
  int posX,lenX,posY,lenY;
} tab[] = {{"CLR","",0,1,0,1},     {"/","/",1,1,0,1},{"*","*",2,1,0,1},{"-","-",3,1,0,1},
	       {"7","7",0,1,1,1},     {"8","8",1,1,1,1},{"9","9",2,1,1,1},{"+","+",3,1,1,2},
	       {"4","4",0,1,2,1},     {"5","5",1,1,2,1},{"6","6",2,1,2,1},
	       {"1","1",0,1,3,1},     {"2","2",1,1,3,1},{"3","3",2,1,3,1},{"Enter","\n",3,1,3,2},
	       {"0","0",0,2,4,1},     {".",".",2,1,4,1},
	       {"(","(",0,2,5,1},     {")",")",2,2,5,1}};

static GtkWidget *text;

static void test_nacisniecia( GtkWidget *widget,gpointer data)
{
  g_print("GTK-test - %s zastal nacisniety\n", (gchar *) data);
}

static void wyjscie_przycisk( GtkWidget *widget,gpointer data)
{
  gtk_main_quit();
}

static void wprowadzony_tekst( GtkWidget *widget,GtkWidget *text)
{
  const gchar *wejscie;
  wejscie = gtk_entry_get_text (GTK_ENTRY (text));
  g_print ("GTK-test wprowadzono: %s\n", wejscie);
}

static void dodaj_do_text(GtkWidget *widget, gpointer data) {
  if(strcmp((gchar*)data, "\n") == 0)
  {
        gtk_entry_append_text(GTK_ENTRY(text), (gchar*)"=");
        char* wejscie = gtk_entry_get_text (GTK_ENTRY (text));;
        int len = strlen(wejscie);
        char* wynik = oblicz(wejscie, len);
        gtk_entry_set_text(GTK_ENTRY(text), wynik);
    }
  if(strcmp((gchar*)data, "") == 0)
  {
        gtk_entry_set_text(GTK_ENTRY(text), "");
    }
  else 
    gtk_entry_append_text(GTK_ENTRY(text), (gchar*)data);
}


int run_window( int   argc,char *argv[] )
{
    GtkWidget *window;
    GtkWidget *box1, *box2;
    GtkWidget *button;
    GtkWidget *table;
    gint       tmp_pos;


    gtk_init (&argc, &argv);

    window = gtk_window_new (GTK_WINDOW_TOPLEVEL);

    gtk_window_set_title (GTK_WINDOW (window), "GTK - test");

    g_signal_connect (G_OBJECT (window), "delete_event",G_CALLBACK (gtk_main_quit), NULL);
    g_signal_connect (G_OBJECT (window), "destroy",G_CALLBACK (gtk_main_quit), NULL);

    gtk_container_set_border_width (GTK_CONTAINER (window), 10);

    box1 = gtk_vbox_new (FALSE, 0);

    gtk_container_add (GTK_CONTAINER (window), box1);


    text = gtk_entry_new ();
    gtk_entry_set_max_length (GTK_ENTRY (text), 50);
    g_signal_connect (G_OBJECT (text), "activate",
		      G_CALLBACK (wprowadzony_tekst),
		      (gpointer) text);
    gtk_entry_set_text (GTK_ENTRY (text), "");
    gtk_editable_select_region (GTK_EDITABLE (text),
			        0, GTK_ENTRY (text)->text_length);
    gtk_box_pack_start (GTK_BOX (box1), text, TRUE, TRUE, 0);
    gtk_widget_show (text);

    table = gtk_table_new(5,4,TRUE);
    gtk_table_set_row_spacings(GTK_TABLE(table), 3);
    gtk_table_set_col_spacings(GTK_TABLE(table), 3);
    gtk_box_pack_start (GTK_BOX (box1), table, TRUE, TRUE, 0);
    gtk_widget_show(table);
	
    for(int i = 0; i < 19; i++) {
      button = gtk_button_new_with_label(tab[i].opis);
      g_signal_connect(G_OBJECT(button), "clicked",G_CALLBACK(dodaj_do_text), (gpointer) tab[i].wyjscie);
      gtk_table_attach_defaults(GTK_TABLE(table), button, tab[i].posX, tab[i].posX+tab[i].lenX, 
	 		                                  tab[i].posY, tab[i].posY+tab[i].lenY);
      gtk_widget_show(button);
    }


    box2 = gtk_hbox_new (FALSE, 0);
    button = gtk_button_new_with_label ("Koniec");
    g_signal_connect (G_OBJECT (button), "clicked",G_CALLBACK (wyjscie_przycisk), NULL);
    gtk_box_pack_start(GTK_BOX (box2), button, TRUE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX (box1), box2, TRUE, TRUE, 0);
    gtk_widget_show (button);
    gtk_widget_show (box2);


    gtk_widget_show (box1);
    gtk_widget_show (window);

    
    gtk_main ();

    return 0;
}

