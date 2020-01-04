#include "stdafx.h"
#include <iostream>
#include <string>
#include <ctime>
#include <cstdlib>
#include <fstream>
#include <vector>
#include <SFML/Graphics.hpp>

using namespace std;

string getItemplayer();
string reflexion(string file, string itemJoueur);
vector<int> CheckWin(vector<int> point, string itemJoueur, string itemIA);



int main()
{
	srand(time(0));
	char replay('o');
	string file("Data/all.txt");

	// Explication du jeu
	cout << "Bienvenue dans l'Intelligence Artificielle pour le jeu du Shi Fu Mi developpe par Chad" << endl << "Cette inteligence s'adapte en fonction de son joueur et apprend de son adversaire," << endl << "c'est a dire qu'elle gagnera de plus en plus facilement les parties ..." << endl << endl;

	// Demande identifiant
	cout << "Quel identifiant voulez vous mettre ? (all = tout les joueurs)" << endl;
	string reponse;
	getline(cin, reponse);
	file = "Data/" + reponse + ".txt";

	//check des Datas
	ifstream flux(file);
	if (flux) {
		cout << "Datas ouvertes correctements pour : " << reponse << ", activation de l'Intelligence Artificielle ..." << endl << endl;
	}
	else {
		cout << "Ce compte n'est pas encore cree, compte " << reponse << " cree, activation de l'Intelligence Artificielle (aleatoire pour le debut avant d'apprendre)..." << endl << endl;
		ofstream flux(file);
	}


	do {
		string precedent("First");
		string itemJoueur("First");
		string itemIA("");
		vector<int> point; /* point[0] = pointIA , point[1] = pointJoueur */
		point.push_back(0); // point[0] = pointIA
		point.push_back(0); // point[1] = pointJoueur

		do {
			cout << "Reflexion ..." << endl;

			// Intelgence
			itemIA = reflexion(file, itemJoueur); // reflexion de l'IA

			/* Choix Joueur */
			cout << "Reflexion terminee ..." << endl;
			itemJoueur = getItemplayer(); // demander l'item du joueur

			cout << "Le joueur a choisis : " << itemJoueur << endl;
			cout << "L IA a choisis : " << itemIA << endl;

			// Sauvegarde des datas pour l'IA
			ofstream flux(file, ios::app);
			flux << precedent << ": " << itemJoueur << endl;
			precedent = itemJoueur;

			// Check win
			point = CheckWin(point, itemJoueur, itemIA);

			// Affichage resultat
			cout << "Point IA : " << point[0] << endl << "Point Joueur : " << point[1] << endl << endl;

		} while (point[0] <= 2 && point[1] <= 2);

		// Affichage gagnant
		if (point[0] == 3) {
			cout << "L IA a gagnee" << endl;
		}
		else {
			cout << "Le joueur a gagnee" << endl;
		}
		cout << "Voulez vous rejouer ? o/n" << endl;
		cin >> replay;
	} while (replay == 'o');

    return 0;
}


string getItemplayer() {
	cout << "Veuillez choisir votre item : pierre(p, 1) ; feuille(f, 2) ; ciseaux(c, 3)" << endl;
	string m_itemjoueur;
	do {
		cin >> m_itemjoueur;
		if (m_itemjoueur == "p" || m_itemjoueur == "1") {
			m_itemjoueur = "pierre";
		}
		else if (m_itemjoueur == "c" || m_itemjoueur == "2") {
			m_itemjoueur = "ciseaux";
		}
		else if (m_itemjoueur == "f" || m_itemjoueur == "3") {
			m_itemjoueur = "feuille";
		}
		if (m_itemjoueur != "pierre" && m_itemjoueur != "ciseaux" && m_itemjoueur != "feuille") {
			cout << "L'item saisit est inconnu ... Veuillez reessayer:" << endl;
		}
	} while (m_itemjoueur != "pierre" && m_itemjoueur != "ciseaux" && m_itemjoueur != "feuille");
	
	return m_itemjoueur;
}


vector<int> CheckWin(vector<int> point, string itemJoueur, string itemIA) {

	if (itemJoueur == itemIA) {
		cout << "Egalite ..." << endl;
	}
	else if (itemJoueur == "feuille") {
		if (itemIA == "pierre") {
			cout << "Plus 1 point pour le joueur" << endl;
			point[1] += 1;
		}
		else if (itemIA == "ciseaux") {
			cout << "Plus 1 point pour l IA" << endl;
			point[0] += 1;
		}
	}
	else if (itemJoueur == "pierre") {
		if (itemIA == "ciseaux") {
			cout << "Plus 1 point pour le joueur" << endl;
			point[1] += 1;
		}
		else if (itemIA == "feuille") {
			cout << "Plus 1 point pour l IA" << endl;
			point[0] += 1;
		}
	}
	else if (itemJoueur == "ciseaux") {
		if (itemIA == "feuille") {
			cout << "Plus 1 point pour le joueur" << endl;
			point[1] += 1;
		}
		else if (itemIA == "pierre") {
			cout << "Plus 1 point pour l IA" << endl;
			point[0] += 1;
		}
	}

	return point;
}




string reflexion(string file, string itemJoueur) {

	string m_itemIA;

	int nbrAlea(rand() % 100);
	int nbrCheck(0);
	int nbrFeuille(0);
	int nbrCiseaux(0);
	int nbrPierre(0);
	string checkData;

	if (itemJoueur == "First") {
		ifstream flux(file);
		while (flux >> checkData) {
			if (checkData == "First:") {
				nbrCheck += 1;
				flux >> checkData;
				if (checkData == "pierre") {
					nbrPierre += 1;
				}
				else if (checkData == "feuille") {
					nbrFeuille += 1;
				}
				else if (checkData == "ciseaux") {
					nbrCiseaux += 1;
				}
			}
		}
	}
	else if (itemJoueur == "pierre") {
		ifstream flux(file);
		while (flux >> checkData) {
			if (checkData == "pierre:") {
				nbrCheck += 1;
				flux >> checkData;
				if (checkData == "pierre") {
					nbrPierre += 1;
				}
				else if (checkData == "feuille") {
					nbrFeuille += 1;
				}
				else if (checkData == "ciseaux") {
					nbrCiseaux += 1;
				}
			}
		}
	}
	else if (itemJoueur == "feuille") {
		ifstream flux(file);
		while (flux >> checkData) {
			if (checkData == "feuille:") {
				nbrCheck += 1;
				flux >> checkData;
				if (checkData == "pierre") {
					nbrPierre += 1;
				}
				else if (checkData == "feuille") {
					nbrFeuille += 1;
				}
				else if (checkData == "ciseaux") {
					nbrCiseaux += 1;
				}
			}
		}
	}
	else if (itemJoueur == "ciseaux") {
		ifstream flux(file);
		while (flux >> checkData) {
			if (checkData == "ciseaux:") {
				nbrCheck += 1;
				flux >> checkData;
				if (checkData == "pierre") {
					nbrPierre += 1;
				}
				else if (checkData == "feuille") {
					nbrFeuille += 1;
				}
				else if (checkData == "ciseaux") {
					nbrCiseaux += 1;
				}
			}
		}
	}
	if (nbrCheck != 0) {
		nbrAlea = rand() % nbrCheck;
		if (nbrAlea <= nbrPierre) {
			m_itemIA = "feuille";
		}
		else if (nbrAlea <= nbrPierre + nbrFeuille) {
			m_itemIA = "ciseaux";
		}
		else {
			m_itemIA = "pierre";
		}
	}
	else {
		if (nbrAlea <= 33) {
			m_itemIA = "pierre";
		}
		else if (nbrAlea <= 66) {
			m_itemIA = "feuille";
		}
		else {
			m_itemIA = "ciseaux";
		}
	}
	return m_itemIA;
}
