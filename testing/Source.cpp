#include <iostream>
#include <memory>
#include <vector>
#include <string>
#include <algorithm>
#include <random>
#include <chrono>
#include <sstream>

class card {
protected:
    std::string cardName;
    bool tapped;
    int manaCost;
public:
    card() :cardName("none"), manaCost(0) {
        tapped = false;
    }
    card(std::string& cn, int mC) : cardName(cn), manaCost(mC) {
        tapped = false;
    }
    card(const card& c) {
        cardName = c.cardName;
        tapped = c.tapped;
        manaCost = c.manaCost;
    }

    void tappedCard() {
        if (!tapped) {
            std::cout << "The card is untapped. You can't play the card." << std::endl;
        }
        else {
            std::cout << "The card is tapped. You can play the card." << std::endl;
        }
    }

    virtual void play(int totalMana, bool played) {

    }

    virtual void printInfo() {

    }
};

class landCard : public card {
protected:
    int manaPoint;

public:
    landCard() :manaPoint(0) {

    }
    landCard(std::string cn, int mC, int mP) : manaPoint(mP), card(cn, mC) {

    }

    /* void play(std::vector<std::string> vect) {
         for (int i = 0; i < vect.size(); i++) {
             manaPoint = manaPoint + 1;
         }
     }*/
     /*void printMana(std::vector<std::string> vect) {
         for (int i = 0; i < vect.size(); i++) {
             manaPoint = manaPoint + 1;
         }
         std::cout << "Current mana: " << manaPoint << std::endl;
     }*/

};

class creatureCard : public card {
protected:
    int creatureAtk;
    int creatureHp;
    bool firstStrike;
    bool trample;

public:
    creatureCard() : creatureAtk(0), creatureHp(0) {
        firstStrike = false;
        trample = false;
    }

    creatureCard(std::string cn, int mC, int atk, int cHp) : creatureAtk(atk), creatureHp(cHp), card(cn, mC) {
        firstStrike = false;
        trample = false;
    }

    void play(int totalMana, bool played) {
        if (totalMana < manaCost) {
            std::cout << "Insufficient mana. You cannot play the card." << std::endl;
            played = false;
        }
        else if (totalMana >= manaCost) {
            std::cout << "Player played " << cardName << "." << std::endl;
            played = true;
            if (cardName == "White Knight" || cardName == "Black Knight") {
                firstStrike = true;
                creatureHp = creatureHp - creatureAtk;
            }
            else if (cardName == "AngryBear" || cardName == "Werewolf") {
                trample = true;
                int excessPower;
                excessPower = creatureAtk - creatureHp;
                creatureAtk = excessPower + creatureAtk;
            }
            else {
                firstStrike = false;
                trample = false;
            }
        }
    }

    void enchantHolyWar(int atk, int cHp) {
        creatureHp = creatureHp + cHp;
        creatureAtk = creatureAtk + atk;
    }

    void enchantHolyLight(int atk, int cHp) {
        creatureHp = creatureHp - 1;
        creatureAtk = creatureAtk - 1;
    };

    void enchantUnholyWar(int atk) {
        creatureAtk = creatureAtk + atk;
    }

    void gainTrample(std::string cn) {
        if (cardName == cn && !trample) {
            trample = true;
        }
    }

    void loseFirstStrike(std::string cn) {
        if (cardName == cn && !firstStrike) {
            firstStrike = false;
        }
    }

    void loseTrample(std::string cn) {
        if (cardName == cn && !trample) {
            trample = false;
        }
    }

    void creatureLoseHp(int dmg) {
        creatureHp = creatureHp - dmg;
    }

};

class sorceryCard : public card {
protected:
    std::string sEffect;

public:
    sorceryCard() : sEffect("") {

    }
    sorceryCard(std::string cn, int mC, std::string sE) : sEffect(sE), card(cn, mC) {

    }

    void play(int totalMana, bool played) {
        if (totalMana < manaCost) {
            std::cout << "Insufficient mana. You cannot play the card." << std::endl;
            played = false;
        }
        else if (totalMana >= manaCost) {
            if (cardName == "Disenchant") {
                std::cout << "Player played " << cardName << ". Destroy one enchantment card." << std::endl;
                //effects.destroyCard();
            }
            else if (cardName == "Lighting Bolt") {
                std::cout << "Player played " << cardName << ". Deal 2 damage to target creature or player." << std::endl;
                //effects.dealDamage();
            }
            else if (cardName == "Flood") {
                std::cout << "Player played " << cardName << ". Destroy one land card." << std::endl;
                //effects.destroyLandCard();
            }
            else if (cardName == "Reanimate") {
                std::cout << "Player played " << cardName << ". Player can revive one card from discard pile" << std::endl;
            }
            else if (cardName == "Plague") {
                std::cout << "Player played " << cardName << ". All creatures take 1 damage." << std::endl;
            }
            else if (cardName == "Terror") {
                std::cout << "Player played " << cardName << ". Destroy one creature card." << std::endl;
                //effects.destroyCreatureCard();
            }
            played = true;
        }
    }
};

class enchantmentCard : public card {
protected:
    std::string eEffect;

public:
    enchantmentCard() : eEffect("") {}
    enchantmentCard(std::string cn, int mC, std::string eE) : eEffect(eE), card(cn, mC) {}

    void play(int totalMana, bool played) {
        if (totalMana < manaCost) {
            std::cout << "Insufficient mana. You cannot play the card." << std::endl;
            played = false;
        }
        else if (totalMana >= manaCost) {
            if (cardName == "Rage") {
                std::cout << "Player played " << cardName << ". One creature gains Trample." << std::endl;
            }
            else if (cardName == "Holy War") {
                std::cout << "Player played " << cardName << ". All creatures gain +1 attack and health point." << std::endl;
            }
            else if (cardName == "Holy Light") {
                std::cout << "Player played " << cardName << ". All enemy creature lose -1 attack and health point." << std::endl;
            }
            else if (cardName == "Unholy War") {
                std::cout << "Player played " << cardName << ". All creatures gain +2 attack." << std::endl;
            }
            else if (cardName == "Restrain") {
                std::cout << "Player played " << cardName << ". All creatures lose Trample." << std::endl;
            }
            else if (cardName == "Slow") {
                std::cout << "Player played " << cardName << ". One of the enemy creatures loses First Strike." << std::endl;
            }
            played = true;
        }
    }
};
class cardinfo : public landCard, public creatureCard, public enchantmentCard, public sorceryCard {
protected:
    std::string cardName;
    int manaCost;
    int creatureAtk;
    int creatureHp;
    std::string sEffect;
    int cardnumber;
public:

    cardinfo() {
        cardnumber = 0;
        creatureHp = 0;
        creatureAtk = 0;
        manaCost = 0;
    }
    void cinfo(std::vector<std::string> hand) {
        for (std::string cardName : hand) {
            if (cardName == "Forest") {
                manaPoint = 1;
                std::cout << "-------------" << std::endl;
                std::cout << "Card Name: " << cardName << std::endl;
                std::cout << "It gives: " << manaPoint << " Mana points." << std::endl;
            }
            else if (cardName == "Island") {
                manaPoint = 1;
                std::cout << "-------------" << std::endl;
                std::cout << "Card Name: " << cardName << std::endl;
                std::cout << "It gives: " << manaPoint << " Mana points." << std::endl;
            }
            else if (cardName == "Mountain") {
                manaPoint = 1;
                std::cout << "-------------" << std::endl;
                std::cout << "Card Name: " << cardName << std::endl;
                std::cout << "It gives: " << manaPoint << " Mana points." << std::endl;
            }
            else if (cardName == "Plains") {
                manaPoint = 1;
                std::cout << "-------------" << std::endl;
                std::cout << "Card Name: " << cardName << std::endl;
                std::cout << "It gives: " << manaPoint << " Mana points." << std::endl;
            }
            else if (cardName == "Swamp") {
                manaPoint = 1;
                std::cout << "-------------" << std::endl;
                std::cout << "Card Name: " << cardName << std::endl;
                std::cout << "It gives: " << manaPoint << " Mana points." << std::endl;
            }
            else if (cardName == "Disenchant") {
                manaCost = 2;
                sEffect = " Destroy 1 Target Enchantment";
                std::cout << "-------------" << std::endl;
                std::cout << "Card Name: " << cardName << std::endl;
                std::cout << "Mana cost: " << manaCost << std::endl;
                std::cout << "Effect: " << sEffect << std::endl;
            }
            else if (cardName == "Lightning Bolt") {
                manaCost = 2;
                sEffect = "Deal 2 dmg to target creature or player";
                std::cout << "-------------" << std::endl;
                std::cout << "Card Name: " << cardName << std::endl;
                std::cout << "Mana cost: " << manaCost << std::endl;
                std::cout << "Effect: " << sEffect << std::endl;
            }
            else if (cardName == "Flood") {
                manaCost = 1;
                sEffect = "Destroy 1 Target Land";
                std::cout << "-------------" << std::endl;
                std::cout << "Card Name: " << cardName << std::endl;
                std::cout << "Mana cost: " << manaCost << std::endl;
                std::cout << "Effect: " << sEffect << std::endl;
            }
            else if (cardName == "Reanimate1") {
                manaCost = 1;
                sEffect = "Return 1 character card from discard to hand";
                std::cout << "-------------" << std::endl;
                std::cout << "Card Name: " << cardName << std::endl;
                std::cout << "Mana cost: " << manaCost << std::endl;
                std::cout << "Effect: " << sEffect << std::endl;
            }
            else if (cardName == "Plague") {
                manaCost = 2;
                sEffect = "Deal 1 dmg to all creatures";
                std::cout << "-------------" << std::endl;
                std::cout << "Card Name: " << cardName << std::endl;
                std::cout << "Mana cost: " << manaCost << std::endl;
                std::cout << "Effect: " << sEffect << std::endl;
            }
            else if (cardName == "Terror") {
                manaCost = 2;
                sEffect = "Destroy 1 Target Creature";
                std::cout << "-------------" << std::endl;
                std::cout << "Card Name: " << cardName << std::endl;
                std::cout << "Mana cost: " << manaCost << std::endl;
                std::cout << "Effect: " << sEffect << std::endl;
            }
            else  if (cardName == "Rage") {
                manaCost = 1;
                eEffect = "1 Target creature gains Trample ";
                std::cout << "-------------" << std::endl;
                std::cout << "Card Name: " << cardName << std::endl;
                std::cout << "Mana cost: " << manaCost << std::endl;
                std::cout << "Effect: " << eEffect << std::endl;
            }
            else if (cardName == "Holy War") {
                manaCost = 2;
                eEffect = "All white creatures gain +1/+1";
                std::cout << "-------------" << std::endl;
                std::cout << "Card Name: " << cardName << std::endl;
                std::cout << "Mana cost: " << manaCost << std::endl;
                std::cout << "Effect: " << eEffect << std::endl;
            }
            else if (cardName == "Holy Light") {
                manaCost = 1;
                eEffect = "All black creatures gain 1/1";
                std::cout << "-------------" << std::endl;
                std::cout << "Card Name: " << cardName << std::endl;
                std::cout << "Mana cost: " << manaCost << std::endl;
                std::cout << "Effect: " << eEffect << std::endl;
            }
            else if (cardName == "Unholy War") {
                manaCost = 2;
                eEffect = "All black creatures gain +2/+0";
                std::cout << "-------------" << std::endl;
                std::cout << "Card Name: " << cardName << std::endl;
                std::cout << "Mana cost: " << manaCost << std::endl;
                std::cout << "Effect: " << eEffect << std::endl;
            }
            else if (cardName == "Restrain") {
                manaCost = 3;
                eEffect = "All green creatures lose Trample";
                std::cout << "-------------" << std::endl;
                std::cout << "Card Name: " << cardName << std::endl;
                std::cout << "Mana cost: " << manaCost << std::endl;
                std::cout << "Effect: " << eEffect << std::endl;
            }
            else if (cardName == "Slow") {
                manaCost = 1;
                eEffect = "1 Target creature loses First Strike";
                std::cout << "-------------" << std::endl;
                std::cout << "Card Name: " << cardName << std::endl;
                std::cout << "Mana cost: " << manaCost << std::endl;
                std::cout << "Effect: " << eEffect << std::endl;
            }
            else  if (cardName == "Soldier") {
                manaCost = 1;
                creatureAtk = 1;
                creatureHp = 1;
                std::cout << "-------------" << std::endl;
                std::cout << "Card Name: " << cardName << std::endl;
                std::cout << "Mana cost: " << manaCost << std::endl;
                std::cout << "Effect: " << eEffect << std::endl;
            }
            else if (cardName == "Armored Pegasus") {
                manaCost = 2;
                creatureAtk = 1;
                creatureHp = 2;
                std::cout << "-------------" << std::endl;
                std::cout << "Card Name: " << cardName << std::endl;
                std::cout << "Mana cost: " << manaCost << std::endl;
                std::cout << "Effect: " << eEffect << std::endl;
            }
            else if (cardName == "White Knight") {
                manaCost = 2;
                creatureAtk = 2;
                creatureHp = 2;
                std::cout << "-------------" << std::endl;
                std::cout << "Card Name: " << cardName << std::endl;
                std::cout << "Mana cost: " << manaCost << std::endl;
                std::cout << "Effect: " << eEffect << std::endl;
            }
            else if (cardName == "Angry Bear") {
                manaCost = 3;
                creatureAtk = 3;
                creatureHp = 2;
                std::cout << "-------------" << std::endl;
                std::cout << "Card Name: " << cardName << std::endl;
                std::cout << "Mana cost: " << manaCost << std::endl;
                std::cout << "Effect: " << eEffect << std::endl;
            }
            else if (cardName == "Guard") {
                manaCost = 4;
                creatureAtk = 2;
                creatureHp = 5;
                std::cout << "-------------" << std::endl;
                std::cout << "Card Name: " << cardName << std::endl;
                std::cout << "Mana cost: " << manaCost << std::endl;
                std::cout << "Effect: " << eEffect << std::endl;

            }
            else if (cardName == "Werewolf") {
                manaCost = 4;
                creatureAtk = 4;
                creatureHp = 6;
                std::cout << "-------------" << std::endl;
                std::cout << "Card Name: " << cardName << std::endl;
                std::cout << "Mana cost: " << manaCost << std::endl;
                std::cout << "Effect: " << eEffect << std::endl;
            }
            else if (cardName == "Skeleton") {
                manaCost = 1;
                creatureAtk = 1;
                creatureHp = 1;
                std::cout << "-------------" << std::endl;
                std::cout << "Card Name: " << cardName << std::endl;
                std::cout << "Mana cost: " << manaCost << std::endl;
                std::cout << "Effect: " << eEffect << std::endl;
            }
            else if (cardName == "Ghost") {
                manaCost = 2;
                creatureAtk = 2;
                creatureHp = 1;
                std::cout << "-------------" << std::endl;
                std::cout << "Card Name: " << cardName << std::endl;
                std::cout << "Mana cost: " << manaCost << std::endl;
                std::cout << "Effect: " << eEffect << std::endl;
            }
            else if (cardName == "Black Knight") {
                manaCost = 2;
                creatureAtk = 2;
                creatureHp = 2;
                std::cout << "-------------" << std::endl;
                std::cout << "Card Name: " << cardName << std::endl;
                std::cout << "Mana cost: " << manaCost << std::endl;
                std::cout << "Effect: " << eEffect << std::endl;

            }
            else if (cardName == "Orc Maniac") {
                manaCost = 3;
                creatureAtk = 4;
                creatureHp = 1;
                std::cout << "-------------" << std::endl;
                std::cout << "Card Name: " << cardName << std::endl;
                std::cout << "Mana cost: " << manaCost << std::endl;
                std::cout << "Effect: " << eEffect << std::endl;

            }
            else if (cardName == "Hobgoblin") {
                manaCost = 3;
                creatureAtk = 3;
                creatureHp = 3;
                std::cout << "-------------" << std::endl;
                std::cout << "Card Name: " << cardName << std::endl;
                std::cout << "Mana cost: " << manaCost << std::endl;
                std::cout << "Effect: " << eEffect << std::endl;

            }
            else if (cardName == "Vampire") {
                manaCost = 4;
                creatureAtk = 6;
                creatureHp = 3;
                std::cout << "-------------" << std::endl;
                std::cout << "Card Name: " << cardName << std::endl;
                std::cout << "Mana cost: " << manaCost << std::endl;
                std::cout << "Effect: " << eEffect << std::endl;
            }

            else {
                continue;
            }
        }
    }
    void Instructions() {
        std::cout << "Welcome to team 12 MTG-simulation >THE PROJECT<" << std::endl;
        std::cout << "\n";
        std::cout << "To select any card that is in your hand just type the number of the card according to the way the cards are displayed." << std::endl;
        std::cout << "\n";
        std::cout << "To end you're turn please type -Y-." << std::endl;
        std::cout << "\n";
        std::cout << "Please type -START- to start the game." << std::endl;
        std::string start;
        std::cin >> start;
        if (start != "START") {
            std::cout << "Please type it correctly -START-." << std::endl;
            std::cin >> start;
        }
        std::cout << "Good luck and Enjoy the game." << std::endl;
        std::cout << " " << std::endl;
        std::cout << " " << std::endl;
        std::cout << " " << std::endl;
    }
    void play(std::vector<std::string> play) {
        int currentMana = 0;
        for (std::string cardName : play) {
            if (cardName == "Forest") {
                currentMana = currentMana + manaPoint;
                manaPoint = 1;
            }
            else if (cardName == "Island") {
                currentMana = currentMana + manaPoint;
                manaPoint = 1;
            }
            else if (cardName == "Mountain") {
                currentMana = currentMana + manaPoint;
                manaPoint = 1;
            }
            else if (cardName == "Plains") {
                currentMana = currentMana + manaPoint;
                manaPoint = 1;
            }
            else if (cardName == "Swamp") {
                currentMana = currentMana + manaPoint;
                manaPoint = 1;
            }
            else if (cardName == "Soldier") {
                currentMana = currentMana - manaCost;
                manaCost = 1;
                creatureAtk = 1;
                creatureHp = 1;
            }
            else if (cardName == "Armored Pegasus") {
                currentMana = currentMana - manaCost;
                manaCost = 2;
                creatureAtk = 1;
                creatureHp = 2;
            }
            else if (cardName == "White Knight") {
                currentMana = currentMana - manaCost;
                manaCost = 2;
                creatureAtk = 2;
                creatureHp = 2;
            }
            else if (cardName == "Angry Bear") {
                currentMana = currentMana - manaCost;
                manaCost = 3;
                creatureAtk = 3;
                creatureHp = 2;
            }
            else if (cardName == "Guard") {
                currentMana = currentMana - manaCost;
                manaCost = 4;
                creatureAtk = 2;
                creatureHp = 5;

            }
            else if (cardName == "Werewolf") {
                currentMana = currentMana - manaCost;
                manaCost = 4;
                creatureAtk = 4;
                creatureHp = 6;
            }
            else if (cardName == "Skeleton") {
                currentMana = currentMana - manaCost;
                manaCost = 1;
                creatureAtk = 1;
                creatureHp = 1;
            }
            else if (cardName == "Ghost") {
                currentMana = currentMana - manaCost;
                manaCost = 2;
                creatureAtk = 2;
                creatureHp = 1;
            }
            else if (cardName == "Black Knight") {
                currentMana = currentMana - manaCost;
                manaCost = 2;
                creatureAtk = 2;
                creatureHp = 2;

            }
            else if (cardName == "Orc Maniac") {
                currentMana = currentMana - manaCost;
                manaCost = 3;
                creatureAtk = 4;
                creatureHp = 1;

            }
            else if (cardName == "Hobgoblin") {
                currentMana = currentMana - manaCost;
                manaCost = 3;
                creatureAtk = 3;
                creatureHp = 3;

            }
            else if (cardName == "Vampire") {
                currentMana = currentMana - manaCost;
                manaCost = 4;
                creatureAtk = 6;
                creatureHp = 3;
            }
            else if (cardName == "Disenchant") {
                currentMana = currentMana - manaCost;
                manaCost = 2;
            }
            else if (cardName == "Lightning Bolt") {
                currentMana = currentMana - manaCost;
                manaCost = 2;
            }
            else if (cardName == "Flood") {
                currentMana = currentMana - manaCost;
                manaCost = 1;
            }
            else if (cardName == "Reanimate1") {
                currentMana = currentMana - manaCost;
                manaCost = 1;
            }
            else if (cardName == "Plague") {
                currentMana = currentMana - manaCost;
                manaCost = 2;
            }
            else if (cardName == "Terror") {
                currentMana = currentMana - manaCost;
                manaCost = 2;
            }
            else  if (cardName == "Rage") {
                currentMana = currentMana - manaCost;
                manaCost = 1;
            }
            else if (cardName == "Holy War") {
                currentMana = currentMana - manaCost;
                manaCost = 2;
            }
            else if (cardName == "Holy Light") {
                currentMana = currentMana - manaCost;
                manaCost = 1;
            }
            else if (cardName == "Unholy War") {
                currentMana = currentMana - manaCost;
                manaCost = 2;
            }
            else if (cardName == "Restrain") {
                currentMana = currentMana - manaCost;
                manaCost = 3;
            }
            else if (cardName == "Slow") {
                currentMana = currentMana - manaCost;
                manaCost = 1;
            }
            else {
                continue;
            }
        }
        std::cout << "Current mana: " << currentMana << std::endl;
    }






};

class effects {
protected:
    int destroyCard;
    int attack;
    int creatureHp;
    int playerHp;
public:
    effects() : destroyCard(0), attack(0), creatureHp(0), playerHp(15) {

    }
    effects(int destroy, int atk, int cHp, int pHp) : destroyCard(destroy), attack(atk), creatureHp(cHp), playerHp(pHp) {

    }
    effects(const effects& e) {
        destroyCard = e.destroyCard;
        attack = e.attack;
        creatureHp = e.creatureHp;
        playerHp = e.playerHp;
    }
    ~effects() {

    }

    void destroyOneCard(bool discard, std::string cardName) {
        if (destroyCard > 0) {
            discard = true;
        }
        else {
            discard = false;
        }
    }

    void attackCard(int atkDmg) {
        creatureHp = creatureHp - atkDmg;
        std::cout << "Creature took " << atkDmg << "." << std::endl;
    }

    void attackPlayer(int atkDmg) {
        playerHp = playerHp - atkDmg;
        std::cout << "Player took " << atkDmg << "." << std::endl;
    }

};

class destroyCreatureCardEffect : public effects {
protected:
    int creatureHp;

public:
    destroyCreatureCardEffect() : creatureHp(0) {

    }
    destroyCreatureCardEffect(int cHp, int destroyCreature, int atk, int pHp) : creatureHp(cHp), effects(destroyCreature, atk, cHp, pHp) {

    }

    void discardCreature(bool discard, std::string cardName) {
        if (creatureHp > 0) {
            std::cout << "Creature survived the attack." << std::endl;
            discard = false;
        }
        else if (cardName == "Terror") {
            discard = true;
        }
        else {
            discard = true;
            std::cout << "Creature died. The card moved to discard pile." << std::endl;
            destroyCard++;
        }
    }
};

class destroyLandCardEffect : public effects {
protected:
    int loseMana;

public:
    destroyLandCardEffect() : loseMana(0) {

    }
    destroyLandCardEffect(int numberOfLands, int destroyLand, std::string lands[], int atk, int cHp, int pHp) : loseMana(numberOfLands), effects(destroyLand, atk, cHp, pHp) {

    }

    void discardLand(std::string cardName, bool discard, std::vector<std::string> played) {
        cardinfo totalMana;
        loseMana = -1;
        if (cardName == "Flood") {
            std::cout << "One land card is destroyed." << std::endl;
            discard = true;
            destroyCard++;
            totalMana.play(played);

        }
        else {
            discard = false;
        }
    }
};

class destroyEnchantmentCardEffect : public effects {
protected:
    int loseEnchantmentCard;

public:
    destroyEnchantmentCardEffect() : loseEnchantmentCard(0) {

    }
    destroyEnchantmentCardEffect(int numberOfEnchantment, int destroyEnchantment, int atk, int cHp, int pHp) : loseEnchantmentCard(numberOfEnchantment), effects(destroyEnchantment, atk, cHp, pHp) {

    }

    void discardEnchantment(bool discard, std::string cardName) {
        enchantmentCard totalEnchantment;
        loseEnchantmentCard = -1;
        if (cardName == "Disenchant") {
            std::cout << "One enchantment card is destroyed." << std::endl;
            discard = true;
            destroyCard++;
            totalEnchantment.play(loseEnchantmentCard, discard);

        }
        else {
            discard = false;
        }
    }
};

class enchantmentEffects : public effects {
protected:
    std::string enchantment;

public:
    enchantmentEffects() :enchantment("none") {

    }
    enchantmentEffects(std::string enchant, int discard, int atk, int cHp, int pHp) :enchantment(enchant), effects(discard, atk, cHp, pHp) {

    }

    void allNoTrample(std::string cardName, std::shared_ptr<std::vector<creatureCard>> eC) {
        std::vector<creatureCard>::iterator ptr;
        for (ptr = eC->begin(); ptr < eC->end(); ptr++) {
            ptr->loseTrample(cardName);
        }
    }

    void upgradeHolyWar(int dmg, int hp, std::shared_ptr<std::vector<creatureCard>> eC2) {
        std::vector<creatureCard>::iterator ptr;
        for (ptr = eC2->begin(); ptr < eC2->end(); ptr++) {
            ptr->enchantHolyWar(dmg, hp);
        }
    }
    void upgradeHolyLight(int dmg, int hp, std::shared_ptr<std::vector<creatureCard>> eC2) {
        std::vector<creatureCard>::iterator ptr;
        for (ptr = eC2->begin(); ptr < eC2->end(); ptr++) {
            ptr->enchantHolyLight(dmg, hp);
        }
    }
    void upgradeUnholyWar(int dmg, std::shared_ptr<std::vector<creatureCard>> eC2) {
        std::vector<creatureCard>::iterator ptr;
        for (ptr = eC2->begin(); ptr < eC2->end(); ptr++) {
            ptr->enchantUnholyWar(dmg);
        }
    }

    void useEnchantment(std::string cardName, std::string creatureName, enchantmentEffects eF, creatureCard cC) {
        if (cardName == "Holy War") {
            std::shared_ptr<std::vector<creatureCard>> creatures = std::make_shared<std::vector<creatureCard>>();
            eF.upgradeHolyWar(1, 1, creatures);
            std::cout << "All creatures gained +1 attack and +1 health." << std::endl;
        }
        else if (cardName == "Holy Light") {
            std::shared_ptr<std::vector<creatureCard>> creatures = std::make_shared<std::vector<creatureCard>>();
            eF.upgradeHolyLight(-1, -1, creatures);
            std::cout << "All opponent's creatures lost -1 attack and -1 health." << std::endl;
        }
        else if (cardName == "Unholy War") {
            std::shared_ptr<std::vector<creatureCard>> creatures = std::make_shared<std::vector<creatureCard>>();
            eF.upgradeUnholyWar(2, creatures);
            std::cout << "All creatures gained +2 attack." << std::endl;
        }
        else if (cardName == "Restrain") {
            std::shared_ptr<std::vector<creatureCard>> creatures = std::make_shared<std::vector<creatureCard>>();
            eF.allNoTrample(creatureName, creatures);
            std::cout << "All creatures with First Strike ability lost their ability." << std::endl;
        }
        else if (cardName == "Slow") {
            cC.loseFirstStrike(creatureName);
            std::cout << creatureName << " lost First Strike." << std::endl;
        }
        else if (cardName == "Rage") {
            cC.gainTrample(creatureName);
            std::cout << creatureName << " gained Trample." << std::endl;
        }

    }


};

class sorceryEffects : public effects {
protected:
    std::string sorcery;
public:
    sorceryEffects() : sorcery("none") {

    }
    sorceryEffects(std::string useSorcery, int discard, int atk, int cHp, int pHp) : sorcery(useSorcery), effects(discard, atk, cHp, pHp) {

    }
    void dealOneDamage(int dmg, std::shared_ptr<std::vector<creatureCard>> sC) {
        std::vector<creatureCard>::iterator ptr;
        for (ptr = sC->begin(); ptr < sC->end(); ptr++) {
            ptr->creatureLoseHp(dmg);
        }
    }

    void useSorcery(std::string cardName, bool discard, destroyEnchantmentCardEffect dE, destroyCreatureCardEffect dC, destroyLandCardEffect dL, sorceryEffects sE) {
        if (cardName == "Disenchant") {
            std::cout << "Player used Disenchant. Destroyed one of the opponent's enchantment." << std::endl;
            destroyCard++;
            discard = true;
            dE.discardEnchantment(discard, cardName);
        }

        else if (cardName == "Lighting Bolt") {
            std::cout << "Player used Lighting Bolt. Dealt 2 damage." << std::endl;
            if (creatureHp > 0) {
                creatureHp = creatureHp - 2;
            }
            else {
                playerHp = playerHp - 2;
            }
        }

        else if (cardName == "Flood") {
            std::cout << "Player used Flood. Destroy one of the opponent's land." << std::endl;
            destroyCard++;
            discard = true;
            //dL.discardLand(discard, cardName);
        }

        else if (cardName == "Reanimate") {
            std::cout << "Player used Reanimate. Take one card from the discard pile." << std::endl;
            destroyCard--;
            discard = false;
        }

        else if (cardName == "Plague") {
            std::cout << "Player used Plague. All creatures take -1 damage." << std::endl;
            std::shared_ptr<std::vector<creatureCard>> creatures = std::make_shared<std::vector<creatureCard>>();
            sE.dealOneDamage(1, creatures);
        }

        else if (cardName == "Terror") {
            std::cout << "Player used Terror. Destroy one of the opponent's creature." << std::endl;
            creatureHp = 0;
            destroyCard++;
            discard = true;
            dC.discardCreature(discard, cardName);
        }
    }
};


class dealAttack : public effects {
protected:
    int damage;

public:
    dealAttack() : damage(0) {

    }
    dealAttack(int dmg, int cHp, int destroyCreature, int atk, int pHp) : damage(dmg), effects(destroyCreature, atk, cHp, pHp) {

    }
    void dealDamageTarget(std::vector<effects>::iterator targetCreature) {
        targetCreature->attackCard(damage);
    }

    void dealDmgPlayer(int* creatureDmg, effects e) {
        e.attackPlayer(*creatureDmg);
    }
};

class player {

protected:
    std::string player_name;
    int player_health;
    std::string player_state;

public:
    void set_name(std::string name) {
        player_name = name;
    }
    std::string get_name() {
        return player_name;
    }
    void set_health(int health) {
        player_health = health;
    }
    int get_health() {
        return player_health;
    }
    void set_state(std::string state) {
        player_state = state;
    }
    std::string get_state() {
        return player_state;
    }

    player(std::string name, int health, std::string state) {
        player_name = name;
        player_health = health;
        player_state = state;
    }

    std::vector<std::string> in_play;
    std::vector<std::string> discard;
    std::vector<std::string> library{ "Rage","Holy Light","Unholy Light","Restrain","Slow","Disenchant",
                                      "Lightning Bolt","Flood","Reanimate","Plague","terror","Soldier",
                                      "Armored Pegasus","White Knight","Angry Bear","Guard","Werewolf",
                                      "Skeleton","Ghost","Black Knight","Orc Maniac","Hobgoblin","Vampire",
                                      "Forest","Island","Mountain","Plains","swamp" };
    std::vector<std::string> hand{ 7,"" };

    void Drawcard(std::vector<std::string> lib) {
        if (hand.size() < 7) {
            copy_n(library.begin(), 1, hand.begin());
            library.erase(library.begin());
        }
        else if (hand.size() == 7) {
            std::cout << "You can't draw more cards." << std::endl;
        }
        else if (library.size() == 0) {
            std::cout << "Game over." << std::endl;
        }
    }
    void playercard() {
        cardinfo cI;
        std::string ans;
        bool endturn = true;
        std::cin >> ans;
        if (ans == "1") {
            in_play.push_back(hand[0]);
            hand.erase(hand.begin() + 0);
            //  cI.play(in_play);
              //cI.playCreature(in_play);
        }
        else if (ans == "2") {
            in_play.push_back(hand[1]);
            hand.erase(hand.begin() + 1);
            // cI.play(in_play);
             //cI.playCreature(in_play);
        }
        else if (ans == "3") {
            in_play.push_back(hand[2]);
            hand.erase(hand.begin() + 2);
            //    cI.play(in_play);
                //cI.playCreature(in_play);
        }
        else if (ans == "4") {
            in_play.push_back(hand[3]);
            hand.erase(hand.begin() + 3);
            //  cI.play(in_play);
              //cI.playCreature(in_play);
        }
        else if (ans == "5") {
            in_play.push_back(hand[4]);
            hand.erase(hand.begin() + 4);
            //  cI.play(in_play);
              //cI.playCreature(in_play);
        }
        else if (ans == "end") {
            std::cout << "PLease type end again to confirm" << std::endl;
        }

        else {
            std::cout << "Invalid entry!" << std::endl;
            std::cout << "Please type Either 1-2-3-4-5, or type -end- to end your turn" << std::endl;
            std::cin >> ans;
        }


    }
};

int main() {
    int x;
    bool endturn = true;
    std::string ans1;
    std::string ans;
    std::string name1;
    int health1 = 15;
    std::string name2;
    int health2 = 15;

    landCard L;

    player player1 = player(name1, health1, "something");
    player player2 = player(name2, health2, "something");

    cardinfo Instructions;
    Instructions.Instructions();
    std::cout << "player one's name:" << std::endl;
    std::cin >> name1;
    player1.set_name(name1);
    std::cout << "player two's name:" << std::endl;
    std::cin >> name2;
    player2.set_name(name2);
    while (name2 == name1) {
        std::cout << "You can't have the same name as player1" << std::endl;
        std::cin >> name2;
        player2.set_name(name2);
    }
    cardinfo playerinfo;
    player1.hand = { 7,"" };
    player2.hand = { 7,"" };
    player1.library = { "Plains","Plains","Plains","Plains","Plains","Forest","Forest",
                        "Forest","Island","Soldier","Soldier","Soldier","Armored Pegasus",
                        "Armored Pegasus","White Knight","White Knight","Angry Bear",
                        "Guard","Werewolf","Disenchant","Lightning Bolt","Flood","Flood",
                        "Rage","Holy War","Holy Light" };

    player2.library = { "Swamp","Swamp","Swamp","Swamp","Swamp","Mountain","Mountain",
                        "Mountain","Island","Skeleton","Skeleton","Skeleton","Ghost","Ghost",
                        "Black Knight","Black Knight","Orc Maniac","Hobgoblin","Vampire",
                        "Reanimate","Plague","Terror","Terror","Unholy War","Restrain",
                        "Slow" };
    player1.in_play;


    unsigned seed = std::chrono::system_clock::now()
        .time_since_epoch()
        .count();
    shuffle(player1.library.begin(), player1.library.end(), std::default_random_engine(seed));
    unsigned seed1 = std::chrono::system_clock::now()
        .time_since_epoch()
        .count();
    shuffle(player2.library.begin(), player2.library.end(), std::default_random_engine(seed1));
    //givecard1
    for (int i = 0; i < 4; i++) {
        player1.hand.push_back(player1.library[i]);
        player1.library.erase(player1.library.begin() + i);
    }
    //givecard2
    for (int i = 0; i < 4; i++) {
        player2.hand.push_back(player2.library[i]);
        player2.library.erase(player2.library.begin() + i);
    }
    while (player1.get_health() > 0 || player2.get_health() > 0) {
    label1:
        for (int i = 0; i < 1; i++) {
            player1.hand.push_back(player1.library[i]);
            player1.library.erase(player1.library.begin() + i);
        }
        std::cout << player1.get_name() << "'s current HP is: " << player1.get_health() << std::endl;
        playerinfo.play(player1.in_play);
        std::cout << player1.get_name() << "'s current cards in hand:\n";
        playerinfo.cinfo(player1.hand);
        std::cout << "-------------" << std::endl;
        std::cout << "Please choose what card you want to play [1-5], or type -end- to end you're turn." << std::endl;
        std::cout << "\n~~~~~In-Play~~~~~~~~~~~~~~~~~~~In-Play field for player1~\n" << std::endl;
        playerinfo.cinfo(player1.in_play);
        std::cout << "\n~~~~~In-Play~~~~~~~~~~~~~~~~~~~In-Play field for player1~\n" << std::endl;
        if (player1.hand.size() == 7) {
            std::cout << "You have reached your'e card limit." << std::endl;
        }
    label3:
        std::cout << "Choose a card to play" << std::endl;
        player1.playercard();
        std::cout << player1.get_name() << "'s current HP is: " << player1.get_health() << std::endl;
        playerinfo.play(player1.in_play);
        std::cout << player1.get_name() << "'s current cards in hand:\n";
        playerinfo.cinfo(player1.hand);
        std::cout << "-------------" << std::endl;
        std::cout << "Please choose what card you want to play [1-5], or type -end- to end you're turn." << std::endl;
        std::cout << "\n~~~~~In-Play~~~~~~~~~~~~~~~~~~~In-Play field for player1~\n" << std::endl;
        playerinfo.cinfo(player1.in_play);
        std::cout << "\n~~~~~In-Play~~~~~~~~~~~~~~~~~~~In-Play field for player1~\n" << std::endl;
        std::cout << "do you want to end your turn? press [Y/N]" << std::endl;
        std::cin >> ans1;
        if (ans1 == "Y") {

            goto label2;
        }
        else if (ans1 == "N") {
            goto label3;
        }
        else {
            goto label3;
        }

    label2:
        for (int i = 0; i < 1; i++) {
            player2.hand.push_back(player2.library[i]);
            player2.library.erase(player2.library.begin() + i);
        }
        std::cout << player2.get_name() << "'s current HP is: " << player2.get_health() << std::endl;
        playerinfo.play(player2.in_play);
        std::cout << player2.get_name() << "'s current cards in hand:\n";
        playerinfo.cinfo(player2.hand);
        std::cout << "-------------" << std::endl;
        std::cout << "Please choose what card you want to play [1-5], or type -end- to end you're turn." << std::endl;
        std::cout << "\n~~~~~In-Play~~~~~~~~~~~~~~~~~~~In-Play field for player2~\n" << std::endl;
        playerinfo.cinfo(player2.in_play);
        std::cout << "\n~~~~~In-Play~~~~~~~~~~~~~~~~~~~In-Play field for player2~\n" << std::endl;
    label4:
        std::cout << "Choose a card to play" << std::endl;
        player2.playercard();
        std::cout << player2.get_name() << "'s current HP is: " << player2.get_health() << std::endl;
        playerinfo.play(player2.in_play);
        std::cout << player2.get_name() << "'s current cards in hand:\n";
        playerinfo.cinfo(player2.hand);
        std::cout << "-------------" << std::endl;
        std::cout << "Please choose what card you want to play [1-5], or type -end- to end you're turn." << std::endl;
        std::cout << "\n~~~~~In-Play~~~~~~~~~~~~~~~~~~~In-Play field for player1~\n" << std::endl;
        playerinfo.cinfo(player2.in_play);
        std::cout << "\n~~~~~In-Play~~~~~~~~~~~~~~~~~~~In-Play field for player1~\n" << std::endl;
        std::cout << "do you want to end your turn? press [Y/N]" << std::endl;
        std::cin >> ans1;
        if (ans1 == "Y") {

            goto label1;
        }
        else if (ans1 == "N") {
            goto label4;
        }
        else {
            goto label4;
        }
    }
    return 0;
}