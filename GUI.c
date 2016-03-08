/*
 * GUI.c
 *
 *  Created on: March 2, 2016
 *  Author: Weiwei Shi
 */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "GUI.h"
#include "ASSEMBLER.h"
#include "FSM.h"

//GUI constructor
void GUI_Main(int argc, char *argv[]) {
	GtkWidget *windowMain;
    GtkWidget *windowInput;

    GtkWidget *filechooserbutton;
    GtkWidget *clearbutton;
    GtkWidget *tranlatebutton;
    GtkWidget *applybutton;

    GtkWidget *textviewinput;
    GtkWidget *textviewtranslate;
    GtkWidget *textviewhelpdialog;

    GtkWidget *resetbutton;
    GtkWidget *helpbutton;
    GtkWidget *aboutbutton;
    GtkWidget *aboutdialog;
    GtkWidget *helpdialog;

    GError *error = NULL;

    gtk_init(&argc, &argv);
	
	builder = gtk_builder_new();
    gtk_builder_add_from_file(builder, "GUI.ui", &error);
    if (error != NULL) {
        g_warning("%s", error->message);
        g_error_free(error);
        exit(1);
    }

    // WINDOWS
    windowMain = GTK_WIDGET(gtk_builder_get_object(builder, "window-main"));
    windowInput = GTK_WIDGET(gtk_builder_get_object(builder, "window-input"));

    gtk_window_set_title(GTK_WINDOW(windowMain), "LC2200 Simulator");
    gtk_window_set_title(GTK_WINDOW(windowInput), "LC2200 Text Editor");

    g_signal_connect(windowMain, "destroy", G_CALLBACK(gtk_main_quit), NULL);
    gtk_window_set_deletable(GTK_WINDOW(windowInput), false);

    // REGISTES LABELS
    GdkColor color;
    GtkWidget *label;
    char reg_disable[7][7] = { "-$zero", "-$at", "-$v0", "-$k0", "-$sp", "-$fp", "-$ra" };
    char (*sp)[7] = &reg_disable[0];
    gdk_color_parse("dark gray", &color);
    int count;
    for (count = 0; count < sizeof(reg_disable) / sizeof(reg_disable[0]); count++) {
        char label_name[12] = "label";
        strcat(label_name, *sp);
        label = GTK_WIDGET(gtk_builder_get_object(builder, label_name));
        gtk_widget_modify_fg(label, GTK_STATE_NORMAL, &color);

        char entry_name[12] = "entry";
        strcat(entry_name, *sp);
        gtk_editable_set_editable(GTK_EDITABLE(gtk_builder_get_object(builder, entry_name)), false);
        sp++;
    }
	
	color_reg_label(builder, "navy", "label-$a0");
    color_reg_label(builder, "navy", "label-$a1");
    color_reg_label(builder, "navy", "label-$a2");
    color_reg_label(builder, "chocolate", "label-$t0");
    color_reg_label(builder, "chocolate", "label-$t1");
    color_reg_label(builder, "chocolate", "label-$t2");
    color_reg_label(builder, "dark green", "label-$s0");
    color_reg_label(builder, "dark green", "label-$s1");
    color_reg_label(builder, "dark green", "label-$s2");
	
	 // REGISTER ENTRIES
    guientries.entry_zero = GTK_WIDGET(gtk_builder_get_object(builder, "entry-$zero"));
    guientries.entry_at = GTK_WIDGET(gtk_builder_get_object(builder, "entry-$at"));
    guientries.entry_v0 = GTK_WIDGET(gtk_builder_get_object(builder, "entry-$v0"));
    guientries.entry_a0 = GTK_WIDGET(gtk_builder_get_object(builder, "entry-$a0"));
    guientries.entry_a1 = GTK_WIDGET(gtk_builder_get_object(builder, "entry-$a1"));
    guientries.entry_a2 = GTK_WIDGET(gtk_builder_get_object(builder, "entry-$a2"));
    guientries.entry_t0 = GTK_WIDGET(gtk_builder_get_object(builder, "entry-$t0"));
    guientries.entry_t1 = GTK_WIDGET(gtk_builder_get_object(builder, "entry-$t1"));
    guientries.entry_t2 = GTK_WIDGET(gtk_builder_get_object(builder, "entry-$t2"));
    guientries.entry_s0 = GTK_WIDGET(gtk_builder_get_object(builder, "entry-$s0"));
    guientries.entry_s1 = GTK_WIDGET(gtk_builder_get_object(builder, "entry-$s1"));
    guientries.entry_s2 = GTK_WIDGET(gtk_builder_get_object(builder, "entry-$s2"));
    guientries.entry_k0 = GTK_WIDGET(gtk_builder_get_object(builder, "entry-$k0"));
    guientries.entry_sp = GTK_WIDGET(gtk_builder_get_object(builder, "entry-$sp"));
    guientries.entry_fp = GTK_WIDGET(gtk_builder_get_object(builder, "entry-$fp"));
    guientries.entry_ra = GTK_WIDGET(gtk_builder_get_object(builder, "entry-$ra"));
	
	  g_signal_connect(G_OBJECT(guientries.entry_a0), "activate", G_CALLBACK(user_input_function),
            "A0");
    g_signal_connect(G_OBJECT(guientries.entry_a1), "activate", G_CALLBACK(user_input_function),
            "A1");
    g_signal_connect(G_OBJECT(guientries.entry_a2), "activate", G_CALLBACK(user_input_function),
            "A2");
    g_signal_connect(G_OBJECT(guientries.entry_t0), "activate", G_CALLBACK(user_input_function),
            "T0");
    g_signal_connect(G_OBJECT(guientries.entry_t1), "activate", G_CALLBACK(user_input_function),
            "T1");
    g_signal_connect(G_OBJECT(guientries.entry_t2), "activate", G_CALLBACK(user_input_function),
            "T2");
    g_signal_connect(G_OBJECT(guientries.entry_s0), "activate", G_CALLBACK(user_input_function),
            "S0");
    g_signal_connect(G_OBJECT(guientries.entry_s1), "activate", G_CALLBACK(user_input_function),
            "S1");
    g_signal_connect(G_OBJECT(guientries.entry_s2), "activate", G_CALLBACK(user_input_function),
            "S2");
			
	// Coloring the register labels
    char reg_label_mark[9][15] = { "label-$a0-mark", "label-$a1-mark", "label-$a2-mark",
            "label-$t0-mark", "label-$t1-mark", "label-$t2-mark", "label-$s0-mark",
            "label-$s1-mark", "label-$s2-mark" };
    char reg_label_value[9][16] = { "label-$a0-value", "label-$a1-value", "label-$a2-value",
            "label-$t0-value", "label-$t1-value", "label-$t2-value", "label-$s0-value",
            "label-$s1-value", "label-$s2-value" };

    char (*mark_sp)[15] = &reg_label_mark[0];
    char (*value_sp)[16] = &reg_label_value[0];
    GtkWidget *mark;
    gdk_color_parse("navy", &color);
    for (count = 0; count < 9; count++) {
        mark = GTK_WIDGET(gtk_builder_get_object(builder, *mark_sp));
        gui_reg_labels[count].label_value = GTK_WIDGET(gtk_builder_get_object(builder, *value_sp));
        gtk_widget_modify_fg(mark, GTK_STATE_NORMAL, &color);
        if (count == 2) {
            gdk_color_parse("chocolate", &color);
        }
        if (count == 5) {
            gdk_color_parse("dark green", &color);
        }
        mark_sp++;
        value_sp++;
    }
	
	 // TREEVIEW
    guiviewstruct.treeview = GTK_TREE_VIEW(gtk_builder_get_object(builder, "treeview-memory"));

    // STATUSBAR
    statusbar = GTK_WIDGET(gtk_builder_get_object(builder, "label-statusbar"));

    // WINDOW TEXT EDITOR
    clearbutton = GTK_WIDGET(gtk_builder_get_object(builder, "button-clear"));
    filechooserbutton = GTK_WIDGET(gtk_builder_get_object(builder, "filechooserbutton"));
    tranlatebutton = GTK_WIDGET(gtk_builder_get_object(builder, "button-translate"));
    applybutton = GTK_WIDGET(gtk_builder_get_object(builder, "button-apply"));

    textviewinput = GTK_WIDGET(gtk_builder_get_object(builder, "textview-input"));
    textviewtranslate = GTK_WIDGET(gtk_builder_get_object(builder, "textview-translate"));
    textviewhelpdialog = GTK_WIDGET(gtk_builder_get_object(builder, "textview-helpdialog"));

    guiviewstruct.buffer1 = gtk_text_view_get_buffer(GTK_TEXT_VIEW(textviewinput));
    gtk_text_buffer_get_iter_at_offset(guiviewstruct.buffer1, &guiviewstruct.iter, 0);
    gtk_text_buffer_insert(guiviewstruct.buffer1, &guiviewstruct.iter, "Assembly code", -1);

    guiviewstruct.buffer2 = gtk_text_view_get_buffer(GTK_TEXT_VIEW(textviewtranslate));
    gtk_text_buffer_get_iter_at_offset(guiviewstruct.buffer2, &guiviewstruct.iter, 0);
    gtk_text_buffer_insert(guiviewstruct.buffer2, &guiviewstruct.iter, "Machine code", -1);

    GtkTextBuffer *buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(textviewhelpdialog));
    gtk_text_buffer_get_iter_at_offset(buffer, &guiviewstruct.iter, 0);
    gtk_text_buffer_insert(buffer, &guiviewstruct.iter, ".ORIG 2000\n"
                                                        "lw $a0, 1000($zero)\n"
                                                        "add $a1, $zero, $zero\n"
                                                        "addi $a1, $a1, 1\n"
                                                        "addi $a1, $a1, 3\n"
                                                        "addi $a1, $a1, 5\n"
                                                        "addi $a1, $a1, 7\n"
                                                        "addi $a1, $a1, 9\n"
                                                        "nand $a2, $a1, $a1\n"
                                                        "addi $a2, $a2, 1\n"
                                                        "add $a0, $a0, $a2\n"
                                                        "sw $a0, 1000($zero)\n"
                                                        ".END", -1);
	
	// WINDOW MAIN
    previousbutton = GTK_WIDGET(gtk_builder_get_object(builder, "button-previous"));
    nextbutton = GTK_WIDGET(gtk_builder_get_object(builder, "button-next"));
    resetbutton = GTK_WIDGET(gtk_builder_get_object(builder, "button-reset"));
    helpbutton = GTK_WIDGET(gtk_builder_get_object(builder, "button-help"));
    aboutbutton = GTK_WIDGET(gtk_builder_get_object(builder, "button-about"));

    // DIALOGS
    helpdialog = GTK_WIDGET(gtk_builder_get_object(builder, "help-dialog"));
    gtk_window_set_deletable(GTK_WINDOW(helpdialog), false);
    gtk_window_set_title(GTK_WINDOW(helpdialog), "Help");
    aboutdialog = GTK_WIDGET(gtk_builder_get_object(builder, "about-dialog"));
    gtk_window_set_deletable(GTK_WINDOW(aboutdialog), false);
    gtk_window_set_title(GTK_WINDOW(aboutdialog), "About");
    errordialog = GTK_WIDGET(gtk_builder_get_object(builder, "error-dialog"));
    gtk_window_set_deletable(GTK_WINDOW(errordialog), false);
    gtk_window_set_title(GTK_WINDOW(errordialog), "ERROR");

    gtk_about_dialog_set_program_name (GTK_ABOUT_DIALOG(aboutdialog), "LC-2200");
    gtk_about_dialog_set_version (GTK_ABOUT_DIALOG(aboutdialog), "Autumn 2015");
    gtk_about_dialog_set_comments  (GTK_ABOUT_DIALOG(aboutdialog),   "TCSS 372 B Computer Architecture\nInstructor: Dr. Liu Xing\nGroup members:\nLan Ly and Christine Vu");

    // SIGNALS
    g_signal_connect(G_OBJECT(filechooserbutton), "file-set", G_CALLBACK(get_filename_function),
    NULL);
    g_signal_connect(G_OBJECT(clearbutton), "clicked", G_CALLBACK(clear_function), NULL);
    g_signal_connect(G_OBJECT(tranlatebutton), "clicked", G_CALLBACK(translate_function),
            applybutton);
    g_signal_connect(G_OBJECT(applybutton), "clicked", G_CALLBACK(applycode_function), nextbutton);

    g_signal_connect(G_OBJECT(previousbutton), "clicked", G_CALLBACK(previous_function), NULL);
    g_signal_connect(G_OBJECT(nextbutton), "clicked", G_CALLBACK(next_function), NULL);
    g_signal_connect(G_OBJECT(resetbutton), "clicked", G_CALLBACK(reset_function), NULL);
    g_signal_connect(G_OBJECT(helpbutton), "clicked", G_CALLBACK(help_function), helpdialog);
    g_signal_connect(G_OBJECT(aboutbutton), "clicked", G_CALLBACK(about_function), aboutdialog);

    g_signal_connect(GTK_DIALOG(helpdialog), "response", G_CALLBACK(dialog_on_close), NULL);
    g_signal_connect(GTK_DIALOG(aboutdialog), "response", G_CALLBACK(dialog_on_close), NULL);
    g_signal_connect(GTK_DIALOG(errordialog), "response", G_CALLBACK(dialog_on_close), NULL);

    gtk_widget_show_all(windowMain);
    gtk_widget_show_all(windowInput);

    FSM_init();
    gtk_main();
}