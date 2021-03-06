#include "snake.h"

Snake::Snake(int blockSize) {
	m_size = blockSize;
	m_lives = 3;
	m_bodyCircle.setRadius(1.0f * m_size / 2);
	Reset();
}

Snake::~Snake() {}

void Snake::Reset() {
	m_snake_body.clear();
	m_snake_body.push_back(SnakeSegment(15, 15));
	m_snake_body.push_back(SnakeSegment(14, 15));
	m_snake_body.push_back(SnakeSegment(13, 15));
	m_dir = Direction::NONE;
	m_speed = 12;
	//m_lives = 3;
	m_score = 0;
	m_lost = false;
}

void Snake::SetDirection(Direction dir) { m_dir = dir; }

Direction Snake::GetDirection() const { return m_dir; }

Direction Snake::GetPhisicalDirection() const {
	if (m_snake_body.size() < 2) { return Direction::NONE; }
	const SnakeSegment& head = m_snake_body[0];
	const SnakeSegment& neck = m_snake_body[1];
	if (head.position.x == neck.position.x) {
		return head.position.y > neck.position.y ? Direction::DOWN : Direction::UP;
	}
	else if (head.position.y == neck.position.y) {
		return head.position.x > neck.position.x ? Direction::RIGHT : Direction::LEFT;
	}
	return Direction::NONE;
}

int Snake::GetSpeed() const { return m_speed; }

sf::Vector2i Snake::GetPosition() const {
	return m_snake_body.empty() ? sf::Vector2i(1, 1) : m_snake_body.front().position;
}

int Snake::GetLives() const { return m_lives; }

int Snake::GetScore() const { return m_score; }

void Snake::IncreaseScore() { m_score += 10; }

bool Snake::HasLost() const { return m_lost; }

void Snake::Lose() { m_lost = true; --m_lives; }

void Snake::ToggleLost() { m_lost = !m_lost; }

void Snake::Extend() {
	if (m_snake_body.empty()) { return; }
	SnakeSegment& tail_head =
		m_snake_body[m_snake_body.size() - 1];

	if (m_snake_body.size() > 1) {
		SnakeSegment& tail_bone =
			m_snake_body[m_snake_body.size() - 2];

		if (tail_head.position.x == tail_bone.position.x) {
			if (tail_head.position.y > tail_bone.position.y) {
				m_snake_body.push_back(SnakeSegment(
					tail_head.position.x, tail_head.position.y + 1));
			}
			else {
				m_snake_body.push_back(SnakeSegment(
					tail_head.position.x, tail_head.position.y - 1));
			}
		}
		else if (tail_head.position.y == tail_bone.position.y) {
			if (tail_head.position.x > tail_bone.position.x) {
				m_snake_body.push_back(SnakeSegment(
					tail_head.position.x + 1, tail_head.position.y));
			}
			else {
				m_snake_body.push_back(SnakeSegment(
					tail_head.position.x - 1, tail_head.position.y));
			}
		}
	}
	else {
		if (m_dir == Direction::UP) {
			m_snake_body.push_back(SnakeSegment(
				tail_head.position.x, tail_head.position.y + 1));
		}
		else if (m_dir == Direction::DOWN) {
			m_snake_body.push_back(SnakeSegment(
				tail_head.position.x, tail_head.position.y - 1));
		}
		else if (m_dir == Direction::LEFT) {
			m_snake_body.push_back(SnakeSegment(
				tail_head.position.x + 1, tail_head.position.y));
		}
		else if (m_dir == Direction::RIGHT) {
			m_snake_body.push_back(SnakeSegment(
				tail_head.position.x - 1, tail_head.position.y));
		}
	}
}

void Snake::Tick() {
	//update, fixed-time
	if (m_snake_body.empty()) return;
	if (m_dir == Direction::NONE) return;
	Move();
	CheckCollsion();
}

void Snake::Move() {
	for (size_t i = m_snake_body.size() - 1; i > 0; --i) {
		m_snake_body[i].position = m_snake_body[i - 1].position;
	}
	switch (m_dir)
	{
	case Direction::UP:
		--m_snake_body[0].position.y;
		break;
	case Direction::DOWN:
		++m_snake_body[0].position.y;
		break;
	case Direction::LEFT:
		--m_snake_body[0].position.x;
		break;
	case Direction::RIGHT:
		++m_snake_body[0].position.x;
		break;
	default:
		break;
	}
}

void Snake::CheckCollsion() {
	if (m_snake_body.size() < 5) return;
	SnakeSegment& head = *m_snake_body.begin();
	for (auto it = std::next(m_snake_body.begin()); it != m_snake_body.end(); ++it) {
		if (it->position == head.position) {
			//int segments_cnt = m_snake_body.end() - it;
			//Cut(segments_cnt);
			m_dir = Direction::NONE;
			m_lost = true;
			break;
		}
	}
}

void Snake::Cut(int segments_cnt) {
	m_snake_body.erase(std::next(m_snake_body.begin(), segments_cnt), m_snake_body.end());
	--m_lives;
}

void Snake::Render(sf::RenderWindow& wnd) {
	if (m_snake_body.empty()) return;
	auto snake_head = m_snake_body.begin();
	m_bodyCircle.setFillColor(sf::Color::Yellow);
	m_bodyCircle.setPosition(
		snake_head->position.x * m_size,
		snake_head->position.y * m_size);
	wnd.draw(m_bodyCircle);
	m_bodyCircle.setFillColor(sf::Color::Green);
	for (auto it = m_snake_body.begin() + 1; it != m_snake_body.end(); ++it) {
		m_bodyCircle.setPosition(it->position.x * m_size, it->position.y * m_size);
		wnd.draw(m_bodyCircle);
	}
	
}

bool Snake::HasSegment(sf::Vector2i pos) const {
	for (auto &segment : m_snake_body) {
		if (segment.position.x == pos.x &&
			segment.position.y == pos.y) return true;
	}
	return false;
}
