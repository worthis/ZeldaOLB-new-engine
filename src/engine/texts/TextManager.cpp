#include "TextManager.h"

#include "../window/WindowManager.h"

TextManager TextManager::instance = TextManager();

TextManager::TextManager() : config(0)
{
}

TextManager::~TextManager()
{
}

TextManager *TextManager::getInstance()
{
    return &instance;
}

void TextManager::setConfiguration(TextConfiguration *conf)
{
    config = conf;
    reloadTexts();
}

void TextManager::reloadTexts()
{
    loadTextsFromFile(config->getTextfile());
}

int TextManager::getWSpace()
{
    return config->getWSpace();
}

int TextManager::getWSize()
{
    return config->getWSize();
}

int TextManager::getHSize()
{
    return config->getHSize();
}

WImage *TextManager::getImage()
{
    return config->getImage();
}

Text *TextManager::getText(int id)
{
    string text = texts[id];

    int begin = -1;
    int end = -1;
    bool in = false;
    for (unsigned int i = 0; i < text.length(); i++)
    {

        if (in)
        {
            if (text[i] == ']')
            {
                char type = text[begin + 1];
                end = i;

                // only color styles ( like [c=?] ) are ignored
                if (text[begin + 2] != '=' || type != 'c')
                {
                    if (text[begin + 2] != '=')
                    {
                        string newValue = config->getCommonValue(text.substr(begin + 1, end - begin - 1));
                        text.replace(begin, end - begin + 1, newValue);
                        i += (newValue.length() - (end - begin + 1));
                    }
                    else
                    {
                        string value = text.substr(begin + 3, end - begin - 1);
                        int number;
                        istringstream ss(value);
                        ss >> number;
                        string newValue = config->getVariableValue(id, number);
                        text.replace(begin, end - begin + 1, newValue);
                        i += (newValue.length() - (end - begin + 1));
                    }
                }

                in = false;
            }
        }
        else
        {
            if (text[i] == '[')
            {
                in = true;
                begin = i;
            }
        }
    }

    return new Text(text);
}

void TextManager::loadTextsFromFile(string filename)
{
    texts.clear();

    ifstream file(filename.c_str());

    if (file)
    {
        string line;
        while (getline(file, line))
        {
            texts.push_back(line);
        }
    }
}

void TextManager::drawLetter(char c, int i, int j, int style)
{
    drawLetterInternal(c, i, j, style);
}

void TextManager::displayNumber(int n, int digits, int a, int b)
{
    int q = 1;
    for (int i = 0; i < digits; i++)
    {
        int d = (n % (q * 10)) / q;
        displayNumberInternal(d, a + ((digits - (i + 1)) * 8), b);
        q *= 10;
    }
}

void TextManager::displayNumberInternal(int d, int i, int j)
{
    int w = getWSize();
    int h = getHSize();
    int x = w * (52 + d);
    int y = 0;
    WindowManager::getInstance()->draw(getImage(), x, y, w, h, i, j);
}

void TextManager::drawLetterInternal(char c, int i, int j, int style)
{

    int x = 0;
    int y = style * getHSize();
    int w = getWSize();
    int h = getHSize();

    int val = (int)c;

    if (val == 32)
        return;

    // chiffres
    if (val >= 48 && val <= 57)
    {
        x = w * (52 + (val - 48));
    }

    // majuscules A-Z
    if (val >= 65 && val <= 90)
    {
        x = w * (val - 65);
    }

    // minuscules a-z
    if (val >= 97 && val <= 122)
    {
        x = w * (26 + (val - 97));
    }

    switch (val)
    {
    case 224:
        // à
        x = w * 62;
        break;
    case 226:
        // â
        x = w * 63;
        break;
    case 228:
        // ä
        x = w * 64;
        break;
    case 231:
        // ç
        x = w * 65;
        break;
    case 232:
        // è
        x = w * 66;
        break;
    case 233:
        // é
        x = w * 67;
        break;
    case 235:
        // ë
        x = w * 68;
        break;
    case 234:
        // ê
        x = w * 69;
        break;
    case 239:
        // ï
        x = w * 70;
        break;
    case 238:
        // î
        x = w * 71;
        break;
    case 244:
        // ô
        x = w * 72;
        break;
    case 246:
        // ö
        x = w * 73;
        break;
    case 249:
        // ù
        x = w * 74;
        break;
    case 251:
        // û
        x = w * 75;
        break;
    case 252:
        // ü
        x = w * 76;
        break;
    case 45:
        // -
        x = w * 77;
        break;
    case 46:
        // .
        x = w * 78;
        break;
    case 44:
        // ,
        x = w * 79;
        break;
    case 39:
        // '
        x = w * 80;
        break;
    case 33:
        // !
        x = w * 81;
        break;
    case 63:
        // ?
        x = w * 82;
        break;
    case 58:
        // :
        x = w * 83;
        break;
    case 37:
        // %
        x = w * 84;
        break;
    case 40:
        // (
        x = w * 85;
        break;
    case 41:
        // )
        x = w * 86;
        break;
    case 47:
        // /
        x = w * 87;
        break;
    case 64:
        // @
        x = w * 88;
        break;
    case 43:
        // +
        x = w * 89;
        break;
    case 61:
        // =
        x = w * 90;
        break;
    case 59:
        // ;
        x = w * 93;
        break;
    case 250:
        // ú
        x = w * 94;
        break;
    case 237:
        // í
        x = w * 95;
        break;
    case 191:
        // ¿
        x = w * 96;
        break;
    case 161:
        // ¡
        x = w * 97;
        break;
    case 243:
        // ó
        x = w * 98;
        break;
    case 225:
        // á
        x = w * 99;
        break;
    case 241:
        // ñ
        x = w * 100;
        break;
    default:
        break;
    }

    // cyrillic chars
    if (config->getTextfile() == "data/texts/russian.txt")
    {
        if (val >= 192 && val <= 255)
        {
            x = w * (val - 192);
            y += 6 * getHSize();
        }
    }

    // sprite.SetSubRect(sf::IntRect(x, y, x + w, y + h));
    // sprite.SetPosition(i, j);
    // WindowManager::getInstance()->draw(sprite);
    WindowManager::getInstance()->draw(getImage(), x, y, w, h, i, j);
}
