/*************************************************************************
                           Decoupeur  -  description
                             -------------------
    début                : $DATE$
    copyright            : (C) $YEAR$ par $AUTHOR$
    e-mail               : $EMAIL$
*************************************************************************/

//---------- Réalisation de la classe <Decoupeur> (fichier Decoupeur.cpp) ------------

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
#include <iostream>
using namespace std;

//------------------------------------------------------ Include personnel
#include "Decoupeur.h"

//------------------------------------------------------------- Constantes

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques
void Decoupeur::LigneSuivante() 
{//TODO: rajouter des filtres pour la selection.
	if(fichier)
	{
		getline(fichier, ligneActuelle);
		DecouperLigne();
	}
} //----- Fin de Méthode

string Decoupeur::DecouperDate() const
{
	return infos[1];	
}

string Decoupeur::DecouperRequete ( ) const
{
	return infos [2];
}

string Decoupeur::DecouperReferer ( ) const
{
	return infos [3];
}

//------------------------------------------------- Surcharge d'opérateurs

//-------------------------------------------- Constructeurs - destructeur

Decoupeur::Decoupeur(string nomFichier) : fichier(nomFichier), ligneActuelle("")
{
#ifdef MAP
    cout << "Appel au constructeur de <Decoupeur>" << endl;
#endif
} //----- Fin de Decoupeur


Decoupeur::~Decoupeur ( )
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au destructeur de <Decoupeur>" << endl;
#endif
    fichier.close();
} //----- Fin de ~Decoupeur


//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes protégées

void Decoupeur::DecouperLigne()
{
	char separateurs [] = { '[', ']', '"', '"', '"', '"', '"', '"' };
	int indexSep = 0;
	char tampon;
	string motTampon;
	bool enregistrer = false;
	int indexString = 0;
	string stringTampon = "";
	while(indexSep < 8)
	{
		tampon = ligneActuelle[indexString];
		if( tampon == separateurs[indexSep])
		{
			++indexSep;
			enregistrer = !enregistrer;
			if(enregistrer)
			{
				infos.push_back(motTampon);
				motTampon = "";
			}
		}
		else if(enregistrer)
		{
			motTampon += tampon;
		}
		++indexString;
	}
}