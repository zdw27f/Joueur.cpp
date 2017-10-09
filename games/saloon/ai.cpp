// AI
// This is where you build your AI

#include "ai.hpp"
using namespace std;

// <<-- Creer-Merge: includes -->> - Code you add between this comment and the end comment will be preserved between Creer re-runs.
// You can add #includes here for your AI.
// <<-- /Creer-Merge: includes -->>

namespace cpp_client
{

namespace saloon
{

/// <summary>
/// This returns your AI's name to the game server.
/// Replace the string name.
/// </summary>
/// <returns>The name of your AI.</returns>
std::string AI::get_name() const
{
    // <<-- Creer-Merge: get-name -->> - Code you add between this comment and the end comment will be preserved between Creer re-runs.
    // REPLACE WITH YOUR TEAM NAME!
    return "Saloon C++ Player";
    // <<-- /Creer-Merge: get-name -->>
}

/// <summary>
/// This is automatically called when the game first starts, once the game objects are created
/// </summary>
void AI::start()
{
    // <<-- Creer-Merge: start -->> - Code you add between this comment and the end comment will be preserved between Creer re-runs.
    // This is a good place to initialize any variables
    // <<-- /Creer-Merge: start -->>
    this->bartender_move_up[0] = false;
    this->bartender_move_up[1] = false;

}

/// <summary>
/// This is automatically called the game (or anything in it) updates
/// </summary>
void AI::game_updated()
{
    // <<-- Creer-Merge: game-updated -->> - Code you add between this comment and the end comment will be preserved between Creer re-runs.
    // If a function you call triggers an update this will be called before it returns.
    // <<-- /Creer-Merge: game-updated -->>
    Cowboy active_cowboy;
    int counter = 0;

    for (int i = 0; i < this->player->cowboys.size(); i++)
    {
        active_cowboy = this->player->cowboys[i];

        if (active_cowboy->job == "Bartender")
        {
            if (active_cowboy->tile->tile_north->is_balcony)
                bartender_move_up[counter] = false;
            else if (active_cowboy->tile->tile_south->is_balcony)
                bartender_move_up[counter] = true;

            counter++;
        }
    }
}

/// <summary>
/// This is automatically called when the game ends.
/// </summary>
/// <param name="won">true if you won, false otherwise</param>
/// <param name="reason">An explanation for why you either won or lost</param>
void AI::ended(bool won, const std::string& reason)
{
    //<<-- Creer-Merge: ended -->> - Code you add between this comment and the end comment will be preserved between Creer re-runs.
    // You can do any cleanup of your AI here.  The program ends when this function returns.
    //<<-- /Creer-Merge: ended -->>
}

/// <summary>
/// This is called every time it is this AI.player's turn.
/// </summary>
/// <returns>Represents if you want to end your turn. True means end your turn, False means to keep your turn going and re-call this function.</returns>
bool AI::run_turn()
{
    // Notice to CS 1570 students.
    // We use pointers extensively throughout the C++ client
    // If you are not familiar with pointers here's the quick and dirty on what you need to know
    // Normally you'd use the `.` (dot) operator to access member variables,
    // e.g. point.x = 0;
    // However with pointers use the `->` (arrow) operator instead
    // e.g. point->x = 0;
    // In Data Structures you will learn why
    // And for those on you in Data Structures, we manage the memory of the game objects automatically for you

    cout << "Start of my turn: " << this->game->current_turn << endl;

    int brawler = 0;
    int sharpshooter = 0;
    int bartender = 0;

    // Obtain the number of each of the types of units
    for (int i = 0; i < this->player->cowboys.size(); i++)
    {
        string cowboys_job = this->player->cowboys[i]->job;

        if (cowboys_job == "Brawler")
            brawler++;
        else if (cowboys_job == "Bartender")
            bartender++;
        else
            sharpshooter++;
    }

    // Grab the young gun
    Young_gun my_young_gun = this->player->young_gun;

    // Try to spawn in units
    if (my_young_gun->can_call_in)
    {
        // Grabs the young gun's call in tile
        Tile call_in_tile = my_young_gun->call_in_tile;

        // Checks to make sure that the call in tile doesn't contain anything
        if (!call_in_tile->cowboy && !call_in_tile->has_hazard &&
            !call_in_tile->bottle && !call_in_tile->furnishing)
        {
            if (bartender < game->max_cowboys_per_job)
            {
                cout << "Calling in Bartender" << endl;
                my_young_gun->call_in("Bartender");
            }
            else if (sharpshooter < game->max_cowboys_per_job)
            {
                cout << "Calling in Sharpshooter" << endl;
                my_young_gun->call_in("Sharpshooter");
            }
            else if (brawler < game->max_cowboys_per_job)
            {
                cout << "Calling in Brawler" << endl;
                my_young_gun->call_in("Brawler");
            }
            else
                cout << "No more units to call in at this time." << endl;
        }

    }

    // Run the game update section
    this->game_updated();
    int bartender_counter = -1;

    // Loop through all the units and have them each do something (if they can)
    for (int i = 0; i < this->player->cowboys.size(); i++)
    {
        // Grab the current cowboy in the cowboy's vector
        Cowboy current_cowboy = this->player->cowboys[i];

        // Check to make sure we can move the cowboy
        if (current_cowboy->can_move && !current_cowboy->is_dead &&
            !current_cowboy->is_drunk && current_cowboy->turns_busy == 0)
        {
            // Grab the enemy player
            Player opponent = this->player->opponent;
            Tile enemy_tile;

            std::vector<Tile> path;

            if (current_cowboy->job == "Bartender")
            {
                bartender_counter++;
                Tile cowboys_north_tile = current_cowboy->tile->tile_north;
                Tile cowboys_south_tile = current_cowboy->tile->tile_south;

                // Get the Bartender to move up or down
                if (this->bartender_move_up[bartender_counter] && !cowboys_north_tile->bottle &&
                    !cowboys_north_tile->cowboy && !cowboys_north_tile->furnishing && !cowboys_north_tile->is_balcony)
                {
                    if (current_cowboy->move(current_cowboy->tile->tile_north))
                    {
                        cout << "Moving cowboy " << current_cowboy->id << " moved to tile ";
                        cout << current_cowboy->tile->tile_north->id << endl;
                    }
                }
                else if (!cowboys_south_tile->bottle && !cowboys_south_tile->cowboy &&
                        !cowboys_south_tile->furnishing && !cowboys_south_tile->is_balcony)
                {
                    if (current_cowboy->move(current_cowboy->tile->tile_south))
                    {
                        cout << "Moving cowboy " << current_cowboy->id << " moved to tile ";
                        cout << current_cowboy->tile->tile_south->id << endl;
                    }
                }

                // Variables used with finding an enemy
                int row = current_cowboy->tile->y;
                bool enemy_found = false;
                Cowboy possible_enemy;

                // Find an enemy cowboy in the same row as the Bartender
                for (int col = 0; col < game->map_width; col++)
                {
                    if (game->get_tile_at(col, row)->cowboy != nullptr)
                    {
                        possible_enemy = game->get_tile_at(col, row)->cowboy;

                        // // Check if the cowboy found is an enemy cowboy
                        if (possible_enemy->owner != this->player)
                        {
                            enemy_found = true;
                            break;
                        }
                    }
                }

                // Now possible_enemy is a confirmed enemy if enemy_found is equal to true
                if (enemy_found)
                {
                    Tile tile;
                    // Throw a bottle at the enemy unit and have them move in a random direction
                    // if they get hit.
                    if (possible_enemy->tile->x < current_cowboy->tile->x)
                    {
                        if (current_cowboy->act(current_cowboy->tile->tile_west, tile->directions.at(rand() % tile->directions.size())))
                            cout << "Cowboy " << current_cowboy->id << " throwing a bottle in west direction." << endl;
                    }
                    else
                    {
                        if (current_cowboy->act(current_cowboy->tile->tile_east, tile->directions.at(rand() % tile->directions.size())))
                            cout << "Cowboy " << current_cowboy->id << " throwing a bottle in east direction." << endl;
                    }
                }

            } // End of Bartender if statement

            else if (current_cowboy->job == "Sharpshooter")
            {


            }

            else // current_cowboy == "Brawler"
            {
                // Checks if an enemy unit exists to hunt down
                if (opponent->cowboys.size() > 0)
                {
                    path = this->find_path(current_cowboy->tile, opponent->cowboys[0]->tile);

                    // if there is a path, move along it
                    //      length 0 means no path could be found to the tile
                    //      length 1 means the enemy is adjacent, and we can't move onto the same tile as the enemy
                    if (path.size() > 1)
                    {
                        if (current_cowboy->move(path[0]))
                            cout << "Moving current cowboy to Tile " << path[0]->id << endl;
                    }

                    // Brawler don't act necessarily, but rather they attack each turn on their own.
                    else if (path.size() == 1)
                        cout << "Attacking enemy unit(s) with the one being targeted at tile " << path[0]->id << endl;

                    else
                        cout << "Couldn't find a path to any enemy units." << endl;
                }

            } // End of Brawler if statement

        } // End of if checking if you can move the current cowboy

    } // End of for loop that loops through all of your coyboys

    /*
    // Grab one of the cowboys(units) and try to do things with him
    Cowboy current_cowboy = nullptr;
    for(int i = 0; i < this->player->cowboys.size(); i++)
    {
        Cowboy cowboy = this->player->cowboys[i];

        // if this cowboy is not dead then make him our active cowboy we will try to control
        if(!cowboy->is_dead)
        {
            current_cowboy = cowboy;
            break;
        }
    }

    // 1. Try to spawn a cowboy.

    // Randomly select a job.
    std::string new_job = game->jobs.at(rand() % game->jobs.size());

    // Count cowboys with selected job
    int job_count = 0;
    for(int i = 0; i < this->player->cowboys.size(); i++)
    {
        Cowboy cowboy = this->player->cowboys[i];

        if(!cowboy->is_dead && cowboy->job == new_job)
        {
            job_count++;
        }
    }

    // Call in the new cowboy with that job if there aren't too many
    //   cowboys with that job already.
    if(this->player->young_gun->can_call_in && job_count < this->game->max_cowboys_per_job)
    {
        std::cout << "1. Calling in: " << new_job << std::endl;
        this->player->young_gun->call_in(new_job);
    }

    // Now lets use him
    if(active_cowboy && !active_cowboy->is_dead)
    {
        // Try to move the cowboy north
        Tile new_tile = active_cowboy->tile->tile_north;

        if(active_cowboy->can_move && new_tile->is_pathable())
            active_cowboy->move(new_tile);

        Tile some_tile = active_cowboy->tile->tile_west;

        if (!some_tile->is_balcony)
        {
            // Try to perform the cowboy's action
            if(active_cowboy->turns_busy <= 0 && active_cowboy->job != "Brawler")
            {   //Brawler's don't have an action, or at least they act on their own.

                active_cowboy->act(active_cowboy->tile->tile_west, "East");
            }
        }
    }

    */

    std::cout << "Ending my turn." << std::endl;
    return true;
}

/// A very basic path finding algorithm (Breadth First Search) that when given a starting Tile, will return a valid path to the goal Tile.
/// <param name="start">the starting Tile</param>
/// <param name="goal">the goal Tile</param>
/// <return>A List of Tiles representing the path, the the first element being a valid adjacent Tile to the start, and the last element being the goal. Or an empty list if no path found.</return>
std::vector<Tile> AI::find_path(const Tile& start, const Tile& goal)
{
    // no need to make a path to here...
    if(start == goal)
    {
        return {};
    }

    // the tiles that will have their neighbors searched for 'goal'
    std::queue<Tile> fringe;

    // How we got to each tile that went into the fringe.
    std::unordered_map<Tile,Tile> came_from;

    // Enqueue start as the first tile to have its neighbors searched.
    fringe.push(start);

    // keep exploring neighbors of neighbors... until there are no more.
    while(fringe.size() > 0)
    {
        // the tile we are currently exploring.
        Tile inspect = fringe.front();
        fringe.pop();

        // Note, we are using the `auto` keyword here
        //   The compiler can discern that this is a `std::vector<Tile>` based on the return type of `getNeighbors()`
        auto neighbors = inspect->get_neighbors();

        // cycle through the tile's neighbors.
        for(int i = 0; i < neighbors.size(); i++)
        {
            Tile neighbor = neighbors[i];

            // If we found the goal we've found the path!
            if(neighbor == goal)
            {
                // Follow the path backward starting at the goal and return it.
                std::deque<Tile> path;
                path.push_front(goal);

                // Starting at the tile we are currently at, insert them retracing our steps till we get to the starting tile
                for(Tile step = inspect; step != start; step = came_from[step])
                {
                    path.push_front(step);
                }

                // we want to return a vector as that's what we use for all containers in C++
                // (and they don't have push_front like we need)
                // So construct the vector-ized path here
                std::vector<Tile> vector_path;
                for(auto& tile : path)
                {
                    vector_path.push_back(tile);
                }
                return vector_path;
            }

            // if the tile exists, has not been explored or added to the fringe yet, and it is pathable
            if(neighbor && came_from.count(neighbor) == 0 && neighbor->is_pathable())
            {
                // add it to the tiles to be explored and add where it came from.
                fringe.push(neighbor);
                came_from[neighbor] = inspect;
            }

        } // for each neighbor

    } // while fringe not empty

    // if you're here, that means that there was not a path to get to where you want to go.
    //   in that case, we'll just return an empty path.
    return {};
}

//<<-- Creer-Merge: methods -->> - Code you add between this comment and the end comment will be preserved between Creer re-runs.
// You can add additional methods here for your AI to call
//<<-- /Creer-Merge: methods -->>

} // saloon

} // cpp_client
