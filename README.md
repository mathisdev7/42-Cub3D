# 🎮 Cub3D

<div align="center">
  <img src="https://i1.wp.com/blogs.letemps.ch/yannick-rochat/wp-content/uploads/sites/46/2016/08/2743857-auteurs-4-romerocarmack93.jpg?resize=300%2C300&ssl=1" width="300">
  <img src="https://shared.fastly.steamstatic.com/store_item_assets/steam/apps/2270/header.jpg?t=1664378515" width="400">
</div>

## 📝 Description
Cub3D is a graphic design project that aims to create a 3D perspective in a maze using raycasting technology, similar to the famous Wolfenstein 3D game. This project is part of the 42 school curriculum.

## ✨ Features
- 🎯 Raycasting rendering engine
- 🏰 Textured walls
- 🎮 Smooth player movement
- 💥 Collision detection
- 🗺️ Dynamic map parsing

## 🛠️ Installation

```bash
# Clone the repository
git clone git@github.com:mathisdev7/42-Cub3D.git

# Go to project directory
cd 42-Cub3D

# Compile the project
make
```

## 🚀 Usage

```bash
./cub3D map.cub
```

## 🗺️ Map Format
The map must be provided as a `.cub` file with the following specifications:

| Character | Description |
|-----------|-------------|
| `1` | Wall |
| `0` | Empty space |
| `N` | Player start position (facing North) |
| `S` | Player start position (facing South) |
| `E` | Player start position (facing East) |
| `W` | Player start position (facing West) |

## 🎮 Controls

| Key | Action |
|-----|--------|
| `W` | Move forward |
| `S` | Move backward |
| `A` | Strafe left |
| `D` | Strafe right |
| `←` | Rotate camera left |
| `→` | Rotate camera right |
| `ESC` | Exit game |

## 🔧 Technical Requirements
- macOS or Linux
- MinilibX library
- C compiler (gcc/clang)

## 👥 Authors
- [mazeghou](https://github.com/mathisdev7) - *Developer*
- [nopareti](https://github.com/Noe-Prt) - *Developer*

## 📄 License
This project is part of 42 School curriculum. For more information about 42, visit [42.fr](https://42.fr).
