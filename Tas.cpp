/****************************************************************************************************************
*Auteur: Pisani Fosso A00187566                                                                                **
*****************************************************************************************************************
*But:	implémenter une file de priorité (classeFPQuatre) en utilisant un tas-min quaternaire générique.       **
*		Unteltasestsimilaire à celui binaire mais chaque noeud peut avoir un maximum de quatre enfants. 	   **
*		Par conséquent, un tas-min quaternaire doit respecter la structure                                     **
*		générale d’un tas en plus des contraintes d’ordre entre chaque noeud parent et ses enfants.            **
*****************************************************************************************************************
*/

#include <iostream>
#include <fstream>
#include <ctime>
using namespace std;

/*La class ci-dessous s'occupera de:
- Ajouter un élement de type T dans la file de priorité et l'ajuster en ordre avec les fonctions inserer et rewind
- Supprimer le minimum dans la file de priorité et l'ajuster en ordre avec les fonctions enleverMin et come_down
- Afficher le minimum dans la file de priorité avec la fonction recuperMin
- Tester si la file de priorité est vide estVide
- Connaitre la taille file de priorité avec la fonction taille
*/
template <class T>
class classeFPQuatre
{
public:
	void swap(T&, T&);
	void show();
	void inserer(T);
	void rewind(int);
	T enleverMin();
	void come_down(int);
	T recuperMin();
	bool estVide();
	int taille();
	classeFPQuatre(T[], int);
	~classeFPQuatre();
private:
	int *Heap;
	int position;
	int parent(int i) { return (i - 1) / 4; }
	int left(int i) { return (4 * i + 1); }
};

/****************************************************************************************************************
Nom de la fonction: swap                                                                                       **
*****************************************************************************************************************
Type de parametres: T; T                                                                                       **
*****************************************************************************************************************
Description:	Prend 2 parametres de même type et les échange                                                 **
*****************************************************************************************************************
*/
template<class T>
void classeFPQuatre	<T>::swap(T &elt1, T& elt2)
{
	T temp = elt1;
	elt1 = elt2;
	elt2 = temp;
}

/****************************************************************************************************************
Nom de la fonction: show                                                                                       **
*****************************************************************************************************************
Type de parametres:		                                                                                       **
*****************************************************************************************************************
Description:	Affche tous les éléments contenue dans la File de priorité                                     **
*****************************************************************************************************************
*/
template <class T>
void classeFPQuatre<T>::show()
{	
	//Si la pile est vide afficher la pile est vide
	if (estVide())
	{	
		cout << "Le Tas est Vide " << endl;
		return;
	}

	//tanque i < taille du tableau afficher l'élément contenu à la position i
	for (int i = 0; i < taille(); i++)
		cout << Heap[i] << " ";
	cout << endl<<endl;
}

/****************************************************************************************************************
Nom de la fonction: inserer                                                                                    **
*****************************************************************************************************************
Type de parametres:	T	                                                                                       **
*****************************************************************************************************************
Description:	Prend l'élément en parametre et l'insert dans la file de priorité                              **
*****************************************************************************************************************
*/
template <class T>
void classeFPQuatre<T>::inserer(T elt)
{
	if (estVide())
		Heap = new T[taille() + 2];	// Si le tas est vide constuire un tas qui contiendra les 2 priorité absoluts
	int i = taille();	//position d'insertion
	Heap[i] = elt;		//insertion dans la file de priorité
	rewind(i);			//ajustement de la file de priorité
	position++;			//incrementer la taille du tableau
}

/****************************************************************************************************************
Nom de la fonction: rewind                                                                                     **
*****************************************************************************************************************
Type de parametres:	int	                                                                                       **
*****************************************************************************************************************
Description:	met le nouvel élément ajouter à sa priorité                                                    **
*****************************************************************************************************************
*/
template <class T>
void classeFPQuatre<T>::rewind(int i)
{
	if (i == 0) return;		//si l'élément est deja à la tête sortir de la fonction
	int p = parent(i);		//actualisation du parent de l'élément

	//si l'élément ajouté est supérieur à sont parent, échanger les et rappeler la fonction jusqu'a ce que 
	//ce ne soit plus cas ou que l'élément est à la tete de la file.
	if (Heap[i] < Heap[p])
	{
		swap(Heap[i], Heap[p]);
		rewind(p);	//rappel de la fonction
	}
}

/****************************************************************************************************************
Nom de la fonction: enleverMin                                                                                 **
*****************************************************************************************************************
Type de parametres:		                                                                                       **
*****************************************************************************************************************
Description:	retire l'élément avec la plus petit priorité (l'élément à la position 0)                       **
*****************************************************************************************************************
*/
template <class T>
T classeFPQuatre<T>::enleverMin()
{
	if (estVide()) return -1;	//Si le tas est vide retourner -1
	T temp = Heap[0];	//Recuperer la l'élément à la position 0
	Heap[0] = Heap[taille() - 1];	//Mettre le dernier élément à la position 0
	position--;			//diminuer la taille du tableau.
	come_down(0);		//Ajuster a file de prioprité
	return temp;		//retourner l'element à la position 0
}

/****************************************************************************************************************
Nom de la fonction: come_down                                                                                  **
*****************************************************************************************************************
Type de parametres:	int	                                                                                       **
*****************************************************************************************************************
Description:	  Ajuster a file de prioprité										                           **
*****************************************************************************************************************
*/
template <class T>
void classeFPQuatre <T>::come_down(int i)
{
	int l = left(i);			//connaitre l'enfant le plus à gauche
	if (l >= taille()) return;	//si il sepérieur à la taille sortir de la fonction il est deja en place
	
	//on cherche le plus petit entre le premier enfant et 4eme enfant
	

	if (l + 3 < taille())
	{
		for (int c = l+1; c < l+3; c++)
		{
			if (Heap[c] < Heap[l])
				l = c;
		}
	}

	//une autre façon de faire les lignes precedentes
	//while (l + 3 < taille() && Heap[l + 1] < Heap[l])
	//l++;


	//si le plus petit es enfant est plus petit que le premier element alors remplacer les 
	//et chercher encore le plus petit dans les enfants les enfants des enfants
	if (Heap[l] < Heap[i]) {
		swap(Heap[l], Heap[i]);
		come_down(l);
	}
	
}

/****************************************************************************************************************
Nom de la fonction: taille                                                                                     **
*****************************************************************************************************************
Type de parametres:		                                                                                       **
*****************************************************************************************************************
Description:	  Connaitre la taille de la file de priorité    					                           **
*****************************************************************************************************************
*/
template <class T>
int classeFPQuatre<T>::taille()
{
	return position;	//retourne la position du dernier élément
}

/****************************************************************************************************************
Nom de la fonction: recuperMin                                                                                 **
*****************************************************************************************************************
Type de parametres:		                                                                                       **
*****************************************************************************************************************
Description:	 Avoir l'élément le plus prioritaire dans la file 					                           **
*****************************************************************************************************************
*/
template <class T>
T classeFPQuatre<T>::recuperMin()
{
	if (estVide())	//Si la file est vide retourner -1
		return -1;	
	return Heap[0];	//Si la liste n'est pas vide 
}

/****************************************************************************************************************
Nom de la fonction: estVide                                                                                    **
*****************************************************************************************************************
Type de parametres:		                                                                                       **
*****************************************************************************************************************
Description:	 determine si la fonction est vide              					                           **
*****************************************************************************************************************
*/
template <class T>
bool classeFPQuatre<T>::estVide()
{
	//Si la taille est 0 le tas est vide
	return taille() == 0;
}

/****************************************************************************************************************
Nom de la fonction: classeFPQuatre                                                                             **
*****************************************************************************************************************
Type de parametres:	T; int                                                                                     **
*****************************************************************************************************************
Description:	construit la file de priorité et initialise la taille				                           **
*****************************************************************************************************************
*/
template <class T>
classeFPQuatre<T>::classeFPQuatre(T random_table[], int size)
{
	Heap = new T[size + 2];
	position = size;

	//remplir le tas de valeurs aléatoires
	for (int i = 0; i < size; i++)
	{
		Heap[i] = random_table[i];
	}
	
	//structuration du tasQuaternaire
	for (int i = size / 4; i >= 0; i--)
		{
			come_down(i);
		}
}

/****************************************************************************************************************
Nom de la fonction: ~classeFPQuatre                                                                            **
*****************************************************************************************************************
Type de parametres:		                                                                                       **
*****************************************************************************************************************
Description:	detruit la file de priorité                          				                           **
*****************************************************************************************************************
*/
template <class T>
classeFPQuatre <T>::~classeFPQuatre()
{
	delete[]Heap;
}

int main()
{
	ifstream myFile;
	myFile.open("Tas.txt");		//ouvrir le fichier 
	
	if (myFile) {

		//Declaration des variables
		int N;
		int priority_P1;
		int priority_P2;
		myFile >> N;
		int *tab = new int[N];		//allouer de l'espace memoire au tableau

		//remplissage du tableau dynamique avec des valeurs dans le fichier txt
		for (int i = 0; i < N; i++)
		{
			myFile >> tab[i];
		}
		
		//recupere les priorités
		myFile >> priority_P1;
		myFile >> priority_P2;

		//instanciation de la file de priorité
		classeFPQuatre <int> Tas(tab, N);

		//inserer les priorité dans la file de priorité
		Tas.inserer(priority_P1);
		Tas.inserer(priority_P2);

		//enlever l'élément le plus prioritaire
		cout << "L'element enleve est: " << Tas.enleverMin() << endl << endl;
		
		//Afficher la file de priorité
		cout << "Le tas est: "; Tas.show();

		//L'élément le plus prioritaire
		cout << "L'element le plus prioritaire est: " << Tas.recuperMin() << endl << endl;

		//taille du Tas
		cout <<"La taille du tas est: "<< Tas.taille() << endl<<endl;

		//Desallouer l'espace memoire occupé par le tableau
		delete[]tab;
	}
	//s'il y a eu de problemes lors de l'ouverture du fichier afficher erreur
	else cerr << "Erreur" << endl;

	return 0;
}
/* ********************** Calcul du temps ***************
			float temps;
			clock_t t1, t2;

			t1 = clock();

			//Code a tester

			t2 = clock();
			temps = ((float)(t2 - t1) / CLOCKS_PER_SEC);
			cout << temps << endl;
*********************************************************
*/

//Exemple:
/*
Input file contain:
15 79 9 99 50 70 74 47 6 37 96 88 46 38 13 91 15 22

Output shell:
9 22 38 13 70 74 47 79 37 96 88 46 99 50 91 15

La taille du tas est: 16

*/

