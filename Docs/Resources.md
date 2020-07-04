# Resources formats

## Sprite 
```json
{
  "spritesheet": "String", The path to the spritesheet
  "opacity": { 
    "hasOpacity": true,
    "color": {
      "r": 0,
      "v": 0,
      "b": 0,
      "a": 0 
    }
  },
  "frames": [
    {
      "rect": {
        "x": 0,
        "y": 0,
        "w": 0,
        "h": 0
      },
      "duration": 0.5,
      "center": {
        "x": 0,
        "y": 0
      },
      "flip": {
        "v": true,
        "h": true
      },
      "rotation": 90
    }
  ]

}
```