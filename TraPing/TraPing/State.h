#pragma once
#ifndef STATE_HPP
#define STATE_HPP

#include <SFML/System/Time.hpp>


namespace Engine
{
	class State
	{
	public:
		State() {};
		~State() {};

		virtual void Init() = 0;
		virtual void ProcessInput() = 0;
		virtual void Update(sf::Time deltaTime) = 0;
		virtual void Draw() = 0;

		//Method
		virtual void Pause() {};
		virtual void Start() {};
	};
} //Namespace Engine

#endif // STATE_HPP