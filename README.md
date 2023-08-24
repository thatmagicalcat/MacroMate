# MacroMate
## Automate you keyboard and applications

<hr>

> ## How to create a macro script
1. `#` to start a commend, used as: `# This is a comment`
2. `@exec <args>` is used to execute a command using cmd
3. `@delay <time (in ms)>` pauses the execution of the script for the specified time
4. `!<text>` type the text, used as: `!hello world`
5. Rest is treated as keystrokes <br>
for example:
  `win`, `enter`, `control`, `escape` <br>

short-cut keys are supported:
```
win 'r
win shift 's
control escape
```
Remember to prefix character with a single quote `'`

*The list of supported keys are given in `keys.txt`* <br>

> ### Here's an example of a script that opens notepad, types and message and then closes notepad

```
# start notepad
@exec start notepad

# wait for notepad to open
@delay 1000

# Type a message
!The quick brown fox jumps over the lazy dog.

# wait 5 seconds
@delay 5000

# close notepad
@exec taskkill /f /im notepad.exe
```
