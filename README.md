![Logo](https://raw.githubusercontent.com/Hylley/ByteMaintainer/main/res/icon.ico)
# ByteMaintainer
I was having trouble learning Git, so instead of actually studying, I created my own version control system.

## Installation

If you expect me to teach you how to clone the repository using Git, you are completely wrong.

- First, **download** it as a zip file from the GitHub page.
- Extract the zip file to the desired location.
- Run `make` to compile the source code into an executable called `byter.exe`.
- Add the executable in Windows PATH variable to be able to run it anywhere.
- If your antivirus warns you that it is a virus, ignore it. Trust me please.

Alternatively, you can download the compiled binary from the release section.

⚠️ Only works on Windows!

## How to use

First, you need to initialize a repository in your folder:
```
byter init
```
After that, a folder called `.byter` will be created in the root folder of your project with the following structure:
```
.byter
├── versions			# All the "shots" will be stored here;
├── .config			# Internal configuration. Just ignore;
└── .lock			# Files matching one of the regex patterns written here will be ignored.
```
Once you have done that, you are ready to proceed. To store a version of your code, type:
````
byter shot [summary]
````
The `[summary]` part is required. Byter will throw an error if you don't provide one. All the summary text is stored in the respective version folder in a file called `summary.txt`.