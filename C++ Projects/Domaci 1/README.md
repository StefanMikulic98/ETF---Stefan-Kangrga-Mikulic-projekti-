# Movie Subtitle Editor (C++)

A console-based subtitle editor for `.srt`-style movie subtitle files, built as a university assignment in C++.

## What it does

- Loads a subtitle file into memory and parses it into timestamped sections
- Supports rich text styling: bold, italic, underline, remove formatting
- Allows time-shifting subtitles forward or backward by a given offset
- Fixes timestamps that exceed film length (`fixLongTime`)
- Inserts new subtitle entries and deletes ranges of subtitles
- Merges two subtitle sections into one
- Wraps long subtitle lines to a configurable character limit (`fixLongLines`)
- Saves the modified subtitle file back to disk
- Provides multi-level undo functionality

## Key concepts demonstrated

| Concept | Implementation detail |
|---------|-----------------------|
| Doubly-linked list | `Section` nodes form a linked list; forward and backward traversal for undo and range operations |
| String manipulation | Parsing time codes (`HH:MM:SS,ms`), inserting HTML-like style tags |
| File I/O | Reading and writing subtitle files line by line |
| Undo mechanism | Previous state stored and restored via linked-list pointer management |
| OOP design | `SubtitleEditor`, `Section`, `Selection` classes with clear responsibilities |

## Building

```bash
g++ -std=c++14 -o subtitle_editor *.cpp
./subtitle_editor
```
