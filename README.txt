This is a scriptfilterer for Xenosaga 1&2 DS
1. Program will attempt to find XXX_XXX.evc format files in "script" folder that is placed in the same folder as the executable
2. Output will be in "script/out" in .txt format but otherwise same filename.

Program follows following logic:
1. Create 6 digit number in rage of 000000 and 999999 and form a filename based on it.
2. Try to open file with that name, if it doesn't exist move to next one.
3. Read the file into buffer and send send the buffer to scanner.
4. If the current character is printable ascii character put it to buffer2.
5. If the current character is hex 80 or bigger, it'll likely be Shift-JIS character. For now the relation between first and second character don't matter.
6. If the current character is a non-printable ascii character, do nothing. 
7. If there has been >= 1 printable characters since last NPC, print newline.
8. Print the resulting string to target file and attempt to open next one.
