/************************************************
 * Nom : Estalella
 * Kevin : Kevin
 * Date: 18.12.2014
 * Version: 1.0
 * Titre: Calendrier
 * Description: Calendrier en mode console
 ***********************************************/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h> //permet d'utiliser le type boolean


typedef enum T_Jour_Semaine T_Jour_Semaine;
typedef enum T_mois T_mois;

enum T_Jour_Semaine {Lu, Ma, Me, Je, Ve, Sa, Di};
enum T_mois {Jan, Fev, Mar, Avr, Mai, Jun, Jui, Aou, Sep, Oct, Nov, Dec};

void initialiserCalendrier(int NBR_SEMAINES_MAX, int NBR_JOURS_SEMAINE, int calendrier[NBR_SEMAINES_MAX][NBR_JOURS_SEMAINE])
{
    int i, j;

    //rempli tout le calendrier avec le symbole 0
    for (i=0; i<NBR_SEMAINES_MAX; i++)
        for (j=0; j<NBR_JOURS_SEMAINE; j++)
            calendrier[i][j] = 0;
}

/*
 * Titre: estBissextile
 *
 * Description: Regarde si l'année passée en argument est bissextiles
 *
 * Retour: Entier. 1 si l'année est bissextile, 0 autrement
 */

int estBissextile(int annee)
{
    //si l'annee est bisextile retourne 1
    if ((((annee % 4) == 0) && !((annee % 100) == 0)) || ((annee % 400) == 0))
        return 1;
    else
        return 0;
}

/*
 * Titre: nbJoursMois
 *
 * Description: Donne le nombre de jours pour un mois
 *
 * Retour: Entier. Retourne le nombre de jours du mois spécifiée en paramètre
 */

int nbJoursMois(int annee, T_mois mois)
{
    switch(mois-1)
    {
        case Fev:
            return 28+estBissextile(annee);  //si l'année est bissextile incrémente février de 1 jour
        case Avr:
        case Jun:
        case Sep:
        case Nov:
            return 30;
        default:
            return 31;
    }
}

/*
 * Titre: premierJourAnnee
 *
 * Description: Donne le premier jour de l'année
 *
 * Retour: T_Jour_Semaine. Retourne le premier jour de l'année spécifiée en paramètre
 */

T_Jour_Semaine premierJourAnnee(int annee)
{
    int const anneeDebut = 1900;
    int somme = 1;

    int i;
    for(i=anneeDebut; i<annee; i++)
    {
        somme += 1 + estBissextile(i);
    }

    return (somme % 7);
}

/*
 * Titre: premierJourMois
 *
 * Description: Donne le premier jour d'un mois
 *
 * Retour: T_Jour_Semaine. Retourne le premier jour du mois et de l'annéee spécifiée en paramètre
 */

T_Jour_Semaine premierJourMois(int annee, T_mois mois)
{
    int somme = 0;

    if (mois > Jan)
    {
        int i;
        for(i=1; i<mois; i++)
        {
            somme = somme + nbJoursMois(annee, i);
        }
    }
    return ((premierJourAnnee(annee) + somme) % 7);
}

/*
 * Titre: nbSemaines
 *
 * Description: Donne le nombre de semaines d'un mois
 *
 * Retour: Rien. Modifie la variable globale en lui affectant le nombre de semaines d'un mois donné
 */

int nbSemaines(int annee, T_mois mois, int premJourMois)
{
    int nbrSemaines;

    nbrSemaines = ((nbJoursMois(annee, mois)) / 7) + 1;

        if ((nbJoursMois(annee, mois) + premJourMois) > 5*7)
            return nbrSemaines+=1;
        else
            return nbrSemaines;

}

/*
 * Titre: faireCalendrier
 *
 * Description: Créer le calendrier sous forme d'un tableau à deux dimension
 *
 * Retour: Rien
 */

int faireCalendrier(int annee, T_mois mois, int NBR_SEMAINES_MAX, int NBR_JOURS_SEMAINE, int calendrier[NBR_SEMAINES_MAX][NBR_JOURS_SEMAINE])
{
    T_Jour_Semaine j = premierJourMois(annee, mois);
    int nbrSemaines;
    int i;
    int ligne = 0;

    nbrSemaines = nbSemaines(annee, mois, j);

    for(i=1; i<=nbJoursMois(annee, mois); i++)
    {
        calendrier[ligne][j] = i;
        j = ((j+1) % 7);
        if (j == 0)
            ligne = ligne + 1;
    }

    return nbrSemaines;
}

/*
 * Titre: afficherCalendrier
 *
 * Description: Affiche le calendrier
 *
 * Retour: Rien
 */

void afficherCalendrier(int nbrSemaines, const int NBR_SEMAINES_MAX, int NBR_JOURS_SEMAINE, int calendrier[NBR_SEMAINES_MAX][NBR_JOURS_SEMAINE])
{
    printf("\n\ndi lu ma me je ve sa");
    printf("\n");

    int i, j;
    for(i=0; i<nbrSemaines; i++)
    {
        for(j=0; j<NBR_JOURS_SEMAINE; j++)
        {
            printf("%d  ", calendrier[i][j]);
        }
        printf("\n");
    }
}

int main()
{
    const int NBR_SEMAINES_MAX = 6;
    int NBR_JOURS_SEMAINE = 7;

    int annee, mois, nbrSemaines;

    int calendrier[NBR_SEMAINES_MAX][NBR_JOURS_SEMAINE];  //déclare notre calendrier
    initialiserCalendrier(NBR_SEMAINES_MAX, NBR_JOURS_SEMAINE, calendrier);

    printf("Entrez un numero d'annee: ");
    scanf("%d", &annee);

    printf("\nEntrez un numero de mois: ");
    scanf("%d", &mois);

    nbrSemaines = faireCalendrier(annee, mois, NBR_SEMAINES_MAX, NBR_JOURS_SEMAINE, calendrier);
    afficherCalendrier(nbrSemaines, NBR_SEMAINES_MAX, NBR_JOURS_SEMAINE, calendrier);

    return 0;
}
