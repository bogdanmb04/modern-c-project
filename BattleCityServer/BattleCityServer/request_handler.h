#pragma once

#include "movement_request.h"
#include "player.h"

class RequestHandler {
public:
    void HandleMovementRequest(Player& player, MovementRequest request) {
        switch (request) {
        case MovementRequest::MoveUp:
            player.MoveUp();
            break;
        case MovementRequest::MoveDown:
            player.MoveDown();
            break;
        case MovementRequest::MoveLeft:
            player.MoveLeft();
            break;
        case MovementRequest::MoveRight:
            player.MoveRight();
            break;
        }
    }
};
