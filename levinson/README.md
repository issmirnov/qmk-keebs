# Levinson

## Colors

- https://github.com/qmk/qmk_firmware/blob/master/docs/feature_rgblight.md
  - main docs.
- https://github.com/qmk/qmk_firmware/blob/master/quantum/rgblight_list.h
  - list of colors
- https://github.com/qmk/qmk_firmware/blob/master/quantum/rgblight.h
  - list of functions for RGB manipulation

## Troubleshooting

- When in doubt, flash both sides of the keyboard. For some reason that helps with LEDs and reponsiveness.
    - `cd qmk_firmware && make keebio/levinson/rev2:issmirnov:dfu-split-right`

## Converting QMK configurator JSON to keymap.c

If we want to take the output of the json from https://config.qmk.fm/#/lets_split/rev2/LAYOUT_ortho_4x12 and turn this into a keymap.c, all we have to do
is `cd ../qmk_firmware`, and then `./bin/qmk json2c foo.json`. This will output a neat `keymap.c` which we can then import into the source.
