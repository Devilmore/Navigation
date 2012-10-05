#include "EZStandard.h"
#include "EZKorrekturKreisPfadverfolgung.h"

#include "EZEreignis.h"
#include "EZFahrzeugbeschreibungskette.h"
#include "EZFahrzeugdatenkette.h"
#include "EZWegstueckSchlange.h"
#include "EZWinkelWrapper.h"
#include "EZPidRegler.h"

//////////////////////////////////////////////////////////////////////

namespace EZ
{

/////////////////////////////////////////////////////////////////////////////

REIMPLEMENTIERE_SCHNITTSTELLE_BEGINN(KorrekturKreisPfadverfolgung, Pfadverfolgung)
	IMPLEMENTIERT_SCHNITTSTELLE_BASISKLASSE(Pfadverfolgung)
REIMPLEMENTIERE_SCHNITTSTELLE_ENDE(KorrekturKreisPfadverfolgung, Pfadverfolgung)

/////////////////////////////////////////////////////////////////////////////

KorrekturKreisPfadverfolgung::KorrekturKreisPfadverfolgung()
: KreiseUndGeradenPfadverfolgung()
{
}

//////////////////////////////////////////////////////////////////////

KorrekturKreisPfadverfolgung::~KorrekturKreisPfadverfolgung()
{
}

//////////////////////////////////////////////////////////////////////

bool KorrekturKreisPfadverfolgung::verarbeiteStartEreignis(sEreignis::Zeiger ereignis)
{
	KreiseUndGeradenPfadverfolgung::verarbeiteStartEreignis(ereignis);
	
	m_vorraussichtRueckwaerts		=	0.5;
	m_vorraussichtVorwaerts			=	0.5;	
	ereignis->attributDouble("Vorraussicht Rueckwaerts", m_vorraussichtRueckwaerts);
	ereignis->attributDouble("Vorraussicht Vorwaerts", m_vorraussichtVorwaerts);
	ereignis->attributDouble("Lenkgeschwinigkeit", m_lenkgeschwindigkeit);
	ereignis->attributBool("treffpunktWandert", m_treffpunktWandert);
	m_kp	=	3.5;
	
	ereignis->attributDouble("Regelungsparameter Rueckwaerts P",	m_kp);

	sAbstrakteFahrzeugbeschreibung::Zeiger zugfahrzeug	= fahrzeugbeschreibungen()->beschreibung(0);
	sAbstrakteFahrzeugbeschreibung::Zeiger anhaenger	= fahrzeugbeschreibungen()->beschreibung(1);

	m_l1 = zugfahrzeug->ersterRadoffset()		-	zugfahrzeug->zweiterRadoffset();
	m_m1 = zugfahrzeug->zweiterRadoffset()		-	zugfahrzeug->hintererKupplungsoffset();
	m_l2 = anhaenger->vordererKupplungsoffset()	-	anhaenger->ersterRadoffset();

	m_festerSollEinknickwinkelVorhanden = false;
	ereignis->attributBool("festerSollEinknickwinkelVorhanden",m_festerSollEinknickwinkelVorhanden);
	m_festerSollEinknickwinkel = 0.0;
	ereignis->attributDouble("festerSollEinknickwinkel",m_festerSollEinknickwinkel);
	m_festerSollEinknickwinkel*=PI/180;
    return false;
}



bool KorrekturKreisPfadverfolgung::verfolgePfad()
{
	// Prüfen, ob Pfadverfolgung möglich ist
	if (wegSchlange()->leer() || !gestartet())
	{
		return false;
	}
	
	// Entferne bereits abgefahrene Wegstücke
	if (!entferneAbgefahreneWegstuecke(fahrzeugdaten(), fahrzeugbeschreibungen(), wegSchlange()))
	{
		// wenn das letzte Pfadstück entfernt wurde, stoppe die Pfadverfolgung und das Fahrzeug
		setzeGestartet(false);
		return false;
	}
	
	// Lies die Sollgeschwindigkeit und sende diese an den LKW
	double geschwindigkeit = wegSchlange()->erstesWegstueck()->rueckwaerts()	? - fabs(wegSchlange()->erstesWegstueck()->geschwindigkeit())
																				:	fabs(wegSchlange()->erstesWegstueck()->geschwindigkeit());
	sendeGeschwindigkeitEreignis(geschwindigkeit);
	
	// Berechne den Solllenkwinkel, beschränke den Solllenkwinkel und die Änderung des Solllenkwinkels und sende das Ergebnis an den LKW
	sendeLenkwinkelEreignis(beschraenkeSollLenkwinkel(berechneSollLenkwinkel(fahrzeugdaten(),fahrzeugbeschreibungen(),wegSchlange())));

	return true;
}

bool KorrekturKreisPfadverfolgung::entferneAbgefahreneWegstuecke( sFahrzeugdatenkette::Zeiger daten, sFahrzeugbeschreibungskette::Zeiger beschreibungen, sWegstueckSchlange::Zeiger wege , double* entfernteLaenge)
{
	if (entfernteLaenge!=NULL)
		(*entfernteLaenge)=0;
	while ((wege->erstesWegstueck()->sollPositionDefinitionswert(aktuellePosition(daten, beschreibungen, wege->erstesWegstueck()->rueckwaerts()))>wege->erstesWegstueck()->weglaenge()))
	{		
		if (entfernteLaenge!=NULL)
			(*entfernteLaenge)+=wege->erstesWegstueck()->weglaenge();
		wege->entferneWegstueckVorne();
		if (wege->leer())
			return false;
	}
	return true;
}

EZ::Punkt2D KorrekturKreisPfadverfolgung::berechneTreffpunkt( double vorraussicht, sWegstueckSchlange::Zeiger wege, double istAusrichtung,Punkt2D istPosition, bool treffpunktWandert )
{		
	double idealWert		= wege->erstesWegstueck()->sollPositionDefinitionswert(istPosition);
	if (!treffpunktWandert)
	{
		return wege->erstesWegstueck()->position(idealWert+vorraussicht);
	}
	
	double treffWert=idealWert+vorraussicht;
	bool istRueckwaerts = wege->erstesWegstueck()->rueckwaerts();

	int i=0;
	for (; (i<wege->anzahl())&&(treffWert>wege->laenge(i))&&(wege->rueckwaerts(i)==istRueckwaerts);i++)
	{
		treffWert-=wege->laenge(i);
	}

	if (i == wege->anzahl())
	{
		// Treffpunkt liegt hinter letztem Wegstück
		sWegstueck::Zeiger weg=wege->letztesWegstueck();
		return weg->position(weg->weglaenge()+treffWert);
	}
	else if (wege->rueckwaerts(i)!=istRueckwaerts)
	{
		// Richtungswechsel
		sWegstueck::Zeiger weg = wege->wegstueck(i-1); 
		// ja, das könnte man mit dem oberen Fall zusammenfassen
		return weg->position(weg->weglaenge()+treffWert);
		// so hier wäre es tangential
		// return weg->position(weg->weglaenge())+Punkt2D(cos(weg->ausrichtung(weg->weglaenge())),sin(weg->ausrichtung(weg->weglaenge())))*treffWert;
	}
	else
	{
		// Passendes Wegstück gefunden und kein Richtungswechsel
		return wege->wegstueck(i)->position(treffWert);
	}
}

Punkt2D KorrekturKreisPfadverfolgung::berechneKorrekturkreisMittelpunkt(Punkt2D treffPunkt, Punkt2D istPunkt, double istAusrichtung)
{
	return Punkt2D(sin(istAusrichtung),-cos(istAusrichtung))*berechneKorrekturkreisRadius(treffPunkt,istPunkt,istAusrichtung)+istPunkt;
}

double KorrekturKreisPfadverfolgung::berechneKorrekturkreisRadius(Punkt2D treffPunkt, Punkt2D istPunkt, double istAusrichtung)
{
	ASSERT(treffPunkt != istPunkt);
	double deltaX = istPunkt.x-treffPunkt.x;
	double deltaY = istPunkt.y-treffPunkt.y;
	// Berechne den Radius des Korrekturkreises (Formel ... in der Ausarbeitung)
	return (deltaY*cos(istAusrichtung)==deltaX*sin(istAusrichtung))	?	NaN() //Korrekturkreis ist eine Gerade
																	:	(deltaX*deltaX+deltaY*deltaY)/(2*(deltaY*cos(istAusrichtung)-deltaX*sin(istAusrichtung)));
}


double KorrekturKreisPfadverfolgung::berechneSollLenkwinkel( sFahrzeugdatenkette::Zeiger daten,sFahrzeugbeschreibungskette::Zeiger beschreibungen,sWegstueckSchlange::Zeiger wege )
{	
	// Bestimme die aktuelle Fahrtrichtung sowie die Position und die Ausrichtung des Bezugsgliedes
	// (also das Zugfahrzeug bei der Vorwärtsfahrt und sonst der Anhänger)
	bool	rueckwaerts		= wegSchlange()->erstesWegstueck()->rueckwaerts();
	double	istAusrichtung	= aktuelleAusrichtung(daten,rueckwaerts);
	Punkt2D	istPunkt		= aktuellePosition(daten, beschreibungen,rueckwaerts);


	// Berechne den Treffpunkt
	double vorraussicht = rueckwaerts	?	m_vorraussichtRueckwaerts
										:	m_vorraussichtVorwaerts;
	Punkt2D	treffPunkt		= berechneTreffpunkt(vorraussicht, wegSchlange(),istAusrichtung,istPunkt,m_treffpunktWandert);
	
	// Berechne die Radius des Korrekturkreises
	double	radius			= berechneKorrekturkreisRadius(treffPunkt,istPunkt,istAusrichtung);
  
	double sollLenkwinkel;
	if (rueckwaerts)
	{	
		// Berechne den Solleinknickwinkel (Formel ... in der Ausarbeitung)
				double sollEinknickwinkel = istNaN(radius)	? 0.0 // Korrekturkreis ist eine Gerade 
															: atan(m_l2/radius)+atan(m_m1/(radius*sqrt(1+(m_l2*m_l2-m_m1*m_m1)/(radius*radius))));
				// Falls ein fester Solleinknickwinkel (zu Testzwecken) vorgegeben wurde) diesen verwenden
				// sonst den berechneten Solleinknickwinkel verwenden und diesen Beschränken (muss im Intervall
				//	[-kritischerEinknickwinkel,+kritischerEinknickwinkel] liegen
				if (m_festerSollEinknickwinkelVorhanden)
					sollEinknickwinkel = m_festerSollEinknickwinkel;
				else
					sollEinknickwinkel = std::max(std::min(kritischerEinknickwinkel(),sollEinknickwinkel),-kritischerEinknickwinkel());
				
				// Berechne den Lenkwinkel, der dem momentan anliegenden Einknickwinkel entspricht (Formel ... in der Ausarbeitung)
				  double stabilerLenkwinkel = -atan(m_l1*sin(daten->einknickwinkel(0))/(m_l2+m_m1*cos(daten->einknickwinkel(0))));

				// Berechne den resultierenden Solllenkwinkel (Formel ... in der Ausarbeitung)
				    sollLenkwinkel = m_kp*(sollEinknickwinkel-daten->einknickwinkel(0))+stabilerLenkwinkel;
			
		
	}
	else
	{
		// Berechne den Solllenkwinkel für die Vorwärtsfahrt (Formel ... in der Ausarbeitung)
		sollLenkwinkel =  istNaN(radius)	?	0.0					// Korrekturkreis ist eine Gerade
											:	atan(-m_l1/radius);	// sonst
	}

	return sollLenkwinkel;
}

double KorrekturKreisPfadverfolgung::beschraenkeSollLenkwinkel( double sollLenkwinkel )
{
	

	// Bestimme den maximalen Lenkwinkel des Fahrzeuges
	double maximalerLenkwinkel = fahrzeugbeschreibungen()->beschreibung(0)->ersterLenkwinkel();	
	
	// Bestimme den aktuellen Lenkwinkel des Fahrzeuges
	double istLenkwinkel = fahrzeugdaten()->daten(0)->ersterLenkwinkel();

	// Bestimme die maximale Lenkwinkelaenderung des Fahrzeuges
	double maximaleLenkwinkelaenderung = m_lenkgeschwindigkeit*PI/180.0; // 20.0 Grad in 0.08 Sekunden; 

	// der Betrag des Solllenkwinkels muss kleiner sein als der maximale Lenkwinkel des Fahrzeuges
	sollLenkwinkel = std::max(-maximalerLenkwinkel,std::min(maximalerLenkwinkel,sollLenkwinkel));
	
	// der Betrag der Lenkwinkeländerung muss kleiner sein als die maximale Lenkwinkeländerung des Fahrzeuges
	double beschraenkteLenkwinkelAenderung = min(maximaleLenkwinkelaenderung,max(-maximaleLenkwinkelaenderung,sollLenkwinkel - istLenkwinkel));
	
	// gib den beschränkten Lenkwinkel zurück
	return istLenkwinkel + beschraenkteLenkwinkelAenderung;
}

//////////////////////////////////////////////////////////////////////

};
