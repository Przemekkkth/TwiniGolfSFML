#ifndef LABEL_H
#define LABEL_H

#include "component.h"
#include "../utils/resource_identifiers.h"
#include "../utils/resource_holder.h"

#include <SFML/Graphics/Text.hpp>


namespace GUI
{

class Label : public Component
{
    public:
        typedef std::shared_ptr<Label> Ptr;


    public:
                            Label(const std::string& text, const FontHolder& fonts);

        virtual bool		isSelectable() const;
        void				setText(const std::string& text);

        virtual void		handleEvent(const sf::Event& event);


    private:
        void				draw(sf::RenderTarget& target, sf::RenderStates states) const;


    private:
        sf::Text			mText;
};

}

#endif // LABEL_H
