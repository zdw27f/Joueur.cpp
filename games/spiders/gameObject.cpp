// Generated by Creer at 05:19AM on April 09, 2016 UTC, git hash: 'f74143f3f89eebeaa381aba30a8afbda7d0e1d89'
// An object in the game. The most basic class that all game classes should inherit from automatically.

#include "gameObject.h"
#include "gameManager.h"

// <<-- Creer-Merge: includes -->> - Code you add between this comment and the end comment will be preserved between Creer re-runs.
// you can add additional #includes(s) here.
// <<-- /Creer-Merge: includes -->>




void Spiders::GameObject::deltaUpdateField(const std::string& fieldName, boost::property_tree::ptree& delta)
{
    Joueur::BaseGameObject::deltaUpdateField(fieldName, delta);

    if (fieldName == "logs")
    {
        this->logs = this->gameManager->unserializeVector(delta, &this->logs);
    }
}



void Spiders::GameObject::log(std::string message)
{
    boost::property_tree::ptree args;
    args.put_child("message", *this->gameManager->serialize((message)));

    auto returned = this->gameManager->runOnServer(*this, "log", args);
}


// <<-- Creer-Merge: methods -->> - Code you add between this comment and the end comment will be preserved between Creer re-runs.
// if you forward declaired additional methods to the GameObject then you can code them here.
// <<-- /Creer-Merge: methods -->>
