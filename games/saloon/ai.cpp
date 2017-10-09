// AI
// This is where you build your AI

#include "ai.hpp"
#include <algorithm>

// <<-- Creer-Merge: includes -->> - Code you add between this comment and the end comment will be preserved between Creer re-runs.
// You can add #includes here for your AI.
// <<-- /Creer-Merge: includes -->>
using namespace std;
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
    return "Example AI";
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
}

/// <summary>
/// This is automatically called the game (or anything in it) updates
/// </summary>
void AI::game_updated()
{
    // <<-- Creer-Merge: game-updated -->> - Code you add between this comment and the end comment will be preserved between Creer re-runs.
    // If a function you call triggers an update this will be called before it returns.
    // <<-- /Creer-Merge: game-updated -->>
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
    // <<-- Creer-Merge: runTurn -->> - Code you add between this comment and the end comment will be preserved between Creer re-runs.
    // Put your game logic here for runTurn

    // Spawn a cowboy
    Cowboy newc;
    do {
        std::string callInJob = game->jobs.at(random() % game->jobs.size());
        newc = spawn(callInJob);
    } while (game->current_player->young_gun->can_call_in && numCowboys() < game->jobs.size() * game->max_cowboys_per_job);

    // Find the pianos
    vector<Tile> tiles;
    for (int i =0; i < game->tiles.size(); i++)
    {
        if (game->tiles[i]->furnishing != nullptr && game->tiles[i]->furnishing->is_piano)
        {
            tiles.push_back(game->tiles[i]);
        }
    }

    // Move each cowboy to a useful location
    for (int i = 0; i < game->current_player->cowboys.size(); i++)
    {
        Cowboy c = game->current_player->cowboys[i];
        if (!c->is_dead && !c->turns_busy) {
            Tile t = c->tile;
            // Find a target piano
            Tile target = nearestPiano(t, tiles);
            if (target != nullptr && target != c->tile) {
                vector<Tile> p = findPath(t, target);
                // Find the piano's location in the vector
                auto p_loc = find(tiles.begin(), tiles.end(), nearestPiano(t, tiles));
                // Remove it from the vector so other cowboys aren't assigned to it
                if (p_loc != tiles.end())
                    tiles.erase(p_loc);
                // Move toward the piano
                if (p.size() > 0)
                {
                    c->move(p.back());
                }
                else
                {
                    // Go find an enemy cowboy to harass
                    Tile e  = nearestEnemy(t);
                    vector<Tile> p = findPath(t, e);
                    if (p.size() > 0)
                    {
                        c->move(p.back());
                    }

                }
            }
        }
    }
    playPianos();
    fight();

    return true;
    // <<-- /Creer-Merge: runTurn -->>
}

// <<-- Creer-Merge: methods -->> - Code you add between this comment and the end comment will be preserved between Creer re-runs.
// you can add additional methods here for your AI to call
Cowboy AI::spawn(string job)
{
    // Count cowboys with selected job
    int jobCount = 0;  
    for(int i = 0; i < player->cowboys.size(); ++i) {
        Cowboy cowboy = player->cowboys.at(i);
        if(!cowboy->is_dead && cowboy->job == job) {
            jobCount++;
        }
    }

    if(player->young_gun->can_call_in && jobCount < game->max_cowboys_per_job) {
        return player->young_gun->call_in(job);
    }
    return nullptr;
}

Tile AI::nearestPiano(Tile tile, vector<Tile> tiles)
{
    Tile nearest = nullptr;
    for (int i = 0; i < tiles.size(); i++)
    {
        Tile t = tiles[i];
        if (t->furnishing && t->furnishing->is_piano && (nearest == nullptr || distance(tile, t) < distance(tile, nearest)))
        {
            nearest = t;
        }
    }
    return nearest;
}

Tile AI::nearestEnemy(Tile tile)
{
    Tile nearest = nullptr;
    for (int i = 0; i < game->current_player->opponent->cowboys.size(); i++)
    {
        Tile t = game->current_player->opponent->cowboys[i]->tile;
        if (t != nullptr && (nearest == nullptr || distance(tile, t) < distance(tile, nearest)))
        {
            nearest = t;
        }
    }
    return nearest;
}

int AI::distance(Tile t1, Tile t2)
{
    // Manhattan Distance
    int dist = (t1->x - t2->x) + (t1->y - t2->y);
    return dist>0?dist:-dist;
}

int AI::numCowboys()
{
    int num = 0;
    for (int i = 0; i < game->current_player->cowboys.size(); i++)
    {
        Cowboy cowboy = player->cowboys.at(i);
        if (!cowboy->is_dead)
            num++;
    }
    return num;
}

std::vector<Tile> AI::findPath(Tile start, Tile goal)
{
  std::unordered_map<Tile,Tile> from;
  std::deque<Tile> frontier{start};

  from[start] = nullptr;

  //while frontier is not empty, continue searching
  while(!frontier.empty()) {
    Tile const top = frontier.front();
    frontier.pop_front();

    //add neighbors to search frontier if we haven't seen them already
    //and they are 'pathable' (see is_pathable on Tile)
    std::vector<Tile> neighbors = top->get_neighbors();
    for(int i = 0; i < neighbors.size(); i++) {
      Tile const neighbor = neighbors.at(i);

      //goal found, reconstruct path
      if(neighbor == goal) {
        std::vector<Tile> path{};
        for(Tile step = top; step != start; step = from[step]) {
          path.push_back(step);
        }
        return path;
      }
      
      if(neighbor && neighbor->is_pathable() && from.count(neighbor) == 0) {
        frontier.push_back(neighbor);
        from[neighbor] = top;
      }
    }
  }

  //no path was found from start to goal
  return {};
}

void AI::playPianos()
{
    for (int i = 0; i < game->current_player->cowboys.size(); i++)
    {
        Cowboy c = game->current_player->cowboys[i];
        if (!c->is_dead) {
            std::vector<Tile> adj = adjacentTiles(c->tile);
            for (int j = 0; j < adj.size(); j++)
            {
                if (adj[j]->furnishing != nullptr && adj[j]->furnishing->is_piano && !adj[j]->furnishing->is_playing)
                {
                    c->play(adj[j]->furnishing);
                    std::cout << "Played a piano!" << std::endl;
                    break;
                }
            }
        }
    }

}

void AI::fight()
{
    for (int i = 0; i < game->current_player->cowboys.size(); i++)
    {
        Cowboy c = game->current_player->cowboys[i];
        if (!c->is_dead && !c->turns_busy && (c->job == "Bartender" || c->job == "Sharpshooter" && c->focus > 0))
        {
            std::vector<Tile> adj = adjacentTiles(c->tile);
            for (int j = 0; j < adj.size(); j++)
            {
                if (adj[j]->cowboy != nullptr && adj[j]->cowboy->owner != game->current_player)
                {
                    //cout << c->job << "CAN ATTACK " << adj[j]->cowboy->job << endl;
                    if (c->job == "Sharpshooter")
                    {
                        c->act(adj[j]);
                        std::cout << "Shot!" << std::endl;
                    }
                    else if (c->job == "Bartender" && !c->turns_busy)
                    {
                        c->act(adj[j], "North");
                        std::cout << "Threw Beer" << std::endl;
                    }
                    break;
                }
            }
        }
    }

}

std::vector<Tile> AI::adjacentTiles(Tile t)
{
    vector<Tile> adj;
    if (t->tile_north != nullptr)
        adj.push_back(t->tile_north);
    if (t->tile_east != nullptr)
        adj.push_back(t->tile_east);
    if (t->tile_south != nullptr)
        adj.push_back(t->tile_south);
    if (t->tile_west != nullptr)
        adj.push_back(t->tile_west);
    return adj;
}
// <<-- /Creer-Merge: methods -->>

} //saloon

} //cpp_client