#pragma once

namespace Engine {
	class State
	{
	public:
		State() {};
		~State() {};

		virtual void Init() = 0;
		virtual void ProcessInput() = 0;
		virtual void Update() = 0;
		virtual void Draw() = 0;

		virtual void Start() {}
		virtual void Pause() {}
	};
}
