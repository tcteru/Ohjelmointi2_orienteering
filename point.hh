/*
 * Kuvaus:
 * Tietorakenne, joka esittelee Point -luokan ja siihen
 * liittyvät funktiot.
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

#ifndef POINT_HH
#define POINT_HH

class Point
{
public:
    // Rakentaja ja purkaja
    Point(int x, int y, int height, char marker);
    ~Point();

    // Funktiot palauttamaan luokan vastaavan yksityisen arvon
    int getX() const;
    int getY() const;
    int getHeight() const;
    char getMarker() const;

private:
    int x_;
    int y_;
    int height_;
    char marker_;

};

#endif // POINT_HH
