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
		do
		{
			getline(fichier, ligneActuelle);
			DecouperLigne();
		}while(fichier && !filtre->LigneEstConforme(infos));
	}
} //----- Fin de Méthode

string * Decoupeur::DecouperDate() const
{
	return new string(infos[0]);	
}

string * Decoupeur::DecouperRequete ( ) const
{
	return new string(infos[2]);
}

string * Decoupeur::DecouperReferer ( ) const
{
	return new string(infos[4]);
}

string * Decoupeur::DecouperNavigateur() const
{
	return new string(infos[5]);
}

bool Decoupeur::EstOK() const
{
	return fichier.good();
}

/*
bool Decoupeur::FiltresOK() const
{
	bool ligneConforme = true;
	for(list<Filtre>::const_iterator it = filtres.begin(); it != filtres.end(); it++)
	{
		if(it->LigneEstConforme(infos) == false)
		{
			ligneConforme = false;
			break;
		}
	}

	return ligneConforme;
}
*/
//------------------------------------------------- Surcharge d'opérateurs

//-------------------------------------------- Constructeurs - destructeur

Decoupeur::Decoupeur(string nomFichier, Filtre * critere) : fichier(nomFichier), ligneActuelle(""), filtre(critere)
{
#ifdef MAP
    cout << "Appel au constructeur de <Decoupeur>" << endl;
#endif
}


Decoupeur::~Decoupeur ( )
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au destructeur de <Decoupeur>" << endl;
#endif
    fichier.close();
    delete filtre;
} //----- Fin de ~Decoupeur


//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes protégées

void Decoupeur::DecouperLigne()
{
	char separateurs [] = { '[', ']', ' ', '"', ' ', ' ', '"', ' ', '"', '"', '"', '"' };
	int indexSep = 0;
	char tampon;
	string motTampon;
	bool enregistrer = false;
	int indexString = 0;
	string stringTampon = "";

	infos.clear();

	while(indexSep < 10)
	{
		tampon = ligneActuelle[indexString];
		if( tampon == separateurs[indexSep])
		{
			++indexSep;
			if(enregistrer)
			{
				infos.push_back(motTampon);
				motTampon = "";
			}
			enregistrer = !enregistrer;
		}
		else if(enregistrer)
		{
			motTampon += tampon;
		}
		++indexString;
	}
}
