#pragma once


class ACubeTest_GameMode : public AGameMode
{
public:
	ACubeTest_GameMode();
	~ACubeTest_GameMode();

	void LevelChangeStart();

protected:
	void BeginPlay()override;
	void Tick(float _DeltaTime)override;

private:
	class ACubeTest_Player* Player;

};


