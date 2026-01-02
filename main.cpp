/* Orienteering
 *
 * Kuvaus:
 * Ohjelma lukee suunnistus-reittejä syötetiedostosta, jonka rivit
 * ovat muotoa:
 * Ensimmäisellä rivillä kerrotaan kartan (koordinaatiston) koko:
 * leveys ja korkeus (positiivisina) kokonaislukuina.
 * Yllä olevassa esimerkissä leveys on 15,
 * joten koordinaatiston x-koordinaatit voivat olla väliltä [1..15].
 * Vastaavasti jos korkeudeksi on annettu 10,
 * koordinaatiston y-koordinaatit voivat olla väliltä [1..10].
 * Sen jälkeisillä riveillä luetellaan haluttu määrä rasteja.
 * Luettelo loppuu riviin, jolla lukee pelkästään sana ROUTES.
 * Rasteista kerrotaan rastin nimi, sen x- ja y-koordinaatit,
 * maaston korkeus kyseisen rastin kohdalla metreinä sekä rastin tunnus
 * (yhden merkin mittainen lyhenne).
 * Rivin ROUTES jälkeen tiedostossa luetellaan reitit, kukin omalla rivillään.
 * Kustakin reitistä kerrotaan nimi sekä niiden rastien nimet,
 * joita pitkin reitti kulkee.
 * Reitillä voi olla rasteja mikä tahansa (äärellinen) määrä.
 * Reitillä voi olla vain sellaisia rasteja, jotka on esitelty tiedoston alkuosassa.
 * Reitit ovat yksisuuntaisia.
 * Ohjelman toiminnan voi lopettaa komennolla quit.
 *
 * Ohjelman kirjoittaja (1)
 * Nimi: Teemu Ruonakoski
 * Opiskelijanumero: 152116224
 * Käyttäjätunnus: tcteru ( Git-repositorion hakemistonimi )
 * E-Mail: teemu.ruonakoski@tuni.fi
 *
 * Ohjelman kirjoittaja (2)
 * Nimi: Joose Haippo
 * Opiskelijanumero: K443432
 * Käyttäjätunnus: rvjoha ( Git-repositorion hakemistonimi )
 * E-Mail: joose.haippo@tuni.fi
 *
 * Huomioita ohjelmasta ja sen toteutuksesta (jos sellaisia on):
 *
 * */
//Pohjustuksena projektille käytetään viikkoharkoissa käytyä esimerkkiä,
//johon tehty pieniä muokkauksia.

#include "orienteeringmap.hh"
#include "parser.hh"
#include "cli.hh"
#include <iostream>

int main()
{
    std::shared_ptr<OrienteeringMap> routes(new OrienteeringMap);
    std::cout << "Input> ";
    std::string input;
    getline(std::cin, input);
    if( not read_input_from_file(input, routes) )
    {
        return EXIT_FAILURE;
    }
    Cli cli(routes);
    while( cli.exec_prompt() ){ }
    return EXIT_SUCCESS;
}
