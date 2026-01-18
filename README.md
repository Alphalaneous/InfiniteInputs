# Infinite Inputs

Tired of being limited to just 6 input triggers in your Geometry Dash levels? This mod unlocks full keyboard and mouse support!

## Features

- **Complete Keyboard Support**: Letters, numbers, function keys, modifiers, and more
- **Full Mouse Support**: All mouse buttons including side buttons
- **Mouse Wheel**: Scroll up/down actions
- **Cursor Tracking**: Make objects follow your mouse cursor

## Usage

This mod works by adding a new **Input Trigger** that can be found in the triggers tab, next to the touch trigger. Internally this is a text object and will show as one for those without the mod. 

Within the trigger, you can choose different inputs to listen to, such as keyboard and mouse key presses and releases. 

## Special Keys

There are special keys that do not have a release event:

- Mouse Wheel Up
- Mouse Wheel D0wn
- Lock to Cursor
- On Mod Loaded

## Key Reference

### Function Keys
`f1, f2, f3, f4, f5, f6, f7, f8, f9, f10, f11, f12`

### Number Row
`1, 2, 3, 4, 5, 6, 7, 8, 9, 0`

### Letters (QWERTY Layout)

q, w, e, r, t, y, u, i, o, p
a, s, d, f, g, h, j, k, l
z, x, c, v, b, n, m

### Special Keys
`enter, space, escape, backspace`

### Modifiers
`leftCtrl, leftShift, leftAlt, rightCtrl, rightShift, rightAlt`

### Mouse Buttons
`leftMouse, rightMouse, middleMouse, mouse3, mouse4`

### Mouse Wheel
`wheelUp, wheelDown`

### Cursor
`cursor`

### Mod Loaded
`modLoaded`

## Notes

- These triggers work similarly to the UI trigger, and are all processed when the level is loaded. These cannot be spawned or toggled.
- Geometry Dash defaults to QWERTY, regardless of operating system settings and there is no way to work around that at the moment 

# Troubleshooting

Enable console in the geode console, as there are quite many logs to help pinpoint issues.

# Bug Reports / Feature Request

File them on [Github Issues](https://github.com/iAndyHD3/InfiniteInputs/issues/new)
Or join the [Discord Server](discord.gg/7kyvwJVcqJ)

# Special Thanks / Credits

- [TheMilkCat](user:7060183) - For commissioning the mod!
- Alphalaneous - For the amazing UI API, which this mod uses, as well as the Custom Trigger UI.