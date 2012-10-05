#include <cmath>
#include "EZStandard.h"
#include "EZGeometrie.h"
#include "EZPfadverfolgung.h"
#include "EZEreignis.h"
#include "EZAbstrakteFahrzeugbeschreibung.h"
#include "EZAbstrakteFahrzeugdaten.h"
#include "EZFahrzeugbeschreibungskette.h"
#include "EZFahrzeugdatenkette.h"
#include "EZAbstrakteFahrzeugbewegungKette.h"
#include <utility>
#include <algorithm>
#include <vector>
#include "EZKreiswegstueck.h"
#include "EZGeradenwegstueck.h"
#include "EZStabileFahrt.h"
#include "EZErweiterteStabileFahrt.h"

#include "EZWegstueckSchlange.h"
#include "EZWinkelWrapper.h"

//////////////////////////////////////////////////////////////////////

namespace EZ 
{

/////////////////////////////////////////////////////////////////////////////

IMPLEMENTIERE_SCHNITTSTELLE_BEGINN(Pfadverfolgung)
    IMPLEMENTIERT_SCHNITTSTELLE(sEreignisempfaenger)
IMPLEMENTIERE_SCHNITTSTELLE_ENDE(Pfadverfolgung)

/////////////////////////////////////////////////////////////////////////////

Pfadverfolgung::Pfadverfolgung()
: m_beendet				(true)
{
    KONSTRUIERE_SCHNITTSTELLE;
}

//////////////////////////////////////////////////////////////////////

Pfadverfolgung::~Pfadverfolgung()
{
    if (m_ereignisverteiler != NULL)
    {
        // abmelden
		m_ereignisverteiler->deregistriereEmpfaenger(this);

		// Interessenten über Abschalten informieren
        if (!m_beendet)
        {
            sEreignis::Zeiger ereignis  = new Ereignis(s_ereignisAusModus);
            ereignis->referenzEntfernen();
            ereignis->setzeAttributString("wert", "beendet");
            ereignis->setzeAttributString("alt", m_modus);
            m_ereignisverteiler->verarbeiteEreignis(ereignis);
        }
    }
}

//////////////////////////////////////////////////////////////////////

bool Pfadverfolgung::initialisiere( sUhr::Zeiger uhr, std::string ereignistyp, sEreignisverteiler::Zeiger ereignisverteiler)
{
	meldeInfo("Pfadverfolgung::initialisiere()");
    ASSERT(uhr != NULL);
    ASSERT(ereignisverteiler != NULL);

    if (!m_beendet)
        return false;

    if (uhr == NULL)
        return false;

    if (ereignisverteiler == NULL)
        return false;


    // Attribute setzen.

    m_uhr   = uhr;

    s_ereignisEinPeriode                = ereignistyp + "/ein/periode";
    s_ereignisEinEreignistypen          = ereignistyp + "/ein/ereignistypen";
    s_ereignisEinModus                  = ereignistyp + "/ein/modus";
    s_ereignisEinPing                   = ereignistyp + "/ein/ping";
	s_ereignisEinStart                  = ereignistyp + "/ein/verfolgungstart";
	s_ereignisEinStop                   = ereignistyp + "/ein/verfolgungstop";
    s_ereignisEinFahrzeugbeschreibungen = "daten/fahrzeugbeschreibungen";
    s_ereignisEinFahrzeugdaten          = "daten/fahrzeugdaten";
	s_ereignisEinPfadHinzufuegen  		= ereignistyp + "/ein/wegHinzufuegen";

    s_ereignisAusModus                  = ereignistyp + "/aus/modus";
    s_ereignisAusGeschwindigkeit 		= "verwaltung/ein/geschwindigkeit";
    s_ereignisAusLenkwinkel		 		= "verwaltung/ein/lenkwinkel";

    m_ereignisverteiler         = ereignisverteiler;


    // Ereignisse registrieren.

    if (   !m_ereignisverteiler->registriereEmpfaenger(this, s_ereignisEinPeriode)
        || !m_ereignisverteiler->registriereEmpfaenger(this, s_ereignisEinEreignistypen)
        || !m_ereignisverteiler->registriereEmpfaenger(this, s_ereignisEinModus)
        || !m_ereignisverteiler->registriereEmpfaenger(this, s_ereignisEinPing)
        || !m_ereignisverteiler->registriereEmpfaenger(this, s_ereignisEinFahrzeugbeschreibungen)
		|| !m_ereignisverteiler->registriereEmpfaenger(this, s_ereignisEinFahrzeugdaten)
		|| !m_ereignisverteiler->registriereEmpfaenger(this, s_ereignisEinStart)
		|| !m_ereignisverteiler->registriereEmpfaenger(this, s_ereignisEinStop)
		|| !m_ereignisverteiler->registriereEmpfaenger(this, s_ereignisEinPfadHinzufuegen))
    {
        m_ereignisverteiler->deregistriereEmpfaenger(this);
        return false;
    }

    m_beendet   = false;

    // Interessenten über Start informieren.
    {
        sEreignis::Zeiger ereignis  = new Ereignis(s_ereignisAusModus);
        ereignis->referenzEntfernen();
        ereignis->setzeAttributString("wert", "wartend");
        ereignis->setzeAttributString("alt", "beendet");
        m_ereignisverteiler->verarbeiteEreignis(ereignis);
    }

    return true;
}

//////////////////////////////////////////////////////////////////////

bool Pfadverfolgung::beendet()
{
    return m_beendet;
}

//////////////////////////////////////////////////////////////////////

bool Pfadverfolgung::verarbeiteEreignis(sEreignis::Zeiger ereignis)
{
    if (m_beendet)
        return false;

    std::string ereignistyp = ereignis->typ();
	if (m_modus == "aktiv")
	{
		if (ereignistyp == s_ereignisEinPeriode)
		{
			if ((m_fahrzeugdaten!= NULL) && (m_fahrzeugbeschreibungen!=NULL))
				verfolgePfad();
			return false;
		}
		//--------------------------------------------------------------------
		if (ereignistyp == s_ereignisEinFahrzeugdaten)
		{
			Schnittstelle::Zeiger               objekt;
			sFahrzeugdatenkette::Zeiger         daten;
			double                              zeit;
			if (   !ereignis->attributObjekt("wert", objekt)
				|| !daten.holeSchnittstelle(objekt)
				|| !ereignis->attributDouble("zeit", zeit))
			{
				EZ::meldeWarnung("Pfadverfolgung::verarbeiteEreignis: Fahrzeugdaten unvollständig");
				return false;
			}

			m_fahrzeugdaten = daten;
			if ((m_fahrzeugbeschreibungen==NULL)&&(m_fahrzeugdaten!=NULL))
			{
				m_fahrzeugbeschreibungen = m_fahrzeugdaten->beschreibungskette();
				if (m_fahrzeugbeschreibungen != NULL)
					aktualisiereKritischenEinknickwinkel();
			}
			return false;
		}
	}	//--------------------------------------------------------------------
    if (ereignistyp == s_ereignisEinFahrzeugbeschreibungen)
	{
		Schnittstelle::Zeiger               objekt;
		sFahrzeugbeschreibungskette::Zeiger beschreibungen;
		if (   !ereignis->attributObjekt("wert", objekt)
			|| !beschreibungen.holeSchnittstelle(objekt))
		{
			EZ::meldeWarnung("Pfadverfolgung::verarbeiteEreignis: Fahrzeugbeschreibungen unvollständig");
			beschreibungen  = NULL;
		}
		m_fahrzeugbeschreibungen    = beschreibungen;
		if (m_fahrzeugbeschreibungen!=NULL)
			aktualisiereKritischenEinknickwinkel();
		return false;
	}

    //--------------------------------------------------------------------
    if (ereignistyp == s_ereignisEinPing)
    {
		double      zeit;
		std::string antworttyp;
		if (   !ereignis->attributDouble("zeit", zeit)
			|| !ereignis->attributString("antworttyp", antworttyp))
		{
			EZ::meldeWarnung("Pfadverfolgung::verarbeiteEreignis: Ereignis enthält zu wenig Daten");
			return false;
		}

		Ereignis::Zeiger    antwortereignis    = new Ereignis(antworttyp);
		antwortereignis->referenzEntfernen();
		antwortereignis->setzeAttributDouble("zeit", zeit);
		antwortereignis->setzeAttributString("quelle", "pfadverfolgung");
		m_ereignisverteiler->verarbeiteEreignis(antwortereignis);

		return false;
	}
    //--------------------------------------------------------------------
    if (ereignistyp == s_ereignisEinEreignistypen)
		return verarbeiteEreignistypenEreignis(ereignis);
    //--------------------------------------------------------------------
    if (ereignistyp == s_ereignisEinModus)
    	return verarbeiteModusEreignis(ereignis);
	//--------------------------------------------------------------------
	if (ereignistyp == s_ereignisEinPfadHinzufuegen)
		return verarbeitePfadHinzufuegenEreignis(ereignis);
	//--------------------------------------------------------------------
	if (ereignistyp == s_ereignisEinStart)
		return verarbeiteStartEreignis(ereignis);
	//--------------------------------------------------------------------
	if (ereignistyp == s_ereignisEinStop)
		return verarbeiteStopEreignis(ereignis);
	//--------------------------------------------------------------------
    return false;
}

void Pfadverfolgung::sendeLenkwinkelEreignis( double winkel )
{
    sEreignis::Zeiger lenkwinkelEreignis  = new Ereignis(s_ereignisAusLenkwinkel);
    lenkwinkelEreignis->referenzEntfernen();
    lenkwinkelEreignis->setzeAttributDouble("wert", winkel);
    lenkwinkelEreignis->setzeAttributDouble("zeit", EZ::zeit());
    m_ereignisverteiler->verarbeiteEreignis(lenkwinkelEreignis);
	meldeInfo("Se envía  lenkwinkel a: " + std::to_string(winkel));
}

bool Pfadverfolgung::verarbeiteModusEreignis(sEreignis::Zeiger ereignis)
{ 
	std::string modus;
    if (!ereignis->attributString("wert", modus))
    {
        EZ::meldeWarnung("Pfadverfolgung::verarbeiteEreignis: Modus unvollständig");
        return false;
    }

    if (   modus != "aktiv"
		&& modus != "wartend"
        && modus != "beendet")
    {
        EZ::meldeWarnung("Pfadverfolgung::verarbeiteEreignis: Modus unbekannt");
        return false;
    }

	if (modus == "wartend")
	{
		verarbeiteModusWartend();
	}

	if (modus == "beendet")
    {
        m_beendet   = true;
        m_ereignisverteiler->deregistriereEmpfaenger(this);
    }

    // Informiere Interessenten
	{
        sEreignis::Zeiger ereignis  = new Ereignis(s_ereignisAusModus);
        ereignis->referenzEntfernen();
        ereignis->setzeAttributString("wert", modus);
        ereignis->setzeAttributString("alt", m_modus);
        m_ereignisverteiler->verarbeiteEreignis(ereignis);
 	 	meldeInfo("Wechsele Modus von "+m_modus+" nach "+modus);
      
	}

	m_modus = modus;

    return false;
}

bool Pfadverfolgung::verarbeiteEreignistypenEreignis(sEreignis::Zeiger ereignis)
{
		std::string typ;
        if (ereignis->attributString("/ein/periode", typ))
        {
            m_ereignisverteiler->deregistriereEmpfaenger(this, s_ereignisEinPeriode);
            s_ereignisEinPeriode = typ;
            m_ereignisverteiler->registriereEmpfaenger(this, typ);
        }

        if (ereignis->attributString("ein/fahrzeugbeschreibungen", typ))
        {
            m_ereignisverteiler->deregistriereEmpfaenger(this, s_ereignisEinFahrzeugbeschreibungen);
            s_ereignisEinFahrzeugbeschreibungen = typ;
            m_ereignisverteiler->registriereEmpfaenger(this, typ);
        }
        if (ereignis->attributString("ein/fahrzeugdaten", typ))
        {
            m_ereignisverteiler->deregistriereEmpfaenger(this, s_ereignisEinFahrzeugdaten);
            s_ereignisEinFahrzeugdaten = typ;
            m_ereignisverteiler->registriereEmpfaenger(this, typ);
        }


        if (ereignis->attributString("aus/lenkwinkel", typ))
        {
            s_ereignisAusLenkwinkel = typ;
        }
        if (ereignis->attributString("aus/modus", typ))
        {
            s_ereignisAusModus = typ;
        }

        if (ereignis->attributString("aus/geschwindigkeit", typ))
        {
            s_ereignisAusGeschwindigkeit = typ;
        }

		if (ereignis->attributString("/ein/verfolgungstop", typ))
		{
			ereignisverteiler()->deregistriereEmpfaenger(this, s_ereignisEinStop);
			s_ereignisEinStop = typ;
			ereignisverteiler()->registriereEmpfaenger(this, typ);
		}

		if (ereignis->attributString("/ein/verfolgungstart", typ))
		{
			ereignisverteiler()->deregistriereEmpfaenger(this, s_ereignisEinStart);
			s_ereignisEinStart = typ;
			ereignisverteiler()->registriereEmpfaenger(this, typ);
		}

		if (ereignis->attributString("/ein/wegHinzufuegen", typ))
		{
			ereignisverteiler()->deregistriereEmpfaenger(this, s_ereignisEinPfadHinzufuegen);
			s_ereignisEinPfadHinzufuegen = typ;
			ereignisverteiler()->registriereEmpfaenger(this, typ);
		}

        std::string antworttyp;
        if (ereignis->attributString("antworttyp", antworttyp))
        {
            Ereignis::Zeiger    ereignis    = new Ereignis(antworttyp);
            ereignis->referenzEntfernen();
            ereignis->setzeAttributString("quelle", "pfadverfolgung");
        	ereignis->setzeAttributDouble("zeit", m_uhr->zeit());
            m_ereignisverteiler->verarbeiteEreignis(ereignis);
        }
		return true;
}

void Pfadverfolgung::sendeGeschwindigkeitEreignis( double geschwindigkeit )
{
	sEreignis::Zeiger geschwindigkeitereignis  = new Ereignis(s_ereignisAusGeschwindigkeit);
	geschwindigkeitereignis->referenzEntfernen();
	geschwindigkeitereignis->setzeAttributDouble("wert", geschwindigkeit);
	geschwindigkeitereignis->setzeAttributDouble("zeit", EZ::zeit());
	m_ereignisverteiler->verarbeiteEreignis(geschwindigkeitereignis);
}

EZ::Punkt2D Pfadverfolgung::aktuellePosition( sFahrzeugdatenkette::Zeiger daten, sFahrzeugbeschreibungskette::Zeiger beschreibungen,  bool rueckwaerts )
{
	Punkt2D ausrichtungVektor = WinkelWrapper(aktuelleAusrichtung(daten,rueckwaerts)).einheitsvektor();
	if (rueckwaerts)
	{
		return daten->daten(1)->position() + ausrichtungVektor*beschreibungen->beschreibung(1)->ersterRadoffset();
	}
	else
	{
		return daten->daten(0)->position() + ausrichtungVektor*beschreibungen->beschreibung(0)->zweiterRadoffset();
	}
}

double Pfadverfolgung::aktuelleAusrichtung( sFahrzeugdatenkette::Zeiger daten, bool rueckwaerts )
{
	return rueckwaerts ?
				daten->daten(1)->ausrichtung()
			:	daten->daten(0)->ausrichtung();
}

void Pfadverfolgung::aktualisiereKritischenEinknickwinkel()
{										
	ErweiterteStabileFahrt::Zeiger stabileFahrt = new ErweiterteStabileFahrt(m_fahrzeugbeschreibungen);
	stabileFahrt->referenzEntfernen();
	double maximalerLenkwinkel = m_fahrzeugbeschreibungen->beschreibung(0)->ersterLenkwinkel();
	stabileFahrt->setzeLenkwinkel(maximalerLenkwinkel, 0);
	
	m_kritischerEinknickwinkel =  fabs(stabileFahrt->einknickwinkel()); // einknickwinkel() mit keine Parameter

	// Falls m_kiritischerEinknicwkwinkel == nan, dann m_kritischerEinknickwinkel = gamma turn wert
	meldeInfo("m_kristischerEinknickwinkel = " + std::to_string(m_kritischerEinknickwinkel, 6));
	if(istNaN(m_kritischerEinknickwinkel))
	{meldeInfo("dentrod de einknickwinkel es nan");
    double m0 = m_fahrzeugbeschreibungen->beschreibung(0)->zweiterRadoffset() - m_fahrzeugbeschreibungen->beschreibung(0)->hintererKupplungsoffset();
    double l1 = m_fahrzeugbeschreibungen->beschreibung(1)->vordererKupplungsoffset() - m_fahrzeugbeschreibungen->beschreibung(1)->ersterRadoffset();
    double gammaturn = PI - acos(m0/l1);
	 m_kritischerEinknickwinkel = gammaturn;
	}	

	 m_kritischerEinknickwinkel = m_kritischerEinknickwinkel -3.0 * PI / 180; // Wir wollen ein kleiner kritischer einknickwinel als gammaturn
     

}

bool Pfadverfolgung::verarbeiteStartEreignis( sEreignis::Zeiger ereignis )
{
	m_gestartet = true;
	return false;
}

bool Pfadverfolgung::verarbeiteStopEreignis( sEreignis::Zeiger ereignis )
{
	sendeGeschwindigkeitEreignis(0.0);
	m_gestartet = false;
	return false;
}

void Pfadverfolgung::verarbeiteModusWartend()
{
	sendeGeschwindigkeitEreignis(0.0);
	m_gestartet = false;
}

void Pfadverfolgung::setzeGestartet( bool val )
{
	m_gestartet = val;
	if (!m_gestartet)
		sendeGeschwindigkeitEreignis(0.0);
}
//////////////////////////////////////////////////////////////////////

};
