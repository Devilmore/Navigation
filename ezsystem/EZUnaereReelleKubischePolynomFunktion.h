#ifndef UNAEREREELEKUBISCHEPOLYNOMFUNKTION_H
#define UNAEREREELEKUBISCHEPOLYNOMFUNKTION_H

/////////////////////////////////////////////////////////////////////////////

#include "EZsUnaereReelleFunktion.h"
#include <vector>
#include "EZStandard.h"
#include "EZPunkt3D.h"


namespace EZ
{

/////////////////////////////////////////////////////////////////////////////

class UnaereReelleKubischePolynomFunktion : VERWENDE_SCHNITTSTELLE(sUnaereReelleFunktion)
{
    SCHNITTSTELLENIMPLEMENTATION(UnaereReelleKubischePolynomFunktion);

protected:
	// Kooeffizienten des Polynoms
	std::vector<double> m_koeffizienten;

	// Grenzen des Definitionsbereichs
	double m_beginn, m_ende;

public:
    //////////////////////////////////////////////////////////////////////
    /// Liefert den kleinsten Wert aus dem Definitionsbereich für den
    /// diese Funktion definiert ist.
    /// @result Der kleinste definierte Argumentwert.
    //--------------------------------------------------------------------
    virtual double definitionsminimum();

    //////////////////////////////////////////////////////////////////////
    /// Liefert den größten Wert aus dem Definitionsbereich für den
    /// diese Funktion definiert ist.
    /// @result Der größte definierte Argumentwert.
    //--------------------------------------------------------------------
    virtual double definitionsmaximum();

    //////////////////////////////////////////////////////////////////////
    /// Berechnet zum übergebenen Wert den Funktionswert.
    /// Wird ein Wert außerhalb des Definitionsbereichs übergeben
    /// ist das Verhalten unspezifiziert.
    /// @param  - Definitionswert
    /// @result Zugehöriger Funktionswert.
    //--------------------------------------------------------------------
    virtual double operator()(double);

	//////////////////////////////////////////////////////////////////////
    /// Konstruktor
	/// @param  a:		a(x-beginn)^3 +
	/// @param  b:		b(x-beginn)^2 +
	/// @param  c:		c(x-beginn) +
	/// @param  d:		d
	/// @param  beginn: Untere Grenze des Definitionsbereiches
	/// @param  ende:   Obere Grenze des Definitionsbereiches
    //--------------------------------------------------------------------
    UnaereReelleKubischePolynomFunktion(double a, double b, double c, double d, 
										double beginn, double ende);

    //////////////////////////////////////////////////////////////////////
    /// Destruktor
    //--------------------------------------------------------------------
    virtual ~UnaereReelleKubischePolynomFunktion();

	virtual Punkt3D bestimmeAbleitungen(double definitionswert);

};

};
/////////////////////////////////////////////////////////////////////////////

#endif
