/*
 * Letter.hpp
 *
 *  Created on: Aug 18, 2009
 *      Author: alienjon
 */
#ifndef LETTER_HPP_
#define LETTER_HPP_

#include <string>

#include "../../Entities/Templates/EntityTemplate.hpp"
#include "../../Entities/Non-Creatures/Item.hpp"

class Player;

/*
 * @brief One of the letters the player can find for extra points.
 */
class Letter : public Item
{
    public:
    /**
     * @brief A default letter.
     * @param subject The subject of the letter.
     * @param message The letter's message.
     */
    Letter(const std::string& name, const EntityTemplate& tmpl, const std::string& subject, const std::string& message);

    /**
     * @brief Get the letter's subject.
     * @return The subject.
     */
    virtual const std::string& getSubject() const;

    /**
     * @brief Get the letter's message.
     * @return The message.
     */
    virtual const std::string& getMessage() const;

    /**
     * @brief Interact with the player.
     * @param player The player.
     */
    virtual void interact(Player* player);

    /**
     * @brief Convert the state of the entity to a string to save.
     * @return A string representation of the entity.
     */
    virtual std::string extract() const;

    private:
    /*
     * The subject and message.
     */
    std::string mSubject;
    std::string mMessage;
};

#endif /* LETTER_HPP_ */
