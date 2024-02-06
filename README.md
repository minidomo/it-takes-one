# It Takes One

A single player third-person puzzle solving game inspired from [It Takes Two](https://en.wikipedia.org/wiki/It_Takes_Two_(video_game)) and made with [Unreal Engine 5.2.1](https://www.unrealengine.com/en-US/unreal-engine-5).

This game was made as a final project by a team of four, including myself, for the course, [CS354P - Game Programming Paradigms](https://www.cs.utexas.edu/users/theshark/courses/cs354p/), at UT Austin. This repository is a slightly modified version of the original private repository on GitLab, so some files may not be included due to GitHub repository size limits. 

View the trailer [here](https://www.youtube.com/watch?v=35o-ncmbmiU). To learn how to play, view the [player guide](#player-guide).

## Releases

| [Windows (x64)](https://github.com/minidomo/it-takes-one/releases/download/2023.1210.0/ItTakesOne-win-x64-2023.1210.0.zip) |
| -------------------------------------------------------------------------------------------------------------------------- |

## Player guide

Refer to [PLAYER_GUIDE.md](./PLAYER_GUIDE.md).

## Developing

Built on Unreal Engine 5.2.1. A [final report](./Documents/cs354p-final-report.pdf) has been written that describes current functionality and controls of the game.

### Downloading the source code

Clone the repository:

```shell
git clone https://github.com/minidomo/it-takes-one.git
cd it-takes-one
```

### Files to manually add

#### Plugins

Our game utilizes additional graphics features such as ray tracing, DLSS, and FSR. Download our compiled [plugins](https://github.com/minidomo/it-takes-one/releases/download/2023.1210.0/ItTakesOne-plugins-2023.1210.0.zip), and extract the contents to the `Plugins` directory.

The `Plugins` directory should look like the following:

```
Plugins
|- amd/
|- nvidia/
|- .gitkeep
```

#### Assets

Some assets were used and could not be included in this repository due to GitHub repository constraints.

Add the following assets to the project:

- [Landscape Pro 2.0 Auto-Generated Material](https://www.unrealengine.com/marketplace/en-US/product/landscape-pro-auto-generated-material)
- [Grocery store props collection](https://www.unrealengine.com/marketplace/en-US/product/grocery-store-props-collection)
