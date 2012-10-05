#ifndef EZ_PFAD_H
#define EZ_PFAD_H

///////////////////////////////////////////////////////////////////////////

#include "EZsPidRegler.h"

///////////////////////////////////////////////////////////////////////////

namespace EZ 
{

///////////////////////////////////////////////////////////////////////////
/// Implementierung von PidRegler
/// @see sPidRegler
//-------------------------------------------------------------------

class PidRegler: VERWENDE_SCHNITTSTELLE(sPidRegler)
{
    SCHNITTSTELLENIMPLEMENTATION(PidRegler);

protected:
	// die Gewichtung des Proportionalanteils
	double m_p;
	// die Gewichtung des Integralanteils
	double m_i;
	// die Gewichtung des Differentialanteils 
	double m_d;
	// Summe der Eingabe-Werte
	double m_summe;
	// letzter Eingabewert
	double m_alterWert;

public:
    /////////////////////////////////////////////////////////////////////
    /// Konstruktor
    //--------------------------------------------------------------------
	PidRegler(double p=0.0, double i=0.0, double d=0.0);
	
    //////////////////////////////////////////////////////////////////////
    ///	Destruktor
    //--------------------------------------------------------------------
    virtual ~PidRegler();

	double berechneAusgabe(double eingabeP, double eingabeI=0);
	virtual void reset();

};

};

#endif // EZ_PFAD_H
