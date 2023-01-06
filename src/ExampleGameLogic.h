#pragma once

#include "GameLogic.h"

class ExampleGameLogic final : public GameLogic
{
public:
	void init() override;
	void update() override;
	void render() override;
	void shutdown() override;
};
