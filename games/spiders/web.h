// Generated by Creer at 05:19AM on April 09, 2016 UTC, git hash: 'f74143f3f89eebeaa381aba30a8afbda7d0e1d89'
// A connection (edge) to a Nest (node) in the game that Spiders can converge on (regardless of owner). Spiders can travel in either direction on Webs.

#ifndef JOUEUR_SPIDERS_WEB_H
#define JOUEUR_SPIDERS_WEB_H

#include "spiders.h"
#include "gameObject.h"

// <<-- Creer-Merge: includes -->> - Code you add between this comment and the end comment will be preserved between Creer re-runs.
// you can add addtional #includes(s) here.
// <<-- /Creer-Merge: includes -->>

/// <summary>
/// A connection (edge) to a Nest (node) in the game that Spiders can converge on (regardless of owner). Spiders can travel in either direction on Webs.
/// </summary>
class Spiders::Web : public Spiders::GameObject
{
    friend Spiders::GameManager;

    protected:
        virtual void deltaUpdateField(const std::string& fieldName, boost::property_tree::ptree& delta);
        Web() {};
        ~Web() {};

    public:
        /// <summary>
        /// How long this Web is, i.e., the distance between its nestA and nestB.
        /// </summary>
        float length;

        /// <summary>
        /// How much weight this Web currently has on it, which is the sum of all its Spiderlings weight.
        /// </summary>
        int load;

        /// <summary>
        /// The first Nest this Web is connected to.
        /// </summary>
        Spiders::Nest* nestA;

        /// <summary>
        /// The second Nest this Web is connected to.
        /// </summary>
        Spiders::Nest* nestB;

        /// <summary>
        /// All the Spiderlings currently moving along this Web.
        /// </summary>
        std::vector<Spiders::Spiderling*> spiderlings;

        /// <summary>
        /// How much weight this Web can take before snapping and destroying itself and all the Spiders on it.
        /// </summary>
        int strength;


        // <<-- Creer-Merge: fields -->> - Code you add between this comment and the end comment will be preserved between Creer re-runs.
        // you can add addtional fields(s) here. None of them will be tracked or updated by the server.
        // <<-- /Creer-Merge: fields -->>


        // <<-- Creer-Merge: methods -->> - Code you add between this comment and the end comment will be preserved between Creer re-runs.
        // you can add addtional method(s) here.
        // <<-- /Creer-Merge: methods -->>
};

#endif
