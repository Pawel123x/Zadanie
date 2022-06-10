#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <regex>
#include <cmath>
#include <algorithm>
#include <vector>

using namespace std;

class Color {
public:
    int r;
    int g;
    int b;
    int a;
    string hex;
    int h = 0;
    int l = 0;
    int s = 0;


    Color(int rr, int gg, int bb, int aa) {
        r = rr;
        g = gg;
        b = bb;
        a = aa;
    }


};


auto read_txt(string name) {

    std::list<string> listRGB;
    std::list<string> listHEX;
    fstream newfile;

    regex eRGB("^([0-9]{1,3},){3}[0-9]{1,3}$");
    regex eHEX("^([0-9a-f]{3}|[0-9a-f]{6}|[0-9a-f]{8})$");

    newfile.open(name, ios::in); //open a file to perform read operation using file object
    if (newfile.is_open()) { //checking whether the file is open
        string tp;
        while (getline(newfile, tp)) {
            if (regex_match(tp, eRGB)) {
                listRGB.push_back(tp);
            } else if (regex_match(tp, eHEX)) {
                listHEX.push_back(tp);

            }
        }
        newfile.close(); //close the file object.

    }
    return std::make_tuple(listRGB, listHEX);
}

std::string rgb2hex(int r, int g, int b, int a, bool with_head) {
    std::stringstream ss;
    if (with_head)
        ss << "#";
    ss << std::hex << (r << 24 | g << 16 | b << 8 | a);
    return ss.str();
}

static float Min(float a, float b) {
    return a <= b ? a : b;
}

static float Max(float a, float b) {
    return a >= b ? a : b;
}


auto RGBToHSL(int rr, int gg, int bb) {
    float h = 0, s = 0, l = 0;
    float r = ((float) rr / 255.0f);
    float g = ((float) gg / 255.0f);
    float b = ((float) bb / 255.0f);

    float min = Min(Min(r, g), b);
    float max = Max(Max(r, g), b);
    float delta = max - min;


    l = (max + min) / 2;
    l = round(l * 255);

    if (delta == 0) {
        h = 0;
        s = 0;
    } else {
        s = (l <= 0.5) ? (delta / (max + min)) : (delta / (2 - max - min));
        s = round(s * 255);
        float hue;

        if (r == max) {
            hue = ((g - b) / 6) / delta;
        } else if (g == max) {
            hue = (1.0f / 3) + ((b - r) / 6) / delta;
        } else {
            hue = (2.0f / 3) + ((r - g) / 6) / delta;
        }

        if (hue < 0)
            hue += 1;
        if (hue > 1)
            hue -= 1;

        h = round((hue * 360));
    }

    return std::make_tuple(h, s, l);
}

void show_atr(std::vector<Color> color) {
    cout << "red= " << color[color.size() - 1].r;
    cout << "\n";
    cout << "green= " << color[color.size() - 1].g;
    cout << "\n";
    cout << "blue= " << color[color.size() - 1].b;
    cout << "\n";
    cout << "alpha= " << color[color.size() - 1].a;
    cout << "\n";
    cout << "hex= " << color[color.size() - 1].hex;
    cout << "\n";
    cout << "hue= " << color[color.size() - 1].h;
    cout << "\n";
    cout << "saturation= " << color[color.size() - 1].s;
    cout << "\n";
    cout << "lightness= " << color[color.size() - 1].l;
    cout << "\n";


}

int average(list<int> lst) {
    int tmp_w = 0;
    for (auto const &i: lst) {
        tmp_w = tmp_w + i;
    }
    return round(tmp_w / lst.size());
}


std::vector<Color> rgb_to_hexhsl(std::vector<Color> color) {

    for (int i = 0; i <= color.size() - 1; i++) {

        string hex = rgb2hex(color[i].r, color[i].g, color[i].b, color[i].a, true);
        color[i].hex = hex;


        int h, s, l;
        std::tie(h, s, l) = RGBToHSL(color[i].r, color[i].g, color[i].b);
        color[i].h = h;
        color[i].l = l;
        color[i].s = s;

    }
    return color;
}

std::vector<Color> mode_mix(std::vector<Color> color) {
    std::list<int> list_r;
    std::list<int> list_g;
    std::list<int> list_b;
    std::list<int> list_a;

    for (int i = 0; i <= color.size() - 1; i++) {
        list_r.push_back(color[i].r);
        list_g.push_back(color[i].g);
        list_b.push_back(color[i].b);
        list_a.push_back(color[i].a);
    }

    int res_r = average(list_r);
    int res_g = average(list_g);
    int res_b = average(list_b);
    int res_a = average(list_a);

    color.emplace_back(Color(res_r, res_g, res_b, res_a));
    color = rgb_to_hexhsl(color);

    return color;
}

std::vector<Color> mode_low(std::vector<Color> color) {
    std::list<int> list_r;
    std::list<int> list_g;
    std::list<int> list_b;
    std::list<int> list_a;
    for (int i = 0; i <= color.size() - 1; i++) {
        list_r.push_back(color[i].r);
        list_g.push_back(color[i].g);
        list_b.push_back(color[i].b);
        list_a.push_back(color[i].a);
    }


    auto minnum_r = min_element(begin(list_r), end(list_r));
    int min_r = *minnum_r;
    auto minnum_g = min_element(begin(list_g), end(list_g));
    int min_g = *minnum_g;
    auto minnum_b = min_element(begin(list_b), end(list_b));
    int min_b = *minnum_b;
    auto minnum_a = min_element(begin(list_a), end(list_a));
    int min_a = *minnum_a;

    color.emplace_back(Color(min_r, min_g, min_b, min_a));
    color = rgb_to_hexhsl(color);

    return color;
}

std::vector<Color> mode_high(std::vector<Color> color) {
    std::list<int> list_r;
    std::list<int> list_g;
    std::list<int> list_b;
    std::list<int> list_a;
    for (int i = 0; i <= color.size() - 1; i++) {
        list_r.push_back(color[i].r);
        list_g.push_back(color[i].g);
        list_b.push_back(color[i].b);
        list_a.push_back(color[i].a);
    }


    auto maxnum_r = max_element(begin(list_r), end(list_r));
    int max_r = *maxnum_r;
    auto maxnum_g = max_element(begin(list_g), end(list_g));
    int max_g = *maxnum_g;
    auto maxnum_b = max_element(begin(list_b), end(list_b));
    int max_b = *maxnum_b;
    auto maxnum_a = max_element(begin(list_a), end(list_a));
    int max_a = *maxnum_a;

    color.emplace_back(Color(max_r, max_g, max_b, max_a));
    color = rgb_to_hexhsl(color);

    return color;
}

float hue2rgb(float p, float q, float t) {

    if (t < 0)
        t += 1;
    if (t > 1)
        t -= 1;
    if (t < 1. / 6)
        return p + (q - p) * 6 * t;
    if (t < 1. / 2)
        return q;
    if (t < 2. / 3)
        return p + (q - p) * (2. / 3 - t) * 6;

    return p;

}


auto hsl2rgb(float h, float s, float l) {
    int r, g, b, a;
    h = h / 255;
    l = l / 255;
    s = s / 255;
    if (0 == s) {
        r = g = b = l; // achromatic
    } else {
        float q = l < 0.5 ? l * (1 + s) : l + s - l * s;
        float p = 2 * l - q;
        r = hue2rgb(p, q, h + 1. / 3) * 255;
        g = hue2rgb(p, q, h) * 255;
        b = hue2rgb(p, q, h - 1. / 3) * 255;

    }
    return std::make_tuple(r, g, b);
}

std::vector<Color> mode_mix_sat(std::vector<Color> color) {
    std::list<int> list_s;
    int r, g, b;

    for (int i = 0; i <= color.size() - 1; i++) {
        list_s.push_back(color[i].s);
    }
    int res_s = average(list_s);
    color[color.size() - 1].s = res_s;

    std::tie(r, g, b) = hsl2rgb(color[color.size() - 1].h, color[color.size() - 1].s, color[color.size() - 1].l);
    color[color.size() - 1].r = r;
    color[color.size() - 1].g = g;
    color[color.size() - 1].b = b;


    string hex = rgb2hex(color[color.size() - 1].r, color[color.size() - 1].g, color[color.size() - 1].b,
                         color[color.size() - 1].a, true);
    color[color.size() - 1].hex = hex;


    return color;
}

std::list<string> hex_to_rgb(std::list<string> listHEX){
    std::list<string> listHEX_RGB;
    for (string n: listHEX) {
        char const *hexColor = n.c_str();
        int r, g, b, a;
        std::sscanf(hexColor, "%02x%02x%02x%02x", &r, &g, &b, &a);
        string rr = to_string(r);
        string gg = to_string(g);
        string bb = to_string(b);
        string aa = to_string(a);
        string rgba = rr + "," + gg + "," + bb + "," + aa;

        listHEX_RGB.push_back(rgba);
    }
    return listHEX_RGB;
}
std::vector<Color> list_to_class(std::list<string> listRGB){

    std::vector<Color> colors;
    for (string n: listRGB) {
        std::string delimiter = ",";
        size_t pos = 0;
        int tt = 0;
        int r;
        int g;
        int b;
        int a;
        std::string token;
        while ((pos = n.find(delimiter)) != std::string::npos) {
            token = n.substr(0, pos);

            if (tt == 0) {
                r = stoi(token);
                tt++;
            } else if (tt == 1) {
                g = stoi(token);
                tt++;
            } else if (tt == 2) {
                b = stoi(token);
                tt++;
            }
            n.erase(0, pos + delimiter.length());
        }
        a = stoi(n);
        if((r>=0 && r <=255)&&(g>=0 && g <=255)&&(b>=0 && b <=255)&&(a>=0 && a <=255)){
            colors.emplace_back(Color(r, g, b, a));
        }
    }
    return colors;
}

int main(int argc, char **argv) {

    std::list<string> list_t;
    regex eRGB("^([0-9]{1,3},){3}[0-9]{1,3}$");
    for (int i = 1; i < argc - 2; ++i) {
        if (regex_match(argv[i], eRGB)) {
            list_t.emplace_back(argv[i]);
        }
    }


    std::list<string> listRGB;
    std::list<string> listHEX;
    std::list<string> listHEX_RGB;


    std::tie(listRGB, listHEX) = read_txt("color.txt");

    listHEX_RGB=hex_to_rgb(listHEX);

    listRGB.splice(listRGB.end(), listHEX_RGB);
    listRGB.splice(listRGB.end(), list_t);


    std::vector<Color> colors = list_to_class(listRGB);

    colors = rgb_to_hexhsl(colors);


    if ((std::string(argv[argc - 2]) == "-m" || std::string(argv[argc - 2]) == "--mode") &&
        string(argv[argc - 1]) == "mix") {
        colors = mode_mix(colors);
        show_atr(colors);
    } else if ((std::string(argv[argc - 2]) == "-m" || std::string(argv[argc - 2]) == "--mode") &&
               string(argv[argc - 1]) == "lowest") {
        colors = mode_low(colors);
        show_atr(colors);
    } else if ((std::string(argv[argc - 2]) == "-m" || std::string(argv[argc - 2]) == "--mode") &&
               string(argv[argc - 1]) == "highest") {
        colors = mode_high(colors);
        show_atr(colors);
    } else if ((std::string(argv[argc - 2]) == "-m" || std::string(argv[argc - 2]) == "--mode") &&
               string(argv[argc - 1]) == "mix-saturate") {
        colors = mode_mix_sat(colors);
        show_atr(colors);
    }
    else{
        cout<<"incorrect mode";
    }
    cout<<colors.size();

}
