#include "button.h"

//__________Button__________//

Button::Button() {}

Button::~Button() {}

sf::Vector2f Button::GetPosition() const { return m_position; }

const sf::Text& Button::GetText() const { return m_text; }

sf::Text& Button::GetText() { return m_text; }

void Button::SetFont(const sf::Font &f) { 
	m_text.setFont(f); 
}

void Button::SetTextStyle(const sf::Text::Style &style) {
	m_text.setStyle(style);
}

void Button::SetTextLetterCpacing(float val) {
	m_text.setLetterSpacing(val);
}

void Button::SetTextOutlineThickness(float val) { m_text.setOutlineThickness(val); }

void Button::SetTextColor(sf::Color color) { m_text.setFillColor(color); }

void Button::SetFontFromFile(const std::string &filename) { 
	m_font.loadFromFile(filename);
	m_text.setFont(m_font);
	
}

void Button::SetText(const std::string &text) { m_text.setString(sf::String(text)); }

void Button::SetCharacterSize(unsigned int size) { m_text.setCharacterSize(size); }

//__________RectButton__________//

RectButton::RectButton() {}

RectButton::~RectButton() {}

sf::FloatRect RectButton::GetLocalBounds() const { return m_rect.getLocalBounds(); }

void RectButton::CenterText() {
	//sf::Vector2f origin = GetText().getOrigin();
	sf::FloatRect text_rect = GetText().getLocalBounds();
	GetText().setOrigin(text_rect.left + text_rect.width / 2.0f,
		text_rect.top + text_rect.height / 2.0f);
	sf::Vector2f rect_origin = m_rect.getOrigin();
	GetText().setPosition(
		m_rect.getGlobalBounds().left + m_rect.getLocalBounds().width / 2.0f,
		m_rect.getGlobalBounds().top + m_rect.getLocalBounds().height / 2.0f);
	//GetText().setOrigin(origin);
}

void RectButton::SetOutlineColor(const sf::Color &color) {
	m_rect.setOutlineColor(color);
}

void RectButton::SetOutlineThickness(float t) {
	m_rect.setOutlineThickness(t);
}

void RectButton::SetOrigin(sf::Vector2f origin) { m_rect.setOrigin(origin); }

void RectButton::SetSize(sf::Vector2f size) { m_rect.setSize(size); }

void RectButton::SetBackgroundColor(const sf::Color & color) { m_rect.setFillColor(color); }

void RectButton::SetPosition(sf::Vector2f pos) { m_rect.setPosition(pos); }

void RectButton::SetTextOrigin(sf::Vector2f origin) {
	GetText().setOrigin(origin);
}

void RectButton::SetTextPosition(sf::Vector2f pos) {
	GetText().setPosition(pos);
}

void RectButton::SetTexture(sf::Texture *t) { 
	m_texture = t; 
	m_rect.setTexture(m_texture);
}

bool RectButton::IsInside(int x_pos, int y_pos) {
	sf::FloatRect global = m_rect.getGlobalBounds();
	return x_pos >= global.left && x_pos <= global.left + global.width &&
		y_pos >= global.top && y_pos <= global.top + global.height;
}

void RectButton::Render(sf::RenderWindow * window) const {
	std::string str = Button::GetText().getString();
	sf::Vector2f rect_pos = m_rect.getPosition();
	sf::Vector2f text_pos = Button::GetText().getPosition();
	
	window->draw(m_rect);
	window->draw(Button::GetText());
}