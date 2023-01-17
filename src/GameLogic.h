#pragma once

class GameLogic
{
public:
    GameLogic() = default;
    virtual ~GameLogic() = default;

    virtual void init(){};
    virtual void update(){};
    virtual void render(){};
    virtual void shutdown(){};
};
