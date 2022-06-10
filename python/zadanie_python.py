#!/usr/bin/python

import re
import colorsys
import argparse


class Color(object):
    color = True
    r = int
    g = int
    b = int
    a = int

def read(lines):

    rgb_r = re.compile("^([0-9]{1,3},){3}[0-9]{1,3}$")
    hex_r = re.compile("^([0-9a-f]{3}|[0-9a-f]{6}|[0-9a-f]{8})$")

    list_rgb = list(filter(rgb_r.match, lines))
    list_hex = list(filter(hex_r.match, lines))

    # delete /n
    list_rgb2 = [x[:-1] for x in list_rgb]
    list_hex2 = [x[:-1] for x in list_hex]

    # rgb string to tuple
    list_rgb2 = [tuple(map(int, sub.split(','))) for sub in list_rgb2]

    list_rgb_only = hex_to_rgb(list_hex2)
    list_rgb_only = list_rgb_only + list_rgb2

    return list_rgb_only


def tou2clas(t_rgb):
    color = []
    for i in range(t_rgb.__len__()):
        color.append(i)
        color[i] = Color()
        color[i].r = t_rgb[i][0]
        color[i].g = t_rgb[i][1]
        color[i].b = t_rgb[i][2]
        color[i].a = t_rgb[i][3]
    return color


def rgb_to_hex(color, x):
    if x == 0:
        for i in range(color.__len__()):
            tmp = '#{:02x}{:02x}{:02x}{:02x}'.format(color[i].r, color[i].g, color[i].b, color[i].a)
            color[i].hex = tmp
    else:
        tmp = '#{:02x}{:02x}{:02x}{:02x}'.format(color[color.__len__() - 1].r, color[color.__len__() - 1].g,
                                                 color[color.__len__() - 1].b, color[color.__len__() - 1].a)
        color[color.__len__() - 1].hex = tmp

    return color


def hex_to_rgb(value):
    list_rgb = []
    for x in range(value.__len__()):
        value[x] = value[x].lstrip('#')
        lv = len(value[x])
        tmp = tuple(int(value[x][i:i + lv // 3], 16) for i in range(0, lv, lv // 3))
        list_rgb.append(tmp)
    return list_rgb


def rgb_to_hsl(color, x):
    if x == 0:
        for i in range(color.__len__()):
            (r, g, b) = (color[i].r / 255, color[i].g / 255, color[i].b / 255)
            # convert to hsv
            (h, l, s) = colorsys.rgb_to_hls(r, g, b)
            # expand HSV range
            (h, s, l) = (round(h * 360), round(s * 1, 2), round(l * 1, 2))
            color[i].h = h
            color[i].s = s
            color[i].l = l
    else:
        (r, g, b) = (
            color[color.__len__() - 1].r / 255, color[color.__len__() - 1].g / 255, color[color.__len__() - 1].b / 255)
        # convert to hsv
        (h, l, s) = colorsys.rgb_to_hls(r, g, b)
        # expand HSV range
        (h, s, l) = (round(h * 360), round(s * 1, 2), round(l * 1, 2))
        color[color.__len__() - 1].h = h
        color[color.__len__() - 1].s = s
        color[color.__len__() - 1].l = l

    return color


def hsl_to_rgb(color):
    (h, s, l) = (color[color.__len__() - 1].h / 360, color[color.__len__() - 1].s, color[color.__len__() - 1].l)
    (r, g, b) = colorsys.hls_to_rgb(h, l, s)

    (r, g, b) = (round(r * 255), round(g * 255), round(b * 255))

    color[color.__len__() - 1].r = r
    color[color.__len__() - 1].g = g
    color[color.__len__() - 1].b = b

    return color


def average(lst):
    return sum(lst) / len(lst)


def show_atr(color):
    print('red= ', color[color.__len__() - 1].r)
    print('green= ', color[color.__len__() - 1].g)
    print('blue= ', color[color.__len__() - 1].b)
    print('alpha= ', color[color.__len__() - 1].a)
    print('hex= ', color[color.__len__() - 1].hex)
    print('hue= ', color[color.__len__() - 1].h)
    print('saturation= ', color[color.__len__() - 1].s)
    print('lightness= ', color[color.__len__() - 1].l)
    return 0


def mode_mix(color):
    list_r = []
    list_g = []
    list_b = []
    list_a = []
    for i in range(color.__len__()):
        list_r.append(color[i].r)
        list_g.append(color[i].g)
        list_b.append(color[i].b)
        list_a.append(color[i].a)

    r = round(average(list_r))
    g = round(average(list_g))
    b = round(average(list_b))
    a = round(average(list_a))

    color.append(color.__len__())
    color[color.__len__() - 1] = Color()
    color[color.__len__() - 1].r = r
    color[color.__len__() - 1].g = g
    color[color.__len__() - 1].b = b
    color[color.__len__() - 1].a = a

    color = rgb_to_hex(color, 1)
    color = rgb_to_hsl(color, 1)

    return color


def mode_low(color):
    list_r = []
    list_g = []
    list_b = []
    list_a = []
    for i in range(color.__len__()):
        list_r.append(color[i].r)
        list_g.append(color[i].g)
        list_b.append(color[i].b)
        list_a.append(color[i].a)

    r = min(list_r)
    g = min(list_g)
    b = min(list_b)
    a = min(list_a)

    color.append(color.__len__())
    color[color.__len__() - 1] = Color()
    color[color.__len__() - 1].r = r
    color[color.__len__() - 1].g = g
    color[color.__len__() - 1].b = b
    color[color.__len__() - 1].a = a

    color = rgb_to_hex(color, 1)
    color = rgb_to_hsl(color, 1)

    return color


def mode_high(color):
    list_r = []
    list_g = []
    list_b = []
    list_a = []
    for i in range(color.__len__()):
        list_r.append(color[i].r)
        list_g.append(color[i].g)
        list_b.append(color[i].b)
        list_a.append(color[i].a)

    r = max(list_r)
    g = max(list_g)
    b = max(list_b)
    a = max(list_a)

    color.append(color.__len__())
    color[color.__len__() - 1] = Color()
    color[color.__len__() - 1].r = r
    color[color.__len__() - 1].g = g
    color[color.__len__() - 1].b = b
    color[color.__len__() - 1].a = a

    color = rgb_to_hex(color, 1)
    color = rgb_to_hsl(color, 1)

    return color


def mode_mix_sat(color):
    list_s = []

    for i in range(color.__len__()):
        list_s.append(color[i].s)

    s = round(average(list_s), 2)

    color[color.__len__() - 1].s = s

    color = hsl_to_rgb(color)
    color = rgb_to_hex(color, 1)

    return color


def read_t(list_t, color_w):
    rgb_r = re.compile("^([0-9]{1,3},){3}[0-9]{1,3}$")

    list_rgb_w = list(filter(rgb_r.match, list_t))
    list_rgb_w = [tuple(map(int, sub.split(','))) for sub in list_rgb_w]
    color_w.extend(list_rgb_w)

    return color_w


if __name__ == "__main__":

    with open('color.txt') as f:
        lines = f.readlines()

    color = read(lines)

    parser = argparse.ArgumentParser(description='Process some integers.')
    parser.add_argument('integers', type=str, metavar='N', nargs='+',
                        help='colors RGBA a,b,c,d a,b,c,d')
    parser.add_argument('-m', '--MODE', help='mode')

    args = parser.parse_args()
    print(args.MODE)
    print(args.integers)


    list_terminal = args.integers
    mode = args.MODE

    color = read_t(list_terminal, color)

    color = tou2clas(color)
    color = rgb_to_hex(color, 0)
    color = rgb_to_hsl(color, 0)

    if mode == 'mix':
        mode_mix(color)
    elif mode == 'max':
        mode_high(color)
    elif mode == 'low':
        mode_low(color)
    elif mode == 'mixsat':
        mode_mix_sat(color)

    show_atr(color)

