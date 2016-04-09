// Generated by Creer at 05:19AM on April 09, 2016 UTC, git hash: 'f74143f3f89eebeaa381aba30a8afbda7d0e1d89'
// A Spiderling that creates and spits new Webs from the Nest it is on to another Nest, connecting them.

#include "spitter.h"
#include "gameManager.h"

#include "nest.h"

// <<-- Creer-Merge: includes -->> - Code you add between this comment and the end comment will be preserved between Creer re-runs.
// you can add additional #includes(s) here.
// <<-- /Creer-Merge: includes -->>




void Spiders::Spitter::deltaUpdateField(const std::string& fieldName, boost::property_tree::ptree& delta)
{
    Spiders::Spiderling::deltaUpdateField(fieldName, delta);

    if (fieldName == "spittingWebToNest")
    {
        this->spittingWebToNest = (Spiders::Nest*)this->gameManager->unserializeGameObject(delta);
    }
}



bool Spiders::Spitter::spit(Spiders::Nest* nest)
{
    boost::property_tree::ptree args;
    args.put_child("nest", *this->gameManager->serialize(static_cast<BaseGameObject*>(nest)));

    auto returned = this->gameManager->runOnServer(*this, "spit", args);
    return this->gameManager->unserializeBool(*returned);
}


// <<-- Creer-Merge: methods -->> - Code you add between this comment and the end comment will be preserved between Creer re-runs.
// if you forward declaired additional methods to the Spitter then you can code them here.
// <<-- /Creer-Merge: methods -->>
