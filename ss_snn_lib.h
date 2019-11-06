/*______________________________________________
| ss_snn_lib
| Scuola Sisini Shallow Neural Network Library
| Francesco Sisini (c) 2019
*/
/*** Livello 1 ***/
/* Calcola l'output di uno strato
percettroni */
void layer_feed_forward
(double v_s[],double v_y[],double v_w[],double v_x[],int n_perc, int n_dend);
/* Mappa l'output v_y in v_x aggiungendo prima l'elemento v_x[0]=1*/
void layer_map_out_in
(double v_x[],double v_y[], int n_dend);
/*** Livello 2 ***/
/* Calcola la risposta del
percettrone */
double perc_calc_output
(double v_w[],double v_x[],int n_dend);
/* Corregge i pesi del percettrone */
void perc_correzione
(double v_w[],double v_x[],double z,double d,double rate,int n_dend);
/*** Livello 3 ***/
/* Calcola il valore della risposta del percettrone*/
double activ_function
(double summed_input);
/* Calcola il valore della derivata della risposta del percettrone*/
double Dactiv_function
(double summed_input);
/* Legge un immagine 28x28 in o e la sua label in out_label */
int get_image
(int * o,int * out_label,FILE * in_stream);
/* Stampa a video una matrice r x c in R,C */
void print_object 
(double x[],int r, int c,int R,int C);
/*_____________________________________________________
| stream: il file su cui scrivere
| v_w: l'array sequenziale con tutti i pesi del layer
| n_dend: numero di dendriti per percettrone
| n_perc: numero di percettroni nel layer
*/
void layer_writedown
(FILE * stream,double *v_w, int n_dend, int n_perc);
/*______________________________________________________
| stream: il file da cui legge i pesi delle connessioni
| v_w: l'array sequenziale con tutti i pesi del layer
| n_dend: numero di dendriti per percettrone
| n_perc: numero di percettroni nel layer
*/
void layer_read
(FILE * stream,double *v_w, int n_dend, int n_perc);
