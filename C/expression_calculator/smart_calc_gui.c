#include <ctype.h>
#include <gtk/gtk.h>
#include <gtk/gtkx.h>
#include <math.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

#include "smart_calc_1_0.h"

int show_error(int error);
void eval_expr_clicked();
void clear_input();
void gnuplotify(char *input, char *result);
void btn_xx_clicked(GtkButton *b1);
void reset_x_clicked();

GtkWidget *main_window;
GtkWidget *fmain;
GtkWidget *stack1;
GtkWidget *f0;
GtkWidget *f1;
GtkWidget *expr_entry;
GtkWidget *draw_button;
GtkWidget *label1;
GtkWidget *x_entry;
GtkWidget *answer_entry;
GtkWidget *reset_x;
GtkWidget *f2;
GtkWidget *stack_switcher;
GtkWidget *err_label;
GtkWidget *err_dialog;
GtkWidget *btn11;
GtkWidget *btn12;
GtkWidget *btn13;
GtkWidget *btn14;
GtkWidget *btn15;
GtkWidget *btn16;
GtkWidget *btn21;
GtkWidget *btn22;
GtkWidget *btn23;
GtkWidget *btn24;
GtkWidget *btn25;
GtkWidget *btn26;
GtkWidget *btn31;
GtkWidget *btn32;
GtkWidget *btn33;
GtkWidget *btn34;
GtkWidget *btn35;
GtkWidget *btn36;
GtkWidget *btn41;
GtkWidget *btn42;
GtkWidget *btn43;
GtkWidget *btn44;
GtkWidget *btn45;
GtkWidget *btn46;
GtkWidget *btn51;
GtkWidget *btn52;
GtkWidget *btn53;
GtkWidget *btn54;
GtkWidget *btn55;
GtkWidget *btn56;
GtkBuilder *builder;

int main(int argc, char **argv) {
  gtk_init(&argc, &argv);

  builder = gtk_builder_new_from_file("smartcalc.glade");
  main_window = GTK_WIDGET(gtk_builder_get_object(builder, "main_window"));
  g_signal_connect(main_window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
  gtk_builder_connect_signals(builder, NULL);

  fmain = GTK_WIDGET(gtk_builder_get_object(builder, "fmain"));
  stack1 = GTK_WIDGET(gtk_builder_get_object(builder, "stack1"));
  f0 = GTK_WIDGET(gtk_builder_get_object(builder, "f0"));
  f1 = GTK_WIDGET(gtk_builder_get_object(builder, "f1"));
  expr_entry = GTK_WIDGET(gtk_builder_get_object(builder, "expr_entry"));
  label1 = GTK_WIDGET(gtk_builder_get_object(builder, "label1"));
  x_entry = GTK_WIDGET(gtk_builder_get_object(builder, "x_entry"));
  answer_entry = GTK_WIDGET(gtk_builder_get_object(builder, "answer_entry"));
  btn11 = GTK_WIDGET(gtk_builder_get_object(builder, "btn11"));
  btn12 = GTK_WIDGET(gtk_builder_get_object(builder, "btn12"));
  btn13 = GTK_WIDGET(gtk_builder_get_object(builder, "btn13"));
  btn14 = GTK_WIDGET(gtk_builder_get_object(builder, "btn14"));
  btn15 = GTK_WIDGET(gtk_builder_get_object(builder, "btn15"));
  btn16 = GTK_WIDGET(gtk_builder_get_object(builder, "btn16"));
  btn21 = GTK_WIDGET(gtk_builder_get_object(builder, "btn21"));
  btn22 = GTK_WIDGET(gtk_builder_get_object(builder, "btn22"));
  btn23 = GTK_WIDGET(gtk_builder_get_object(builder, "btn23"));
  btn24 = GTK_WIDGET(gtk_builder_get_object(builder, "btn24"));
  btn25 = GTK_WIDGET(gtk_builder_get_object(builder, "btn25"));
  btn26 = GTK_WIDGET(gtk_builder_get_object(builder, "btn26"));
  btn31 = GTK_WIDGET(gtk_builder_get_object(builder, "btn31"));
  btn32 = GTK_WIDGET(gtk_builder_get_object(builder, "btn32"));
  btn33 = GTK_WIDGET(gtk_builder_get_object(builder, "btn33"));
  btn34 = GTK_WIDGET(gtk_builder_get_object(builder, "btn34"));
  btn35 = GTK_WIDGET(gtk_builder_get_object(builder, "btn35"));
  btn36 = GTK_WIDGET(gtk_builder_get_object(builder, "btn36"));
  btn41 = GTK_WIDGET(gtk_builder_get_object(builder, "btn41"));
  btn42 = GTK_WIDGET(gtk_builder_get_object(builder, "btn42"));
  btn43 = GTK_WIDGET(gtk_builder_get_object(builder, "btn43"));
  btn44 = GTK_WIDGET(gtk_builder_get_object(builder, "btn44"));
  btn45 = GTK_WIDGET(gtk_builder_get_object(builder, "btn45"));
  btn46 = GTK_WIDGET(gtk_builder_get_object(builder, "btn46"));
  btn51 = GTK_WIDGET(gtk_builder_get_object(builder, "btn51"));
  btn52 = GTK_WIDGET(gtk_builder_get_object(builder, "btn52"));
  btn53 = GTK_WIDGET(gtk_builder_get_object(builder, "btn53"));
  btn54 = GTK_WIDGET(gtk_builder_get_object(builder, "btn54"));
  btn55 = GTK_WIDGET(gtk_builder_get_object(builder, "btn55"));
  btn56 = GTK_WIDGET(gtk_builder_get_object(builder, "btn56"));
  reset_x = GTK_WIDGET(gtk_builder_get_object(builder, "reset_x"));
  draw_button = GTK_WIDGET(gtk_builder_get_object(builder, "draw_button"));

  f2 = GTK_WIDGET(gtk_builder_get_object(builder, "f2"));
  stack_switcher =
      GTK_WIDGET(gtk_builder_get_object(builder, "stack_switcher"));
  gtk_window_set_title(GTK_WINDOW(main_window), "SmartCalc v1.0");
  gtk_widget_show(main_window);
  gtk_main();
  return EXIT_SUCCESS;
}

void eval_expr_clicked() {
  char input[300];
  int error;
  int err = OK;
  s21_stack rpn = {0};
  double x;
  double res;
  char res_str[16];
  GtkWidget *container;

  gtk_entry_set_text(GTK_ENTRY(answer_entry), "");

  err_dialog = gtk_dialog_new();
  gtk_window_set_title(GTK_WINDOW(err_dialog), "Error!");
  gtk_window_set_modal(GTK_WINDOW(err_dialog), TRUE);
  gtk_widget_set_size_request(err_dialog, 200, 150);
  err_label = gtk_label_new("");
  container = gtk_dialog_get_content_area(GTK_DIALOG(err_dialog));
  gtk_container_add(GTK_CONTAINER(container), err_label);

  if (strlen((char *)gtk_entry_get_text(GTK_ENTRY(expr_entry))) > 255) {
    gtk_label_set_text(GTK_LABEL(err_label),
                       (const gchar *)"String too long. Max length - 255");
    gtk_widget_show_all(err_dialog);
  } else {
    sprintf(input, "%s", gtk_entry_get_text(GTK_ENTRY(expr_entry)));
    sscanf(gtk_entry_get_text(GTK_ENTRY(x_entry)), "%lf", &x);
    error = convert_to_rpn(input, &rpn);
    err = show_error(error);
    if (err == OK) {
      error = eval_expr(rpn, x, &res);
      err = show_error(error);
      if (err == OK) {
        snprintf(res_str, 16, "%.8lf", res);
        gtk_entry_set_text(GTK_ENTRY(answer_entry), (const gchar *)res_str);
      }
    }
  }
  s21_clear_stack(&rpn);
}

int show_error(int error) {
  int ret = OK;
  if (error == STRING_TOO_BIG) {
    gtk_label_set_text(GTK_LABEL(err_label),
                       (const gchar *)"String too long. Max length - 255");
    gtk_widget_show_all(err_dialog);
    ret = 1;
  } else if (error == INVALID_EXPRESSION) {
    gtk_label_set_text(GTK_LABEL(err_label), "");
    gtk_label_set_text(GTK_LABEL(err_label),
                       (const gchar *)"Invalid expression");
    gtk_widget_show_all(err_dialog);
    ret = 1;
  } else if (error == PARSE_ERROR) {
    gtk_label_set_text(GTK_LABEL(err_label), "");
    gtk_label_set_text(GTK_LABEL(err_label),
                       (const gchar *)"Invalid expression");
    gtk_widget_show_all(err_dialog);
    ret = 1;
  } else if (error == BRACKET_MISSMATCH) {
    gtk_label_set_text(GTK_LABEL(err_label), "");
    gtk_label_set_text(GTK_LABEL(err_label),
                       (const gchar *)"Bracket missmatch");
    gtk_widget_show_all(err_dialog);
    ret = 1;
  } else if (error == NUMBER_OVERFLOW) {
    gtk_label_set_text(GTK_LABEL(err_label), "");
    gtk_label_set_text(
        GTK_LABEL(err_label),
        (const gchar
             *)"Number too big. (numbers must be from -1000000 to 1000000");
    gtk_widget_show_all(err_dialog);
    ret = 1;
  } else if (error == DIV_BY_ZERO) {
    gtk_label_set_text(GTK_LABEL(err_label), "");
    gtk_label_set_text(GTK_LABEL(err_label),
                       (const gchar *)"Division by zero is not allowed");
    gtk_widget_show_all(err_dialog);
    ret = 1;
  } else if (error == MATH_ERROR) {
    gtk_label_set_text(GTK_LABEL(err_label), "");
    gtk_label_set_text(GTK_LABEL(err_label),
                       (const gchar *)"Invalid mathematical expression");
    gtk_widget_show_all(err_dialog);
    ret = 1;
  }
  return ret;
}

void draw_function() {
  char expr[255];
  char buff[400];
  char command[600];
  GtkWidget *container;
  s21_stack rpn = {0};
  err_dialog = gtk_dialog_new();
  gtk_window_set_title(GTK_WINDOW(err_dialog), "Error!");
  gtk_window_set_modal(GTK_WINDOW(err_dialog), TRUE);
  gtk_widget_set_size_request(err_dialog, 200, 150);
  err_label = gtk_label_new("");
  container = gtk_dialog_get_content_area(GTK_DIALOG(err_dialog));
  gtk_container_add(GTK_CONTAINER(container), err_label);

  if (strlen((char *)gtk_entry_get_text(GTK_ENTRY(expr_entry))) > 255) {
    gtk_label_set_text(GTK_LABEL(err_label),
                       "String too long. Max length - 255");
    gtk_widget_show_all(err_dialog);
  } else {
    sprintf(expr, "%s", gtk_entry_get_text(GTK_ENTRY(expr_entry)));
    int err = convert_to_rpn(expr, &rpn);
    if (err != 0) {
      printf("%d\n", err);
      gtk_label_set_text(GTK_LABEL(err_label), "Error, gnuplot failed");
      gtk_widget_show_all(err_dialog);
    } else {
      gnuplotify(expr, buff);
      sprintf(command,
              "gnuplot -p -e \'set xlabel %s;set ylabel %s; set key bottom "
              "left box; set grid; set border 3; set tics nomirror ; plot %s\'",
              "\"X\"", "\"Y\"", buff);
      err = system(command);
    }
  }
  s21_clear_stack(&rpn);
}

void gnuplotify(char *input, char *result) {
  strcpy(result, input);
  char *pos;
  int index = 0;
  char buff[300];
  int i = 0;
  while ((pos = strstr(result + index + i, "log")) != NULL) {
    i = 3;
    strcpy(buff, result);
    index = pos - result;
    result[index] = '\0';
    strcat(result, "log10");
    strcat(result, buff + index + 3);
  }
  while ((pos = strstr(result + index + i, "X")) != NULL) {
    strcpy(buff, result);
    index = pos - result;
    result[index] = '\0';
    strcat(result, "x");
    strcat(result, buff + index + 1);
  }
  while ((pos = strstr(result, "ln")) != NULL) {
    strcpy(buff, result);
    index = pos - result;
    result[index] = '\0';
    strcat(result, "log");
    strcat(result, buff + index + 2);
  }
  while ((pos = strstr(result, "^")) != NULL) {
    strcpy(buff, result);
    index = pos - result;
    result[index] = '\0';
    strcat(result, "**");
    strcat(result, buff + index + 1);
  }
}

void btn_xx_clicked(GtkButton *b1) {
  char *name;
  int len = 0;
  GtkEntryBuffer *buff;
  name = (char *)gtk_button_get_label(b1);
  if (is_function(name, 0) && (strcmp(name, "mod") != 0)) {
    strcat(name, "(");
  }
  if (strcmp(name, "pow") == 0) {
    name = "^";
  }
  len = gtk_entry_get_text_length(GTK_ENTRY(expr_entry));
  buff = gtk_entry_get_buffer(GTK_ENTRY(expr_entry));
  gtk_entry_buffer_insert_text(buff, len, name, strlen(name));
}

void clear_input() {
  gtk_entry_set_text(GTK_ENTRY(expr_entry), "");
}

void reset_x_clicked() {
  gtk_entry_set_text(GTK_ENTRY(x_entry), (const gchar *)"0");
}
