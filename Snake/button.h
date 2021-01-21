#pragma once
#include <string>
#include <SFML\Graphics.hpp>

class Button {
private:
	sf::Font m_font;
	sf::Text m_text;
	sf::Vector2f m_position;
protected:
	const sf::Text& GetText() const;
public:
	Button();
	virtual ~Button();
	sf::Vector2f GetPosition() const;
	sf::Text& GetText();
	void SetTextStyle(const sf::Text::Style &style);
	void SetTextLetterCpacing(float val);
	void SetTextOutlineThickness(float val);
	void SetCharacterSize(unsigned int size);
	void SetTextColor(sf::Color color);
	void SetFontFromFile(const std::string& filename);
	void SetFont(const sf::Font &f);
	virtual void SetOrigin(sf::Vector2f origin) = 0;
	virtual void SetPosition(sf::Vector2f pos) = 0;
	virtual void SetTextOrigin(sf::Vector2f origin) = 0;
	virtual void SetTextPosition(sf::Vector2f pos) = 0;
	void SetText(const std::string &text);
	virtual void Render(sf::RenderWindow * wnd) const = 0;
};

class RectButton : public Button {
private:
	sf::RectangleShape m_rect;
	sf::Color m_backgroundColor;
	sf::Texture* m_texture;
public:
	RectButton();
	~RectButton();
	sf::FloatRect GetLocalBounds() const;
	void CenterText();
	void SetOrigin(sf::Vector2f origin);
	void SetSize(sf::Vector2f size);
	void SetBackgroundColor(const sf::Color & color);
	void SetOutlineColor(const sf::Color &color);
	void SetOutlineThickness(float t);
	void SetPosition(sf::Vector2f pos);
	void SetTextOrigin(sf::Vector2f origin);
	void SetTextPosition(sf::Vector2f pos);
	void SetTexture(sf::Texture *texture);
	bool IsInside(int x_pos, int y_pos);
	void Render(sf::RenderWindow * wnd) const;
};