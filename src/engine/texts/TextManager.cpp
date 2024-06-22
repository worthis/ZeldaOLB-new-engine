#include "TextManager.h"

#include "../window/WindowManager.h"

TextManager TextManager::instance=TextManager();

TextManager::TextManager() : config(0) {
}

TextManager::~TextManager() {
}

TextManager* TextManager::getInstance() {
    return &instance;
}

void TextManager::setConfiguration(TextConfiguration* conf) {
    config = conf;
    reloadTexts();
}

void TextManager::reloadTexts() {
    loadTextsFromFile(config->getTextfile());
}

int TextManager::getWSpace() {
    return config->getWSpace();
}

int TextManager::getWSize() {
    return config->getWSize();
}

int TextManager::getHSize() {
    return config->getHSize();
}

WImage* TextManager::getImage() {
    return config->getImage();
}

Text* TextManager::getText(int id) {
    string text = texts[id];

    int begin = -1;
    int end = -1;
    bool in = false;
    for (unsigned int i = 0; i < text.length(); i++) {

        if (in) {
            if (text[i] == ']') {
                char type = text[begin + 1];
                end = i;

                // only color styles ( like [c=?] ) are ignored
                if (text[begin + 2] != '=' || type != 'c') {
                    if (text[begin + 2] != '=') {
                        string newValue = config->getCommonValue(text.substr(begin + 1, end - begin - 1));
                        text.replace(begin, end - begin + 1, newValue);
                        i += (newValue.length() - (end - begin + 1));
                    } else {
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
        } else {
            if (text[i] == '[') {
                in = true;
                begin = i;
            }
        }



    }

    return new Text(text);
}

void TextManager::loadTextsFromFile(string filename) {
    texts.clear();

    ifstream file(filename.c_str());

    if (file) {
        string line;
        while (getline(file, line)) {
            texts.push_back(line);
        }
    }
}

void TextManager::drawLetter(char c, int i, int j, int style) {
    drawLetterInternal(c, i, j, style);
}

void TextManager::displayNumber(int n, int digits, int a, int b) {
    int q = 1;
    for (int i = 0; i < digits; i++) {
        int d = (n%(q*10))/q;
        displayNumberInternal(d, a + ((digits - (i + 1)) * 8), b);
        q *= 10;
    }
}

void TextManager::displayNumberInternal(int d, int i, int j) {
    int w = getWSize();
    int h = getHSize();
    int x = w * (52 + d);
    int y = 0;
    WindowManager::getInstance()->draw(getImage(), x, y, w, h, i, j);
}

void TextManager::drawLetterInternal(char c, int i, int j, int style) {

    int x = 0;
    int y = style * getHSize();
    int w = getWSize();
    int h = getHSize();

    int val = (int)c;

    if (val == 32) return;

    //minuscules a-z
    if (val >= 97 && val <= 122) {
        x = w * (26 + (val - 97));
    }

    //majuscules A-Z
    if (val >= 65 && val <= 90) {
        x = w * (val - 65);
    }

    //chiffres
    if (val >= 48 && val <= 57) {
        x = w * (52 + (val - 48));
    }

    if (c == 'à') {x = w * 62;}
    if (c == 'â') {x = w * 63;}
    if (c == 'ä') {x = w * 64;}
    if (c == 'ç') {x = w * 65;}
    if (c == 'è') {x = w * 66;}
    if (c == 'é') {x = w * 67;}
    if (c == 'ë') {x = w * 68;}
    if (c == 'ê') {x = w * 69;}
    if (c == 'ï') {x = w * 70;}
    if (c == 'î') {x = w * 71;}
    if (c == 'ô') {x = w * 72;}
    if (c == 'ö') {x = w * 73;}
    if (c == 'ù') {x = w * 74;}
    if (c == 'û') {x = w * 75;}
    if (c == 'ü') {x = w * 76;}
    if (c == '-') {x = w * 77;}
    if (c == '.') {x = w * 78;}
    if (c == ',') {x = w * 79;}
    if (c == '\'') {x = w * 80;}
    if (c == '!') {x = w * 81;}
    if (c == '?') {x = w * 82;}
    if (c == ':') {x = w * 83;}
    if (c == '%') {x = w * 84;}
    if (c == '(') {x = w * 85;}
    if (c == ')') {x = w * 86;}
    if (c == '/') {x = w * 87;}
    if (c == '@') {x = w * 88;}
    if (c == '+') {x = w * 89;}
    if (c == '=') {x = w * 90;}
    if (c == ';') {x = w * 93;}
    if (c == 'ú') {x = w * 94;}
    if (c == 'í') {x = w * 95;}
    if (c == '¿') {x = w * 96;}
    if (c == '¡') {x = w * 97;}
    if (c == 'ó') {x = w * 98;}
    if (c == 'á') {x = w * 99;}
    if (c == 'ñ') {x = w * 100;}



    //sprite.SetSubRect(sf::IntRect(x, y, x + w, y + h));
    //sprite.SetPosition(i, j);
    //WindowManager::getInstance()->draw(sprite);
    WindowManager::getInstance()->draw(getImage(), x, y, w, h, i, j);

}
