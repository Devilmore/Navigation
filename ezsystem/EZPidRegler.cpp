#include "EZStandard.h"
#include "EZPidRegler.h"

namespace EZ {

IMPLEMENTIERE_SCHNITTSTELLE_BEGINN(PidRegler)
	IMPLEMENTIERT_SCHNITTSTELLE(sPidRegler)
IMPLEMENTIERE_SCHNITTSTELLE_ENDE(PidRegler)

PidRegler::PidRegler(double p/*=0.0*/, double i/*=0.0*/, double d/*=0.0*/)
	:	m_p			(p),
		m_i			(i),
		m_d			(d),
		m_summe		(0.0),
		m_alterWert (0.0)
{
	KONSTRUIERE_SCHNITTSTELLE;
}

PidRegler::~PidRegler()
{

}

double PidRegler::berechneAusgabe( double eingabeP, double eingabeI )
{
	double ausgabe(0.0);
	ausgabe += eingabeP * m_p;
	m_summe += eingabeI;
	m_summe *= 0.95;
	//meldeInfo("EingabeP: "+std::to_string(eingabeP));
	//meldeInfo("EingabeI: "+std::to_string(eingabeI));
	ausgabe += m_summe * m_i;
	ausgabe += (m_alterWert-eingabeP) * m_d;
	m_alterWert = eingabeP;
	return ausgabe;
}

void PidRegler::reset()
{
	m_summe = 0.0;
}
};

