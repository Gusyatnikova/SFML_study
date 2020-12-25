#pragma once

#include <vector>

#include "SFML//Graphics.hpp"

using MessageContainer = std::vector<std::string>;

class TextBox {
public:
	TextBox();
	TextBox(int visible, int charSize, int width, 
		sf::Vector2f screenPos, const std::string& fontPath);
	~TextBox();

	void Setup(int visible, int charSize, int width, 
		sf::Vector2f screenPos, const std::string& fontPath);
	void Add(const std::string& message);
	void Clear();

	void Render(sf::RenderWindow& wnd);
private:
	int m_numVisible;
	MessageContainer m_messages;
	sf::RectangleShape m_backdrop;
	std::string m_fontPath;
	sf::Font m_font;
	sf::Text m_content;
};
