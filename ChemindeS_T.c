/*-------------------------------------------------------------------
 TP1: recherche d'un chemin d'un sommet s vers un sommet t dans un graphe oriente
*/
#include <stdio.h>
#include <stdlib.h>
#define les_sommets 6
// definition de structure de la liste 
typedef struct cel {
    int val; // valuer d'une cellule
    struct cel *svt; // cellule suivante
}cellul;


cellul *Creer_cellule(int elm)
{
	cellul *cl;
	cl=(cellul*)malloc(sizeof(cellul));
	if(!cl)
	{
		printf("Erreur d'allocation !");
        exit(0);
	}
	cl->val=elm;
	cl->svt=NULL;
	return (cellul*)cl;
}


cellul *insererTeteListe(cellul *liste, int valeur) 
{
	cellul *ne;
	ne=Creer_cellule(valeur);		
	if(!liste)  return (cellul*)ne;     
	ne->svt=liste;
	return (cellul*)ne;	
    
}

cellul *supprimerTeteListe(cellul *Maliste) 
{   
    cellul *crt;
 	if(!Maliste) return ((cellul*)NULL); //si la liste n'existe pas on sort
 	crt=Maliste;
 	Maliste=Maliste->svt;
 	free(crt);
 	//printf("\nl element supprimer est %d",crt->val);
 	return ((cellul*)Maliste);
}

void chemin_de_s_vers_t( int MatriceAdj[les_sommets][les_sommets],int s, int t, int nb_sommets) 
{
    int sommtsCh, //pour garder puis afficher les sommets d'un chemin
        etat[nb_sommets],// tableau des sommets marques
        x,i,y; // sommet de parcours
    // liste des sommets du chemin final
    cellul *L = NULL;
    
    s--;
    t--; //pour avoir leur indice correctement (on commence du 0)
    
    if(s >= nb_sommets || s < 0)
    {
        printf("sommet %d innexistant \n",s+1);
        return;
    }
    if(t >= nb_sommets || t < 0)
    {
        printf("sommet %d innexistant \n",t+1);
        return;
    }
    
    //initialiser les sommets marques
    for (i = 0; i < nb_sommets; etat[i++] = 0);
    
    // inserer le sommet du depart dans la liste
    L = insererTeteListe(L, s);
    etat[s] = 1;
    
    //tanque la liste et non vide et le somment final n'est pas atteint
    while (L && etat[t] == 0) 
    {
        x = L->val; 
        L = supprimerTeteListe(L);
        for (y = 0; y < nb_sommets; ++y) //Traiter les successeurs du s
        {
            // si le sommet 'y' est successeur du sommet 'x'
            if (MatriceAdj[x][y] > 0) 
            {
                // si le sommet 'y' n'est pas atteint
                if (etat[y] == 0) 
                {
                    etat[y] = x;
                    L = insererTeteListe(L, y);
                }
            }
        }
    }
    // si le sommet final est  etat
    if (etat[t] != 0)
    {
        printf("\nvoici un chemin de s=(%d) à t=(%d)\n Dans l'ordre inverse : ", s+1, t+1);
        sommtsCh=t;
        while (sommtsCh != s) 
        {
            printf("%d <--", sommtsCh+1);
            sommtsCh = etat[sommtsCh];
        }
        printf("%d\n", s+1);
    }
    else //sinon pas de chemin
        printf("\nAucun chemin entre s=(%d) et t=(%d)\n", s+1, t+1);
}



int main(int argc, char* argv[])
{    
    int n, i, j;
    FILE *f;
    f = fopen("Matrice_Adjacence.txt", "r");
    if (f == NULL) 
    {
        printf("Erreur lors de l'ouverture du fichier.");
        exit(1);
    }
    fscanf(f, "%d", &n); // lecture du nombre de sommets
    int matrice_adjacence[n][n];
    for (i = 0; i < n; i++) 
    {
        for (j = 0; j < n; j++) 
        {
            fscanf(f, "%d", &matrice_adjacence[i][j]); // lecture de la matrice d'adjacence
        }
    }

    //afficher la matrice
    for(i=0; i<n; i++)
    {
        for(j=0; j<n; j++)   
            printf("%d ",matrice_adjacence[i][j]);
        printf("\n");
    }
    //chercher et afficher le chemin entre s et t s'il existe
    chemin_de_s_vers_t(matrice_adjacence,1,4,n);
    fclose(f); // fermeture du fichier
    return 0;
}

