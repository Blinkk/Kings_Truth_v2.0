#include "Player.h"
#include "Tile.h"
#include "Engine_Core.h"


Player::Player()
{
	// Default values
	isMoving = false;
	isAttacking = false;
	_goLeft = false;
	_goRight = false;
	_goUp = false;
	_goDown = false;
	_canGoLeft = true;
	_canGoRight = true;
	_canGoUp = true;
	_canGoDown = true;
	depth = 0;
	facingUp = true;
	facingLeft = false;
	tag = "Player";
	_health = 5;
	_speed = 2.0f;
	_animState = PLAYER_ANIM_STATES::IDLE;

	// Register with event system
	g_Engine->GetEventManager()->RegisterListener(this, Events::PLAYER_INPUT);
	g_Engine->GetEventManager()->RegisterListener(this, Events::PLAYER_DAMAGED);
	g_Engine->GetEventManager()->RegisterListener(this, Events::PLAYER_DEAD);

	// Initialize player rendering information
	Renderer.Initialize(1, 1, 16, 16, 16, 0, 0, 100, 1, 0, SCREENW / 2, SCREENH - (TILE_SIZE_Y * 2), "player.png");
	Renderer.SetAnimateFlag(true);

	// Initialize hitbox
	hitBox.Initialize(Renderer.GetPos().GetX(), Renderer.GetPos().GetY(), 
		Renderer.GetAdjustedWidth(), Renderer.GetAdjustedHeight());

	// Initialize inventory
	_playerInventory = &Inventory::GetInstance();
}


Player::~Player()
{
	// Purge event listeners
	g_Engine->GetEventManager()->PurgeListener(ID, Events::PLAYER_INPUT);
}


void Player::HandleEvent(IEvent *e)
{
	#pragma region Player_Input_Event
	if (e->Event_Type == Events::PLAYER_INPUT)
	{
		PlayerInputEvent *pTemp = static_cast<PlayerInputEvent*>(e);

		// If not moving and not attacking check for input
		if (!isMoving)
		{
			if (!isAttacking)
			{
				////////////////////////////////////
				// Handle the event and set flags
				////////////////////////////////////
				if (pTemp->up)
				{
					_moveStartPos = GetCurrentPos();

					// Set movement flags
					if (_canGoUp)
					{
						facingUp = true;
						isMoving = true;
						_goUp = true;
						_goDown = false;
						_goRight = false;
						_goLeft = false;
					}

					// Set animation frames
					if (_animState != PLAYER_ANIM_STATES::WALKING_UP)
					{
						//Renderer.SetCurrentFrame(2);
						//Renderer.SetStartFrame(2);
						//Renderer.SetEndFrame(3);
						Renderer.Initialize(16, 16, 2, 3, 100);
						_animState = PLAYER_ANIM_STATES::WALKING_UP;
					}

					// Set keypress value
					_lastKeyPress = KEY_PRESS::UP;
				}
				else if (pTemp->down)
				{
					_moveStartPos = GetCurrentPos();

					// Set movement flags
					if (_canGoDown)
					{
						facingUp = false;
						isMoving = true;
						_goUp = false;
						_goDown = true;
						_goRight = false;
						_goLeft = false;
					}

					// Set animation frames
					if (_animState != PLAYER_ANIM_STATES::WALKING_DOWN)
					{
						Renderer.SetCurrentFrame(0);
						Renderer.SetStartFrame(0);
						Renderer.SetEndFrame(1);
						_animState = PLAYER_ANIM_STATES::WALKING_DOWN;
					}

					// Set keypress value
					_lastKeyPress = KEY_PRESS::DOWN;
				}
				else if (pTemp->left)
				{
					_moveStartPos = GetCurrentPos();
					
					// Set movement flags
					if (_canGoLeft)
					{
						facingLeft = true;
						isMoving = true;
						_goUp = false;
						_goDown = false;
						_goLeft = true;
						_goRight = false;
					}

					// Set animation frames
					if (_animState != PLAYER_ANIM_STATES::WALKING_LEFT)
					{
						Renderer.SetCurrentFrame(6);
						Renderer.SetStartFrame(6);
						Renderer.SetEndFrame(7);
						_animState = PLAYER_ANIM_STATES::WALKING_LEFT;
					}

					// Set keypress value
					_lastKeyPress = KEY_PRESS::LEFT;
				}
				else if (pTemp->right)
				{
					_moveStartPos = GetCurrentPos();

					// Set movement flags
					if (_canGoRight)
					{
						facingLeft = false;
						isMoving = true;
						_goUp = false;
						_goDown = false;
						_goLeft = false;
						_goRight = true;
					}

					// Set animation frames
					if (_animState != PLAYER_ANIM_STATES::WALKING_RIGHT)
					{
						Renderer.SetCurrentFrame(4);
						Renderer.SetStartFrame(4);
						Renderer.SetEndFrame(5);
						_animState = PLAYER_ANIM_STATES::WALKING_RIGHT;
					}

					// Set keypress value
					_lastKeyPress = KEY_PRESS::RIGHT;
				}

				/////////// TEMPORARY ////////////
				else if (pTemp->attack)
				{
					PlayerDamagedEvent *pTempEvent = new PlayerDamagedEvent();
					if (pTempEvent) pTempEvent->damage = 1;
					g_Engine->GetEventManager()->DispatchEvent(pTempEvent);
				}
			}
		}
	}
#pragma endregion

	if (e->Event_Type == Events::PLAYER_DAMAGED)
	{
		// Cast to proper event
		PlayerDamagedEvent* pEvent = static_cast<PlayerDamagedEvent*>(e);

		if (pEvent)
		{
			// Decrement health based on damage
			_health -= pEvent->damage;
		}
	}
}


void Player::Update(float deltaTime)
{
	if (isMoving)
	{
		if (_goUp)
		{
			Renderer.ModifyY(-_speed);

			if (_moveStartPos.y - _currentPos.y >= TILE_SIZE_Y)
			{
				// Ensure that it stopped at the correct spot
				Renderer.SetY(_moveStartPos.y - TILE_SIZE_Y);
				isMoving = false;
			}
		}
		if (_goDown)
		{
			Renderer.ModifyY(_speed);

			if (_currentPos.y - _moveStartPos.y >= TILE_SIZE_Y)
			{
				// Ensure that it stopped at the correct spot
				Renderer.SetY(_moveStartPos.y + TILE_SIZE_Y);
				isMoving = false;
			}
		}
		if (_goLeft)
		{
			Renderer.ModifyX(-_speed);

			if (_moveStartPos.x - _currentPos.x >= TILE_SIZE_X)
			{
				// Ensure that it stopped at the correct spot
				Renderer.SetX(_moveStartPos.x - TILE_SIZE_X);
				isMoving = false;
			}
		}
		if (_goRight)
		{
			Renderer.ModifyX(_speed);

			if (_currentPos.x - _moveStartPos.x >= TILE_SIZE_X)
			{
				// Ensure that it stopped at the correct spot
				Renderer.SetX(_moveStartPos.x + TILE_SIZE_X);
				isMoving = false;
			}
		}
	}
	else
	{
		/////////////////////////////////////////
		// Set frame to idle in current position
		/////////////////////////////////////////
		switch (_lastKeyPress)
		{
		case KEY_PRESS::UP:
			Renderer.SetCurrentFrame(2);
			Renderer.SetStartFrame(2);
			Renderer.SetEndFrame(2);
			_animState = PLAYER_ANIM_STATES::IDLE;
			break;

		case KEY_PRESS::DOWN:
			Renderer.SetCurrentFrame(0);
			Renderer.SetStartFrame(0);
			Renderer.SetEndFrame(0);
			_animState = PLAYER_ANIM_STATES::IDLE;
			break;

		case KEY_PRESS::LEFT:
			Renderer.SetCurrentFrame(6);
			Renderer.SetStartFrame(6);
			Renderer.SetEndFrame(6);
			_animState = PLAYER_ANIM_STATES::IDLE;
			break;

		case KEY_PRESS::RIGHT:
			Renderer.SetCurrentFrame(4);
			Renderer.SetStartFrame(4);
			Renderer.SetEndFrame(4);
			_animState = PLAYER_ANIM_STATES::IDLE;
			break;

		default:
			debug << "\t_lastPress value out of range. Value = " <<
				_lastKeyPress << ", acceptable range is 0-3" << std::endl;
			break;
		}
	}
	Renderer.Update();

	// Update currentPos
	_currentPos = Renderer.GetPos();

	// Update hitbox
	hitBox.UpdateCollider(Renderer.GetPos().GetX(), Renderer.GetPos().GetY());

	// Keep play within boundaries
	KeepInBounds();
}


void Player::Render()
{
	if (Renderer.HasTexture())
		Renderer.Render();
}


void Player::SetIdle()
{
	Renderer.SetCurrentFrame(0);	// Revert to startFrame (can be changed)
}


void Player::KeepInBounds()
{
	// Right boundary
	if (hitBox.GetBoundingBox().right > SCREENW)
	{
		// Prevent the player from moving off the right side of the screen
		Renderer.ModifyX(-(hitBox.GetBoundingBox().right - SCREENW));
	}

	// Left boundary
	if (hitBox.GetBoundingBox().left < 0)
	{
		// Prevent the player from moving off the left side of the screen
		Renderer.ModifyX(-(hitBox.GetBoundingBox().left));
	}

	// Top boundary
	if (hitBox.GetBoundingBox().top < 0)
	{
		// Prevent the player from moving off the top of the screen
		Renderer.ModifyY(0 - hitBox.GetBoundingBox().top);
	}

	// Bottom boundary
	if (hitBox.GetBoundingBox().bottom > SCREENH)
	{
		// Prevent the player from moving off the bottom of the screen
		Renderer.ModifyY(-(hitBox.GetBoundingBox().bottom - SCREENH));
	}
}

/////////////////////////
// Utility Functions
/////////////////////////
void Player::SetMovementFlags(bool left, bool right, bool up, bool down)
{
	_canGoLeft = left;
	_canGoRight = right;
	_canGoUp = up;
	_canGoDown = down;
}


void Player::AddItemToInventory(IGameObject* item)
{
	// Check if inventory limit has been reached
	if (_playerInventory->GetNumItems() < _playerInventory->GetInventoryMax())
		_playerInventory->AddItem(item);
	else
		return;
}



/////////////////////////
// Accessors / Mutators
/////////////////////////
Vector2 Player::GetCurrentPos()
{
	return _currentPos;
}


RECT Player::GetHitbox()
{
	return Renderer.GetBoundingBox();
}
