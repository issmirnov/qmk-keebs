import os
import sys
import re


_KEYNAMES = {
    "_______": "",
    "XXXXXXX": "",

    "KC_COMM": ",",
    "KC_DOT": ".",
    "KC_SLSH": "/",
    "KC_SCLN": ";",
    "KC_COLN": ":",
    "KC_TILD": "~",
    "KC_GRV": "`",
    "KC_BSLS": "\\",
    "KC_PIPE": "|",
    "KC_EXLM": "!",
    "KC_AT": "@",
    "KC_HASH": "#",
    "KC_DLR": "$",
    "KC_PERC": "%",
    "KC_CIRC": "^",
    "KC_AMPR": "&",
    "KC_ASTR": "*",
    "KC_UNDS": "_",
    "KC_MINS": "-",
    "KC_PLUS": "+",
    "KC_EQL": "=",
    "KC_QUOT": "'",
    "KC_DQT": '"',

    "KC_LPRN": "(",
    "KC_RPRN": ")",
    "KC_LBRC": "[",
    "KC_RBRC": "]",
    "KC_LCBR": "{",
    "KC_RCBR": "}",
    "KC_LT": "<",
    "KC_GT": ">",

    "KC_LSFT": "Shift",
    "KC_RSFT": "Shift",
    "KC_LCTL": "Ctl",
    "KC_RCTL": "Ctl",
    "KC_LALT": "Alt",
    "KC_RALT": "Alt",
    "KC_LGUI": "Mod",
    "KC_RGUI": "Mod",

    "KC_SPC": "Space",
    "KC_ENT": "Enter",
    "KC_BSPC": "BckSp",
    "KC_SFTENT": "Enter",

    "KC_UP": "↑",
    "KC_DOWN": "↓",
    "KC_LEFT": "←",
    "KC_RGHT": "→",

    "KC_PGDN": "PgDn",
    "KC_PGUP": "PgUp",
    "KC_MPLY": "Play",
    "KC_MPRV": "Prev",
    "KC_MNXT": "Next",
    "KC_VOLD": "Vol-",
    "KC_VOLU": "Vol+",

    "AG_NORM": "Linux",
    "AG_SWAP": "Mac",
}


class _Template(object):

    def __init__(self, template):
        self.width = max(len(line) for line in template.split("\n"))
        self.template = template

    def render(self, layer):
        rendered = self.template
        for i, key in enumerate(layer.key_names()):
            match = re.search(" +{} +".format(i), rendered).group()
            label = "{:^{width}.{width}}".format(key, width=len(match))
            rendered = rendered.replace(match, label)
        return "{:^{}}\n".format(layer.name.title(), self.width) + rendered


class _Rows(object):

    def __init__(self, rows):
        self.rows = rows

    def expand(self, line):
        for (name, keys) in self.rows.items():
            line = line.replace(name, keys)
        return line


class _Layer(object):

    def __init__(self, name, codes):
        self.name = name
        self.codes = codes

    def key_name(self, idx):
        code = self.codes[idx]
        if code in _KEYNAMES:
            return _KEYNAMES[code]
        return code.replace("KC_", "").title().replace("_", "")

    def key_names(self):
        for code in self.codes:
            if code in _KEYNAMES:
                yield _KEYNAMES[code]
            else:
                yield code.replace("KC_", "").title().replace("_", "")


def _load_rows(row_lines):
    row_re = re.compile(r"#define (\w+) +(.*)")

    rows = dict()
    for line in row_lines:
        match = row_re.match(line)
        if match:
            rows[match.group(1)] = match.group(2)
    return _Rows(rows)


def _load_layers(keymap_lines, rows):
    start_re = re.compile(r"^\[_(\w+)\] =")
    end_re = re.compile(r"^\),")

    layers = []
    layer_name = None
    codes = None
    for line in keymap_lines:
        line = rows.expand(line)
        start = start_re.match(line)
        if layer_name:
            if end_re.match(line):
                layers.append(_Layer(layer_name, codes))
                layer_name = None
                codes = None
            else:
                codes += filter(None, (code.strip()
                                       for code in line.split(",")))
        elif start:
            layer_name = start.group(1)
            codes = []
    return layers


def visualize(user_dir, keyboard_dir):
    with open(os.path.join(user_dir, "rows.h")) as f:
        rows = _load_rows(f)
    with open(os.path.join(keyboard_dir, "keymap.c")) as f:
        layers = _load_layers(f, rows)
    with open(os.path.join(keyboard_dir, "template.txt")) as f:
        template = _Template(f.read())
    for layer in layers:
        print(template.render(layer))
