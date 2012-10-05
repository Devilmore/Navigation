#include "EZUnaereReelleSplineFunktion.h"
#include "EZMatrix.h"

//////////////////////////////////////////////////////////////////////

#include "EZStandard.h"


namespace EZ
{
//////////////////////////////////////////////////////////////////////

REIMPLEMENTIERE_SCHNITTSTELLE_BEGINN(UnaereReelleSplineFunktion, DiskreteUnaereReelleFunktion)
    IMPLEMENTIERT_SCHNITTSTELLE_BASISKLASSE(DiskreteUnaereReelleFunktion)
REIMPLEMENTIERE_SCHNITTSTELLE_ENDE(UnaereReelleSplineFunktion, DiskreteUnaereReelleFunktion)

//////////////////////////////////////////////////////////////////////

void UnaereReelleSplineFunktion::berechne_a()
{
	for (unsigned short int i = 1;i<m_b.size();i++)
		m_a.push_back ( (m_b[i] - m_b[i-1])/(3*(m_x[i]-m_x[i-1])) ); // (III)
}

void UnaereReelleSplineFunktion::berechne_b()
{
	Matrix m(m_x.size()-2,m_x.size()-2);
	Vektor v(m_x.size()-2);

	for (unsigned short int zeile = 1;zeile<m_x.size()-1;zeile++)
	{
		v[zeile-1] = 3*((m_d[zeile+1]-m_d[zeile])/(m_x[zeile+1]-m_x[zeile]) - (m_d[zeile]-m_d[zeile-1])/(m_x[zeile]-m_x[zeile-1])); // (VI)
	}
	
	// Initialisiere Koeffizientenmatrix 
	for (unsigned short int zeile = 1;zeile<m_x.size()-1;zeile++)
		for (unsigned short int spalte = 1;spalte<m_x.size()-1;spalte++)
		{
			if (zeile==spalte)
				m[zeile-1][spalte-1] = 2*(m_x[zeile+1]-m_x[zeile-1]);
			else if (spalte==zeile+1)
			{
				m[zeile-1][spalte-1] = m_x[spalte]-m_x[zeile];
			}
			else if (spalte==zeile-1)
				m[zeile-1][spalte-1] = m_x[zeile]-m_x[spalte];
			// else m[zeile-1][spalte-1] = 0.0 (ist schon so initialisiert)
		}
	Vektor loesung = m.loeseLinearesGleichungssystem(v);
		for (unsigned short int i = 0; i < m_x.size(); i++)
			if ((i==0) || (i==m_x.size()-1))
				m_b.push_back(0.0);
			else m_b.push_back(loesung[i-1]);// hier ergebnis eintragen
}

void UnaereReelleSplineFunktion::berechne_c()
{
	for (unsigned short int i = 1;i<m_b.size();i++)
		m_c.push_back ((m_d[i]-m_d[i-1])/(m_x[i]-m_x[i-1]) - (m_b[i]-m_b[i-1])*(m_x[i]-m_x[i-1])/3 - m_b[i-1]*(m_x[i]-m_x[i-1])); // (V)
}

void UnaereReelleSplineFunktion::berechne_d()
{
	for (unsigned short int i = 0;i<m_wertepaare.size();i++)
		m_d.push_back(m_wertepaare[i].second);
}

void UnaereReelleSplineFunktion::berechne_x()
{
	for (unsigned short int i = 0;i<m_wertepaare.size();i++)
		m_x.push_back(m_wertepaare[i].first);
}

void UnaereReelleSplineFunktion::berechneKoeffizienten()
{
	m_x.clear();
	m_d.clear();
	m_c.clear();
	m_b.clear();
	m_a.clear();

	berechne_x();
	berechne_d();
	berechne_b();
	berechne_a();
	berechne_c();
}


UnaereReelleSplineFunktion::UnaereReelleSplineFunktion()
	: DiskreteUnaereReelleFunktion()
{

}

//////////////////////////////////////////////////////////////////////

bool UnaereReelleSplineFunktion::wertHinzufuegen(double definitionswert, double funktionswert)
{
	DiskreteUnaereReelleFunktion::wertHinzufuegen(definitionswert,funktionswert);
	if (gibAnzahlWerte()>=3)
	{
		berechneKoeffizienten();
		m_polynomListe.clear();
		for (unsigned short int i = 0; i< m_a.size();i++)
		{
			UnaereReelleKubischePolynomFunktion::Zeiger polynom = new UnaereReelleKubischePolynomFunktion(m_a[i],m_b[i],m_c[i],m_d[i],m_x[i],m_x[i+1]);
			polynom->referenzEntfernen();
			m_polynomListe.push_back(polynom);
			//m_aggregierteFunktion->segmentHinzufuegen(polynom,m_x[i],m_x[i+1]);
		}
		return true;
	}
	return false;
}

double UnaereReelleSplineFunktion::operator()(double definitionswert)
{
	if (m_polynomListe.empty())
		return NaN();
	return (*findePolynom(definitionswert))(definitionswert);
}

UnaereReelleSplineFunktion::~UnaereReelleSplineFunktion()
{

}

UnaereReelleKubischePolynomFunktion::Zeiger UnaereReelleSplineFunktion::findePolynom( double d )
{
	if (m_polynomListe.empty())
		return NULL;
	for (PolynomListe::iterator iter = m_polynomListe.begin();iter!=m_polynomListe.end();iter++)
	{
		if (d<(*iter)->definitionsminimum())
			return *iter;
	}
	return m_polynomListe.back();
}

EZ::Punkt3D UnaereReelleSplineFunktion::bestimmeAbleitungen( double d)
{
	if (m_polynomListe.empty())
		return Punkt3D(NaN(),NaN(),NaN());
	return findePolynom(d)->bestimmeAbleitungen(d);
}
//////////////////////////////////////////////////////////////////////
}