# Python bindings for slop

Just a quick python extension for region selecting. Read https://github.com/naelstrof/slop for info on what kind of region selecting.

## Usage

```python
import slop
rect = slop.select(border=30,r=1,g=0,b=0,a=0.5)
print(rect)
```
returns
```python
{'x': 308, 'y': 179, 'w': 654, 'h': 447, 'id': 4199883, 'cancelled': 0}
```

Available arguments:

| Argument      | Type     | Description                                                                                     |
|---------------|----------|-------------------------------------------------------------------------------------------------|
| border        | Float    | The border width in pixels.                                                                     |
| padding       | Float    | Space between the actual selection and the returned pixels, this is visible during selection.   |
| tolerance     | Float    | The distance the mouse has to move in pixels before detecting a drag selection.                 |
| highlight     | Bool     | Draws an overlay over the selection with the given color. Only useful with alpha.               |
| noopengl      | Bool     | Disables OpenGL accelleration, as well as shaders.                                              |
| nokeyboard    | Bool     | Disables being able to cancel a selection with the keyboard.                                    |
| nodecorations | Bool     | Set to 0, 1 or 2. Enables different methods for removing window frame decorations.              |
| shaders       | List     | A list of shader names. Example ["wiggle", "blur1", "blur2"]. Requires files, see slop website. |
| r             | Float    | The red component of the rectangle color.                                                       |
| g             | Float    | The green component of the rectangle color.                                                     |
| b             | Float    | The blue component of the rectangle color.                                                      |
| a             | Float    | The alpha component of the rectangle color.                                                     |
| xdisplay      | String   | The desired X display string.                                                                   |
| quiet         | Bool     | If set to true, keeps slop from printing info to std::cout.                                     |

## Installation

Windows: `python setup.py install`
Linux: `sudo python setup.py install`
