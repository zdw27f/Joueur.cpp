// Generated by Creer at 01:31AM on December 23, 2015 UTC, git hash: '1b69e788060071d644dd7b8745dca107577844e1'
// A typical abandoned warehouse... that anarchists hang out in and can be bribed to burn down Buildings.

#ifndef JOUEUR_ANARCHY_WAREHOUSE_H
#define JOUEUR_ANARCHY_WAREHOUSE_H

#include "anarchy.h"
#include "building.h"

// <<-- Creer-Merge: includes -->> - Code you add between this comment and the end comment will be preserved between Creer re-runs.
// you can add addtional #includes(s) here.
// <<-- /Creer-Merge: includes -->>

/// <summary>
/// A typical abandoned warehouse... that anarchists hang out in and can be bribed to burn down Buildings.
/// </summary>
class Anarchy::Warehouse : public Anarchy::Building
{
    friend Anarchy::GameManager;

    protected:
        virtual void deltaUpdateField(const std::string& fieldName, boost::property_tree::ptree& delta);
        Warehouse() {};
        ~Warehouse() {};

    public:
        /// <summary>
        /// How exposed the anarchists in this warehouse are to PoliceDepartments. Raises when bribed to ignite buildings, and drops each turn if not bribed.
        /// </summary>
        int exposure;

        /// <summary>
        /// The amount of fire added to buildings when bribed to ignite a building. Headquarters add more fire than normal Warehouses.
        /// </summary>
        int fireAdded;


        // <<-- Creer-Merge: fields -->> - Code you add between this comment and the end comment will be preserved between Creer re-runs.
        // you can add addtional fields(s) here. None of them will be tracked or updated by the server.
        // <<-- /Creer-Merge: fields -->>

        /// <summary>
        /// Bribes the Warehouse to light a Building on fire. This adds this building's fireAdded to their fire, and then this building's exposure is increased based on the Manhatten distance between the two buildings.
        /// </summary>
        /// <param name="building">The Building you want to light on fire.</param>
        /// <returns>The exposure added to this Building's exposure. -1 is returned if there was an error.</returns>
        int ignite(Anarchy::Building* building);


        // <<-- Creer-Merge: methods -->> - Code you add between this comment and the end comment will be preserved between Creer re-runs.
        // you can add addtional method(s) here.
        // <<-- /Creer-Merge: methods -->>
};

#endif
