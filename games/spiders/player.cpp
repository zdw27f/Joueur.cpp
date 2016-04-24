// Generated by Creer at 03:31AM on April 24, 2016 UTC, git hash: '087b1901032ab5bed5806b24830233eac5c2de55'
// A player in this game. Every AI controls one player.

#include "player.h"
#include "gameManager.h"

// <<-- Creer-Merge: includes -->> - Code you add between this comment and the end comment will be preserved between Creer re-runs.
// you can add additional #includes(s) here.
// <<-- /Creer-Merge: includes -->>




void Spiders::Player::deltaUpdateField(const std::string& fieldName, boost::property_tree::ptree& delta)
{
    Spiders::GameObject::deltaUpdateField(fieldName, delta);

    if (fieldName == "broodMother")
    {
        this->broodMother = (Spiders::BroodMother*)this->gameManager->unserializeGameObject(delta);
    }
    else if (fieldName == "clientType")
    {
        this->clientType = this->gameManager->unserializeString(delta);
    }
    else if (fieldName == "lost")
    {
        this->lost = this->gameManager->unserializeBool(delta);
    }
    else if (fieldName == "maxSpiderlings")
    {
        this->maxSpiderlings = this->gameManager->unserializeInt(delta);
    }
    else if (fieldName == "name")
    {
        this->name = this->gameManager->unserializeString(delta);
    }
    else if (fieldName == "otherPlayer")
    {
        this->otherPlayer = (Spiders::Player*)this->gameManager->unserializeGameObject(delta);
    }
    else if (fieldName == "reasonLost")
    {
        this->reasonLost = this->gameManager->unserializeString(delta);
    }
    else if (fieldName == "reasonWon")
    {
        this->reasonWon = this->gameManager->unserializeString(delta);
    }
    else if (fieldName == "spiders")
    {
        this->spiders = this->gameManager->unserializeVectorOfGameObjects<Spiders::Spider*>(delta, &this->spiders);
    }
    else if (fieldName == "timeRemaining")
    {
        this->timeRemaining = this->gameManager->unserializeDouble(delta);
    }
    else if (fieldName == "won")
    {
        this->won = this->gameManager->unserializeBool(delta);
    }
}




// <<-- Creer-Merge: methods -->> - Code you add between this comment and the end comment will be preserved between Creer re-runs.
// if you forward declaired additional methods to the Player then you can code them here.
// <<-- /Creer-Merge: methods -->>
