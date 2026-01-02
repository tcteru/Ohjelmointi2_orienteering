/* Orienteeringmap
 *
 * Kuvaus:
 * Tämä lähdekooditiedosto käsittelee kaikki orienteeringmap
 * -luokan komennot.
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

#include "orienteeringmap.hh"

OrienteeringMap::OrienteeringMap() :
    width_(0), height_(0)
{

}

OrienteeringMap::~OrienteeringMap()
{

}

void OrienteeringMap::set_map_size(int width, int height)
{
    width_ = width;
    height_ = height;
}

void OrienteeringMap::add_point(string name, int x, int y, int height, char marker)
{
    // Tarkistetaan onko piste kartalla
    if (x < 0 || x > width_ || y < 0 || y > height_)
    {
        cout << "Error: point coordinates are not on the map" << endl;
        return;
    }

    // Tarkistetaan onko piste jo olemassa
    if ( all_points_.find(name) != all_points_.end())
    {
        cout << "Error: point already exists on the map" << endl;
        return;
    }

    all_points_[name] = make_shared<Point>(x, y, height, marker);
}

bool OrienteeringMap::connect_route(string from, string to, string route_name)
{
    // Tarkistetaan pisteiden olemassaolo
    auto from_it = all_points_.find(from);
    auto to_it = all_points_.find(to);

    if ( from_it == all_points_.end() || to_it == all_points_.end())
    {
        cout << "Error: Points specified in route can't be found" << endl;
        return false;
    }

    shared_ptr<Point> from_point = from_it->second;
    shared_ptr<Point> to_point = to_it->second;

    // Luodaan uusi reitti tarvittaessa
    if ( all_routes_.find(route_name) == all_routes_.end())
    {
        all_routes_[route_name] = make_shared<Route>(Route{route_name, {}});
    }

    shared_ptr<Route> route = all_routes_[route_name];

    // Tarkistetaan from-pisteen olemassaolo ja lisätään tarvittaessa
    if ( route->route_.empty() || route->route_.back() != from_point )
    {
        route->route_.push_back(from_point);
    }

    // Lisätään "to" reittiin seuraavana pisteenä
    route->route_.push_back(to_point);

    return true;
}

// funktio tulostaa tiedostossa määritellyn kokoisen kartan
// ja tulostaa kerrotut pisteet kartalle oikeaan paikkaan,
// jos pisteet ovat kartan alueella.
void OrienteeringMap::print_map() const
{
    // Luodaan tyhjä kartta, joka täytetään ensin pisteillä
    vector<vector<char>> grid(height_, vector<char>(width_, '.'));

    // Käydään läpi suunnistuspisteet ja sijoitetaan kartalle
    for ( const auto& pair : all_points_)
    {
        shared_ptr<Point> point = pair.second;
        int x = point->getX();
        int y = point->getY();
        char marker = point->getMarker();

        // Tarkistetaan onko piste annetun kartan sisällä
        if ( x > 0 && x <= width_ && y > 0 && y <= height_ )
        {
            grid[y - 1][x - 1] = marker;
        }
    }

    // sarakenumerot
    cout << "   ";
    for (int x = 1; x <= width_; ++x)
    {
        cout << setw(2) << x << " ";
    }
    cout << endl;

    // rivit
    for ( int y = 0; y < height_; ++y)
    {
        cout << setw(2) << (y + 1) << " ";

        for ( int x = 0; x < width_; ++x)
        {
            cout << " " << grid[y][x] << " ";
        }
        cout << endl;
    }
}

// Tulostaa kaikki annetut reitit aakkosjärjestyksessä
void OrienteeringMap::print_routes() const
{
    cout << "Routes: " << endl;

    for ( auto& pair : all_routes_ )
    {
        cout << " - " << pair.first << endl;
    }
}

// Tulostaa kaikki annetut pisteet aakkosjärjestyksessä
void OrienteeringMap::print_points() const
{
    cout << "Points: " << endl;

    for ( auto& pair : all_points_ )
    {
        cout << " - " << pair.first << " : " << pair.second->getMarker() << endl;
    }
}

// tulostaa kulkujärjestyksessä halutun reitin kaikki pisteet.
// ottaa parametrinä halutun reitin nimen
void OrienteeringMap::print_route(const string &name) const
{
    if (name.empty())
    {
        cout << "Error: Wrong amount of parameters" << endl;
        return;
    }

    int help_nr = 1;
    auto it = all_routes_.find(name);

    if ( it != all_routes_.end() )
    {
        for ( const shared_ptr<Point>& point : it->second->route_ )
        {
            for ( const auto& pair : all_points_ )
            {
                if (pair.second == point)
                {
                    if ( help_nr > 1)
                    {
                        cout << " -> ";
                    }
                    cout << pair.first << endl;
                    help_nr++;
                }
            }
        }
    }
    else
    {
        cout << "Error: Route named " << name << " can't be found" << endl;
    }
}

// Tulostaa annetun reitin pituuden, joka lasketaan
// peräkkäisten rastien välisten etäisyyksien summana.
// Ottaa parametrinä halutun reitin nimen.
void OrienteeringMap::route_length(const string &name) const
{
    if (name.empty())
    {
        cout << "Error: Wrong amount of parameters" << endl;
        return;
    }

    auto route_it = all_routes_.find(name);
    if (route_it == all_routes_.end())
    {
       cout << "Error: Route named " << name << " can't be found" << endl;
       return;
    }

    const shared_ptr<Route>& route = route_it->second;
    double total_length = 0.0;

    for (size_t i = 1; i < route->route_.size(); ++i)
    {
        shared_ptr<Point> p1 = route->route_[i - 1];
        shared_ptr<Point> p2 = route->route_[i];
        double distance = std::sqrt(std::pow(p2->getX() - p1->getX(), 2) +
                                   std::pow(p2->getY() - p1->getY(), 2));
        total_length += distance;
    }

    cout << setprecision(2) << "Route " << name
         << " length was " << total_length << endl;
}

// Tulostaa suurimman jatkuvan nousun annetulta rastilta lähdettäessä
// eli lopettaa etsinnän kun reitti alkaa uudestaan laskea.
// Ottaa parametrinä halutun rastin nimen ja kertoo tältä rastilta
// lähtevät nousut.
void OrienteeringMap::greatest_rise(const string &point_name) const
{
    if (point_name.empty())
    {
        cout << "Error: Wrong amount of parameters" << endl;
        return;
    }

    auto start_it = all_points_.find(point_name);
    if (start_it == all_points_.end())
    {
        cout << "Error: Point named " << point_name << " can't be found" << endl;
        return;
    }

    shared_ptr<Point> start_point = start_it->second;
    int max_rise = 0;
    vector<string> best_routes;

    for (const auto& route_pair : all_routes_)
    {
        const string& route_name = route_pair.first;
        const shared_ptr<Route>& route = route_pair.second;
        int current_rise = 0;
        bool found_start = false;
        shared_ptr<Point> current_point = start_point;

        for (const auto& point : route->route_)
        {
            if (point == start_point)
            {
                found_start = true;
                current_rise = 0;
                current_point = start_point;
            }
            else if (found_start)
            {
                int rise = point->getHeight() - current_point->getHeight();
                if (rise < 0)
                {
                    break;
                }
                current_rise += rise;
                current_point = point;
            }
        }

        if (current_rise > max_rise)
        {
            max_rise = current_rise;
            best_routes.clear();
            best_routes.push_back(route_name);
        }
        else if (current_rise == max_rise && current_rise > 0)
        {
            best_routes.push_back(route_name);
        }
    }

    if (max_rise == 0)
    {
        cout << "No route rises after point " << point_name << endl;
    }
    else
    {
        cout << "Greatest rise after point " << point_name
             << ", " << max_rise << " meters, is on route(s):" << endl;
        for (const auto& route_name : best_routes)
        {
            cout << " - " << route_name << endl;

        }
    }
}
