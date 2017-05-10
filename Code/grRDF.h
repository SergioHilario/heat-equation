/*!
 * \brief Estructura graella d'evoluci\'o.
 *
 * Aquesta estructura est\`a preparada per a contenir una
 * llesca de temps de la graella corresponent a la resoluci\'o
 * per difer\`encies finites d'una EDP d'evoluci\'o sobre un
 * rectangle.
 */
typedef struct {
/*!\brief Pas en x (i.e. \f$\delta_x\f$). */
   double dx;
/*!\brief Pas en y (i.e. \f$\delta_y\f$). */
   double dy;
/*!\brief "Pendent num\`eric" en x (i.e. \f$\mu_x\f$). */
   double mux;
/*!\brief "Pendent num\`eric" en y (i.e. \f$\mu_y\f$). */
   double muy;
/*!\brief Nombre de nodes en x menys 1 (i.e. \f$n_x\f$). */
   int nx;
/*!\brief Nombre de nodes en y menys 1 (i.e. \f$n_y\f$). */
   int ny;
/*!\brief Instant de temps al qual correspon el contingut de
 * la graella. */
   double t;
/*!\brief Pas en temps (i.e. \f$\delta_t\f$) */
   double dt;
/*!\brief Graella.
 *
 * El valor de la funci\'o al punt de coordenades
 * <tt>x=i*dx</tt> i <tt>y=j*dy</tt> \'es <tt>u[j*(nx+1)+i]</tt>
 * */
   double *u;
} grRDF;

/*!
 * \brief Inicialitza un objecte grRDF.
 *
 * Assigna par\`ametres, allocata mem\`oria i posa temps a zero.
 */
void grRDF_init (grRDF *gr, double dx, double dy, double dt,
      int nx, int ny, double (*h)(double x, double y));

/*!
 * \brief Per a l'equaci\'o de la calor sobre un rectangle, fa
 * un pas en temps del m\`etode expl\'{\i}cit (3) (o sigui, un pas
 * en k de l'algorisme 1.1)
 */
void grRDF_pasCalExpl (grRDF *gr,
      double (*f)(double t, double x, double y),
      double (*g)(double t, double x, double y));

/*!
 * \brief Escriu un objecte grRDF, en aquest format:
 * \verbatim
 * # t <valor de t>
 * <x> <y> <u(x,y)>
 * ...
 * \endverbatim
 * Recorre la graella per files, insertant un salt de l\'{\i}nia
 * a cada canvi de fila, i dos salts de l\'{\i}nia un cop
 * completada la graella
 */
void grRDF_escriure (grRDF *gr, FILE *fp);

/*!\brief Allibera la mem\`oria d'un objecte \c grRDF. */
void grRDF_allib (grRDF *gr);

/*!
 * \brief Per a l'equaci\'o de la calor sobre un rectangle, fa
 * un pas en temps del m\`etode de Crank-Nicolson (5) (o
 * sigui, un pas en k de l'algorisme 1.2)
 */
int grRDF_pasCalCN (grRDF *gr, double w, double tol, int maxit,
      double (*f)(double t, double x, double y),
      double (*g)(double t, double x, double y));

