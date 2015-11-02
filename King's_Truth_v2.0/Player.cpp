#include "Player.h"
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
	_speed = 2.0f;
	_animState = IDLE;

	// Register with event system
	g_Engine->GetEventManager()->RegisterListener(this, Events::PLAYER_INPUT);

	// Initialize player rendering information
	Renderer.Initialize(1, 1, 16, 16, 16, 0, 0, 100, 1, 0, SCREENW / 2, SCREENH / 2, "player.png");
	Renderer.SetAnimateFlag(true);

	// Initialize hitbox
	hitBox.Initialize(Renderer.GetPos().GetX(), Renderer.GetPos().GetY(), 
		Renderer.GetAdjustedWidth(), Renderer.GetAdjustedHeight());
}


Player::~Player()
{
	// Purge event listeners
	g_Engine->GetEventManager()->PurgeListener(ID, Events::PLAYER_INPUT);
}


void Player::HandleEvent(IEvent *e)
{
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
					if (_animState != WALKING_UP)
					{
						Renderer.SetCurrentFrame(2);
						Renderer.SetStartFrame(2);
						Renderer.SetEndFrame(3);
						_animState = WALKING_UP;
					}

					// Set keypress value
					_lastKeyPress = UP;
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
					if (_animState != WALKING_DOWN)
					{
						Renderer.SetCurrentFrame(0);
						Renderer.SetStartFrame(0);
						Renderer.SetEndFrame(1);
						_animState = WALKING_DOWN;
					}

					// Set keypress value
					_lastKeyPress = DOWN;
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
					if (_animState != WALKING_LEFT)
					{
						Renderer.SetCurrentFrame(6);
						Renderer.SetStartFrame(6);
						Renderer.SetEndFrame(7);
						_animState = WALKING_LEFT;
					}

					// Set keypress value
					_lastKeyPress = LEFT;
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
					if (_animState != WALKING_RIGHT)
					{
						Renderer.SetCurrentFrame(4);
						Renderer.SetStartFrame(4);
						Renderer.SetEndFrame(5);
						_animState = WALKING_RIGHT;
					}

					// Set keypress value
					_lastKeyPress = RIGHT;
				}
			}
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

			if (_moveStartPos.y - _currentPos.y >= 16)
			{
				// Ensure that it stopped at the correct spot
				Renderer.SetY(_moveStartPos.y - 16);
				isMoving = false;
			}
		}
		if (_goDown)
		{
			Renderer.ModifyY(_speed);

			if (_currentPos.y - _moveStartPos.y >= 16)
			{
				// Ensure that it stopped at the correct spot
				Renderer.SetY(_moveStartPos.y + 16);
				isMoving = false;
			}
		}
		if (_goLeft)
		{
			Renderer.ModifyX(-_speed);

			if (_moveStartPos.x - _currentPos.x >= 16)
			{
				// Ensure that it stopped at the correct spot
				Renderer.SetX(_moveStartPos.x - 16);
				isMoving = false;
			}
		}
		if (_goRight)
		{
			Renderer.ModifyX(_speed);

			if (_currentPos.x - _moveStartPos.x >= 16)
			{
				// Ensure that it stopped at the correct spot
				Renderer.SetX(_moveStartPos.x + 16);
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
		case UP:
			Renderer.SetCurrentFrame(2);
			Renderer.SetStartFrame(2);
			Renderer.SetEndFrame(2);
			_animState = IDLE;
			break;

		case DOWN:
			Renderer.SetCurrentFrame(0);
			Renderer.SetStartFrame(0);
			Renderer.SetEndFrame(0);
			_animState = IDLE;
			break;

		case LEFT:
			Renderer.SetCurrentFrame(6);
			Renderer.SetStartFrame(6);
			Renderer.SetEndFrame(6);
			_animState = IDLE;
			break;

		case RIGHT:
			Renderer.SetCurrentFrame(4);
			Renderer.SetStartFrame(4);
			Renderer.SetEndFrame(4);
			_animState = IDLE;
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

//////////////////////
// Set movement flags
//////////////////////
void Player::SetMovementFlags(bool left, bool right, bool up, bool down)
{
	_canGoLeft = left;
	_canGoRight = right;
	_canGoUp = up;
	_canGoDown = down;
}
