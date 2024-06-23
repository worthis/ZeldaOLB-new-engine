#include "WindowManager.h"

#include <stdlib.h>
#include <string.h>

/*!
\brief Alpha adjustment table for custom blitter.
The table provides values for a modified, non-linear
transfer function which maintain brightness.
*/
const unsigned int GFX_ALPHA_ADJUST_ARRAY[256] = {
	0,	 /* 0 */
	15,	 /* 1 */
	22,	 /* 2 */
	27,	 /* 3 */
	31,	 /* 4 */
	35,	 /* 5 */
	39,	 /* 6 */
	42,	 /* 7 */
	45,	 /* 8 */
	47,	 /* 9 */
	50,	 /* 10 */
	52,	 /* 11 */
	55,	 /* 12 */
	57,	 /* 13 */
	59,	 /* 14 */
	61,	 /* 15 */
	63,	 /* 16 */
	65,	 /* 17 */
	67,	 /* 18 */
	69,	 /* 19 */
	71,	 /* 20 */
	73,	 /* 21 */
	74,	 /* 22 */
	76,	 /* 23 */
	78,	 /* 24 */
	79,	 /* 25 */
	81,	 /* 26 */
	82,	 /* 27 */
	84,	 /* 28 */
	85,	 /* 29 */
	87,	 /* 30 */
	88,	 /* 31 */
	90,	 /* 32 */
	91,	 /* 33 */
	93,	 /* 34 */
	94,	 /* 35 */
	95,	 /* 36 */
	97,	 /* 37 */
	98,	 /* 38 */
	99,	 /* 39 */
	100, /* 40 */
	102, /* 41 */
	103, /* 42 */
	104, /* 43 */
	105, /* 44 */
	107, /* 45 */
	108, /* 46 */
	109, /* 47 */
	110, /* 48 */
	111, /* 49 */
	112, /* 50 */
	114, /* 51 */
	115, /* 52 */
	116, /* 53 */
	117, /* 54 */
	118, /* 55 */
	119, /* 56 */
	120, /* 57 */
	121, /* 58 */
	122, /* 59 */
	123, /* 60 */
	124, /* 61 */
	125, /* 62 */
	126, /* 63 */
	127, /* 64 */
	128, /* 65 */
	129, /* 66 */
	130, /* 67 */
	131, /* 68 */
	132, /* 69 */
	133, /* 70 */
	134, /* 71 */
	135, /* 72 */
	136, /* 73 */
	137, /* 74 */
	138, /* 75 */
	139, /* 76 */
	140, /* 77 */
	141, /* 78 */
	141, /* 79 */
	142, /* 80 */
	143, /* 81 */
	144, /* 82 */
	145, /* 83 */
	146, /* 84 */
	147, /* 85 */
	148, /* 86 */
	148, /* 87 */
	149, /* 88 */
	150, /* 89 */
	151, /* 90 */
	152, /* 91 */
	153, /* 92 */
	153, /* 93 */
	154, /* 94 */
	155, /* 95 */
	156, /* 96 */
	157, /* 97 */
	158, /* 98 */
	158, /* 99 */
	159, /* 100 */
	160, /* 101 */
	161, /* 102 */
	162, /* 103 */
	162, /* 104 */
	163, /* 105 */
	164, /* 106 */
	165, /* 107 */
	165, /* 108 */
	166, /* 109 */
	167, /* 110 */
	168, /* 111 */
	168, /* 112 */
	169, /* 113 */
	170, /* 114 */
	171, /* 115 */
	171, /* 116 */
	172, /* 117 */
	173, /* 118 */
	174, /* 119 */
	174, /* 120 */
	175, /* 121 */
	176, /* 122 */
	177, /* 123 */
	177, /* 124 */
	178, /* 125 */
	179, /* 126 */
	179, /* 127 */
	180, /* 128 */
	181, /* 129 */
	182, /* 130 */
	182, /* 131 */
	183, /* 132 */
	184, /* 133 */
	184, /* 134 */
	185, /* 135 */
	186, /* 136 */
	186, /* 137 */
	187, /* 138 */
	188, /* 139 */
	188, /* 140 */
	189, /* 141 */
	190, /* 142 */
	190, /* 143 */
	191, /* 144 */
	192, /* 145 */
	192, /* 146 */
	193, /* 147 */
	194, /* 148 */
	194, /* 149 */
	195, /* 150 */
	196, /* 151 */
	196, /* 152 */
	197, /* 153 */
	198, /* 154 */
	198, /* 155 */
	199, /* 156 */
	200, /* 157 */
	200, /* 158 */
	201, /* 159 */
	201, /* 160 */
	202, /* 161 */
	203, /* 162 */
	203, /* 163 */
	204, /* 164 */
	205, /* 165 */
	205, /* 166 */
	206, /* 167 */
	206, /* 168 */
	207, /* 169 */
	208, /* 170 */
	208, /* 171 */
	209, /* 172 */
	210, /* 173 */
	210, /* 174 */
	211, /* 175 */
	211, /* 176 */
	212, /* 177 */
	213, /* 178 */
	213, /* 179 */
	214, /* 180 */
	214, /* 181 */
	215, /* 182 */
	216, /* 183 */
	216, /* 184 */
	217, /* 185 */
	217, /* 186 */
	218, /* 187 */
	218, /* 188 */
	219, /* 189 */
	220, /* 190 */
	220, /* 191 */
	221, /* 192 */
	221, /* 193 */
	222, /* 194 */
	222, /* 195 */
	223, /* 196 */
	224, /* 197 */
	224, /* 198 */
	225, /* 199 */
	225, /* 200 */
	226, /* 201 */
	226, /* 202 */
	227, /* 203 */
	228, /* 204 */
	228, /* 205 */
	229, /* 206 */
	229, /* 207 */
	230, /* 208 */
	230, /* 209 */
	231, /* 210 */
	231, /* 211 */
	232, /* 212 */
	233, /* 213 */
	233, /* 214 */
	234, /* 215 */
	234, /* 216 */
	235, /* 217 */
	235, /* 218 */
	236, /* 219 */
	236, /* 220 */
	237, /* 221 */
	237, /* 222 */
	238, /* 223 */
	238, /* 224 */
	239, /* 225 */
	240, /* 226 */
	240, /* 227 */
	241, /* 228 */
	241, /* 229 */
	242, /* 230 */
	242, /* 231 */
	243, /* 232 */
	243, /* 233 */
	244, /* 234 */
	244, /* 235 */
	245, /* 236 */
	245, /* 237 */
	246, /* 238 */
	246, /* 239 */
	247, /* 240 */
	247, /* 241 */
	248, /* 242 */
	248, /* 243 */
	249, /* 244 */
	249, /* 245 */
	250, /* 246 */
	250, /* 247 */
	251, /* 248 */
	251, /* 249 */
	252, /* 250 */
	252, /* 251 */
	253, /* 252 */
	253, /* 253 */
	254, /* 254 */
	255	 /* 255 */
};

WindowManager WindowManager::instance = WindowManager();

WindowManager::WindowManager() : fullScreen(FULLSCREEN), event(0), joystick(0), window(0), windowTmp(0), open(false)
{
	buttonA = false;
	buttonB = false;
	buttonX = false;
	buttonY = false;
	buttonStart = false;
	buttonSelect = false;
	buttonLB = false;
	buttonRB = false;
	buttonLS = false;
	buttonRS = false;
}

WindowManager::~WindowManager()
{
	delete event;
}

WindowManager *WindowManager::getInstance()
{
	return &instance;
}

int WindowManager::init()
{
	if (window == 0)
	{
		if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_JOYSTICK) == -1)
		{
			printf("Could not load SDL : %s\n", SDL_GetError());
			return -1;
		}

		// atexit(SDL_Quit);
	}
	return 0;
}

int WindowManager::createWindow(string title, string iconName, bool full)
{
	if (window == 0)
	{
		fullScreen = true;

		SDL_WM_SetCaption(title.c_str(), NULL);
		SDL_ShowCursor(fullScreen ? SDL_DISABLE : SDL_ENABLE);

		window = SDL_SetVideoMode(WINDOW_SIZE_W, WINDOW_SIZE_H, 32, SDL_HWSURFACE | SDL_DOUBLEBUF | SDL_FULLSCREEN);
		windowTmp = SDL_CreateRGBSurface(SDL_HWSURFACE, GAME_SIZE_W, GAME_SIZE_H, 32, 0, 0, 0, 0);

		event = new Event();
		lastAnimTime = SDL_GetTicks();
		open = true;

		joystick = SDL_JoystickOpen(0);
		SDL_JoystickEventState(SDL_QUERY);
	}
	return 0;
}

bool WindowManager::isOpened()
{
	return open;
}

void WindowManager::setFullScreen(bool b)
{
}

bool WindowManager::isFullScreen()
{
	return fullScreen;
}

Event *WindowManager::getEvent()
{

	const Uint8 *keys = SDL_GetKeyState(NULL);
	SDL_JoystickUpdate();

	if (joystick != 0)
	{
		if (SDL_NumJoysticks() == 0)
		{
			SDL_JoystickClose(joystick);
			joystick = 0;
		}
	}
	else
	{
		if (SDL_NumJoysticks() > 0)
		{
			joystick = SDL_JoystickOpen(0);
		}
	}

	int temp = SDL_GetModState();
	temp = temp & KMOD_CAPS;
	bool capslock = temp == KMOD_CAPS;

	event->update(keys, capslock);

	if (event->isPushed(RESIZE))
	{
		setFullScreen(!fullScreen);
	}

	SDL_Event sdlEvent;
	while (SDL_PollEvent(&sdlEvent))
	{
		switch (sdlEvent.type)
		{
		case SDL_QUIT:
			event->setEvent(QUIT, true);
			break;
		case SDL_MOUSEBUTTONDOWN:
			event->setMouseX(sdlEvent.button.x);
			event->setMouseY(sdlEvent.button.y);
			event->setEvent(mouseDown, true);
			break;
		case SDL_MOUSEBUTTONUP:
			event->setMouseX(sdlEvent.button.x);
			event->setMouseY(sdlEvent.button.y);
			event->setEvent(mouseUp, true);
			break;
		case SDL_MOUSEMOTION:
			event->setMouseX(sdlEvent.button.x);
			event->setMouseY(sdlEvent.button.y);
			break;
		case SDL_JOYBUTTONDOWN:
			if (sdlEvent.jbutton.button == 0)
				buttonA = true;
			else if (sdlEvent.jbutton.button == 1)
				buttonB = true;
			else if (sdlEvent.jbutton.button == 2)
				buttonX = true;
			else if (sdlEvent.jbutton.button == 3)
				buttonY = true;
			else if (sdlEvent.jbutton.button == 4)
				buttonLB = true;
			else if (sdlEvent.jbutton.button == 5)
				buttonRB = true;
			else if (sdlEvent.jbutton.button == 6)
				buttonSelect = true;
			else if (sdlEvent.jbutton.button == 7)
				buttonStart = true;
			else if (sdlEvent.jbutton.button == 8)
				buttonLS = true;
			else if (sdlEvent.jbutton.button == 9)
				buttonRS = true;
			break;
		case SDL_JOYBUTTONUP:
			if (sdlEvent.jbutton.button == 0)
				buttonA = false;
			else if (sdlEvent.jbutton.button == 1)
				buttonB = false;
			else if (sdlEvent.jbutton.button == 2)
				buttonX = false;
			else if (sdlEvent.jbutton.button == 3)
				buttonY = false;
			else if (sdlEvent.jbutton.button == 4)
				buttonLB = false;
			else if (sdlEvent.jbutton.button == 5)
				buttonRB = false;
			else if (sdlEvent.jbutton.button == 6)
				buttonSelect = false;
			else if (sdlEvent.jbutton.button == 7)
				buttonStart = false;
			else if (sdlEvent.jbutton.button == 8)
				buttonLS = false;
			else if (sdlEvent.jbutton.button == 9)
				buttonRS = false;
			break;
		}
	}

	if (joystick != 0)
	{
		if (buttonA)
			event->setEvent(jA, true);
		if (buttonB)
			event->setEvent(jB, true);
		if (buttonX)
			event->setEvent(jX, true);
		if (buttonY)
			event->setEvent(jY, true);
		if (buttonLB)
			event->setEvent(jLB, true);
		if (buttonRB)
			event->setEvent(jRB, true);
		if (buttonSelect)
			event->setEvent(jSelect, true);
		if (buttonStart)
			event->setEvent(jStart, true);
		if (buttonLS)
			event->setEvent(jLS, true);
		if (buttonRS)
			event->setEvent(jRS, true);

		// hats
		Uint8 hats = SDL_JoystickGetHat(joystick, 0);
		if (hats & SDL_HAT_UP)
			event->setEvent(jUp, true);
		if (hats & SDL_HAT_DOWN)
			event->setEvent(jDown, true);
		if (hats & SDL_HAT_LEFT)
			event->setEvent(jLeft, true);
		if (hats & SDL_HAT_RIGHT)
			event->setEvent(jRight, true);

		int lx = SDL_JoystickGetAxis(joystick, 0);
		int ly = SDL_JoystickGetAxis(joystick, 1);
		int lt = SDL_JoystickGetAxis(joystick, 2);
		int rx = SDL_JoystickGetAxis(joystick, 3);
		int ry = SDL_JoystickGetAxis(joystick, 4);
		int rt = SDL_JoystickGetAxis(joystick, 5);

		// left stick
		if (abs(lx) < 8000)
			lx = 0;
		if (abs(ly) < 8000)
			ly = 0;
		if (lx != 0 || ly != 0)
		{
			double dist = sqrt(lx * lx + ly * ly);
			double cos = lx / dist;
			double angle = (ly <= 0) ? acos(cos) : -acos(cos);
			if (angle < 0)
				angle += 2 * PI;
			int cas = ((int)((1 + (angle / (PI / 8))) / 2)) % 8;

			switch (cas)
			{
			case 0:
				event->setEvent(jLRight, true);
				break;
			case 1:
				event->setEvent(jLRight, true);
				event->setEvent(jLUp, true);
				break;
			case 2:
				event->setEvent(jLUp, true);
				break;
			case 3:
				event->setEvent(jLLeft, true);
				event->setEvent(jLUp, true);
				break;
			case 4:
				event->setEvent(jLLeft, true);
				break;
			case 5:
				event->setEvent(jLLeft, true);
				event->setEvent(jLDown, true);
				break;
			case 6:
				event->setEvent(jLDown, true);
				break;
			case 7:
				event->setEvent(jLRight, true);
				event->setEvent(jLDown, true);
				break;
			default:
				break;
			}
		}

		// right stick
		if (abs(rx) < 8000)
			rx = 0;
		if (abs(ry) < 8000)
			ry = 0;
		if (rx != 0 || ry != 0)
		{
			double dist = sqrt(rx * rx + ry * ry);
			double cos = rx / dist;
			double angle = (ry <= 0) ? acos(cos) : -acos(cos);
			if (angle < 0)
				angle += 2 * PI;
			int cas = ((int)((1 + (angle / (PI / 8))) / 2)) % 8;

			switch (cas)
			{
			case 0:
				event->setEvent(jRRight, true);
				break;
			case 1:
				event->setEvent(jRRight, true);
				event->setEvent(jRUp, true);
				break;
			case 2:
				event->setEvent(jRUp, true);
				break;
			case 3:
				event->setEvent(jRLeft, true);
				event->setEvent(jRUp, true);
				break;
			case 4:
				event->setEvent(jRLeft, true);
				break;
			case 5:
				event->setEvent(jRLeft, true);
				event->setEvent(jRDown, true);
				break;
			case 6:
				event->setEvent(jRDown, true);
				break;
			case 7:
				event->setEvent(jRRight, true);
				event->setEvent(jRDown, true);
				break;
			default:
				break;
			}
		}

		// lt
		if (lt > 0)
		{
			event->setEvent(jLT, true);
		}

		// rt
		if (rt > 0)
		{
			event->setEvent(jRT, true);
		}
	}

	return event;
}

void WindowManager::close()
{
	open = false;
}

void WindowManager::display()
{
	SDL_Surface *tmp = zoomSurface(windowTmp, 2, 2, 0);
	SDL_BlitSurface(tmp, NULL, window, NULL);
	SDL_FreeSurface(tmp);

	SDL_Flip(window);

	if (SDL_GetTicks() < lastAnimTime + (1000 / 60))
		SDL_Delay(lastAnimTime + (1000 / 60) - SDL_GetTicks());
	lastAnimTime = SDL_GetTicks();
}

void WindowManager::draw(SDL_Surface *object)
{
	SDL_BlitSurface(object, NULL, windowTmp, NULL);
}

void WindowManager::draw(WImage *image, int srcX, int srcY, int srcW, int srcH, int dstX, int dstY, int alpha)
{
	SDL_Rect src = {srcX, srcY, srcW, srcH};
	SDL_Rect dst = {dstX, dstY, srcW, srcH};
	SDL_BlitSurface(image->getImage(), &src, windowTmp, &dst);
}

void WindowManager::draw(SDL_Surface *object, int srcX, int srcY, int srcW, int srcH, int dstX, int dstY, int alpha)
{
	SDL_Rect src = {srcX, srcY, srcW, srcH};
	SDL_Rect dst = {dstX, dstY, srcW, srcH};
	SDL_BlitSurface(object, &src, windowTmp, &dst);
}

void WindowManager::exit()
{
	if (SDL_JoystickOpened(0))
	{
		SDL_JoystickClose(joystick);
	}
	SDL_FreeSurface(windowTmp);
	SDL_ShowCursor(SDL_ENABLE);
	SDL_Quit();
}

int WindowManager::nbJoysticks()
{
	return SDL_NumJoysticks();
}

int WindowManager::filledEllipseRGBA(SDL_Surface *dst, Sint16 x, Sint16 y, Sint16 rx, Sint16 ry, Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
	return (filledEllipseColor(dst, x, y, rx, ry, ((Uint32)r << 24) | ((Uint32)g << 16) | ((Uint32)b << 8) | (Uint32)a));
}

int WindowManager::filledEllipseColor(SDL_Surface *dst, Sint16 x, Sint16 y, Sint16 rx, Sint16 ry, Uint32 color)
{
	Sint16 left, right, top, bottom;
	int result;
	Sint16 x1, y1, x2, y2;
	int ix, iy;
	int h, i, j, k;
	int oh, oi, oj, ok;
	int xmh, xph;
	int xmi, xpi;
	int xmj, xpj;
	int xmk, xpk;

	if ((dst->clip_rect.w == 0) || (dst->clip_rect.h == 0))
	{
		return (0);
	}

	if ((rx < 0) || (ry < 0))
	{
		return (-1);
	}

	if (rx == 0)
	{
		return (vlineColor(dst, x, y - ry, y + ry, color));
	}
	if (ry == 0)
	{
		return (hlineColor(dst, x - rx, x + rx, y, color));
	}

	x2 = x + rx;
	left = dst->clip_rect.x;
	if (x2 < left)
	{
		return (0);
	}
	x1 = x - rx;
	right = dst->clip_rect.x + dst->clip_rect.w - 1;
	if (x1 > right)
	{
		return (0);
	}
	y2 = y + ry;
	top = dst->clip_rect.y;
	if (y2 < top)
	{
		return (0);
	}
	y1 = y - ry;
	bottom = dst->clip_rect.y + dst->clip_rect.h - 1;
	if (y1 > bottom)
	{
		return (0);
	}

	oh = oi = oj = ok = 0xFFFF;

	result = 0;
	if (rx > ry)
	{
		ix = 0;
		iy = rx * 64;

		do
		{
			h = (ix + 32) >> 6;
			i = (iy + 32) >> 6;
			j = (h * ry) / rx;
			k = (i * ry) / rx;

			if ((ok != k) && (oj != k))
			{
				xph = x + h;
				xmh = x - h;
				if (k > 0)
				{
					result |= hlineColor(dst, xmh, xph, y + k, color);
					result |= hlineColor(dst, xmh, xph, y - k, color);
				}
				else
				{
					result |= hlineColor(dst, xmh, xph, y, color);
				}
				ok = k;
			}
			if ((oj != j) && (ok != j) && (k != j))
			{
				xmi = x - i;
				xpi = x + i;
				if (j > 0)
				{
					result |= hlineColor(dst, xmi, xpi, y + j, color);
					result |= hlineColor(dst, xmi, xpi, y - j, color);
				}
				else
				{
					result |= hlineColor(dst, xmi, xpi, y, color);
				}
				oj = j;
			}

			ix = ix + iy / rx;
			iy = iy - ix / rx;

		} while (i > h);
	}
	else
	{
		ix = 0;
		iy = ry * 64;

		do
		{
			h = (ix + 32) >> 6;
			i = (iy + 32) >> 6;
			j = (h * rx) / ry;
			k = (i * rx) / ry;

			if ((oi != i) && (oh != i))
			{
				xmj = x - j;
				xpj = x + j;
				if (i > 0)
				{
					result |= hlineColor(dst, xmj, xpj, y + i, color);
					result |= hlineColor(dst, xmj, xpj, y - i, color);
				}
				else
				{
					result |= hlineColor(dst, xmj, xpj, y, color);
				}
				oi = i;
			}
			if ((oh != h) && (oi != h) && (i != h))
			{
				xmk = x - k;
				xpk = x + k;
				if (h > 0)
				{
					result |= hlineColor(dst, xmk, xpk, y + h, color);
					result |= hlineColor(dst, xmk, xpk, y - h, color);
				}
				else
				{
					result |= hlineColor(dst, xmk, xpk, y, color);
				}
				oh = h;
			}

			ix = ix + iy / ry;
			iy = iy - ix / ry;

		} while (i > h);
	}

	return (result);
}

int WindowManager::vlineColor(SDL_Surface *dst, Sint16 x, Sint16 y1, Sint16 y2, Uint32 color)
{
	Sint16 left, right, top, bottom;
	Uint8 *pixel, *pixellast;
	int dy;
	int pixx, pixy;
	Sint16 h;
	Sint16 ytmp;
	int result = -1;
	Uint8 *colorptr;

	if ((dst->clip_rect.w == 0) || (dst->clip_rect.h == 0))
	{
		return (0);
	}

	if (y1 > y2)
	{
		ytmp = y1;
		y1 = y2;
		y2 = ytmp;
	}

	left = dst->clip_rect.x;
	right = dst->clip_rect.x + dst->clip_rect.w - 1;
	if ((x < left) || (x > right))
	{
		return (0);
	}
	top = dst->clip_rect.y;
	if (y2 < top)
	{
		return (0);
	}
	bottom = dst->clip_rect.y + dst->clip_rect.h - 1;
	if (y1 > bottom)
	{
		return (0);
	}

	if (y1 < top)
	{
		y1 = top;
	}
	if (y2 > bottom)
	{
		y2 = bottom;
	}

	h = y2 - y1;

	if ((color & 255) == 255)
	{
		colorptr = (Uint8 *)&color;
		if (SDL_BYTEORDER == SDL_BIG_ENDIAN)
		{
			color = SDL_MapRGBA(dst->format, colorptr[0], colorptr[1], colorptr[2], colorptr[3]);
		}
		else
		{
			color = SDL_MapRGBA(dst->format, colorptr[3], colorptr[2], colorptr[1], colorptr[0]);
		}

		if (SDL_MUSTLOCK(dst))
		{
			if (SDL_LockSurface(dst) < 0)
			{
				return (-1);
			}
		}

		dy = h;
		pixx = dst->format->BytesPerPixel;
		pixy = dst->pitch;
		pixel = ((Uint8 *)dst->pixels) + pixx * (int)x + pixy * (int)y1;
		pixellast = pixel + pixy * dy;

		switch (dst->format->BytesPerPixel)
		{
		case 1:
			for (; pixel <= pixellast; pixel += pixy)
			{
				*(Uint8 *)pixel = color;
			}
			break;
		case 2:
			for (; pixel <= pixellast; pixel += pixy)
			{
				*(Uint16 *)pixel = color;
			}
			break;
		case 3:
			for (; pixel <= pixellast; pixel += pixy)
			{
				if (SDL_BYTEORDER == SDL_BIG_ENDIAN)
				{
					pixel[0] = (color >> 16) & 0xff;
					pixel[1] = (color >> 8) & 0xff;
					pixel[2] = color & 0xff;
				}
				else
				{
					pixel[0] = color & 0xff;
					pixel[1] = (color >> 8) & 0xff;
					pixel[2] = (color >> 16) & 0xff;
				}
			}
			break;
		default:
			for (; pixel <= pixellast; pixel += pixy)
			{
				*(Uint32 *)pixel = color;
			}
			break;
		}

		if (SDL_MUSTLOCK(dst))
		{
			SDL_UnlockSurface(dst);
		}
		result = 0;
	}
	else
	{
		result = _VLineAlpha(dst, x, y1, y1 + h, color);
	}

	return (result);
}

int WindowManager::hlineColor(SDL_Surface *dst, Sint16 x1, Sint16 x2, Sint16 y, Uint32 color)
{
	Sint16 left, right, top, bottom;
	Uint8 *pixel, *pixellast;
	int dx;
	int pixx, pixy;
	Sint16 xtmp;
	int result = -1;
	Uint8 *colorptr;
	Uint8 color3[3];

	if ((dst->clip_rect.w == 0) || (dst->clip_rect.h == 0))
	{
		return (0);
	}

	if (x1 > x2)
	{
		xtmp = x1;
		x1 = x2;
		x2 = xtmp;
	}

	left = dst->clip_rect.x;
	if (x2 < left)
	{
		return (0);
	}
	right = dst->clip_rect.x + dst->clip_rect.w - 1;
	if (x1 > right)
	{
		return (0);
	}
	top = dst->clip_rect.y;
	bottom = dst->clip_rect.y + dst->clip_rect.h - 1;
	if ((y < top) || (y > bottom))
	{
		return (0);
	}

	if (x1 < left)
	{
		x1 = left;
	}
	if (x2 > right)
	{
		x2 = right;
	}

	dx = x2 - x1;

	if ((color & 255) == 255)
	{
		colorptr = (Uint8 *)&color;
		if (SDL_BYTEORDER == SDL_BIG_ENDIAN)
		{
			color = SDL_MapRGBA(dst->format, colorptr[0], colorptr[1], colorptr[2], colorptr[3]);
		}
		else
		{
			color = SDL_MapRGBA(dst->format, colorptr[3], colorptr[2], colorptr[1], colorptr[0]);
		}

		if (SDL_MUSTLOCK(dst))
		{
			if (SDL_LockSurface(dst) < 0)
			{
				return (-1);
			}
		}

		pixx = dst->format->BytesPerPixel;
		pixy = dst->pitch;
		pixel = ((Uint8 *)dst->pixels) + pixx * (int)x1 + pixy * (int)y;

		switch (dst->format->BytesPerPixel)
		{
		case 1:
			memset(pixel, color, dx + 1);
			break;
		case 2:
			pixellast = pixel + dx + dx;
			for (; pixel <= pixellast; pixel += pixx)
			{
				*(Uint16 *)pixel = color;
			}
			break;
		case 3:
			pixellast = pixel + dx + dx + dx;
			if (SDL_BYTEORDER == SDL_BIG_ENDIAN)
			{
				color3[0] = (color >> 16) & 0xff;
				color3[1] = (color >> 8) & 0xff;
				color3[2] = color & 0xff;
			}
			else
			{
				color3[0] = color & 0xff;
				color3[1] = (color >> 8) & 0xff;
				color3[2] = (color >> 16) & 0xff;
			}
			for (; pixel <= pixellast; pixel += pixx)
			{
				memcpy(pixel, color3, 3);
			}
			break;
		default:
			dx = dx + dx;
			pixellast = pixel + dx + dx;
			for (; pixel <= pixellast; pixel += pixx)
			{
				*(Uint32 *)pixel = color;
			}
			break;
		}

		if (SDL_MUSTLOCK(dst))
		{
			SDL_UnlockSurface(dst);
		}

		result = 0;
	}
	else
	{
		result = _HLineAlpha(dst, x1, x1 + dx, y, color);
	}

	return (result);
}

int WindowManager::_VLineAlpha(SDL_Surface *dst, Sint16 x, Sint16 y1, Sint16 y2, Uint32 color)
{
	return (filledRectAlpha(dst, x, y1, x, y2, color));
}

int WindowManager::_HLineAlpha(SDL_Surface *dst, Sint16 x1, Sint16 x2, Sint16 y, Uint32 color)
{
	return (filledRectAlpha(dst, x1, y, x2, y, color));
}

int WindowManager::filledRectAlpha(SDL_Surface *dst, Sint16 x1, Sint16 y1, Sint16 x2, Sint16 y2, Uint32 color)
{
	Uint8 alpha;
	Uint32 mcolor;
	int result = 0;

	if (SDL_MUSTLOCK(dst))
	{
		if (SDL_LockSurface(dst) < 0)
		{
			return (-1);
		}
	}

	alpha = color & 0x000000ff;
	mcolor =
		SDL_MapRGBA(dst->format, (color & 0xff000000) >> 24,
					(color & 0x00ff0000) >> 16, (color & 0x0000ff00) >> 8, alpha);

	result = _filledRectAlpha(dst, x1, y1, x2, y2, mcolor, alpha);

	if (SDL_MUSTLOCK(dst))
	{
		SDL_UnlockSurface(dst);
	}

	return (result);
}

int WindowManager::_filledRectAlpha(SDL_Surface *dst, Sint16 x1, Sint16 y1, Sint16 x2, Sint16 y2, Uint32 color, Uint8 alpha)
{
	SDL_PixelFormat *format;
	Uint32 Rmask, Gmask, Bmask, Amask;
	Uint32 Rshift, Gshift, Bshift;

#ifdef DEFAULT_ALPHA_PIXEL_ROUTINE
	Uint32 Ashift;
#endif

	Uint32 sR, sG, sB, sA;
	Uint32 dR, dG, dB, dA;
	Sint16 x, y;

	if (dst == NULL)
	{
		return (-1);
	}

	format = dst->format;
	switch (format->BytesPerPixel)
	{
	case 1:
	{ /* Assuming 8-bpp */
		Uint8 *row, *pixel;
		Uint8 R, G, B;
		SDL_Color *colors = format->palette->colors;
		SDL_Color dColor;
		SDL_Color sColor = colors[color];
		sR = sColor.r;
		sG = sColor.g;
		sB = sColor.b;

		for (y = y1; y <= y2; y++)
		{
			row = (Uint8 *)dst->pixels + y * dst->pitch;
			for (x = x1; x <= x2; x++)
			{
				if (alpha == 255)
				{
					*(row + x) = color;
				}
				else
				{
					pixel = row + x;

					dColor = colors[*pixel];
					dR = dColor.r;
					dG = dColor.g;
					dB = dColor.b;

					R = dR + ((sR - dR) * alpha >> 8);
					G = dG + ((sG - dG) * alpha >> 8);
					B = dB + ((sB - dB) * alpha >> 8);

					*pixel = SDL_MapRGB(format, R, G, B);
				}
			}
		}
	}
	break;

	case 2:
	{ /* Probably 15-bpp or 16-bpp */
		Uint16 *row, *pixel;
		Uint16 R, G, B, A;
		Uint16 dc;
		Rmask = format->Rmask;
		Gmask = format->Gmask;
		Bmask = format->Bmask;
		Amask = format->Amask;

		sR = (color & Rmask);
		sG = (color & Gmask);
		sB = (color & Bmask);
		sA = (color & Amask);

		for (y = y1; y <= y2; y++)
		{
			row = (Uint16 *)dst->pixels + y * dst->pitch / 2;
			for (x = x1; x <= x2; x++)
			{
				if (alpha == 255)
				{
					*(row + x) = color;
				}
				else
				{
					pixel = row + x;
					dc = *pixel;

					dR = (dc & Rmask);
					dG = (dc & Gmask);
					dB = (dc & Bmask);

					R = (dR + ((sR - dR) * alpha >> 8)) & Rmask;
					G = (dG + ((sG - dG) * alpha >> 8)) & Gmask;
					B = (dB + ((sB - dB) * alpha >> 8)) & Bmask;
					*pixel = R | G | B;
					if (Amask != 0)
					{
						dA = (dc & Amask);
						A = (dA + ((sA - dA) * alpha >> 8)) & Amask;
						*pixel |= A;
					}
				}
			}
		}
	}
	break;

	case 3:
	{ /* Slow 24-bpp mode, usually not used */
		Uint8 *row, *pixel;
		Uint8 R, G, B;
		Uint8 Rshift8, Gshift8, Bshift8;

		Rshift = format->Rshift;
		Gshift = format->Gshift;
		Bshift = format->Bshift;

		Rshift8 = Rshift >> 3;
		Gshift8 = Gshift >> 3;
		Bshift8 = Bshift >> 3;

		sR = (color >> Rshift) & 0xff;
		sG = (color >> Gshift) & 0xff;
		sB = (color >> Bshift) & 0xff;

		for (y = y1; y <= y2; y++)
		{
			row = (Uint8 *)dst->pixels + y * dst->pitch;
			for (x = x1; x <= x2; x++)
			{
				pixel = row + x * 3;

				if (alpha == 255)
				{
					*(pixel + Rshift8) = sR;
					*(pixel + Gshift8) = sG;
					*(pixel + Bshift8) = sB;
				}
				else
				{
					dR = *((pixel) + Rshift8);
					dG = *((pixel) + Gshift8);
					dB = *((pixel) + Bshift8);

					R = dR + ((sR - dR) * alpha >> 8);
					G = dG + ((sG - dG) * alpha >> 8);
					B = dB + ((sB - dB) * alpha >> 8);

					*((pixel) + Rshift8) = R;
					*((pixel) + Gshift8) = G;
					*((pixel) + Bshift8) = B;
				}
			}
		}
	}
	break;

#ifdef DEFAULT_ALPHA_PIXEL_ROUTINE
	case 4:
	{ /* Probably :-) 32-bpp */
		Uint32 *row, *pixel;
		Uint32 R, G, B, A;
		Uint32 dc;
		Rmask = format->Rmask;
		Gmask = format->Gmask;
		Bmask = format->Bmask;
		Amask = format->Amask;

		Rshift = format->Rshift;
		Gshift = format->Gshift;
		Bshift = format->Bshift;
		Ashift = format->Ashift;

		sR = (color & Rmask) >> Rshift;
		sG = (color & Gmask) >> Gshift;
		sB = (color & Bmask) >> Bshift;
		sA = (color & Amask) >> Ashift;

		for (y = y1; y <= y2; y++)
		{
			row = (Uint32 *)dst->pixels + y * dst->pitch / 4;
			for (x = x1; x <= x2; x++)
			{
				if (alpha == 255)
				{
					*(row + x) = color;
				}
				else
				{
					pixel = row + x;
					dc = *pixel;

					dR = (dc & Rmask) >> Rshift;
					dG = (dc & Gmask) >> Gshift;
					dB = (dc & Bmask) >> Bshift;

					R = ((dR + ((sR - dR) * alpha >> 8)) << Rshift) & Rmask;
					G = ((dG + ((sG - dG) * alpha >> 8)) << Gshift) & Gmask;
					B = ((dB + ((sB - dB) * alpha >> 8)) << Bshift) & Bmask;
					*pixel = R | G | B;
					if (Amask != 0)
					{
						dA = (dc & Amask) >> Ashift;
#ifdef ALPHA_PIXEL_ADDITIVE_BLEND
						A = (dA | GFX_ALPHA_ADJUST_ARRAY[sA & 255]) << Ashift; // make destination less transparent...
#else
						A = ((dA + ((sA - dA) * alpha >> 8)) << Ashift) & Amask;
#endif
						*pixel |= A;
					}
				}
			}
		}
	}
	break;
#endif

#ifdef EXPERIMENTAL_ALPHA_PIXEL_ROUTINE
	case 4:
	{ /* Probably :-) 32-bpp */
		Uint32 *row, *pixel;
		Uint32 dR, dG, dB, dA;
		Uint32 dc;
		Uint32 surfaceAlpha, preMultR, preMultG, preMultB;
		Uint32 aTmp;

		Rmask = format->Rmask;
		Gmask = format->Gmask;
		Bmask = format->Bmask;
		Amask = format->Amask;

		dR = (color & Rmask);
		dG = (color & Gmask);
		dB = (color & Bmask);
		dA = (color & Amask);

		Rshift = format->Rshift;
		Gshift = format->Gshift;
		Bshift = format->Bshift;
		Ashift = format->Ashift;

		preMultR = (alpha * (dR >> Rshift));
		preMultG = (alpha * (dG >> Gshift));
		preMultB = (alpha * (dB >> Bshift));

		for (y = y1; y <= y2; y++)
		{
			row = (Uint32 *)dst->pixels + y * dst->pitch / 4;
			for (x = x1; x <= x2; x++)
			{
				if (alpha == 255)
				{
					*(row + x) = color;
				}
				else
				{
					pixel = row + x;
					dc = *pixel;

					surfaceAlpha = ((dc & Amask) >> Ashift);
					aTmp = (255 - alpha);
					if (A = 255 - ((aTmp * (255 - surfaceAlpha)) >> 8))
					{
						aTmp *= surfaceAlpha;
						R = (preMultR + ((aTmp * ((dc & Rmask) >> Rshift)) >> 8)) / A << Rshift & Rmask;
						G = (preMultG + ((aTmp * ((dc & Gmask) >> Gshift)) >> 8)) / A << Gshift & Gmask;
						B = (preMultB + ((aTmp * ((dc & Bmask) >> Bshift)) >> 8)) / A << Bshift & Bmask;
					}
					*pixel = R | G | B | (A << Ashift & Amask);
				}
			}
		}
	}
	break;
#endif
	}

	return (0);
}
