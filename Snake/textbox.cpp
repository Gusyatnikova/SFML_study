#include <sstream>

#include "textbox.h"

TextBox::TextBox() {
	Setup(5, 9, 200, { 0, 0 }, "../Source/TitilliumWeb-Regular.ttf");
}
//visibleCnt is number of visible lines int textBox
TextBox::TextBox(int visibleCnt, int charSize, int width, 
	sf::Vector2f screenPos, const std::string& fontPath) {
	Setup(visibleCnt, charSize, width, screenPos, fontPath);
}

TextBox::~TextBox() { Clear(); }

void TextBox::Setup(int visibleCnt, int charSize, int width,
	sf::Vector2f screenPos, const std::string& fontPath) {
	m_numVisible = visibleCnt;
	sf::Vector2f offset(0.0f, 0.0f);
	m_font.loadFromFile(fontPath);
	m_content.setFont(m_font);
	m_content.setString("");
	m_content.setCharacterSize(charSize);
	//m_content.setColor(sf::Color::White);
	m_content.setFillColor(sf::Color::Black);
	m_content.setPosition(screenPos + offset);
	m_backdrop.setSize({ width * 1.0f, visibleCnt * charSize * 1.2f });
	m_backdrop.setFillColor(sf::Color(90, 90, 90, 150));
	m_backdrop.setPosition(screenPos);
}

void TextBox::Add(const std::string& msg) {
	m_messages.push_back(msg);
	//if (m_messages.size() < m_numVisible) return;
	if (m_messages.size() < 6) return;
	m_messages.erase(m_messages.begin());
}

void TextBox::Clear() { m_messages.clear(); }

void TextBox::Render(sf::RenderWindow& window) {
	std::stringstream contentStream;
	for (const auto& it : m_messages) {
		contentStream << it << "\n";
	}
	//if (!contentStream.str().empty()) {
		m_content.setString(contentStream.str());
		window.draw(m_backdrop);
		window.draw(m_content);
	//}
}

