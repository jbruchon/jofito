Introduction
-------------------------------------------------------------------------------
Jody Bruchon's File Tool: a script engine for building advanced, high-
performance file and disk management tools.

This project is pre-alpha and not usable yet. If you want to be notified of
releases, go to https://github.com/jbruchon/jofito and "watch" the repository's
releases (Watch - Custom - Releases).

The goal of this project is to provide a better solution to file management
tasks where a user would normally either write a shell script or spend a lot of
time on a throw-away lengthy one-line "script" to accomplish a goal. In many
cases a custom C program would greatly outperform a shell script but the time
cost of writing a C program is prohibitive; likewise, a custom Python script
could possibly fill in the gap, but Python is an order of magnitude slower than
C and writing tools in Python still requires a decent amount of time.

Instead of using slow and often messy shell scripts or undertaking writing new
tools in general-purpose programming language, jofito aims to offer a domain-
specific scripting language that requires less effort than shell scripts while
offering advanced features like automatic parallelization of operations and
disk "thrashing" mitigation.

The following is a "wish list" of things I've either done with shell scripts
already or functionality that would be nice to have.


Wish list
-------------------------------------------------------------------------------
This list references a tool I wrote called zeromerge which can be found at
https://github.com/jbruchon/zeromerge

- `find -type d -exec rmdir -p '{}' +`
- `find -type f -size 0 -delete`
- Find files with the same size (and maybe same basename) and zeromerge them
- Refresh directories in alphabetical order (possibly with recursion)
- Be able to dedupe, merge, etc. over a network, with offline hash DB, etc.
- Break hard links into separate files
- Zeromerge left/right/separate with/without file length/data difference check
- Partial duplicate "matching" with zeromerge for matches
- Trim excess allocations like XFS preallocations
- Recursively collect file statistics and sort the output
- Merge directories (copy recurseively, skipping or overwriting existing files)
- If a subdirectory contains ONE file, move file to its parent & delete subdir
- Read the list of files in various archive file formats (zip, 7z, tar, etc.)
- Files with same name but different extensions: delete largest file(s)


Contact information
-------------------------------------------------------------------------------
To post bug reports/feature requests: https://github.com/jbruchon/jofito/issues
For all other jofito inquiries, contact Jody Bruchon <jody@jodybruchon.com>


Legal information and software license
-------------------------------------------------------------------------------
jofito is Copyright (C) 2023 by Jody Bruchon <jody@jodybruchon.com>

The MIT License

Permission is hereby granted, free of charge, to any person obtaining a copy of
this software and associated documentation files (the "Software"), to deal in
the Software without restriction, including without limitation the rights to
use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies
of the Software, and to permit persons to whom the Software is furnished to do
so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
Includes other code libraries which are (C) 2015-2023 by Jody Bruchon
