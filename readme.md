<center>

# Red Text Editor

[![Forks](https://img.shields.io/github/forks/ElhoubeBrahim/red-text-editor)](https://github.com/ElhoubeBrahim/red-text-editor/network)
[![Stars](https://img.shields.io/github/stars/ElhoubeBrahim/red-text-editor)](https://github.com/ElhoubeBrahim/red-text-editor/stargazers)
[![Issues](https://img.shields.io/github/issues/ElhoubeBrahim/red-text-editor)](https://github.com/ElhoubeBrahim/red-text-editor/issues)
</center>

## About the project

Red Text is light weight text editor built with cpp. I have a lot of fun during the process of building, my goal was to boost my cpp and oop skills, another goal is to add a gui application to my portfolio as a software developer. Thank you for testing my app ^_^

### screenshots

![Screenshot](/assets/images/screenshot.png)

### Built with

- C++ language
- Sfml gui library
- Makefile

## How to use

Firstly, clone this repository using git :
```bash
git clone https://github.com/ElhoubeBrahim/red-text-editor.git
```
Next make sure that you have the gcc compiler and make installed. Then run the `make` command inside the project folder, this will compile the cpp code, link it with sfml and then launch the application.

Congrats the editor should appear now with a demo text file.

If you wanna change the target file, open the `makefile`, go to the line `6` and change the `DEMOFILE` constant with your file path :

```
DEMOFILE = path/to/your/file.txt
```

After that compile the source code by running the command `make` again.

## Classes

This is a simple explaination to have a general overview about my source code :

| Class          | Role    |
|:---------------|:--------|
| `Document`     | This is the backbone of this application, it acts like a glue for other editor components and settings, such as: fonts, lines, cursor, positions, view ... |
| `EditorLine`   | This class contains info about a single line in our document, like: content, number, drawings, position ... |
| `Cursor`       | This is the visual cursor, it holds its position and the blinking rectangle |
| `EditorView`   | This class is useful to handle scrolling and resizing events, in addition it has the sfml view object as the main camera |
| `Utils`        | This class is a collection of some useful methods |
| `Header`       | This class contains the header draw method and header buttons actions such as switch theme, open new file or save the existing one |
| `History`      | Here is all the states - mementos - of my document are stored, it helps to perform undo and redo operations  |
| `Memento`      | An instance of this class holds the state of the document at a given moment. The state is nothing but lines content and (row, col) cursor coords |
| `TextSelection`| This class is used to describe the user selected text using document coords and content. It provides helper methods to handle and manage the selected zone |

## Todo

This is my first gui application in cpp, so I am sure there is a lot of imporovements to do and bugs to fix. For this reason, I made this todo list to store the next steps :

- [x] Enable saving file
- [x] Add theme switcher (Dark, Light)
- [x] Highlight active lines
- [x] Undo and Redo actions - ctrl + z && ctrl + y
- [x] Allow text selection
- [x] Allow text copy/paste - ctrl + c && ctrl + x && ctrl + v
- [ ] Add settings page - to change fonts, sizes and colors
- [ ] Add arabic support
- [ ] Add a scroll bar
- [ ] Add words dictionary

## Contact me

- Brahim Elhoube - [@brahim_elhoube](https://twitter.com/brahim_elhoube) - brahim.elhoube@gmail.com

- Project Link: [https://github.com/ElhoubeBrahim/red-text-editor](https://github.com/ElhoubeBrahim/red-text-editor)