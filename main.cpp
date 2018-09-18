/*
 * Name: MotMystere
 * Author: Valentin Besse
 * Email: valentinbesse@aumbox.net
 * License: CC-Zero
 * Description: Jeu du mot mystere
 *
*/

#include <iostream> // gestion des entrées et sorties
#include <string>	// gestion des strings
#include <ctime>    // Obligatoire pour le melange des lettres
#include <cstdlib>  // Obligatoire pour le melange des lettres
#include <algorithm>
#include <fstream>  // Gestion vers les fichiers

using namespace std;

/**
 * @brief messageBienvenue  Message d'acceuil
 */
void messageBienvenue()
{
    cout << "Bienvenue dans le jeu du mot Mystere." << endl;
    cout << "Le but du jeu est de deviner le mot a partir des lettres affichees." << endl;
}

/**
 * @brief motDico  Va chercher un mot dans le dictionnaire au hasard
 * @return motMystere  Renvoi le mot mystere choisi dans le dictionnaire
 */
string motDico()
{
    int nombreDeMot(323576), motHasard(0), i(0);    // Nombre de mot dans le fichier dictionnaire
    ifstream fluxDico("/home/valentinbesse/Documents/Programmation/Openclassroom/MotMystere/dico.txt");  // Ouverture du fichier dictonnaire en lecture (ne fonctionne pas en chemin relatif
    // ifstream fluxDico("dico.txt");  // Ouverture du fichier dictonnaire en lecture
    string motMystere;  // Mot mystere a deviner

    srand(time(0)); // Appel de fonction obligatoire pour la generation de nombre aleatoire

    motHasard = rand() % nombreDeMot;   // Nombre aleatoire entre 0 et 323576
    motHasard++;    // Nombre aléatoire entre 1 et 323577

    for (i=0; i <= motHasard; i++)  // Boucle pour selectionner le mot du dictionnaire
    {
        getline(fluxDico,motMystere);
    }

    motMystere.erase(motMystere.size()-1,1);    // Supprime le caractere en trop a la fin du mot (saut de ligne)

    return motMystere;
}

/**
 * @brief Fonction de saisi du mot mystere
 * @return motMystere  Le mot mystere
 */
string saisirMotMystere()
{

    string motMystere;
    int i(0);

    cout << "Veuillez saisir le mot mystere : ";
    cin >> motMystere;  // Saisie du mot mystere

    for (i=0; i<30;i++)
    {
        cout << endl;
    }

    transform(motMystere.begin(), motMystere.end(),motMystere.begin(), ::toupper);    // Transforme le string en majuscule

    return motMystere;
}

/**
 * @brief Fonction qui melange les mots.
 * @param motIntermediaire  Le mot mystere a melanger
 * @return motMelange  Le mot melange
 */
string melangeMot(string motIntermediaire)
{

    string motMelange;
    int nbAleatoire(0), i(0), longueurMot = motIntermediaire.size();

    srand(time(0)); // Appel de fonction obligatoire pour la generation de nombre aleatoire

    for(i = 0; i < longueurMot; i++)
    {
        nbAleatoire = rand() % motIntermediaire.size();   // Nombre aleatoire entre 0 et longueur du mot mystere.
        motMelange += motIntermediaire[nbAleatoire];
        motIntermediaire.erase(nbAleatoire, 1);  // Retire la lettre a la position du nombre aleatoire

    }

    return motMelange;
}

/**
 * @brief Boucle de jeu
 * @param motMelange  Le mot melange
 * @param motMystere  Le mot mystere a deviner
 * @param nombreDeCoup  Nombre de coup pour deviner
*/
void tourDeJeu(string motMelange, string motMystere, int nombreDeCoup)
{

    string motSaisi;

    int i(1);

    do // Premier tour de jeu
    {
        cout << "Il vous reste : " << nombreDeCoup - i + 1 << " tentatives." << endl;   // Affichage des tentatives restantes
        cout << "Quel est le mot mystere ? " << motMelange << endl;  // Affichage du mot melange
        cin >> motSaisi;
        std::transform(motSaisi.begin(), motSaisi.end(),motSaisi.begin(), ::toupper);    // Transforme le string en majuscule
        if (motSaisi == motMystere) // Reussite
        {
            cout << "Bravo !!!" << endl;
        }
        else    // Echec
        {
            cout << "Ce n'est pas le mot mystere." << endl;
            i++;
        }

    }
    while (motSaisi != motMystere && i <= nombreDeCoup);

    if (i > nombreDeCoup)
    {
        cout << "Vous avez perdu." << endl;
    }

}

int main()
{

    // Declaration des variables
    string  motMelange, motMystere, continuJeu;
    int nombreDeCoup(5), nombreJoueur(1);

    messageBienvenue(); // Message de bienvenue

    cout << "Combien de joueur(s) ? 1/2 : ";
    cin >> nombreJoueur;

    if (nombreJoueur == 1)  // Boucle 1 joueur
    {
        do
        {
        motMystere = motDico();

        motMelange = melangeMot(motMystere);    // Melange des lettres

        tourDeJeu(motMelange, motMystere, nombreDeCoup);    // Tour de jeu

        cout << "Voulez-vous faire une autre partie ? (o/N) : ";
        cin >> continuJeu;
        }
        while(continuJeu == "o" || continuJeu == "O");
    }
    else if (nombreJoueur == 2) // Boucle 2 joueurs
    {
        do
        {
            motMystere = saisirMotMystere();    // Saisit du mot

            motMelange = melangeMot(motMystere);    // Melange des lettres

            tourDeJeu(motMelange, motMystere, nombreDeCoup);

            cout << "Voulez-vous faire une autre partie ? (o/N) : ";
            cin >> continuJeu;
        }
        while(continuJeu == "o" || continuJeu == "O");
    }

    return 0;
}
