#pragma once
namespace onodrim {
	class Core
	{
	public:
		Core();
		~Core();

		void Start();
		void GameLoop();
	private:
		void Update();
		void Render();
	};
}
