/* Point
 *
 * Kuvaus:
 * Tämä lähdekooditiedosto käsittelee kaikki Point -luokan komennot
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
*/

#include "point.hh"

Point::Point(int x, int y, int height, char marker)
    : x_(x), y_(y), height_(height), marker_(marker)
{

}

Point::~Point()
{

}

int Point::getX() const
{
    return x_;
}

int Point::getY() const
{
    return y_;
}

int Point::getHeight() const
{
    return height_;
}

char Point::getMarker() const
{
    return marker_;
}
